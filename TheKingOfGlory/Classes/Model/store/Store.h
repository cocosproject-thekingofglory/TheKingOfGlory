#pragma once

#include "../Tower.h"
#include "EquipmentBase.h"
#include "../GameMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

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
	void createMenu();
	void createCloseButton();

	Vector<EquipmentBase*> _equipmentList;
	Size _visibleSize;

	Text* _title;
	Sprite* _storeMenu;
	Button* _closeButton;

};