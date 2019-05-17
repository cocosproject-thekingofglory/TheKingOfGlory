#pragma once

#include"cocos2d.h"
#include"Model/Player.h"
#include "Model/GameMap.h"

USING_NS_CC;



class PlayerManager :public cocos2d::Layer
{
public:
	virtual bool init();


	//role 定义为英雄的顺序
	Player* createPlayer(const std::string& id, int role);
	Player* createLocalPlayer(const std::string& id, int role);

	void setStatus(const std::string& id, Player::Status status);
	Player* getPlayer(const std::string& id);
	Player* getLocalPlayer();

	Map<std::string, Player*> getPlayerList();


	CREATE_FUNC(PlayerManager);

private:
	cocos2d::Map<std::string, Player*> _playerList;

	Player* _localPlayer;
	
	void addCustomEvent();
	void initPlayer(float delta);
};

