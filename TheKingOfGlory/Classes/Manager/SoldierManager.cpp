#include "SoldierManager.h"

USING_NS_CC;

Soldier* SoldierManager::createSoldier(const std::string &filename, int color)
{
	auto soldier = Soldier::createWithSpriteFrameName(filename);
	if (soldier)
	{
		soldier->setColor(color);
		_soldierList.pushBack(soldier);
		return
	}
}