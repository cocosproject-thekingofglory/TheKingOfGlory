#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SpriteBase.h"
#include "BulletBase.h"
#include "Scene/GameScene.h"

USING_NS_CC;
using namespace ui;

//³õÊ¼ÊôÐÔÖµ
const float TOWER_ATTACK_RADIUS =1500;
const float TOWER_DAMAGE = 50;
const float TOWER_HPVALUE = 2000;
const int TOWER_ATTACK_INTERVAL = 180;


class Tower :public SpriteBase
{
public:
	static Tower* createWithSpriteFrameName(const std::string& filename,int color);


	virtual bool init(int color);

	virtual bool attack();
	virtual float beAttack(const float damage);
	void destroy();

	void setHPBar();
	void updateHPBar();

	void initAnimation();

	bool insideAttack(SpriteBase*beAttacker);


private:


};