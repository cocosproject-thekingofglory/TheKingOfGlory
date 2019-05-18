#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "SpriteBase.h"

USING_NS_CC;
using namespace ui;


//ƒ¨»œ Ù–‘÷µ
const float SPEED = 10.0;



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

	void setBullet(Sprite*bullet) { _bullet = bullet; }
	Sprite* getBullet() { return _bullet; }

	SpriteBase* getAttack() { return _attacker; }

	void setBeAttack(SpriteBase*beAttacker) { _beAttacker = beAttacker; }
	SpriteBase* getBeAttack() { return _beAttacker; }

	bool init();

	static bool removeFromMap(BulletBase*bullet);
	
	void move();

	bool collisionDetection();

	static void create(SpriteBase*attacker, SpriteBase*beAttacker, std::string animationName, std::string spriteName, float speed = SPEED);

	static void initAnimation(std::string animationName, BulletBase*bullet);

	//static Vector<BulletBase*> bulletList[2];

	CREATE_FUNC(BulletBase);

private:
	float _speed;
	float _damage;
	int _color;

	Sprite* _bullet;

	SpriteBase* _attacker;
	SpriteBase* _beAttacker;

	

	std::string _animationName;
	
};