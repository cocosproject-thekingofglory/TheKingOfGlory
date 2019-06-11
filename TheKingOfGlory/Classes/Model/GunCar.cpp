#include "Model/GameMap.h"
#include "GUnCar.h"
#include <cmath>

bool GunCar::init(int color)
{
	/*if (!SpriteBase::init())
	{
		return false;
	}*/
	setColor(color);
	setStatus(Status::STANDING);
	setAttackRadius(GUNCAR_ATTACK_RADIUS);
	setHPValue(GUNCAR_HPVALUE);
	setNowHPValue(GUNCAR_HPVALUE);
	setDamage(GUNCAR_DAMAGE);
	setAttackInterval(GUNCAR_ATTACK_INTERVAL);
	setSpeed(GUNCAR_MOVE_SPEED);
	setDefend(GUNCAR_DEFEND);

	setKillExperience(GUNCAR_KILL_EXPRIENCE);
	setKillMoney(GUNCAR_KILL_MONEY);

	setScale(2);

	initAnimation();
	setHPBar();
	//_soldier = Sprite::createWithSpriteFrameName("soldierMove_01.png");

	//_bullet = Sprite::createWithSpriteFrameName("soldierBullet.png");
	//_bullet->setVisible(false);

	return true;
}

void GunCar::initAnimation()
{
	/*
	动画命名wei"move_01.png"
	*/

	const float delay = 0.1;
	loadAnimation("soldierMove", delay, 8);

	loadAnimation("soldierAttack", delay, 8);

}

void GunCar::move()
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

void GunCar::startMove()
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
		schedule(CC_CALLBACK_0(Soldier::move, this), 0.05f, "move");
		setStatus(Status::MOVING);
	}
}

void GunCar::stopMove()
{
	//stopAnimation("soldierMove",this);
	unschedule("move");
}

bool GunCar::attack()
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
				auto bullet = BulletBase::create(this, target, "bullet", "bullet (1).png");
				GameMap::getCurrentMap()->addChild(bullet);
				Vec2 pos = Vec2(getPosition().x + getContentSize().width / 2, getPosition().y + getContentSize().height / 2);
				bullet->setPosition(pos);
				return true;
			}
		}
	}
	return false;
}

void GunCar::stopAttack()
{
	stopAnimation("soldierAttack", this);
}

float GunCar::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage * (1 - this->getDefend());

	/*std::string stip;
	stip.append(StringUtils::format("- %.1f", damage*(1 - this->getDefend())));
	auto tip = Tip::create(stip, 1.0, Color4B::RED);
	tip->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	this->addChild(tip);*/

	if (nowHP <= 0.0)
	{
		//停止动画，并在能攻击它的小兵的列表中删除它
		stopMove();
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
	}
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	return nowHP;
}

void GunCar::setHPBar()
{
	if (getColor() == RED)
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");
	else if (getColor() == BLUE)
		_HPBar = LoadingBar::create("Pictures/GameItem/greenBar.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(0);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}

void GunCar::updateHPBar()
{
	if (_HPBar != NULL)
	{
		log("Percent:%f", 100.0*getNowHPValue() / getHPValue());
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}
}


GunCar* GunCar::createWithSpriteFrameName(const std::string& filename, int color)
{
	auto sprite = new GunCar();
	if (sprite&&sprite->initWithSpriteFrameName(filename) && sprite->init(color))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool GunCar::insideAttack(SpriteBase*beAttacker)
{
	Vec2 towerPos = this->getPosition(), pos = beAttacker->getPosition();
	float dx = towerPos.x - pos.x, dy = towerPos.y - pos.y;
	return dx * dx + dy * dy <= getAttackRadius()*getAttackRadius();
}