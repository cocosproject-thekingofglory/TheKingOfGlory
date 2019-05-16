#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"

USING_NS_CC;
using namespace ui;

//���������أ����̵꣩����λ��
const Vec2 RED_STORE = Vec2(10.0, 10.0);
const Vec2 BLUE_STORE = Vec2(150.0, 150.0);

const int RED = 0, BLUE = 1;

//��������������ȼ�
const int attackGrade = 3;
const int SOLDIER = 1, HERO = 0, ACTIVE_HERO = 2;

class SpriteBase :public cocos2d::Sprite, public AnimationLoader
{
public:
	enum Type
	{
		Player, Soldier
	};

	virtual bool init();
	//����
	void setType(Type type) { _type = type; };
	Type getType() { return _type; };
	//��Ӫ
	void setColor(int color) { _color = color; }
	int getColor() { return _color; }
	//�˺�
	int getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }
	//Ѫ��
	LoadingBar* getHPBar() { return _HPBar; }
	virtual void setHPBar() {};
	//������Χ
	void setAttackRadius(float radius) { _attackRadius = radius; }
	int getAttackRadius() { return _attackRadius; }
	//��ǰѪ��
	void setNowHPValue(float nowHPValue) { _nowHPValue = nowHPValue; }
	float getNowHPValue() { return _nowHPValue; }
	//��Ѫ��
	float getHPValue() { return _HPValue; }
	void setHPValue(float HPValue) { _HPValue = HPValue; }
	//λ��
	//���ι����ļ��(/֡)
	void setAttackInterval(int attackInterval) { _attackInterval = attackInterval; }
	int getAttackInterval() { return _attackInterval; }

	static SpriteBase* createWithSpriteFrameName(const std::string& filename);

	virtual void updateHPBar(){}

	virtual bool attack() { return true; }

	virtual void addBeAttackTarget(SpriteBase*enemy) { _beAttackTargetList.pushBack(enemy); };

	Vector<SpriteBase*> getBeAttackTarget() { return _beAttackTargetList; }

	virtual void addAttackTarget(SpriteBase* attackTarget) { _attackTargetList.pushBack(attackTarget); }

	Vector<SpriteBase*> getAttackTarget() { return _attackTargetList; }

	virtual float beAttack(const float damage) { return 0.0; }

	virtual void initAnimation() {};

	CREATE_FUNC(SpriteBase);

protected:

	LoadingBar* _HPBar=NULL;
	Vector<SpriteBase*> _beAttackTargetList;
	Vector<SpriteBase*> _attackTargetList;

private:
	Type _type;

	float _HPValue;
	
	float _nowHPValue;
	int _color;
	float _damage;
	float _attackRadius;

	int _attackInterval;

	Vec2 _position;
};