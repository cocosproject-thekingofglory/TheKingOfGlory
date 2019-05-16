#pragma once

#include "cocos2d.h"
#include "SpriteBase.h"

USING_NS_CC;

//С���ĳ�ʼ����ֵ
const float SOLDIER_ATTACK_RADIUS = 3.0;
const float SOLDIER_DAMAGE = 10.0;
const float SOLDIER_HPVALUE = 100.0;
const int SOLDIER_ATTACK_INTERVAL = 180;
const float SOLDIER_MOVE_SPEED = 10;

const int SOLDIER_MOVE_ACTION = 1;

class Soldier :public SpriteBase
{
public:
	virtual bool init();
	CREATE_FUNC(Soldier);

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

	void startMove();
	void stopMove();

	virtual bool attack();//�����Ƿ�����˹���
	void stopAttack();

	virtual float beAttack(const float damage);

	static Soldier* createWithSpriteFrameName(const std::string& filename);

	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() { return _speed; }

	void setHPBar();
	void updateHPBar();

	void setDestination(Vec2 destination) { _destination = destination; }
	Vec2 getDestination() { return _destination; }

	void initAnimation();
	void move();

	void randomDestination();

private:
	float _speed;
	Vec2 _destination;
	Status _status;
	//Sprite* _bullet;
	//Sprite* _soldier;
};