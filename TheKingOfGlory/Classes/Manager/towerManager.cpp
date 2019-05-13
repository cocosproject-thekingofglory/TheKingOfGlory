#include "towerManager.h"

Tower* TowerManager::createTower(const std::string&id, const int color, const cocos2d::Vec2 pos, float damage, float attackRadius)
{
	auto tower = Tower::createWithSpriteFrameName(id);
	if (tower)
	{
		tower->setPosition(pos);
		_towerList.insert(color, tower);
		tower->setColor(color);
		tower->setDamage(damage);
		tower->setAttackRadius(attackRadius);
		tower->setVec2(pos);
		return tower;
	}
	return nullptr;
}

