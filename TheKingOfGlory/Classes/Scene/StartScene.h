#pragma once
#include "cocos2d.h"

class StartScene:public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;
	std::string text_Font;
	cocos2d::Color3B label_Color;
	float text_Size;

	void createBackground();
	void createPlayButton();
	void createSettingButton();
	void createHelpButton();
	void createExitButton();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
};

