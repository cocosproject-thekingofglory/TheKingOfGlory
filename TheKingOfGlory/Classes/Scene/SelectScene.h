#pragma once
#include "cocos2d.h"
#include "UI/CocosGUI.h"
#include "Network/Server.h"
#include "Network/Client.h"

class SelectScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectScene);

private:
	void createBackground();
	void createButton();

};
class SelectModeScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectModeScene);

private:
	void createBackground();
	void createButton();

};

class OnlineScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OnlineScene);
private:
	void createBackground();
	void createButton();
};

class ServerScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ServerScene);
private:
	cocos2d::ui::TextField* portInput;
	cocos2d::Label* connectionMsg;
	Server* gameServer{ nullptr };
	Client* gameClient{ nullptr };

	void createBackground();
	void createButton();
	void createInput();
	void connectionSchedule();
};

class ClientScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ClientScene);
private:
	cocos2d::ui::TextField* ipInput;
	cocos2d::ui::TextField* portInput;
	Client* gameClient{ nullptr };
	cocos2d::Label* connectionMsg;
	int timer_ = 0;


	void createBackground();
	void createButton();
	void createInput();
	void waitStart();
	void startSchedule();
};