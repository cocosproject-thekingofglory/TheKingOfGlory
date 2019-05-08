#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoginScene :public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;
	cocos2d::Sprite* usernameBG;
	cocos2d::ui::TextField* usernameInput;


	void onEnter();
	void createBackground();
	void createLoginButton();
	void initUserBox();

	void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();


	CREATE_FUNC(LoginScene);
};

