#include"Monster.h"
#include"Model/GameMap.h"
#include<cmath>

bool Monster::Soldier::init(int color)
{
	setColor(color);
	setStatus(Status::STANDING);
	setAttackRadius(MONSTER_ATTACK_RADIUS);
	setHPValue(MONSTER_HPVALUE);
	setNowHPValue(MONSTER_HPVALUE);
	setDamage(MONSTER_DAMAGE);
	setAttackInterval(MONSTER_ATTACK_INTERVAL);

	initAnimation();
	setHPBar();

	return true;
}

void Monster::Soldier::initAnimation()
{

	const float delay = 0.1;
	loadAnimation("monsterStand", delay, 8);
}

//移动寻路
void Monster::Soldier::move()
{
	if (getStatus() == Status::MOVING)
	{
		//在规定限定区域内遇到英雄攻击移动

		auto position = this->getPosition();


	}
}


void Monster::Soldier::stopMove()
{
	setStatus(Monster::Status::STANDING);
	unschedule("move");
}

bool Monster::Soldier::attack()
{
	if (_attackTargetList.size())
	{
		runAnimation("monsterAttack", this);
		setStatus(Status::ATTACKING);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() > 0.0)
			{

				auto target = _attackTargetList.at(i);
				target->beAttack(this->getDamage());
				return true;
			}
		}
	}

	return false;
}

void Monster::Soldier::stopAttack()
{
	stopAnimation("monsterAttack", this);
}

float Monster::Soldier::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage;
	if (nowHP <= 0.0)
	{
		//停止动画，并在能攻击它的野怪的列表中删除它
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
	}
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	return nowHP;
}

void Monster::Soldier::setHPBar()
{

	_HPBar = LoadingBar::create("Pictures/GameItem/blueBar.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(0);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}

void Monster::Soldier::updateHPBar()
{
	if (_HPBar != NULL)
	{
		log("Percent:%f", 100.0*getNowHPValue() / getHPValue());
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}
}

Monster* Monster::createWithSpriteFrameName(const std::string& filename, int color)
{
	auto sprite = new Monster();
	if (sprite&&sprite->initWithSpriteFrameName(filename) && sprite->init(color))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}