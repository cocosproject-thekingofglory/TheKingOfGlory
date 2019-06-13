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
const float TOWER_ATTACK_RADIUS =400;
const float TOWER_DAMAGE = 1000;
const float TOWER_HPVALUE = 20000;
const int TOWER_ATTACK_INTERVAL = 180;
const float TOWER_DEFEND = 0.5;
//击杀经验和金钱
const int TOWER_KILL_EXPRIENCE = 500;
const int TOWER_KILL_MONEY = 500;
//
const float BUFF_ATTACK_RADIUS = 400;
const float BUFF_DAMAGE = 300;
const float BUFF_HPVALUE = 3000;
const int BUFF_ATTACK_INTERVAL = 180;
const float BUFF_DEFEND = 0.1;
//击杀经验和金钱
const int BUFF_KILL_EXPRIENCE = 100;
const int BUFF_KILL_MONEY = 100;

const float BLUE_BUFF_ADD_DEFEND = 0.15;
const float RED_BUFF_ADD_DAMAGE = 500;


class Tower :public SpriteBase
{
public:

	static Tower* createWithSpriteFrameName(const std::string& filename,int color, TYPE type = TOWER);


	virtual bool init(int color,TYPE type= TOWER);

	virtual bool attack();
	virtual float beAttack(const float damage);
	virtual void destroy();

	void setHPBar();
	void updateHPBar();

	void initAnimation();

	bool insideAttack(SpriteBase*beAttacker);

	void runAttackAnimation();
	void stopAttackAnimation();
	
	void runStandAnimation();
	void stopStandAnimation();

private:

};