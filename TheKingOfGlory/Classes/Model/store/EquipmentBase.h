#pragma once

#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Util/AnimationLoader.h"
#include "../SpriteBase.h"

class EquipmentBase:public Sprite
{
public:


protected:
	float _addHP;

	float _minusAttackInterval;
	float _addDamage;
	float _addDefend;

	float _addCritOdds;
	float _addCritDamage;

	float _addMoneyPerSecond;
	float _addHPPerSecond;

	float _addSpeed;
};
