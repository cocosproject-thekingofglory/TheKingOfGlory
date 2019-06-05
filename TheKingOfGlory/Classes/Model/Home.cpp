#include "Home.h"

Home * Home::create(const std::string& fileName, int color)
{
	auto home = new Home();
	if (home&&home->initWithFile(fileName)&&home->init(color))
	{
		home->autorelease();
		return home;
	}
	CC_SAFE_DELETE(home);
	return nullptr;
}

bool Home::init(int color)
{
	this->setColor(color);
	this->setAnchorPoint(Vec2::ZERO);
	schedule(CC_CALLBACK_0(Home::recoverPlayer, this), 3.0f, "Recover");
	return true;
}

bool Home::isAtHome(Player * player)
{
	return this->getBoundingBox().intersectsRect(player->getBoundingBox());
}

void Home::recoverPlayer()
{
	for (auto& player : _recoverList)
	{
		if (!(player->getStatus() == Player::Status::DEAD))
		{
			player->setNowHPValue(MIN(player->getNowHPValue() + 20.0, player->getHPValue()));
			player->updateHPBar();
		}
	}
}
