#include"Hero.h"
#include "Model/SkillBase.h"
#include "Model/GameMap.h"

USING_NS_CC;


Warrior* Warrior::create(const std::string& id, int color)
{
	auto warrior = new(std::nothrow) Warrior();
	if (warrior&&warrior->initWithRole(0, color))
	{
		warrior->_id = id;
		warrior->autorelease();
		return warrior;
	}
	CC_SAFE_DELETE(warrior);
	return nullptr;
}

bool Warrior::init(int role, int color)
{
	if (!Player::init(role, color))
		return false;


	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 10,10,8,7,4,14,7,14 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
	//��ĳһ������,���ض�����delayҲ��Ҫ���ǣ���ֹ0.2f
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	if (getColor() == RED)
		setDirection(Direction::RIGHTUP);
	else
		setDirection(Direction::LEFTDOWN);
	setStatus(Player::Status::STANDING);

	return true;
}

void Warrior::skill1()
{
	if (_isSkill&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
			{
				auto target = _attackTargetList.at(i);
				target->beAttack(Damage::SKILL1);

			}
		}
		auto sequence = Sequence::create(DelayTime::create(1.4f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);

		}), NULL);
		this->runAction(sequence);
	}
}

void Warrior::skill2()
{
	if (_isSkill&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
			{
				auto target = _attackTargetList.at(i);
				target->beAttack(Damage::SKILL2);

			}
		}
		auto sequence = Sequence::create(DelayTime::create(0.7f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Warrior::skill3()
{
	if (_isSkill&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
			{
				auto target = _attackTargetList.at(i);
				target->beAttack(Damage::SKILL3);

			}
		}
		auto sequence = Sequence::create(DelayTime::create(1.4f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}


Aviator* Aviator::create(const std::string& id, int color)
{
	auto aviator = new(std::nothrow) Aviator();
	if (aviator&&aviator->initWithRole(1, color))
	{
		aviator->_id = id;
		aviator->autorelease();
		return aviator;
	}
	CC_SAFE_DELETE(aviator);
	return nullptr;
}

bool Aviator::init(int role, int color)
{
	if (!Player::init(role, color))
		return false;


	std::string animationNames[] = { "move","move","attack","dead","behit","skill3","skill2","skill1" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 8,8,8,2,5,13 ,8,16};
	_animationFrameNum.assign(animationNum, animationNum + 8);
	for (int i = 1; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	if (getColor() == RED)
		setDirection(Direction::RIGHTUP);
	else
		setDirection(Direction::LEFTDOWN);
	setStatus(Player::Status::STANDING);

	return true;
}

void Aviator::skill2()
{
	if (_isSkill&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		auto skill = SkillBase::create("skillbone (1).png","skillbone",16,3.0f,getColor(),Damage::SKILL2);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::One;
		pos.y += ds[(int)getDirection()][1] * Radius::One;
		skill->setPosition(pos);


		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Aviator::skill3()
{
	if (_isSkill&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		for (int i = 0; i < 8; i++)
		{
			auto skill = SkillBase::create("skillstab (1).png", "skillstab", 17, 3.0f, getColor(), Damage::SKILL2);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += ds[i][0] * Radius::Two;
			pos.y += ds[i][1] * Radius::Two;
			skill->setPosition(pos);

		}

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL3))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Aviator::skill1()
{
	if (_isSkill&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create("skillring (1).png", "skillring", 5, 5.0f, getColor(), Damage::SKILL1);
		GameMap::getCurrentMap()->addSprite(skill);
		skill->setPosition(this->getPosition());
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		float dx = ds[(int)getDirection()][0] * Radius::Three;
		float dy = ds[(int)getDirection()][1] * Radius::Three;
		skill->runAction(MoveBy::create(5.0f, Vec2(dx, dy)));

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL1))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}


Mage* Mage::create(const std::string& id, int color)
{
	auto mage = new(std::nothrow) Mage();
	if (mage&&mage->initWithRole(2, color))
	{
		mage->_id = id;
		mage->autorelease();
		return mage;
	}
	CC_SAFE_DELETE(mage);
	return nullptr;

}

bool Mage::init(int role, int color)
{
	return false;
}

void Mage::skill1()
{
}

void Mage::skill2()
{
}

void Mage::skill3()
{
}
