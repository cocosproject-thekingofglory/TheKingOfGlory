#include "Client.h"
#include "Controller/GameController.h"
using namespace boost::asio;
using boost::system::error_code;

Client* Client::create(std::string ip, int port)
{
	auto s = new Client(ip, port);
	s->thread_ = new boost::thread(boost::bind(&io_service::run, &s->io_service_));
	//	s->thread_->detach();
	return s;
}

Client * Client::getInstance()
{
	auto client = dynamic_cast<GameController*>(cocos2d::Director::getInstance()->getRunningScene()->
		getChildByName("GameScene")->getChildByName("GameController"))->gameClient;
	return client;
}

Client::Client(std::string ip, int port) : socket_(io_service_),
endpoint_(ip::address_v4::from_string(ip), port)
{
	socket_.async_connect(endpoint_, boost::bind(&Client::handle_connect, this, _1));
}

/*
void Client::write(const socket_message & msg)
{
	io_service_.post(boost::bind(&Client::do_write, this, msg));
}*/

void Client::close()
{
	io_service_.post(boost::bind(&Client::do_close, this)); 
}

int Client::camp() const
{
	while (!start_flag_);
	return camp_;
}

int Client::total() const
{
	while (!start_flag_);
	return total_;
}

void Client::onMessage(int code, const void * msg)
{
	auto func = getFunc(code);
	if (func) func(msg);
}

void Client::sendMessage(std::string s)
{
	if (error_flag_)
		return;
	//io_service_.post(boost::bind(&Client::write_data, this, s));
	write_data(s);
}

void Client::sendMessage(socket_message& msg)
{
	if (error_flag_)
		return;
	write(socket_, buffer(msg.data(), msg.length()));
}

std::string Client::getMessage()
{
	return read_data();
}

void Client::bind(int code, _Callback func)
{
	funcList[code] = func;
}

void Client::clear()
{
	funcList.clear();
}

void Client::handle_connect(const boost::system::error_code & error)
{
	try
	{
		if (!error)
		{

			std::cout << "connected\n";
			/*char data[30] = { 0 };
			error_code error;
			size_t length = socket_.read_some(buffer(data, 30), error);
			if (error || length < 10)
				throw boost::system::system_error(error);
			char header[4 + 1] = "";
			strncat_s(header, data + 10, 4);
			total_ = atoi(header);
			camp_ = atoi(data + 14);*/
			start_flag_ = true;
			async_read(socket_, buffer(read_msg_.data(), socket_message::header_length),
				boost::bind(&Client::handle_read_header, this, _1));

		}
		else
		{
			std::cerr << "failed to connect" << std::endl;
			throw boost::system::system_error(error);
			error_flag_ = true;

		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in connection: " << e.what() << "\n";
	}
}

void Client::handle_read_header(const boost::system::error_code & error)
{
	if (!error && read_msg_.decode_header()) //分别处理数据报头和数据部分
	{
		async_read(socket_,buffer(read_msg_.body(), read_msg_.body_length()),//读取数据包数据部分
			boost::bind(&Client::handle_read_body, this,_1));
	}
	else
	{
		do_close();
	}
}

void Client::handle_read_body(const boost::system::error_code & error)
{
	if (!error)
	{

		//std::cout.write(read_msg_.body(), read_msg_.body_length()); //输出消息
		//std::cout << "\n";
		boost::lock_guard<boost::mutex> lk{ mut };
		read_msg_deque_.push_back(read_msg_);
		data_cond_.notify_one();
		async_read(socket_,buffer(read_msg_.data(), socket_message::header_length),
			boost::bind(&Client::handle_read_header, this,_1));
	}
	else
	{
		do_close();
	}
}
/*
void Client::do_write(socket_message msg)
{
	bool write_in_progress = !write_msgs_.empty(); //空的话变量为false
	write_msgs_.push_back(msg); //把要写的数据push至写队列
	if (!write_in_progress)//队列初始为空 push一个msg后就有一个元素了
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			boost::bind(&Client::handle_write, this,
				boost::asio::placeholders::error));
	}
}
*/
/*
void Client::handle_write(const boost::system::error_code & error)
{
	if (!error)
	{
		write_msgs_.pop_front();//刚才处理完一个数据 所以要pop一个
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&Client::handle_write, this,
					boost::asio::placeholders::error)); //循环处理剩余的消息
		}
	}
	else
	{
		do_close();
	}
}
*/
void Client::do_close()
{

	try {
		boost::lock_guard<boost::mutex> lk{ mut };
		error_flag_ = true;
		socket_message empty_msg;
		memcpy(empty_msg.data(), "0001\0", 5);
		read_msg_deque_.push_back(empty_msg);
		data_cond_.notify_one();
		io_service_.stop();
		error_code ec;
		socket_.shutdown(ip::tcp::socket::shutdown_both, ec);
		if (!ec)
			throw boost::system::system_error(ec);
		socket_.close();
		thread_->join();

	}
	catch (std::exception&e)
	{

		e.what();
	}
}

void Client::write_data(std::string s)
{
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

std::string Client::read_data()
{
	if (error_flag_)
		return "";
	boost::unique_lock<boost::mutex> lk{ mut };
	while (read_msg_deque_.empty())
		data_cond_.wait(lk);
	auto read_msg = read_msg_deque_.front();
	read_msg_deque_.pop_front();
	lk.unlock();
	auto ret = std::string(read_msg.body(), read_msg.body_length());
	return ret;
}


