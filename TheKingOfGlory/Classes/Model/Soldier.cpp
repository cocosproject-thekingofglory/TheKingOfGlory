#include "Soldier.h"
#include "Model/GameMap.h"
#include <cmath>

bool Soldier::init(int color)
{
	/*if (!SpriteBase::init())
	{
		return false;
	}*/
	setColor(color);
	setStatus(Status::STANDING);
	setAttackRadius(SOLDIER_ATTACK_RADIUS);
	setHPValue(SOLDIER_HPVALUE);
	setNowHPValue(SOLDIER_HPVALUE);
	setDamage(SOLDIER_DAMAGE);
	setAttackInterval(SOLDIER_ATTACK_INTERVAL);
	setSpeed(SOLDIER_MOVE_SPEED);

	initAnimation();
	setHPBar();
	//_soldier = Sprite::createWithSpriteFrameName("soldierMove_01.png");

	//_bullet = Sprite::createWithSpriteFrameName("soldierBullet.png");
	//_bullet->setVisible(false);
	
	return true;
}

void Soldier::initAnimation()
{
	/*
	动画命名wei"move_01.png"
	*/

	const float delay = 0.1;
	loadAnimation("soldierMove", delay, 8);

	loadAnimation("soldierAttack", delay, 8);

}

void Soldier::move()
{
	if (getStatus() == Status::MOVING)
	{
		//直线移动，遇到障碍物则在小范围内随机移动，再继续向目的地移动

		auto position = this->getPosition();

		if (position.equals(getBigDestination()))
		{
			randomBigDestination();
		}

		if (position.equals(getSmallDestination()))
		{
			setSmallDestination(getBigDestination());
		}

		Vec2 smallDestination = getSmallDestination();

		int flagX = (position.x < smallDestination.x) ? 1 : -1, flagY = (position.y < smallDestination.y) ? 1 : -1;

		this->setFlippedX(!(position.x <= _destination.x));

		float dx = flagX * MIN(getSpeed(), fabs(smallDestination.x - position.x));
		float dy = flagY * MIN(getSpeed(), fabs(smallDestination.y - position.y));


		Vec2 target = Vec2(position.x + dx, position.y + dy);

		auto map = GameMap::getCurrentMap();

		if (map->isCanAssess(map->positionToTileCoord(target)))
		{
			this->setPosition(target);
		}
		else
		{
			randomSmallDestination();
		}
	}

}

void Soldier::randomSmallDestination()
{
	float dx = rand() % 200 - 100;
	float dy = rand() % 200 - 100;
	setSmallDestination(Vec2(getPositionX() + dx, getPositionY() + dy));
}

void Soldier::randomBigDestination()
{
	float dx = rand() % 400 - 200;
	float dy = rand() % 400 - 200;
	setBigDestination(Vec2(getPositionX() + dx, getPositionY() + dy));
}

void Soldier::startMove()
{
	if (_isMove)
	{
		srand(time(NULL));
		Vec2 toPosition;
		/*if (this->getColor() == RED)toPosition = BLUE_STORE;
		else toPosition = RED_STORE;*/
		if (getColor() == BLUE)
			toPosition = GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Tower_Red);
		else
			toPosition = GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Tower_Blue);
		runAnimation("soldierMove", this);
		this->setBigDestination(toPosition);
		schedule(CC_CALLBACK_0(Soldier::move,this),0.05f,"move");
		setStatus(Status::MOVING);
	}
}

void Soldier::stopMove()
{
	//stopAnimation("soldierMove",this);
	unschedule("move");
}

bool Soldier::attack()
{
	if (_attackTargetList.size())
	{
		runAnimation("soldierAttack", this);
		setStatus(Status::ATTACKING);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() > 0.0)
			{
			
				auto target = _attackTargetList.at(i);
				target->beAttack(this->getDamage());
				return true;
			}
		}
	}
	
	return false;
}

void Soldier::stopAttack()
{
	stopAnimation("soldierAttack",this);
}

float Soldier::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage;
	if (nowHP <= 0.0)
	{
		//停止动画，并在能攻击它的小兵的列表中删除它
		stopMove();
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this,false);
		}
	}
	setNowHPValue(MAX(nowHP,0));
	updateHPBar();
	return nowHP;
}

void Soldier::setHPBar()
{
	if(getColor()==RED)
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");
	else if(getColor()==BLUE)
		_HPBar = LoadingBar::create("Pictures/GameItem/greenBar.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);
	
	_HPBar->setPercent(0);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}

void Soldier::updateHPBar()
{
	if (_HPBar != NULL)
	{
		log("Percent:%f", 100.0*getNowHPValue() / getHPValue());
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}
}


Soldier* Soldier::createWithSpriteFrameName(const std::string& filename,int color)
{
	auto sprite = new Soldier();
	if(sprite&&sprite->initWithSpriteFrameName(filename)&&sprite->init(color))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}