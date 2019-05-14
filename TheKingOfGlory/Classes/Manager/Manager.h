#pragma once

#include "cocos2d.h"
#include "Model/Soldier.h"

USING_NS_CC;


const int SOLDIER_APPEAR_INTERVAL = 60 * 10;
const int SOLDIER_UPDATE_INTERVAL = 30;

const Vec2 RED_BIRTH_POINT = Vec2(10.0, 10.0);
const Vec2 BLUE_BIRTH_POINT = Vec2(150.0, 150.0);

const std::string RED_SOLDIER_FILENAME = "red_soldier.png";
const std::string BLUE_SOLDIER_FILENAME = "blue_soldier.png";



class Manager :public cocos2d::Layer
{
public:
	Soldier* createSoldier(const std::string &filename, const int color);

	//Soldier* getSoldier(const std::string);

	virtual void update(float dt);

	virtual bool init();

	CREATE_FUNC(Manager);
private:

	bool insideAttack(SpriteBase* beAttack, SpriteBase* attack);

	Vector<Soldier*> _soldierList[2];

};