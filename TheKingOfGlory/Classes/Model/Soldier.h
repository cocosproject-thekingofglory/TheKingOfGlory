#pragma once

#include "cocos2d.h"
#include "SpriteBase.h"
#include "Player.h"

USING_NS_CC;

//小兵的初始属性值
const float SOLDIER_ATTACK_RADIUS = 10.0;
const float SOLDIER_DAMAGE = 200.0;
const float SOLDIER_HPVALUE = 2000;
const int SOLDIER_ATTACK_INTERVAL = 100;
const float SOLDIER_MOVE_SPEED = 5;
const float SOLDIER_DEFEND = 0.1;

const int SOLDIER_KILL_MONEY = 50;
const int SOLDIER_KILL_EXP = 50;

const int SOLDIER_MOVE_ACTION = 1;

class Soldier :public SpriteBase
{
public:
	virtual bool init(int color);

	bool _isMove = 1;
	bool _isAttack = 0;

	enum class Status : std::int8_t
	{
		STANDING,
		MOVING,
		ATTACKING,
		DEAD,
	};


	void setStatus(Status status) { _status = status; }
	Status getStatus() { return _status; }

	virtual void startMove();
	virtual void stopMove();

	virtual bool attack();//返回是否进行了攻击
	virtual void stopAttack();

	virtual float beAttack(const float damage);

	static Soldier* createWithSpriteFrameName(const std::string& filename,int color);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() { return _speed; }

	virtual void setHPBar();
	virtual void updateHPBar();

	void setSmallDestination(Vec2 destination) { _destination = destination; }
	Vec2 getSmallDestination() { return _destination; }

	void setBigDestination(Vec2 destination) { _Destination = destination; }
	Vec2 getBigDestination() { return _Destination; }

	void addPath(std::vector<ValueMap> valueMap);

	virtual void initAnimation();
	virtual void move();

	void randomSmallDestination();
	void randomBigDestination();

protected:
	float _speed;
	Vec2 _destination;
	Vec2 _Destination;
	Status _status;
	std::vector<Vec2> path;
	int moveStep;
	bool isFlipped;
	//Sprite* _bullet;
	//Sprite* _soldier;

};