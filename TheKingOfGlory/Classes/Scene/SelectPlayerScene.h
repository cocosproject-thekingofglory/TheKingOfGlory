#pragma once
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Model/Player.h"
#include"Scene/GameScene.h"


class SelectPlayerScene :public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;

public:
	static cocos2d::Scene* createScene();


	virtual bool init();
	void yaseCallback(cocos2d::Ref* pSender);
	void houyiCallback(cocos2d::Ref* pSender);
	void dajiCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(SelectPlayerScene);
};