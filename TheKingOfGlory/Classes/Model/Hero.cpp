#include"Hero.h"
#include<ctime>
#include<cmath>
#include"GameMap.h"

USING_NS_CC;


Warrior* Warrior::createWarrior(const std::string& id, int role, int color)
{
	auto warrior = new(std::nothrow) Warrior();
	if (warrior&&warrior->initWithRole(0, color))
	{
		warrior->id = id;
		warrior->autorelease();
		return warrior;
	}
	CC_SAFE_DELETE(warrior);

	warrior->initWithRole(0, color);
	warrior->init(0, color);
	if(warrior->init(0,color)&&warrior->initWithRole(0,color))
		return nullptr;
}

bool Warrior::launchSkill()
{
	stopMove();
	int skillType;
	//判断调用了哪个技能？在GameController里面
	for (int i = 0; i <= 3; i++) {
		if (GameController::getSkillList().at(i)->isOn())
		{
			skillType = i;
			break;
		}
	}

	switch (skillType)
	{
	case 1:
		setStatus(Status::SKILL1); break;
	case 2:
		setStatus(Status::SKILL2); break;
	case 3:
		setStatus(Status::SKILL3); break;
	}
	for (int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
		{
			auto target = _attackTargetList.at(i);
			target->beAttack(this->getDamage() + WARRIOR_DAMAGE);//beAttack考虑damage, 加大伤害
		}
	}
	auto sequence = Sequence::create(DelayTime::create(0.8f), CallFunc::create([=]() {
		this->setStatus(Status::STANDING);
	}), NULL);
	this->runAction(sequence);

	return true;
}

void Warrior::stopSkill()
{
	setStatus(Status::STANDING);
}

Archer* Archer::createArcher(const std::string& id, int role, int color)
{
	auto archer = new(std::nothrow) Archer();
	if (archer&&archer->initWithRole(1, color))
	{
		archer->id = id;
		archer->autorelease();
		return archer;
	}
	CC_SAFE_DELETE(archer);

	archer->initWithRole(1, color);
	archer->init(1, color);
	if (archer->init(1, color) && archer->initWithRole(1, color))
		return nullptr;
}

bool Archer::launchSkill()
{
	stopMove();
	int skillType;
	for (int i = 0; i <= 3; i++) {
		if (GameController::getSkillList().at(i)->isOn())
		{
			skillType = i;
			break;
		}
	}

	switch (skillType)
	{
	case 1:
		setStatus(Status::SKILL1); break;
	case 2:
		setStatus(Status::SKILL2); break;
	case 3:
		setStatus(Status::SKILL3); break;
	}
	for (int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
		{
			auto target = _attackTargetList.at(i);
			target->beAttack(this->getDamage() + ARCHER_DAMAGE);
		}
	}
	auto sequence = Sequence::create(DelayTime::create(0.8f), CallFunc::create([=]() {
		this->setStatus(Status::STANDING);
	}), NULL);
	this->runAction(sequence);

	return true;
}

void Archer::stopSkill()
{
	setStatus(Status::STANDING);
}

Mage* Mage::createMage(const std::string& id, int role, int color)
{
	auto mage = new(std::nothrow) Mage();
	if (mage&&mage->initWithRole(2, color))
	{
		mage->id = id;
		mage->autorelease();
		return mage;
	}
	CC_SAFE_DELETE(mage);

	mage->initWithRole(2, color);
	mage->init(2, color);
	if (mage->init(2, color) && mage->initWithRole(2, color))
		return nullptr;
}

bool Mage::launchSkill()
{
	stopMove();
	int skillType;
	for (int i = 0; i <= 3; i++) {
		if (GameController::getSkillList().at(i)->isOn())
		{
			skillType = i;
			break;
		}
	}

	switch (skillType)
	{
	case 1:
		setStatus(Status::SKILL1); break;
	case 2:
		setStatus(Status::SKILL2); break;
	case 3:
		setStatus(Status::SKILL3); break;
	}
	for (int i = _attackTargetList.size() - 1; i >= 0; i--)
	{
		if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
		{
			auto target = _attackTargetList.at(i);
			target->beAttack(this->getDamage() + MAGE_DAMAGE);
		}
	}
	auto sequence = Sequence::create(DelayTime::create(0.8f), CallFunc::create([=]() {
		this->setStatus(Status::STANDING);
	}), NULL);
	this->runAction(sequence);

	return true;
}

void Mage::stopSkill()
{
	setStatus(Status::STANDING);
}