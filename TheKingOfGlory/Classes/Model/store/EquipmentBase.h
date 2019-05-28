#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "../SpriteBase.h"
//#include "../../Manager/PlayerManager.h"

const int EQUIPMENT_CNT = 2;
const int PLAYER_MAX_EQUIPMENT_CNT = 6;

const float HP[] = { 0,0,0 };
const float DAMAGE[] = { 0,10,0 };
const float DEFEND[] = { 0,0,0.05 };//小于1;
const int MONEY[] = { 0,10,10 };

class Manager;

class EquipmentBase:public Sprite
{
public:

	virtual bool init(int id);

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

	static EquipmentBase* createWithSpriteFrameName(const std::string& filename,int id);

	EventListenerTouchOneByOne*listener;

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

	//static Player* _localplayer;
	//static int _localMoney;

};
