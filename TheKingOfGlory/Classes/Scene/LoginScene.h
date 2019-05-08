#pragma once
#include "cocos2d.h"

class LoginScene :public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnter();

	void createBackground();
	CREATE_FUNC(LoginScene);
};

