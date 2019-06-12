#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "Model/BulletBase.h"
#include "../UI/Tip.h"

USING_NS_CC;
using namespace ui;
class BulletBase;

//红蓝方基地（即商店）所在位置
const Vec2 RED_STORE = Vec2(10.0, 10.0);
const Vec2 BLUE_STORE = Vec2(150.0, 150.0);

const int RED = 0, BLUE = 1, YELLOW = 2;

//被攻击对象的优先级
const int attackGrade = 3;
const int SOLDIER = 1, HERO = 0, ACTIVE_HERO = 2;

class SpriteBase :public cocos2d::Sprite, public AnimationLoader
{
public:

	enum TYPE
	{
		REDBUFF, BLUEBUFF, TOWER, STORE,OTHER
	};

	void setType(TYPE type) { _type = type; }
	TYPE getType() { return _type; }
	TYPE _type = OTHER;

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

	void setDefend(float defend) { _defend = defend; }
	float getDefend() { return _defend; }
	//击杀经验
	void setKillExperience(int killExperience) { _killExperience = killExperience; }
	int getKillExperience() { return _killExperience; }
	//击杀金钱
	void setKillMoney(int killMoney) { _killMoney = killMoney; }
	int getKillMoney() { return _killMoney; }
	//武器装备
	void addDefend(float add) { _defend += add; }
	void addDamage(float add) { _damage += add; }
	void addHPValue(float add);
	void addNowHPValue(float add);

protected:

	LoadingBar* _HPBar=NULL;
	Vector<SpriteBase*> _beAttackTargetList;
	Vector<SpriteBase*> _attackTargetList;
	Vector<BulletBase*> _beAttackBulletList;

private:


	float _HPValue;
	
	float _nowHPValue;
	int _color;
	float _damage;
	float _attackRadius;
	float _defend;//伤害等于damage*(1-defend)

	int _attackInterval;

	Vec2 _position;

	int _killExperience;
	int _killMoney;

};