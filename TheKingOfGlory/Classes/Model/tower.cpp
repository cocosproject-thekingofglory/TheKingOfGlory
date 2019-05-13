#include "tower.h"

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
	loadAnimation("   ", delay, 3);
	*/
}

void Tower::attack()
{

}

bool Tower::insideAttack(Vec2 enemyPosition)
{
	float dx = enemyPosition.x - _towerPosition.x;
	float dy = enemyPosition.y - _towerPosition.y;
	return dx * dx + dy * dy <= _attackRadius * _attackRadius;
}