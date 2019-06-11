#include "Tower.h"
#include "GameMap.h"
#include "UI/Tip.h"

Tower* Tower::createWithSpriteFrameName(const std::string& filename,int color)
{
	auto tower = new Tower();
	if (tower&&tower->initWithSpriteFrameName(filename)&& tower->init(color))
	{
		tower->autorelease();
		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}

bool Tower::init(int color)
{
	setAnchorPoint(Vec2::ZERO);
	setColor(color);
	if (_type == TOWER)
	{
		setAttackRadius(TOWER_ATTACK_RADIUS);
		setHPValue(TOWER_HPVALUE);
		setNowHPValue(TOWER_HPVALUE);
		setDamage(TOWER_DAMAGE);
		setAttackInterval(TOWER_ATTACK_INTERVAL);
		setDefend(TOWER_DEFEND);
		setKillExperience(TOWER_KILL_EXPRIENCE);
		setKillMoney(TOWER_KILL_MONEY);
	}
	else
	{
		setAttackRadius(BUFF_ATTACK_RADIUS);
		setHPValue(BUFF_HPVALUE);
		setNowHPValue(BUFF_HPVALUE);
		setDamage(BUFF_DAMAGE);
		setAttackInterval(BUFF_ATTACK_INTERVAL);
		setDefend(BUFF_DEFEND);
		setKillExperience(BUFF_KILL_EXPRIENCE);
		setKillMoney(BUFF_KILL_MONEY);
	}

	initAnimation();
	setHPBar();
	return true;
}

void Tower::initAnimation()
{
	loadAnimation("blast",0.1f, 8);
}

bool Tower::attack()
{
	for (int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
		{
			auto target = _attackTargetList.at(i);
			auto bullet=BulletBase::create(this, target, "bullet", "bullet (1).png");
			GameMap::getCurrentMap()->addChild(bullet);
			bullet->setPosition(getPosition());
			Vec2 pos = Vec2(getPosition().x + getContentSize().width*getScale() / 2,
				getPosition().y + getContentSize().height*getScale() / 2);
			bullet->setPosition(pos);
			return true;
		}
	}
	return false;
}

float Tower::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	
	nowHP -= damage * (1 - this->getDefend());

	std::string stip;
	stip.append(StringUtils::format("- %.1f", damage*(1 - this->getDefend())));
	auto tip = Tip::create(stip, 1.0, Color4B::RED, 24, "fonts/arial.ttf");
	tip->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	Vec2 to = Vec2(this->getContentSize().width / 2, this->getContentSize().height);
	auto moveup = MoveTo::create(1.0, to);
	tip->runAction(moveup);
	tip->setScale(1.0/this->getScale());
	this->addChild(tip);

	if (nowHP <= 0.0)
	
	{
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
		//playDestoryAnimation();
	}
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	return nowHP;

}

void Tower::destroy()
{
	runAnimation("blast",this);
}


void Tower::setHPBar()
{
	if(getColor()==BLUE)
		_HPBar = LoadingBar::create("Pictures/GameItem/blueBar.png");
	else
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");

	_HPBar->setScale(0.4);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(100);
	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.05);
	_HPBar->setPosition(HPpos);
	this->addChild(_HPBar);

}


void Tower::updateHPBar()
{
	if (_HPBar != NULL)
	{
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}
}


bool Tower::insideAttack(SpriteBase*beAttacker)
{
	Vec2 towerPos = this->getPosition(), pos = beAttacker->getPosition();
	float dx = towerPos.x - pos.x, dy = towerPos.y - pos.y;
	return dx * dx + dy * dy <= getAttackRadius()*getAttackRadius();

}
