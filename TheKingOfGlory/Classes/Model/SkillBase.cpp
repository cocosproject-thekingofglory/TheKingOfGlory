#include "SkillBase.h"
#include "Manager/Manager.h"
#include "UI/Tip.h"
USING_NS_CC;




SkillBase * SkillBase::create(SpriteBase* attacker,const std::string & spriteName, const std::string & animationName,
	int animationNum, int delay,int color, float damage)
{
	auto skill = new SkillBase();
	if (skill&&skill->initWithSpriteFrameName(spriteName) && skill->init(attacker,animationName ,animationNum,delay,color, damage))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool SkillBase::init(SpriteBase* attacker, const std::string & animationName, int animationNum, int delay,int color, float damage)
{
	_color = color;
	_damage = damage;
	_animationName = animationName;
	_attacker = attacker;

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
			{
				player->beAttack(_damage);
				if (player->getNowHPValue() <= 0.0)
				{
					killedTarget(player);
				}
			}
		}
		auto soldiers = manager->_soldierList[_color ^ 1];
		for (auto soldier : soldiers)
		{
			if (box.intersectsRect(soldier->getBoundingBox()))
			{
				soldier->beAttack(_damage);
				if (soldier->getNowHPValue() <= 0.0)
				{
					killedTarget(soldier);
				}
			}
		}
		auto towers = manager->_towerList[_color ^ 1];
		for (auto tower : towers)
		{
			if (box.intersectsRect(tower->getBoundingBox()))
			{
				tower->beAttack(_damage);
				if (tower->getNowHPValue() <= 0.0)
				{
					killedTarget(tower);
				}
			}
		}
		auto cars = manager->_guncarList[_color ^ 1];
		for (auto car : cars)
		{
			if (box.intersectsRect(car->getBoundingBox()))
			{
				car->beAttack(_damage);
				if (car->getNowHPValue() <= 0.0)
				{
					killedTarget(car);
				}
			}
		}
		auto wildMonster = manager->_wildMonsterList;
		for (auto wild : wildMonster)
		{
			if (box.intersectsRect(wild->getBoundingBox()))
			{
				wild->beAttack(_damage);
				if (wild->getNowHPValue() <= 0.0)
				{
					killedTarget(wild);

					auto localPlayer = Manager::getInstance()->playerManager->getLocalPlayer();
					if (wild->getType() == SpriteBase::REDBUFF && !localPlayer->red_buffExist)
					{
						std::string stip;
						stip.append(StringUtils::format("Gain Red Buff!!!"));
						auto tip = Tip::create(stip, 1.0, Color4B::RED);
						tip->setPosition(Vec2(localPlayer->getContentSize().width / 2, localPlayer->getContentSize().height / 2));
						Vec2 to = Vec2(localPlayer->getContentSize().width / 2, localPlayer->getContentSize().height);
						auto moveup = MoveTo::create(1.0, to);
						tip->runAction(moveup);
						localPlayer->addChild(tip);
						localPlayer->addDamage(RED_BUFF_ADD_DAMAGE);
						localPlayer->red_buffExist = true;
						
					}
					else if (localPlayer->getType() == SpriteBase::BLUEBUFF && !localPlayer->blue_buffExist)
					{
						std::string stip;
						stip.append(StringUtils::format("Gain Blue Buff!!!"));
						auto tip = Tip::create(stip, 1.0, Color4B::BLUE);
						tip->setPosition(Vec2(localPlayer->getContentSize().width / 2, localPlayer->getContentSize().height / 2));
						Vec2 to = Vec2(localPlayer->getContentSize().width / 2, localPlayer->getContentSize().height);
						auto moveup = MoveTo::create(1.0, to);
						tip->runAction(moveup);
						localPlayer->addChild(tip);
						localPlayer->addDefend(BLUE_BUFF_ADD_DEFEND);
						localPlayer->blue_buffExist = true;
					}


				}
			}

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
				auto text = Tip::create(s, 0.1f, cocos2d::Color4B::GREEN, 24, "fonts/arial.ttf");
				text->setPosition(Vec2(this->getContentSize().width *0.8,
					this->getContentSize().height*1.2));
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
void SkillBase::killedTarget(SpriteBase*target)
{
	dynamic_cast<Player*>(_attacker)->addEXP(target->getKillExperience());
	dynamic_cast<Player*>(_attacker)->addMoney(target->getKillMoney());

	std::string stip;
	stip.append(StringUtils::format("+ %d", target->getKillMoney()));
	auto tip = Tip::create(stip, 1.0, Color4B::BLUE);
	tip->setPosition(Vec2(_attacker->getContentSize().width / 2, _attacker->getContentSize().height / 2));
	Vec2 to = Vec2(_attacker->getContentSize().width / 2, _attacker->getContentSize().height);
	auto moveup = MoveTo::create(1.0, to);
	tip->runAction(moveup);
	_attacker->addChild(tip);
}
