#pragma once

#include"cocos2d.h"
#include"Model\SpriteBase.h"
#include"Model\Player.h"

USING_NS_CC;

//野怪的初始属性值
const float MONSTER_ATTACK_RADIUS = 3.0;
const float MONSTER_DAMAGE = 5.0;
const float MONSTER_HPVALUE = 100.0;
const int MONSTER_ATTACK_INTERVAL = 100;
const float MONSTER_EXPVALUE = 30.0;
const int MONSTER_MONEY = 5;

class Monster :public SpriteBase
{
public:
	virtual bool init(int color);

	bool _isAttack = 0;

	enum class Status : std::int8_t
	{
		STANDING,
		ATTACKING,
		DEAD,
	};

	enum MonsterType {
		MONSTER,
		REDBUFF,
		BLUEBUFF
	};

	void setStatus(Status status) { _status = status; }
	Status getStatus() { return _status; }

	virtual bool attack();//返回是否进行了攻击
	void stopAttack();

	virtual float beAttack(const float damage);

	static Monster* createWithSpriteFrameName(const std::string& filename, int color);

	virtual void setHPBar();
	virtual void updateHPBar();

	void setDestination(Vec2 destination) { _destination = destination; }
	Vec2 getDestination() { return _destination; }

	virtual void initAnimation();

	void randomDestination();

private:
	Vec2 _destination;
	Status _status;

};