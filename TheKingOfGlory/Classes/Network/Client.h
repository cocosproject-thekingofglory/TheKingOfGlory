#pragma once
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <unordered_map>
#include "socket_message.h"
#include "GameMsg_generated.h"
#define CLIENT_ON(__code__, __func__,_client_) _client_->bind(__code__, CC_CALLBACK_1(__func__, this));

using boost::asio::ip::tcp;

typedef std::deque<socket_message> message_queue;

class GameController;
class Client
{

public:
	using _Callback = std::function<void(const void*)>;

	static Client* create(std::string ip, int port);
	static Client* getInstance();
	Client(std::string ip, int port);
	//void write(const socket_message& msg);
	void close();
	bool started() const { return start_flag_; }
	bool error()const { return error_flag_; }
	int camp() const;
	int total() const;
	void onMessage(int code,const void * msg);
	void sendMessage(std::string s);
	void sendMessage(socket_message& msg);
	std::string getMessage();
	bool remainMessage() { return !read_msg_deque_.empty(); }

	// bind callback function
	void bind(int code, _Callback func);
	// remove all callback function
	void clear();

private:

	void handle_connect(const boost::system::error_code& error);
	void handle_read_header(const boost::system::error_code& error);
	void handle_read_body(const boost::system::error_code& error);
	//void do_write(socket_message msg);
	//void handle_write(const boost::system::error_code& error);
	void do_close();
	void write_data(std::string s);
	std::string read_data();

	_Callback Client::getFunc(int code)
	{
		auto func = funcList.find(code);
		return func == funcList.cend() ? nullptr : func->second;
	}

private:

	boost::asio::io_service io_service_;
	tcp::socket socket_;
	tcp::endpoint endpoint_;
	socket_message read_msg_;
	message_queue read_msg_deque_;

	bool start_flag_{ false }, error_flag_{ false };

	boost::thread *thread_;
	int camp_, total_;

	boost::condition_variable data_cond_;
	boost::mutex mut;

	std::unordered_map<int, _Callback> funcList;

};

