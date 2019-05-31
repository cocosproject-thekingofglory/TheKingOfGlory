#pragma once
#include "cocos2d.h"
#include "../Model/GameMap.h"
#include "Manager/Manager.h"
#include "Model/Skill.h"

class GameController:public cocos2d::Layer
{
public:
	Manager* manager = Manager::getInstance();
	virtual bool init();
	CREATE_FUNC(GameController);

	void setMap(GameMap* map);
	void initGame(float delta);
	static cocos2d::Vector<Skill*>& getSkillList() { return _skillList; }

private:
	GameMap* map;

	static cocos2d::Vector<Skill*> _skillList;
	cocos2d::EventListenerTouchOneByOne* touchListener;
	cocos2d::EventListenerKeyboard* keyListener;

	void createTouchListener();
	void createKeyListener();
	void addSkill();
	void onEnter();
	void update(float delta);
	void isResult(float delta);
	void toOver(cocos2d::EventCustom* event);
	
};

