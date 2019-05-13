#pragma once

#include "cocos2d.h"
#include "SpriteBase.h"

USING_NS_CC;

//小兵的初始属性值
const float SOLDIER_ATTACK_RADIUS = 3.0;
const float SOLDIER_DAMAGE = 1.0;
const float SOLDIER_HPVALUE = 5.0;


class Soldier :public SpriteBase
{
public:
	virtual bool init();

	CREATE_FUNC(Soldier);

	bool _isMove;
	bool _isAttack;

	void move(Vec2 toPosition);
	void stopMove();

	void attack(const void* enemy);
	void stopAttack();

	//static Soldier* createWithSpriteFrameName(const std::string& filename);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() { return _speed; }

	void setHPBar();

	void initAnimation();

private:

	float _speed;

	Sprite* _soldier;
	Sprite* _bullet;
};