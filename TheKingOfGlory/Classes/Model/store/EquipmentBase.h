#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "../SpriteBase.h"
#include <string>
//#include "../../Manager/PlayerManager.h"

static int EQUIPMENT_CNT = 14;
const int PLAYER_MAX_EQUIPMENT_CNT = 6;

const float HP[] = { 0,0,0,0,0,0,2000,2400,2800,3200,3600,1000,1400,1800,2200,5000};
const float DAMAGE[] = { 0,100,110,120,130,140,0,0,0,0,0,100,110,120,130,300 };
const float DEFEND[] = { 0,0,0,0,0,0,0.1,0.12,0.14,0.16,0.20,0.05,0.06,0.07,0.08,0.15 };//小于1;
const int MONEY[] = { 0,500,1700,1900,2100,2300,1500,1700,1900,2100,2300,3000,3500,4000,4500,10000 };


static bool _hasbg = false;

class Manager;
class Store;

class EquipmentBase:public Sprite
{
public:

	virtual bool init(int id, Store*store);

	void setHP(float HP) { _addHP = HP; }
	float getHP() { return _addHP; }
	
	void setDamage(float damage) { _addDamage = damage; }
	float getDamage() { return _addDamage; }

	void setDefend(float defend) { _addDefend = defend; }
	float getDefend() { return _addDefend; }

	void setCostMoney(int costMoney) { _costMoney = costMoney; }
	int getCostMoney() { return _costMoney; }

	void setId(int id) { _id = id; }
	int getId() { return _id; }

	static EquipmentBase* createWithSpriteFrameName(const std::string& filename, int id, Store*store);

	EventListenerTouchOneByOne*listener;

	void removeBg();
	void buy();
	
	//listener

	//static void getLocalPlayer();

private:


	int _id;//从1001开始

	float _addHP;

	float _minusAttackInterval;
	float _addDamage;
	float _addDefend;

	float _addCritOdds;
	float _addCritDamage;

	int _addMoneyPerSecond;
	float _addHPPerSecond;

	float _addSpeed;

	int _costMoney;

	void createListener();
	bool onTouchBegin(Touch*touch, Event*event);
	void onTouchEnded(Touch*touch, Event*event);

	Sprite* _bg;
	Text* createText(std::string context);
	Store*_store;


	//static Player* _localplayer;
	//static int _localMoney;

};
