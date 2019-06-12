#include "Home.h"
#include "UI/Tip.h"

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
	schedule(CC_CALLBACK_0(Home::recoverPlayer, this), 1.0f, "Recover");
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
		if (!(player->getStatus() == Player::Status::DEAD)&&player->getNowHPValue()<player->getHPValue())
		{
			player->addNowHPValue(player->getHPValue()/5);
			std::stringstream str;
			str << player->getHPValue()/6;
			std::string s = "+" + str.str();
			auto text = Tip::create(s, 0.3f, cocos2d::Color4B::GREEN, 24, "fonts/arial.ttf");
			text->setPosition(Vec2(player->getContentSize().width *player->getScale()*0.8,
				player->getContentSize().height*player->getScale()*1.2));
			text->setScale(1.0/player->getScale());
			player->addChild(text);

		}
	}
}
