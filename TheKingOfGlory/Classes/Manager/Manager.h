#pragma once

#include "cocos2d.h"
#include "Model/Soldier.h"
#include "Model/Monster.h"
#include "Model/GameMap.h"
#include "Model/Tower.h"
#include "PlayerManager.h"
#include "Model/Home.h"

USING_NS_CC;


const Vec2 RED_BIRTH_POINT = Vec2(10.0, 10.0);
const Vec2 BLUE_BIRTH_POINT = Vec2(150.0, 150.0);

//const std::string RED_SOLDIER_FILENAME = "red_soldier.png";
//const std::string BLUE_SOLDIER_FILENAME = "blue_soldier.png";
const std::string RED_SOLDIER_FILENAME = "soldierMove (1).png";
const std::string BLUE_SOLDIER_FILENAME = "soldierMove (1).png";

const std::string RED_TOWER_FILENAME = "tower.png";
const std::string BLUE_TOWER_FILENAME = "tower.png";

const std::string RED_MONSTER_FILENAME = "redMonsterStand (1).png";
const std::string BLUE_MONSTER_FILENAME = "blueMonsterStand (1).png";

class Manager :public cocos2d::Layer
{
public:
	PlayerManager* playerManager;


	Soldier* createSoldier(const std::string &filename, const int color);

	Monster* createMonster(const std::string &filename, const int color);

	Tower* createTower(const std::string &filename, const int color);



	void scheduleAttack();
	void scheduleCreateSoldier();
	void scheduleCreateMonster(); //À¿Õˆ∫Û¥¥Ω®
	void scheduleDeadDetect();
	void scheduleTowerAttack();
	void scheduleHomeRecover();
	void AIHero();

	virtual bool init();
	Vector<Soldier*> _soldierList[2];
	Vector<Tower*> _towerList[2];
	Vector<Monster*> _monsterList[2];
	Vector<Home*> _homeList;
	CREATE_FUNC(Manager);

	static Manager* getInstance();
private:

	bool insideAttack(SpriteBase* beAttack, SpriteBase* attack);

	static Manager* _instance;

};