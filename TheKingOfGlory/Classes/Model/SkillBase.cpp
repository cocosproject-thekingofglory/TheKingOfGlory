#include "SkillBase.h"
#include "Manager/Manager.h"
#include "UI/Tip.h"
USING_NS_CC;




SkillBase * SkillBase::create(const std::string & spriteName, const std::string & animationName,
	int animationNum, int delay,int color, float damage)
{
	auto skill = new SkillBase();
	if (skill&&skill->initWithSpriteFrameName(spriteName) && skill->init(animationName ,animationNum,delay,color, damage))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool SkillBase::init(const std::string & animationName, int animationNum, int delay,int color, float damage)
{
	_color = color;
	_damage = damage;
	_animationName = animationName;

	initAnimation(animationName, animationNum);
	runAnimation(animationName, this);

	schedule(CC_CALLBACK_0(SkillBase::collisionDetection, this), 0.2f, "Collision");
	scheduleOnce(CC_CALLBACK_0(SkillBase::remove, this), delay, "Remove");
	return true;
}

void SkillBase::initAnimation(const std::string&animationName,int animationNum)
{
	const float delay = 0.1;
	loadAnimation(animationName, delay, animationNum);

}

void SkillBase::collisionDetection()
{
	auto box = this->getBoundingBox();
	auto manager=dynamic_cast<Manager*>(cocos2d::Director::getInstance()->getRunningScene()->
		getChildByName("GameScene")->getChildByName("GameController")->getChildByName("Manager"));
	if (_damage > 0)
	{
		auto players = manager->playerManager->getPlayerList();
		for (auto pair : players)
		{
			auto player = pair.second;
			if (player->getColor() != _color & box.intersectsRect(player->getBoundingBox()))
				player->beAttack(_damage);
		}
		auto soldiers = manager->_soldierList[_color ^ 1];
		for (auto soldier : soldiers)
		{
			if (box.intersectsRect(soldier->getBoundingBox()))
				soldier->beAttack(_damage);
		}
		auto gunCars= manager->_guncarList[_color ^ 1];
		for (auto gunCar:gunCars)
		{
			if (box.intersectsRect(gunCar->getBoundingBox()))
				gunCar->beAttack(_damage);
		}
		auto towers = manager->_towerList[_color ^ 1];
		for (auto tower : towers)
		{
			if (box.intersectsRect(tower->getBoundingBox()))
				tower->beAttack(_damage);
		}
	}
	else
	{
		auto players = manager->playerManager->getPlayerList();
		for (auto pair : players)
		{
			auto player = pair.second;
			if (player->getColor() != _color && player->getStatus() != Player::Status::DEAD
				&&player->getNowHPValue() > 0.0&& box.intersectsRect(player->getBoundingBox()))
			{
				std::stringstream str;
				str << -_damage;
				std::string s = "+" + str.str();
				auto text = Tip::create(s, 0.1f, cocos2d::Color4B::GREEN);
				text->setPosition(Vec2(player->getContentSize().width*player->getScale() *0.8,
					player->getContentSize().height*player->getScale()*1.2));
				text->setScale(1.0/player->getScale());
				player->addChild(text);
				player->addNowHPValue(-_damage);
			}

		}
	}

}

void SkillBase::remove()
{
	unschedule("Collision");
	stopAnimation(this);
	removeFromParentAndCleanup(true);

}
