#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "SpriteBase.h"

USING_NS_CC;
using namespace ui;

class SpriteBase;

//默认属性值
const float SPEED = 10.0;

//子弹的zorder
const int BULLET_ZORDER = 10;

class BulletBase :public cocos2d::Sprite, public AnimationLoader
{
public:
	
	void setSpeed(float speed) { _speed = speed; }
	float getSpeed() { return _speed; }

	float getDamege() { return _damage; }
	void setDamage(float damage) { _damage = damage; }

	void setColor(int color) { _color = color; }
	int getColor() { return _color; }

	void setAnimationName(std::string animationName) { _animationName = animationName; }
	std::string getAnimationName() { return _animationName; }

	void setAttack(SpriteBase* attacker) { _attacker = attacker; }
	SpriteBase* getAttack() { return _attacker; }

	void setBeAttack(SpriteBase* beAttacker) { _beAttacker = beAttacker; }
	SpriteBase* getBeAttack() { return _beAttacker; }


	static bool removeFromMap(BulletBase*bullet);
	
	void move();

	bool collisionDetection();

	static BulletBase* create(SpriteBase*attacker, SpriteBase*beAttacker,const std::string& animationName,const std::string& spriteName, float speed = SPEED);

	static void initAnimation(const std::string& animationName, BulletBase*bullet);

	bool init(SpriteBase*attacker, SpriteBase*beAttacker, const std::string& animationName, float speed);

private:
	float _speed;
	float _damage;
	float _times;
	int _color;

	Sprite* _bullet;

	SpriteBase* _attacker;
	SpriteBase* _beAttacker;

	

	std::string _animationName;
	
};