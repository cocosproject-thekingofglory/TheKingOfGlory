#include "Server.h"
using namespace boost::asio;
using boost::system::error_code;


TcpConnection::pointer TcpConnection::create(io_service& io_service, Server* parent)
{
	return pointer(new TcpConnection(io_service, parent));
}

tcp::socket& TcpConnection::socket()
{
	return socket_;
}

void TcpConnection::start()
{
	//	
	//	_timer_.async_wait(std::bind(&TcpConnection::check_timer, this));
	//	steady_timer_.expires_from_now(std::chrono::seconds(60));
	async_read(socket_,
		buffer(read_msg_.data(), socket_message::header_length),
		boost::bind(&TcpConnection::handle_read_header, this, _1));
}

void TcpConnection::write_data(std::string s)
{
	if (error_flag_) return;
	socket_message msg;
	if (s.size() == 0)
	{
		s = std::string("\0");
		msg.body_length(1);
	}
	else
		msg.body_length(s.size());
	memcpy(msg.body(), &s[0u], msg.body_length());
	msg.encode_header();
	write(socket_, buffer(msg.data(), msg.length()));
}

void TcpConnection::write_data(socket_message & msg)
{
	if (error_flag_) return;
	write(socket_, buffer(msg.data(), msg.length()));
}

std::string TcpConnection::read_data()
{
	if (error_flag_)
		return "";
	boost::unique_lock<boost::mutex> lk{ mut_ };
	while (read_msg_deque_.empty())
		data_cond_.wait(lk);
	auto read_msg = read_msg_deque_.front();
	read_msg_deque_.pop_front();
	lk.unlock();
	auto ret = std::string(read_msg.body(), read_msg.body_length());
	return ret;
}

void TcpConnection::do_close()
{
	try {
		//		steady_timer_.cancel();
		error_flag_ = true;
		socket_message empty_msg;
		memcpy(empty_msg.data(), "0001\0", 5);
		read_msg_deque_.push_back(empty_msg);
		read_msg_deque_.push_back(empty_msg);
		data_cond_.notify_one();
		error_code ec;
		socket_.shutdown(ip::tcp::socket::shutdown_both, ec);
		if (!ec)
			throw boost::system::system_error(ec);
		socket_.close();


	}
	catch (std::exception&e)
	{
		e.what();
	}
	delete_from_parent();
}

void TcpConnection::handle_read_header(const error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		async_read(socket_,
			buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&TcpConnection::handle_read_body, this, _1));
	}
	else
	{
		do_close();
	}
}

void TcpConnection::handle_read_body(const error_code& error)
{
	if (!error)
	{
		//		steady_timer_.expires_from_now(std::chrono::seconds(10));
		boost::lock_guard<boost::mutex> lk{ mut_ };
		read_msg_deque_.push_back(read_msg_);
		data_cond_.notify_one();
		async_read(socket_, buffer(read_msg_.data(), socket_message::header_length),
			boost::bind(&TcpConnection::handle_read_header, this, _1));
	}
	else
	{
		do_close();
	}
}

TcpConnection::TcpConnection(io_service& io_service, Server* parent) :
	socket_(io_service), parent(parent)
	//,steady_timer_(io_service)
{
}

//void TcpConnection::check_timer()
//{
//	if (steady_timer_.expires_at() <= std::chrono::steady_clock::now())
//	{
//		// The deadline has passed. The socket is closed so that any outstanding
//		// asynchronous operations are cancelled.
//		do_close();
//		steady_timer_.expires_at(std::chrono::steady_clock::time_point::max());
//		return;
//	}
//
//	// Put the actor back to sleep.
//	steady_timer_.async_wait(std::bind(&TcpConnection::check_timer, this));
//}


void TcpConnection::delete_from_parent()
{
	//if (parent)
		//shared_from_this()->parent->remove_connection(shared_from_this());
	parent = nullptr;
}

Server * Server::create(int port)
{
	auto s = new Server(port);
	s->thread_ = new boost::thread(boost::bind(&io_service::run, &s->io_service_));
	//s->thread_->detach();
	return s;
}

Server::Server(int port) : acceptor_(io_service_, tcp::endpoint(tcp::v4(), port))
{
	start_accept();
}

void Server::start_accept()
{
	TcpConnection::pointer new_connection =
		TcpConnection::create(acceptor_.get_io_service(), this);

	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&Server::handle_accept, this, new_connection, _1));
}
void Server::close()
{
	try {
		connections_.clear();
		io_service_.stop();
		acceptor_.close();
		//		thread_ = nullptr;
		thread_->join();
	}
	catch (std::exception&e)
	{
		std::cerr << e.what() << std::endl;
	}
}
void Server::button_start()
{
	acceptor_.close();
	using namespace std; // For sprintf and memcpy.
	char total[4 + 1] = "";
	sprintf_s(total, "%4d", static_cast<int>(connections_.size()));

	for (auto i = 0; i < connections_.size(); i++)
		connections_[i]->write_data("SelectHero");
	connection_num_ = connections_.size();
	this->button_thread_ = new boost::thread(std::bind(&Server::loop_process, this));
	button_thread_->detach();
}
bool Server::error() const
{
	return error_flag_;
}
int Server::connection_num() const
{
	return connections_.size();
}
std::vector<TcpConnection::pointer> Server::get_connection() const
{
	return std::vector<TcpConnection::pointer>();
}
void Server::remove_connection(TcpConnection::pointer p)
{
	boost::unique_lock<boost::mutex> lock(delete_mutex_);
	auto position = std::find(connections_.begin(), connections_.end(), p);
	if (position == connections_.end())
		std::cout << "delete not succ\n";
	else
		connections_.erase(position);
	std::cout << "delete succ\n";
}

void Server::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code & error)
{
	if (!error)
	{
		connections_.push_back(new_connection);
		std::cout << new_connection->socket().remote_endpoint().address()
			<< ":" << new_connection->socket().remote_endpoint().port() << std::endl;
		new_connection->start();
	}
	start_accept();
}

void Server::loop_process()
{
	while (true)
	{
		if (connections_.size() != connection_num_)
		{
			error_flag_ = true;
			break;
		}
		boost::unique_lock<boost::mutex> lock(delete_mutex_);
		std::vector<std::string> ret;
		for (auto r : connections_)
		{
			if (r->error())
				error_flag_ |= r->error();
			ret.push_back(r->read_data());
		}
		if (ret.front() == "SelectOK")
		{
			for (auto r : connections_)
				r->write_data("StartGame");
			ret.clear();
		}
		else if (ret.front().substr(0, 4) == "Init")
		{
			std::vector<std::pair<std::string,int>> players;
			for (auto s : ret)
			{
				auto flit = s.substr(5).find(' ');
				std::string name = s.substr(5,flit);
				int role = std::stoi(s.substr(flit+5 + 1));
				players.push_back(std::pair<std::string, int>(name, role));
			}
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			std::vector<flatbuffers::Offset<Player>> Players;
			for (int i = 0; i < players.size(); ++i)
			{
				auto name = builder.CreateString(players.at(i).first);
				auto color = Color(i % 2);
				auto role = RoleType(players.at(i).second);
				Players.push_back(CreatePlayer(builder, name, color, role));
			}
			auto gameInit = CreateGameInit(builder, time(NULL), builder.CreateVector(Players));
			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_GameInit, Date::Date_gameInit, gameInit.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			for (auto r : connections_)
				r->write_data(message);

			ret.clear();


		}
		else
		{
			using namespace::GameMsg;
			for (auto s : ret)
			{
				if(GetMsg(s.c_str())->msg()!=MsgType::MsgType_MsgType_None)
					for (auto r : connections_)
						r->write_data(s);
			}
			ret.clear();
		}



	}
}