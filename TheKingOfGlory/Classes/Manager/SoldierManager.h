#pragma once

#include "cocos2d.h"
#include "Model/Soldier.h"

USING_NS_CC;

class SoldierManager :public cocos2d::Layer
{
public:

	Soldier* createSoldier(const std::string &filename, int color);

	Soldier* getSoldier(const std::string);

	void attack();

	virtual bool init();
	CREATE_FUNC(SoldierManager);
private:
	Vector<Soldier*> _soldierList;

};