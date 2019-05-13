#pragma once
#include "cocos2d.h"
#include "Model/tower.h"

class TowerManager :public cocos2d::Layer
{
public:
	Tower* createTower(const std::string&id, const int color, const cocos2d::Vec2 pos, float damage = 1.0, float attackRadius = 5.0);

	Tower* getTower(int color);

	virtual bool init();

private:
	cocos2d::Map<int, Tower*> _towerList;


};