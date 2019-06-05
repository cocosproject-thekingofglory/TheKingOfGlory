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

const float HP[] = { 0,0,0,0,0,0,200,240,280,320,360,100,140,180,220,500};
const float DAMAGE[] = { 0,10,11,12,13,14,0,0,0,0,0,10,11,12,13,30 };
const float DEFEND[] = { 0,0,0,0,0,0,0.1,0.12,0.14,0.16,0.20,0.05,0.06,0.07,0.08,0.30 };//С��1;
const int MONEY[] = { 0,10,170,190,210,230,150,170,190,210,230,300,350,400,450,1000 };


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
	void sell();

	//static void getLocalPlayer();

private:


	int _id;//��1001��ʼ

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