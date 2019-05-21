#include "Tower.h"
#include "GameMap.h"

Tower* Tower::createWithSpriteFrameName(const std::string& filename,int color)
{
	auto tower = new Tower();
	if (tower&&tower->initWithSpriteFrameName(filename)&& tower->init(color))
	{
		tower->autorelease();
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}

bool Tower::init(int color)
{
	setAnchorPoint(Vec2::ZERO);
	setColor(color);
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
			auto bullet=BulletBase::create(this, target, "warrior_attack_down", "warrior_attack_down (1).png");
			GameMap::getCurrentMap()->addChild(bullet);
			Vec2 pos = Vec2(getPosition().x + getContentSize().width / 2, getPosition().y + getContentSize().height / 2);
			bullet->setPosition(pos);
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
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	return nowHP;

}

void Tower::destroy()
{

}

bool Tower::playDestoryAnimation()
{
	//runAnimation("Tower_Destory", this);
	return true;
}

void Tower::setHPBar()
{
	_HPBar = LoadingBar::create("Pictures/GameItem/blueBar.png");

	_HPBar->setScale(0.4);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(100);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.05);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}


void Tower::updateHPBar()
{
	if (_HPBar != NULL)
	{
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}
}


bool Tower::insideAttack(SpriteBase*beAttacker)
{
	Vec2 towerPos = this->getPosition(), pos = beAttacker->getPosition();
	float dx = towerPos.x - pos.x, dy = towerPos.y - pos.y;
	return dx * dx + dy * dy <= getAttackRadius()*getAttackRadius();
}