#pragma once
#include "cocos2d.h"
#include "../Model/GameMap.h"
#include "../Model/Soldier.h"

class GameController:public cocos2d::Layer
{
public:
	Soldier* soldier;
	virtual bool init();
	CREATE_FUNC(GameController);

	void setMap(GameMap* map);
	void initGame();

private:
	GameMap* map;


	void createTouchListener();
	void createKeyListener();
	void onEnter();
	void update(float delta);
	void isResult(float delta);
	void toOver(bool isWin);

};

