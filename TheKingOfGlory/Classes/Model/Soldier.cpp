#include "Soldier.h"
#include <cmath>

bool Soldier::init()
{
	if (!SpriteBase::init())
	{
		return false;
	}

	setAttackRadius(SOLDIER_ATTACK_RADIUS);
	setHPValue(SOLDIER_HPVALUE);
	setDamage(SOLDIER_DAMAGE);
	setAttackInterval(SOLDIER_ATTACK_INTERVAL);


	initAnimation();
	setHPBar();

	//_soldier = Sprite::createWithSpriteFrameName("soldier.png");

	//_bullet = Sprite::createWithSpriteFrameName("soldierBullet.png");
	//_bullet->setVisible(false);
	
	return true;
}

void Soldier::initAnimation()
{
	/*
	动画命名wei"move_01.png"
	*/
	/*
	const float delay=
	loadAnimation("soldierMove", delay, 3);

	loadAnimation("soldierAttack", delay, 3);
	*/
}

void Soldier::startMove()
{
	if (_isMove)
	{
		Vec2 toPosition;
		if (this->getColor() == RED)toPosition = BLUE_STORE;
		else toPosition = RED_STORE;
		//runAnimation("soldierMove", this);
		auto _position = getPosition();
		float dx = toPosition.x - _position.x;
		float dy = toPosition.y - _position.y;
		float dist = sqrt(dx*dx + dy * dy);
		float interval = dist / (getSpeed());
		auto moveTo = MoveTo::create(interval, toPosition);
		moveTo->setTag(SOLDIER_MOVE_ACTION);
		this->runAction(moveTo);
		LoadingBar *HP = getHPBar();
		HP->runAction(moveTo);
	}
}

void Soldier::stopMove()
{
	//stopAnimation("soldierMove",this);
	this->stopActionByTag(1);
	LoadingBar *HP = getHPBar();
	HP->stopActionByTag(SOLDIER_MOVE_ACTION);
}

bool Soldier::attack()
{
	//runAnimation("soldierAttack", this);
	for (unsigned int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() > 0.0)
		{
			_attackTargetList.at(i)->beAttack(this->getDamage());
			return true;
		}
		//else _attackTargetList.popBack();
	}
	return false;
}

void Soldier::stopAttack()
{
	//stopAnimation("soldierAttack",this);
}

float Soldier::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage;
	if (nowHP <= 0.0)
	{
		//停止动画，并在能攻击它的小兵的列表中删除它
		stopMove();
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this,false);
		}
	}
	setNowHPValue(nowHP);
	if (nowHP > 0)updateHPBar();
	return nowHP;
}

void Soldier::setHPBar()
{
	_HPBar = LoadingBar::create("planeHP.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);
	
	_HPBar->setPercent(100);
	Vec2 pos = this->getPosition();
	_HPBar->setPosition(Vec2(pos.x, pos.y + 30.0));

}

void Soldier::updateHPBar()
{
	if (_HPBar != NULL)
	{
		_HPBar->setPercent(getNowHPValue() / getHPValue());
	}
}


Soldier* Soldier::createWithSpriteFrameName(const std::string& filename)
{
	auto sprite = new Soldier();
	if (sprite&&sprite->initWithSpriteFrameName(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}