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

	_isMove = false;
	_isAttack = false;

	initAnimation();
	//setHPBar();

	_soldier = Sprite::createWithSpriteFrameName("warrior_walk_down_1.png");

	//_bullet = Sprite::createWithSpriteFrameName("soldierBullet.png");
	//_bullet->setVisible(false);
	
	return true;
}

void Soldier::initAnimation()
{

	const float delay = 0.1f;
	loadAnimation("warrior_walk_down", delay, 10);
	loadAnimation("warrior_walk_left", delay, 10);
	loadAnimation("warrior_walk_right", delay, 10);
	loadAnimation("warrior_walk_up", delay, 10);


}

void Soldier::move(Vec2 toPosition)
{
	if (_isMove)
	{
		//runAnimation("soldierMove", this);
		auto _position = getPosition();
		float dx = toPosition.x - _position.x;
		float dy = toPosition.y - _position.y;
		float dist = sqrt(dx*dx + dy * dy);
		float interval = dist / (getSpeed());
		auto moveTo = MoveTo::create(interval, toPosition);
		moveTo->setTag(1);
		this->runAction(moveTo);
		LoadingBar *HP = getHPBar();
		HP->runAction(moveTo);
	}
}

void Soldier::stopMove()
{
	if (_isMove)
	{
		//stopAnimation("soldierMove",this);
		_isMove = false;
		this->stopActionByTag(1);
		LoadingBar *HP = getHPBar();
		HP->stopActionByTag(1);
	}
}

void Soldier::attack(const void*enemy)
{
	if (_isAttack)
	{
		//runAnimation("soldierAttack", this);
		_isAttack = false;
	}
}

void Soldier::stopAttack()
{
	if (_isAttack)
	{
		//stopAnimation("soldierAttack",this);
		_isAttack = false;
	}
}

void Soldier::setHPBar()
{
	_HPBar = LoadingBar::create("hpBg1.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);
	
	_HPBar->setPercent(100);
	Vec2 pos = _soldier->getPosition();
	_HPBar->setPosition(Vec2(pos.x, pos.y + 30.0));

}