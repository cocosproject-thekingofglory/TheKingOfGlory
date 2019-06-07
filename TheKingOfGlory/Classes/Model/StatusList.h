#pragma once
#include "../Manager/Manager.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>


USING_NS_CC;

const std::string BG_FILENAME = "statusBG.png";
static bool hasList = false;

class StatusList :public Sprite
{
public:
	virtual bool init();
	
	static StatusList*createStatusList();

private:

	Text* createText(std::string context);
	void remove();
	//bool onTouchEnded(Touch*touch, Event*event);

	int _choseEquipmentID;
	void sell(EquipmentBase*equip);
	EventListenerTouchOneByOne*_sellListener;


};