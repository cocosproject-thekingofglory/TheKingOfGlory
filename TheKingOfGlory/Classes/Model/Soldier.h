#pragma once

#include "cocos2d.h"
#include "SpriteBase.h"

USING_NS_CC;

//小兵的初始属性值
const float SOLDIER_ATTACK_RADIUS = 3.0;
const float SOLDIER_DAMAGE = 1.0;
const float SOLDIER_HPVALUE = 5.0;
const int SOLDIER_ATTACK_INTERVAL = 180;

const int SOLDIER_MOVE_ACTION = 1;

class Soldier :public SpriteBase
{
public:
	virtual bool init();

	CREATE_FUNC(Soldier);

	bool _isMove = 1;
	bool _isAttack = 0;

	void startMove();
	void stopMove();

	virtual bool attack();//返回是否进行了攻击
	void stopAttack();

	virtual float beAttack(const float damage);

	static Soldier* createWithSpriteFrameName(const std::string& filename);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() { return _speed; }

	void setHPBar();
	void updateHPBar();

	void initAnimation();

private:

	float _speed;

	Sprite* _bullet;
};