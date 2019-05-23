#pragma once
#include "cocos2d.h"
#include "../Model/GameMap.h"
#include "Manager/Manager.h"

class GameController:public cocos2d::Layer
{
public:
	Manager* manager = Manager::getInstance();
	virtual bool init();
	CREATE_FUNC(GameController);

	void setMap(GameMap* map);
	void initGame(float delta);

private:
	GameMap* map;


	void createTouchListener();
	void createKeyListener();
	void onEnter();
	void update(float delta);
	void isResult(float delta);
	void toOver(cocos2d::EventCustom* event);

};

