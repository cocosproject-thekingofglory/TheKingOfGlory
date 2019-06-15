#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelpScene :public cocos2d::Layer
{
private:
	void menuOkCallback(cocos2d::Ref *pSender);

	char *fontToUTF8(const char* font);//×ª»»¸ñÊ½
	cocos2d::Label * createLabel(const char * text);
	cocos2d::Menu* createText();

	void onEnter();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);
};