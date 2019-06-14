#pragma once
#include "cocos2d.h"
#include "Util/AnimationLoader.h"
#include "SpriteBase.h"

class SkillBase:public cocos2d::Sprite, public AnimationLoader
{
public:
	static SkillBase* create(SpriteBase* attacker, const std::string& spriteName,const std::string& animationName,
		int animationNum ,int delay,int color,float damage);

	bool init(SpriteBase* attacker, const std::string& animationName, int animationNum, int delay,int color, float damage);
	void initAnimation(const std::string&animationName,int animationNum);
	void collisionDetection();
	void remove();

private:
	float _damage;
	int _color;
	SpriteBase* _attacker;

	std::string _animationName;
	void killedTarget(SpriteBase*target);
};

