#include "Soldier.h"
#include "Model/GameMap.h"
#include <cmath>

bool Soldier::init()
{
	/*if (!SpriteBase::init())
	{
		return false;
	}*/
	setType(SpriteBase::Type::SOLDIER);
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
		auto position = this->getPosition();
		if (position.equals(_destination))
			randomDestination();
		int flagX = (position.x < _destination.x) ? 1 : -1, flagY = (position.y < _destination.y) ? 1 : -1;
		this->setFlippedX(!(position.x <= _destination.x));
		float dx = flagX * MIN(getSpeed(), fabs(_destination.x - position.x));
		float dy = flagY * MIN(getSpeed(), fabs(_destination.y - position.y));
		
		Vec2 target = Vec2(position.x + dx, position.y + dy);
		auto map = GameMap::getCurrentMap();

		if (map->isCanAssess(map->positionToTileCoord(target)))
			this->setPosition(target);
		else
			randomDestination();
	}

}

void Soldier::randomDestination()
{
	float dx = rand() % 400 - 200;
	float dy = rand() % 400 - 200;
	setDestination(Vec2(getPositionX() + dx, getPositionY() + dy));
}

void Soldier::startMove()
{
	if (_isMove)
	{
		Vec2 toPosition;
		/*if (this->getColor() == RED)toPosition = BLUE_STORE;
		else toPosition = RED_STORE;*/
		if(getColor()==BLUE)
			toPosition = Vec2(500,500);
		else
			toPosition = Vec2(6000, 6000);
		runAnimation("soldierMove", this);
		_destination = toPosition;
		auto position = this->getPosition();
		schedule(CC_CALLBACK_0(Soldier::move,this),"move");
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
				/*switch (_attackTargetList.at(i)->getType())
				{
				case SpriteBase::PLAYER:
				{
					auto target = dynamic_cast<Player*>(_attackTargetList.at(i));
					target->beAttack(this->getDamage());
					log("\nPlayer be hit\n");
					return true;
				}
				break;
				case SpriteBase::SOLDIER:
				{
					auto target = dynamic_cast<Soldier *>(_attackTargetList.at(i));
					target->beAttack(this->getDamage());
					return true;
				}
				break;
				}*/
				auto target = _attackTargetList.at(i);
				target->beAttack(this->getDamage());
				return true;
			}
			else
			{

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
	_HPBar = LoadingBar::create("Pictures/GameItem/planeHP.png");

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


Soldier* Soldier::createWithSpriteFrameName(const std::string& filename)
{
	auto sprite = new Soldier();
	if (sprite&&sprite->initWithSpriteFrameName(filename)&&sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}