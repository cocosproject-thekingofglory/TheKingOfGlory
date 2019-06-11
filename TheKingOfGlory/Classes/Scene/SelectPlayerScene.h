#pragma once
#include"cocos2d.h"
#include "Network/Client.h"
#include "Network/Server.h"



class SelectPlayerScene :public cocos2d::Layer
{
private:
	bool isOnline;
	Client * _client;
	Server * _server;
	cocos2d::Label* connectionMsg;
	int timer_=0;
public:
	static cocos2d::Scene* createScene(Client* client, Server*server = nullptr);
	static SelectPlayerScene* create(Client * client, Server * server);

	virtual bool init(Client* client, Server* server);

	void startSchedule();

};