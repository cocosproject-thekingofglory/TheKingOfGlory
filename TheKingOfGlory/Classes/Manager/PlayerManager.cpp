#include"PlayerManager.h"
#include<ctime>

USING_NS_CC;

bool PlayerManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addCustomEvent();

	scheduleUpdate();

	return true;
}

Player* PlayerManager::createPlayer(const std::string& id, int role)
{
	auto player = Player::createPlayer(id, role);
	if (player)
	{
		player->isLocal(false);
		this->_playerList.insert(id, player);
		return player;
	}
	return nullptr;
}

Player* PlayerManager::createLocalPlayer(const std::string& id, int role)
{
	localPlayer = createPlayer(id, role);
	if (localPlayer)
	{
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

Player * PlayerManager::getLocalPlayer()
{
	return localPlayer;
}

void PlayerManager::localPlayerMove()
{
	if (localPlayer->getStatus() != Player::Status::STANDING) return;

	auto map = GameMap::getCurrentMap();
	if (map == nullptr) return;
	//´ý²¹³ä£º

}

void PlayerManager::update(float dt)
{
	if (localPlayer) {
		localPlayerMove();
	}
}

std::pair<cocos2d::Vec2, std::pair<cocos2d::Vec2, cocos2d::Vec2>> PlayerManager::getNextPos(const cocos2d::Vec2& pos, Player::Direction direction, float step)
{
	Vec2 nextPos(pos), logicPos1(pos), logicPos2(pos);
	//´ý²¹³ä
}


void PlayerManager::addCustomEvent()
{

}