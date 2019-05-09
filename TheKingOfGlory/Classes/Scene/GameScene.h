#pragma once
#include "cocos2d.h"

class GameScene:public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;
	cocos2d::Sprite* menu;
	cocos2d::Sprite* continueButton;
	cocos2d::Sprite* settingButton;
	cocos2d::Sprite* restartButton;
	cocos2d::Sprite* returnButton;
	cocos2d::Label* continueLabel;
	cocos2d::Label* settingLabel;
	cocos2d::Label* restartLabel;
	cocos2d::Label* returnLabel;
	cocos2d::EventListenerTouchOneByOne* menuListener;
	cocos2d::Rect menuRect;

	void onEnter();
	void createMap();
	void createMenu();
	void menuCallback(cocos2d::Ref* pSender);
	void menuOnTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Rect rectOfSprite(cocos2d::Sprite* sprite);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};

