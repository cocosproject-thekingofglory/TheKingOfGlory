#ifndef __MANAGER_PLAYER_H__
#define __MANAGER_PLAYER_H__

#include"cocos2d.h"
#include"Player.h"

USING_NS_CC;
using namespace std;

class PlayerManager :public cocos2d::Layer
{
public:
	virtual bool init();

	Player* createPlayer(const std::string& id, int role);
	Player* createLocalPlayer(const std::string& id, int role);

	void setStatus(const std::string& id, Player::Status status);
	Player* getPlayer(const std::string& id);
	Player* getLocalPlayer();
	Map<std::string, Player*> getPlayerList();

	CREATE_FUNC(PlayerManager);

private:
	cocos2d::Map<std::string, Player*> _playerList;
	Player* localPlayer = nullptr;
	
	void addCustomEvent();
};
#endif