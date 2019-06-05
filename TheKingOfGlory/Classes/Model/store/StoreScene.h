#pragma once
#include "EquipmentBase.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class StoreScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();



private:
	void onEnter();
	Vector<EquipmentBase*> _equipmentList;

	//void createCloseButton();
	void menuOkCallback(cocos2d::Ref * pSender);
	Size _visibleSize;

	cocos2d::ui::CheckBox * createCheckBox(std::function<void(cocos2d::Ref*, cocos2d::ui::CheckBox::EventType)> callback);
	cocos2d::Label * createLabel(const char * text);
	cocos2d::Menu* createText();

};