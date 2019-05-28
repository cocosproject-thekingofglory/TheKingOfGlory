#pragma once

#include "../Tower.h"
#include "EquipmentBase.h"
#include "../GameMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"

USING_NS_CC;
using namespace ui;

class EquipmentBase;

class Store:public Tower
{
public:
	static Store* createWithSpriteFrameName(const std::string& filename, int color);
	virtual bool init(int color);

	//CREATE_FUNC(Store);
private:
	
	void createListener();
	void onTouchEnded(Touch*touch, Event*event);
	bool onTouchBegan(Touch*touch, Event*event);

	Vector<EquipmentBase*> _equipmentList;


	bool _hasbg;

	void createBg();
	void removeBg();
	Size _visibleSize;
	Sprite* _bg;
	Button* _closeButton;

	void bgMove();
};