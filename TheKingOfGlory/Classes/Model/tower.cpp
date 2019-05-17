#include "Tower.h"

Tower* Tower::createWithSpriteFrameName(const std::string& filename)
{
	auto tower = new Tower();
	if (tower&&tower->initWithSpriteFrameName(filename))
	{
		tower->autorelease();
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}

bool Tower::init()
{

	return true;
}

void Tower::initAnimation()
{
	/*
	const float delay=
	loadAnimation("Tower_Destory", delay, 3);

	*/
}

bool Tower::attack()
{
	return true;
}

float Tower::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage;
	if (nowHP <= 0.0)
	{
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
	}
	setNowHPValue(nowHP);
	if (nowHP > 0)updateHPBar();
	return nowHP;
}

bool Tower::beDestory()
{
	//runAnimation("Tower_Destory", this);
	return true;
}

void Tower::setHPBar()
{
	_HPBar = LoadingBar::create("hpBg1.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(100);
	Vec2 pos = this->getPosition();
	_HPBar->setPosition(Vec2(pos.x, pos.y + 30.0));

}

void Tower::updateHPBar()
{
	if (_HPBar != NULL)
	{
		_HPBar->setPercent(getNowHPValue() / getHPValue());
	}
}