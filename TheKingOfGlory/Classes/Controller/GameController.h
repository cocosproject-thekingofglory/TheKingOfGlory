#pragma once
#include "cocos2d.h"
#include "../Model/GameMap.h"
#include "Manager/Manager.h"
#include "UI/Skill.h"
#include "Network/Server.h"
#include "Network/Client.h"
#include "Network/ChatBox.h"

class GameController:public cocos2d::Layer
{
public:
	bool isOnline;
	bool hasSend;
	Server* gameServer;
	Client* gameClient;
	Manager* manager = Manager::getInstance();
	static GameController* create(Client* client, Server*server );
	virtual bool init(Client* client, Server*server);

	void setMap(GameMap* map);
	void initGame(float delta);
	cocos2d::Vector<Skill*>& getSkillList() { return _skillList; }

private:
	GameMap* map;
	cocos2d::Vector<Skill*> _skillList;
	cocos2d::EventListenerTouchOneByOne* touchListener;
	cocos2d::EventListenerKeyboard* keyListener;
	ChatBox* chatBox;

	void createTouchListener();
	void createKeyListener();
	void addSkill();
	void addChatBox();
	void onEnter();
	void toOver(cocos2d::EventCustom* event);

	void sendEmptyMsg();
	void processMsg();
	void onGameInit(const void * msg);
	void onPlayerMove(const void *msg);
	void onPlayerAttack(const void* msg);
	void onPlayerSkill(const void* msg);
	void onChatMsg(const void* msg);

};
