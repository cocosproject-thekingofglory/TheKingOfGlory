<<<<<<< HEAD
#include"PlayerManager.h"
#include "Model/GameMap.h"

USING_NS_CC;



bool PlayerManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addCustomEvent();


	scheduleOnce(schedule_selector(PlayerManager::initPlayer),0.1f);

	return true;
}

Player* PlayerManager::createPlayer(const std::string& id, int role,int color)
{
	auto player = Player::createPlayer(id, role,color);
	if (player)
	{
		player->isLocal(false);
		this->_playerList.insert(id, player);
		return player;
	}

	CC_SAFE_DELETE(player);
	return nullptr;
}

Player* PlayerManager::createLocalPlayer(const std::string& id, int role,int color)
{

	auto localPlayer = Player::createPlayer(id, role,color);
	if (localPlayer)
	{
		_localPlayer = localPlayer;
		localPlayer->isLocal(true);
		this->_playerList.insert(id, localPlayer);
	}
	return localPlayer;
}

void PlayerManager::setStatus(const std::string& id, Player::Status status)
{
	auto player = this->getPlayer(id);
	if (player)
	{
		player->setStatus(status);
	}
}

Player * PlayerManager::getPlayer(const std::string& id)
{
	return _playerList.at(id);
}


Map<std::string, Player*>& PlayerManager::getPlayerList()
{
	return _playerList;
}

Player * PlayerManager::getLocalPlayer()
{
	if (!_localPlayer)
	{
		auto delay = DelayTime::create(5.0);
		this->runAction(delay);
	}
	return _localPlayer;
}

void PlayerManager::addCustomEvent()
{
}

void PlayerManager::initPlayer(float delta)
{

	auto player = this->createPlayer("Haha", 0, BLUE);
	GameMap::getCurrentMap()->addSprite(player, GameMap::Type::Player_Blue);

	this->createLocalPlayer(UserDefault::getInstance()->getStringForKey("username"), 0,RED);
	GameMap::getCurrentMap()->addSprite(this->getLocalPlayer(), GameMap::Type::Player_Red);
	GameMap::getCurrentMap()->addCenterSprite(this->getLocalPlayer());

}

=======
#include"PlayerManager.h"
#include "Model/GameMap.h"
#include "Model/Hero.h"

USING_NS_CC;



bool PlayerManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addCustomEvent();


	scheduleOnce(schedule_selector(PlayerManager::initPlayer),0.1f);

	return true;
}

Player* PlayerManager::createPlayer(const std::string& id, int role,int color)
{
	Player *player;
	switch (role)
	{
	case 0: {player = Warrior::create(id, color);	break; }
	case 1: {player = Aviator::create(id, color);	break; }
	}
	if (player)
	{
		player->isLocal(false);
		this->_playerList.insert(id, player);
		return player;
	}

	CC_SAFE_DELETE(player);
	return nullptr;
}

Player* PlayerManager::createLocalPlayer(const std::string& id, int role,int color)
{
	Player *localPlayer;
	switch (role)
	{
	case 0: {localPlayer = Warrior::create(id, color);	break; }
	case 1: {localPlayer = Aviator::create(id, color);	break; }
	}
	if (localPlayer)
	{
		_localPlayer = localPlayer;
		localPlayer->isLocal(true);
		this->_playerList.insert(id, localPlayer);
	}
	return localPlayer;
}

void PlayerManager::setStatus(const std::string& id, Player::Status status)
{
	auto player = this->getPlayer(id);
	if (player)
	{
		player->setStatus(status);
	}
}

Player * PlayerManager::getPlayer(const std::string& id)
{
	return _playerList.at(id);
}


Map<std::string, Player*>& PlayerManager::getPlayerList()
{
	return _playerList;
}

Player * PlayerManager::getLocalPlayer()
{
	return _localPlayer;
}

void PlayerManager::addCustomEvent()
{
}

void PlayerManager::initPlayer(float delta)
{

	auto player = this->createPlayer("Haha", 0, BLUE);
	GameMap::getCurrentMap()->addSprite(player, GameMap::Type::Player_Blue);

	this->createLocalPlayer(UserDefault::getInstance()->getStringForKey("username"), 1,RED);
	GameMap::getCurrentMap()->addSprite(this->getLocalPlayer(), GameMap::Type::Player_Red);
	GameMap::getCurrentMap()->addCenterSprite(this->getLocalPlayer());

}
>>>>>>> 5b3eddb339298e6c578e13d983c5f029cd75fdb0
