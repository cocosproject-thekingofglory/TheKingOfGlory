#include "SpriteBase.h"

bool SpriteBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

bool SpriteBase::insideAttack(Vec2 enemyPosition)
{
	float dx = enemyPosition.x - _position.x;
	float dy = enemyPosition.y - _position.y;
	return dx * dx + dy * dy <= _attackRadius * _attackRadius;
}

SpriteBase* SpriteBase::createWithSpriteFrameName(const std::string& filename)
{
	auto sprite = new SpriteBase();
	if (sprite&&sprite->initWithSpriteFrameName(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void SpriteBase::initAnimation()
{
	/*
	const float delay=
	loadAnimation("   ", delay, 3);
	*/
}
