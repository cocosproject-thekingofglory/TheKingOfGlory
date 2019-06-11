#pragma once
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "socket_message.h"
#include "GameMsg_generated.h"

using boost::asio::ip::tcp;


class Server;
class TcpConnection
	: public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::shared_ptr<TcpConnection> pointer;
	//	~TcpConnection();
	static pointer create(boost::asio::io_service& io_service, Server* parent);
	tcp::socket& socket();

	void start();

	void write_data(std::string s);
	void write_data(socket_message& msg);

	std::string read_data();
	bool error()const { return error_flag_; }


	void do_close();
private:

	void handle_read_header(const boost::system::error_code& error);

	void handle_read_body(const boost::system::error_code& error);


	TcpConnection(boost::asio::io_service& io_service,Server* parent);;

	//void check_timer();
	void delete_from_parent();

	tcp::socket socket_;
	Server* parent;
	bool error_flag_{ false };

	socket_message read_msg_;
	std::deque<socket_message> read_msg_deque_;
	boost::condition_variable data_cond_;
	boost::mutex mut_;
	//	asio::steady_timer steady_timer_;

};


class Server
{
public:
	boost::thread  *thread_;
	boost::asio::io_service io_service_;
	static Server* create(int port);
	Server(int port);
	void start_accept();
	void close();
	void button_start();
	bool error() const;
	int connection_num() const;
	std::vector<TcpConnection::pointer> get_connection() const;
	void remove_connection(TcpConnection::pointer p);

	void loop_process();

private:

	void handle_accept(TcpConnection::pointer new_connection,const boost::system::error_code& error);



	tcp::acceptor acceptor_;

	std::vector<TcpConnection::pointer> connections_;
	int connection_num_;


	boost::thread  *button_thread_{ nullptr };
	boost::mutex delete_mutex_;
	bool error_flag_{ false };
	boost::condition_variable data_cond_;
};

