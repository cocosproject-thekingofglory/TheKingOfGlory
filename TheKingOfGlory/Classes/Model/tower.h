#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"

USING_NS_CC;
using namespace ui;

const int RED = 1, BULE = 2;

const int attackGrade = 4;
const int SOLDIER = 2, HERO = 1, ACTIVE_HERO = 3;

class Tower :public cocos2d::Sprite, public AnimationLoader
{
public:
	bool init() {};

	void setColor(int color) { _color = color; }
	int getColor() { return _color; }

	int getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }

	LoadingBar* getHP() { return _HP; }
	void setHP(LoadingBar* HP) { _HP = HP; }

	void setAttackRadius(float radius) { _attackRadius = radius; }
	int getAttackRadius() { return _attackRadius; }

	void setHPInterval(float HPInterval) { _HPInterval = HPInterval; }
	float getHPInterval() { return _HPInterval; }

	int getLifeValue() { return _lifeValue; }
	void setLifeValue(int lifeValue) { _lifeValue = lifeValue; }

	void setVec2(Vec2 vec2) { _towerPosition = vec2; }
	//Vec2 getVec2() { return _vec2; }

	static Tower* createWithSpriteFrameName(const std::string& filename);

	void attack();

	bool insideAttack(Vec2 enemyPosition);

	CREATE_FUNC(Tower);

private:

	int _lifeValue;
	LoadingBar* _HP;
	float _HPInterval;
	int _color;
	float _damage;
	float _attackRadius;

	Vector<Sprite*> attackTarget[attackGrade];

	void initAnimation();
	
	Vec2 _towerPosition;

};