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

class Monster :public Soldier
{
public:

	enum MonsterType {
		MONSTER1,
		MONSTER2,
		MONSTER3,
		MONSTER4,
		REDBUFF,
		BLUEBUFF
	};

	static Monster* createWithSpriteFrameName(const std::string& filename, int color);


	void setDestination(Vec2 destination) { _destination = destination; }
	Vec2 getDestination() { return _destination; }

	void randomDestination();

private:
	Vec2 _destination;
	Status _status;

};