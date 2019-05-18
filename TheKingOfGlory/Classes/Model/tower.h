#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SpriteBase.h"
#include "BulletBase.h"

USING_NS_CC;
using namespace ui;

//≥ı º Ù–‘÷µ
const float TOWER_ATTACK_RADIUS = 3.0;
const float TOWER_DAMAGE = 5.0;
const float TOWER_HPVALUE = 50.0;
const int TOWER_ATTACK_INTERVAL = 180;


class Tower :public SpriteBase
{
public:
	static Tower* createWithSpriteFrameName(const std::string& filename);

	CREATE_FUNC(Tower);

	virtual bool init();

	virtual bool attack();
	virtual float beAttack(const float damage);

	virtual bool playDestoryAnimation();

	void setHPBar();
	void updateHPBar();

	void initAnimation();

	bool insideAttack(SpriteBase*beAttacker);

private:

};