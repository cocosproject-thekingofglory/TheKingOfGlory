#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"Model/SpriteBase.h"
#include"Model/Player.h"
#include"Model/Skill.h"
#include"Controller/GameController.h"

USING_NS_CC;

const float WARRIOR_DAMAGE = 10.0;
const float ARCHER_DAMAGE = 8.0;
const float MAGE_DAMAGE = 12.0;

class Warrior :public Player
{
public:
	static Warrior* createWarrior(const std::string& id, int role, int color);

	virtual bool launchSkill();
	virtual void stopSkill();

private:
	std::string id;
};

class Archer :public Player
{
public:
	static Archer* createArcher(const std::string& id, int role, int color);

	virtual bool launchSkill();
	virtual void stopSkill();

private:
	std::string id;
};

class Mage :public Player
{
public:
	static Mage* createMage(const std::string& id, int role, int color);

	virtual bool launchSkill();
	virtual void stopSkill();

private:
	std::string id;
};