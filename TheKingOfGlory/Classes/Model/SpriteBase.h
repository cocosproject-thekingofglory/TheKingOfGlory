#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "Model/BulletBase.h"

USING_NS_CC;
using namespace ui;
class BulletBase;

//红蓝方基地（即商店）所在位置
const Vec2 RED_STORE = Vec2(10.0, 10.0);
const Vec2 BLUE_STORE = Vec2(150.0, 150.0);

const int RED = 0, BLUE = 1;

//被攻击对象的优先级
const int attackGrade = 3;
const int SOLDIER = 1, HERO = 0, ACTIVE_HERO = 2;

class SpriteBase :public cocos2d::Sprite, public AnimationLoader
{
public:

	virtual bool init();
	//阵营
	void setColor(int color) { _color = color; }
	int getColor() { return _color; }
	//伤害
	float getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }
	//血条
	LoadingBar* getHPBar() { return _HPBar; }
	virtual void setHPBar() {};
	//攻击范围
	void setAttackRadius(float radius) { _attackRadius = radius; }
	int getAttackRadius() { return _attackRadius; }
	//当前血量
	void setNowHPValue(float nowHPValue) { _nowHPValue = nowHPValue; }
	float getNowHPValue() { return _nowHPValue; }
	//总血量
	float getHPValue() { return _HPValue; }
	void setHPValue(float HPValue) { _HPValue = HPValue; }
	//位置
	//两次攻击的间隔(/帧)
	void setAttackInterval(int attackInterval) { _attackInterval = attackInterval; }
	int getAttackInterval() { return _attackInterval; }

	static SpriteBase* createWithSpriteFrameName(const std::string& filename);

	virtual void updateHPBar(){}
	virtual void updateEXPBar(){}


	virtual bool attack() { return true; }

	virtual void addBeAttackTarget(SpriteBase*enemy) { _beAttackTargetList.pushBack(enemy); };

	Vector<SpriteBase*>& getBeAttackTarget() { return _beAttackTargetList; }

	virtual void addAttackTarget(SpriteBase* attackTarget) { _attackTargetList.pushBack(attackTarget); }

	Vector<SpriteBase*>& getAttackTarget() { return _attackTargetList; }

	virtual void addBeAttackBullet(BulletBase* bullet) { _beAttackBulletList.pushBack(bullet); }

	Vector<BulletBase*>& getBeAttackBullet() { return _beAttackBulletList; }

	virtual float beAttack(const float damage) { return 0; }

	virtual void initAnimation() {};

	CREATE_FUNC(SpriteBase);

protected:

	LoadingBar* _HPBar=NULL;
	LoadingBar* _EXPBar = NULL;
	Vector<SpriteBase*> _beAttackTargetList;
	Vector<SpriteBase*> _attackTargetList;
	Vector<BulletBase*> _beAttackBulletList;

private:


	float _HPValue;
	float _EXPValue = 0.0;
	
	int _nowLevel;
	float _nowHPValue;
	float _nowEXPValue = 0.0;
	int _color;
	float _damage;
	float _attackRadius;

	int _attackInterval;

	Vec2 _position;
};