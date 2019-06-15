#pragma once

#include "cocos2d.h"
#include "Model/Soldier.h"
#include "Model/GameMap.h"
#include "Model/Tower.h"
#include "PlayerManager.h"
#include "Model/Home.h"
#include "Model/store/Store.h"
#include "Model/GunCar.h"

USING_NS_CC;


const Vec2 RED_BIRTH_POINT = Vec2(10.0, 10.0);
const Vec2 BLUE_BIRTH_POINT = Vec2(150.0, 150.0);

//const std::string RED_SOLDIER_FILENAME = "red_soldier.png";
//const std::string BLUE_SOLDIER_FILENAME = "blue_soldier.png";
const std::string RED_SOLDIER_FILENAME = "soldier_move_right (1).png";
const std::string BLUE_SOLDIER_FILENAME = "soldier_move_right (1).png";

const std::string RED_GUNCAR_FILENAME = "guntruck_move_rightdown (1).png";
const std::string BLUE_GUNCAR_FILENAME = "guntruck_move_rightdown (1).png";

const std::string RED_TOWER_FILENAME = "redtower.png";
const std::string BLUE_TOWER_FILENAME = "bluetower.png";

const std::string RED_STORE_FILENAME = "store.png";
const std::string BLUE_STORE_FILENAME = "store.png";

const std::string MONSTER1_RED_FILENAME = "monster1RedStand (1).png";
const std::string MONSTER1_BLUE_FILENAME = "monster1BlueStand (1).png";
const std::string MONSTER2_RED_FILENAME = "monster2RedStand (1).png";
const std::string MONSTER2_BLUE_FILENAME = "monster2BlueStand (1).png";
const std::string MONSTER3_RED_FILENAME = "monster3RedStand (1).png";
const std::string MONSTER3_BLUE_FILENAME = "monster3BlueStand (1).png";
const std::string MONSTER4_RED_FILENAME = "monster4RedStand (1).png";
const std::string MONSTER4_BLUE_FILENAME = "monster4BlueStand (1).png";
const std::string REDBUFF1_FILENAME = "redBuff1Stand (1).png";
const std::string REDBUFF2_FILENAME = "redBuff2Stand (1).png";
const std::string RED_BUFF_FILENAME = "redbuff_stand_leftdown (1).png";

const std::string BLUE_BUFF_FILENAME = "bluebuff_stand_rightdown (1).png";

class Manager :public cocos2d::Layer
{
public:
	PlayerManager* playerManager;


	Soldier* createSoldier(const std::string &filename, const int color,int path);

	GunCar* createGunCar(const std::string &filename, const int color,int path);

	Tower* createTower(const std::string &filename, const int color);

	Store* createStore(const std::string &filename, const int color);

	void scheduleSoldierAttack();
	void scheduleGunCarAttack();
	void scheduleWildMonsterAttack();
	void scheduleCreateSoldier();
	void scheduleCreateGunCar();
	void scheduleCreateWildMonster();
	void scheduleDeadDetect();
	void scheduleTowerAttack();
	void scheduleHomeRecover();
	void scheduleBuffDetect();
	void AIHero();
	void toOver(bool isWin);

	virtual bool init();
	Vector<Soldier*> _soldierList[2];
	Vector<GunCar*> _guncarList[2];
	Vector<Tower*> _towerList[2];
	Vector<Home*> _homeList;
  	//Vector<Monster*> _monsterList[2];
  	Vector<Tower*>_wildMonsterList;
	CREATE_FUNC(Manager);

	static Manager* getInstance();
private:
	enum Mode
	{
		One=1,Five=5
	}mode;
	bool isOnline;
	bool insideAttack(SpriteBase* beAttack, SpriteBase* attack);
	int time_AI;
	int time_soldier;
	int time_gunCar;

};

