#include"Monster.h"
#include"Model/GameMap.h"
#include<cmath>

bool Monster::init(int color)
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

void Monster::initAnimation()
{

	const float delay = 0.1;
	loadAnimation("monsterStand", delay, 8);
}

//貌似不用
void Monster::randomDestination()
{
	float dx = rand() % 400 - 200;
	float dy = rand() % 400 - 200;
	setDestination(Vec2(getPositionX() + dx, getPositionY() + dy));
}

bool Monster::attack()
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

void Monster::stopAttack()
{
	stopAnimation("monsterAttack", this);
}

float Monster::beAttack(const float damage)
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

void Monster::setHPBar()
{
	if (getColor() == RED)
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");
	else if (getColor() == BLUE)
		_HPBar = LoadingBar::create("Pictures/GameItem/greenBar.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(0);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}

void Monster::updateHPBar()
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