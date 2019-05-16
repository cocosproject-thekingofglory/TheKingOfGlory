#pragma once
#include "cocos2d.h"

class GameScene:public cocos2d::Layer
{
private:
	bool hasMenu;
	cocos2d::Size visible_Size;
	cocos2d::Sprite* menu;
	cocos2d::Label* continueLabel;
	cocos2d::Label* settingLabel;
	cocos2d::Label* restartLabel;
	cocos2d::Label* returnLabel;
	cocos2d::EventListenerTouchOneByOne* menuListener;
	cocos2d::Rect menuRect;

	void onEnter();
	void createMenuButton();
	void updateMenu();
	void createMenu();
	void removeMenu();
	void createResultBox(cocos2d::EventCustom* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Rect rectOfLabel(cocos2d::Label* label);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

};

