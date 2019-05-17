#include"PlayerManager.h"

USING_NS_CC;

bool PlayerManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addCustomEvent();

	scheduleOnce(schedule_selector(PlayerManager::initPlayer), 1.0f);

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
	CC_SAFE_DELETE(player);
	return nullptr;
}

Player* PlayerManager::createLocalPlayer(const std::string& id, int role)
{
	auto localPlayer = Player::createPlayer(id, role);
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

Map<std::string, Player*> PlayerManager::getPlayerList()
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
	this->createLocalPlayer(UserDefault::getInstance()->getStringForKey("username"), 0);
	GameMap::getCurrentMap()->addSprite(this->getLocalPlayer(), GameMap::Type::Tower_Blue);
}