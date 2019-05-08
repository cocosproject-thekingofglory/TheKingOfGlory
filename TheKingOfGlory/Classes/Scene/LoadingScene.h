#pragma once
#include "cocos2d.h"

class LoadingScene:public cocos2d::Layer
{
private:
	cocos2d::Size visible_Size;
	int sourceCount;
	cocos2d::ProgressTimer* progress;
	float progress_Interval;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	void createBackground();
	void createProgressBar();
	void loadMusic(cocos2d::ValueVector musicFiles);
	void loadEffect(cocos2d::ValueVector effectFiles);
	void loadSpriteSheets(cocos2d::ValueVector spriteFiles);
	void progressUpdate();
	CREATE_FUNC(LoadingScene);
};

