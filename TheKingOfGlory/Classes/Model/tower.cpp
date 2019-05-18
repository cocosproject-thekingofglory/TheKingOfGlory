#include "Tower.h"

Tower* Tower::createWithSpriteFrameName(const std::string& filename)
{
	auto tower = new Tower();
	if (tower&&tower->initWithSpriteFrameName(filename)&& sprite->init())
	{
		tower->autorelease();
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}

bool Tower::init()
{
	setAttackRadius(TOWER_ATTACK_RADIUS);
	setHPValue(TOWER_HPVALUE);
	setNowHPValue(TOWER_HPVALUE);
	setDamage(TOWER_DAMAGE);
	setAttackInterval(TOWER_ATTACK_INTERVAL);


	initAnimation();
	setHPBar();
	return true;
}

void Tower::initAnimation()
{
	/*
	const float delay=
	loadAnimation("Tower_Destory", delay, 3);

	loadAnimation("",delay,3);

	*/
}

bool Tower::attack()
{
	for (int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
		{
			auto target = _attackTargetList.at(i);
			BulletBase::create(this, target, "towerAttack", "towerAttack");
			return true;
		}
	}
	return false;
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
		//playDestoryAnimation();
	}
	else 
	{
		setNowHPValue(nowHP);
		updateHPBar();
	}
	return nowHP;
}

bool Tower::playDestoryAnimation()
{
	//runAnimation("Tower_Destory", this);
	return true;
}

void Tower::setHPBar()
{
	_HPBar = LoadingBar::create("Pictures/GameItem/planeHP.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(0);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}


void Tower::updateHPBar()
{
	if (_HPBar != NULL)
	{
		_HPBar->setPercent(getNowHPValue() / getHPValue());
	}
}


bool Tower::insideAttack(SpriteBase*beAttacker)
{
	Vec2 towerPos = this->getPosition(), pos = beAttacker->getPosition();
	float dx = towerPos.x - pos.x, dy = towerPos.y - pos.y;
	return dx * dx + dy * dy <= getAttackRadius()*getAttackRadius();
}