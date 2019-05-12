#pragma once
#include "cocos2d.h"
#include "../Model/GameMap.h"

class GameController:public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameController);

	void setMap(GameMap* map);
	void initGame();

private:
	GameMap* map;

	void createTouchListener();
	void createKeyListener();
	void onEnter();

};

