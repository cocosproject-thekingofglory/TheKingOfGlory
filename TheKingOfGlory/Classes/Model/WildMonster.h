#pragma once
#include "Tower.h"
#include "cocos2d.h"

USING_NS_CC;

const float WILDMONSTER_ATTACK_RADIUS = 3.0;
const float WILDMONSTER_DAMAGE = 30.0;
const float WILDMONSTER_HPVALUE = 500.0;
const int WILDMONSTER_ATTACK_INTERVAL = 100;
const float WILDMONSTER_MOVE_SPEED = 10;
const float WILDMONSTER_DEFEND = 0.1;


//击杀经验、金钱
const int WILDMONSTER_KILL_EXPRIENCE = 5;
const int WILDMONSTER_KILL_MONEY = 10;

const int RED_BUFF = 1;
const int BLUE_BUFF = 0;
const float BUFF_DAMAGE[] = { 10,20 };
const float BUFF_DEFEND[] = { 0.2,0.1 };
const Vec2 BUFF_POS[] = { Vec2(50,50),Vec2(70,70) };
const float BUFF_EXIST_TIME = 15.0;
const float BUFF_APPEAR_TIME = 15.0;


class WildMonster :public Tower
{
public:
	virtual bool init(int type);


	virtual bool attack();//返回是否进行了攻击
	//virtual void stopAttack();

	virtual float beAttack(const float damage);


	static WildMonster* createWithSpriteFrameName(const std::string& filename, int type);
	//void initAnimation();


private:
	Vec2 _originPos;

	int _type;


};