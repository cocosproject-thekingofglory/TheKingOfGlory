#include "Model/GameMap.h"
#include "GUnCar.h"
#include "UI/Tip.h"
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

	setScale(0.2);

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
	loadAnimation("guntruck_move_rightdown", delay, 8);

	loadAnimation("guntruck_attack_rightdown", delay, 11);

}

void GunCar::move()
{
	Soldier::move();
	this->setRotation((isFlipped) ? (0) : (-45.0));

}

void GunCar::startMove()
{
	if (_isMove)
	{
		runAnimation("guntruck_move_rightdown", this);
		schedule(CC_CALLBACK_0(GunCar::move, this), 0.05f, "move");
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
		runAnimation("guntruck_attack_rightdown", this);
		setStatus(Status::ATTACKING);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() > 0.0)
			{
				auto target = _attackTargetList.at(i);
				auto bullet = BulletBase::create(this, target, "bullet", "bullet (1).png");
				GameMap::getCurrentMap()->addChild(bullet);
				Vec2 pos = Vec2(getPosition().x + getContentSize().width*getScale() / 2, getPosition().y + getContentSize().height*getScale() / 2);
				bullet->setPosition(getPosition());
				return true;
			}
		}
	}
	return false;
}

void GunCar::stopAttack()
{
	stopAnimation("guntruck_attack_rightdown", this);
}

float GunCar::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
  
	nowHP -= damage * (1 - this->getDefend());
	std::stringstream str;
	str << damage * (1 - this->getDefend());
	std::string s = "-" + str.str();
	auto text = Tip::create(s, 0.1f, cocos2d::Color4B::RED);
	text->setPosition(Vec2(this->getContentSize().width*getScale() *0.8,
		this->getContentSize().height*getScale()*1.2));
	text->setScale(1.0/this->getScale());
	addChild(text);

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

	_HPBar->setPercent(100);
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
