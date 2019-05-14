#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"

USING_NS_CC;
using namespace ui;

const int RED = 0, BULE = 1;

//被攻击对象的优先级
const int attackGrade = 4;
const int SOLDIER = 2, HERO = 1, ACTIVE_HERO = 3;

class SpriteBase :public cocos2d::Sprite, public AnimationLoader
{
public:
	virtual bool init();

	void setColor(int color) { _color = color; }
	int getColor() { return _color; }

	int getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }

	LoadingBar* getHPBar() { return _HPBar; }
	virtual void setHPBar() {};

	void setAttackRadius(float radius) { _attackRadius = radius; }
	int getAttackRadius() { return _attackRadius; }

	void setNowHPValue(float nowHPValue) { _nowHPValue = nowHPValue; }
	float getNowHPValue() { return _nowHPValue; }

	float getHPValue() { return _HPValue; }
	void setHPValue(float HPValue) { _HPValue = HPValue; }

	void setVec2(Vec2 vec2) { _position = vec2; }
	Vec2 getVec2() { return _position; }

	static SpriteBase* createWithSpriteFrameName(const std::string& filename);

	virtual void attack() {}

	bool insideAttack(Vec2 enemyPosition);

	virtual void initAnimation();

	CREATE_FUNC(SpriteBase);

protected:

	LoadingBar* _HPBar=NULL;

private:

	float _HPValue;
	
	float _nowHPValue;
	int _color;
	float _damage;
	float _attackRadius;

	Vec2 _position;
};