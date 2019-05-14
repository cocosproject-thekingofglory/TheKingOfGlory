#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SpriteBase.h"

USING_NS_CC;
using namespace ui;


class Tower :public SpriteBase
{
public:
	Tower* createWithSpriteFrameName(const std::string& filename);

	CREATE_FUNC(Tower);

	virtual bool init();

	virtual bool attack();
	virtual float beAttack(const float damage);

	virtual bool beDestory();

	void setHPBar();
	void updateHPBar();

	void initAnimation();

private:

	Sprite* _bullet;
};