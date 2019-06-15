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
	setAttackRadius(PLAYER_ATTACK_RADIUS);


	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 10,10,8,7,4,14,7,14 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
	//对某一个动作,加载动作，delay也需要考虑，不止0.2f
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
	if (_isSkill&&getStatus()!=Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create(this,"skilllight (1).png", "skilllight", 18, 3.0f, getColor(), Damage::SKILL1);
		this->addChild(skill, -1);
		auto sequence = Sequence::create(DelayTime::create(1.4f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);

		}), NULL);
		this->runAction(sequence);
	}
}

void Warrior::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		auto skill = SkillBase::create(this, "skillsword (1).png", "skillsword" ,21, 3.0f, getColor(), Damage::SKILL2);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::Two;
		pos.y += ds[(int)getDirection()][1] * Radius::Two;
		skill->setPosition(pos);


		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Warrior::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		{
			auto skill = SkillBase::create(this, "skillfenghuangL (1).png", "skillfenghuangL", 17, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x -= Radius::Three;
			skill->setPosition(pos);
			skill->setScale(1.5);
		}
		{
			auto skill = SkillBase::create(this, "skillfenghuangR (1).png", "skillfenghuangR", 17, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += Radius::Three;
			skill->setPosition(pos);
			skill->setScale(1.5);
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
	setAttackRadius(PLAYER_ATTACK_RADIUS);


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

void Aviator::skill1()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create(this, "skillring (1).png", "skillring", 5, 5.0f, getColor(), Damage::SKILL1);
		GameMap::getCurrentMap()->addSprite(skill);
		skill->setPosition(this->getPosition());
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		float dx = ds[(int)getDirection()][0] * Radius::One;
		float dy = ds[(int)getDirection()][1] * Radius::One;
		skill->runAction(MoveBy::create(5.0f, Vec2(dx, dy)));

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL1))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Aviator::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		auto skill = SkillBase::create(this, "skillbone (1).png","skillbone",16,3.0f,getColor(),Damage::SKILL2);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::Two;
		pos.y += ds[(int)getDirection()][1] * Radius::Two;
		skill->setPosition(pos);


		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Aviator::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		for (int i = 0; i < 8; i++)
		{
			auto skill = SkillBase::create(this, "skillstab (1).png", "skillstab", 17, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += ds[i][0] * Radius::Three;
			pos.y += ds[i][1] * Radius::Three;
			skill->setPosition(pos);

		}

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL3))*0.1f), CallFunc::create([=]() {
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
	if (!Player::init(role, color))
		return false;
	setAttackRadius(Radius::Attack);


	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 11,8,8,10,7,16,17,16 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 4; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	{
		int i = 5;
		for (int j = 4; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}
		i = 7;
		for (int j = 5; j < 7; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}
	}
	{
		int i = 4;
		for (int j = 1; j < 4; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}
		i = 6;
		for (int j = 0; j < 4; j++)
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

void Mage::skill1()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		if (_attackTargetList.size())
		{
			for (int i = _attackTargetList.size() - 1; i >= 0; i--)
			{
				if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
				{
					auto target = _attackTargetList.at(i);
					auto bullet = BulletBase::create(this, target, "skillball", "skillball (1).png");
					GameMap::getCurrentMap()->addChild(bullet);
					Vec2 pos = Vec2(getPosition().x + getContentSize().width / 2, getPosition().y + getContentSize().height / 2);
					bullet->setPosition(pos);
					bullet->setScale(1.5);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				auto skill = SkillBase::create(this, "skillball (1).png", "skillball", 19, 5.0f, getColor(), Damage::SKILL1);
				GameMap::getCurrentMap()->addSprite(skill);
				skill->setPosition(this->getPosition());
				int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
				float dx = ds[(int)getDirection()][0] * Radius::One;
				float dy = ds[(int)getDirection()][1] * Radius::One;
				skill->runAction(MoveBy::create(5.0f, Vec2(dx, dy)));
				skill->setScale(1.5);
			}

		}

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL1))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Mage::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		if (_attackTargetList.size())
		{
			for (int i = _attackTargetList.size() - 1; i >= 0; i--)
			{
				if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
				{
					auto skill = SkillBase::create(this, "skillwater (1).png", "skillwater", 15, 3.0f, getColor(), Damage::SKILL2);
					GameMap::getCurrentMap()->addSprite(skill);
					auto pos = _attackTargetList.at(i)->getPosition();
					skill->setPosition(pos);

				}
			}
		}
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1} };
		for (int i =0; i < 4 - _attackTargetList.size(); i++)
		{
			auto skill = SkillBase::create(this, "skillwater (1).png", "skillwater", 15, 3.0f, getColor(), Damage::SKILL2);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += ds[i][0] * Radius::Two;
			pos.y += ds[i][1] * Radius::Two;
			skill->setPosition(pos);


		}

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Mage::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		for (int i = 0; i < 8; i++)
		{
			auto skill = SkillBase::create(this, "skillfog (1).png", "skillfog", 15, 5.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			skill->setPosition(pos);
			pos.x += ds[i][0] * Radius::Three;
			pos.y += ds[i][1] * Radius::Three;
			skill->runAction(MoveTo::create(5.0f, pos));
			skill->setScale(1.5);

		}
		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL3))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Mage::setStatus(Status status)
{

	this->_status = status;
	if ((int)status > 7)
		return;
	std::string animation = _roleName + "_";
	animation += _animationNames.at(int(status)) + "_";

	Direction direction=Direction::RIGHTDOWN;
	switch (status)
	{
	case Status::STANDING:
	case Status::ATTACKING:
	case Status::MOVING:
	case Status::DEAD:
	case Status::SKILL1:
	{
		if (int(_direction) >= 4)
		{
			direction = _direction;
		}
		else
		{
			int dd[] = { 4,6,3,3 };
			direction = Player::Direction((int)_direction + dd[(int)_direction]);
		}
		break;
	}
	case Status::SKILL2:
	case Status::BEINGHIT:
	{
		if (int(_direction) < 4)
		{
			direction = _direction;
			if (int(_direction) == 2)
				direction = Player::Direction((int)_direction - 1);
		}
		else
		{
			int dd[] = { 4,4,3,6 };
			direction = Player::Direction((int)_direction - dd[(int)_direction]);
		}
		break;
	}
	case Status::SKILL3:
	{
		switch (_direction)
		{
		case Direction::LEFT:
		case Direction::UP:
		case Direction::LEFTUP:
		case Direction::LEFTDOWN:
		{
			direction = Direction::LEFTUP;
			break;
		}
		case Direction::RIGHT:
		case Direction::DOWN:
		case Direction::RIGHTDOWN:
		case Direction::RIGHTUP:
		{
			direction = Direction::RIGHTDOWN;
			break;
		}
		}
		break;
	}

	}
	if ((int)direction < 0 || (int)direction>7)
		direction = Direction::RIGHTDOWN;

	std::string directionName[]{ "left","right","up","down","leftdown","leftup","rightdown","rightup" };
	animation += directionName[int(direction)];

	AnimationLoader::runAnimation(animation, this);
}


Paladin* Paladin::create(const std::string& id, int color)
{
	auto paladin = new(std::nothrow) Paladin();
	if (paladin&&paladin->initWithRole(3, color))
	{
		paladin->_id = id;
		paladin->autorelease();
		return paladin;
	}
	CC_SAFE_DELETE(paladin);
	return nullptr;

}

bool Paladin::init(int role, int color)
{
	if (!Player::init(role, color))
		return false;
	setAttackRadius(PLAYER_ATTACK_RADIUS);


	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 9,12,13,11,6,4,8,18 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	for (int i = 2; i < 7; i++)
	{
		for (int j = 4; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	{
		int i = 7;
		for (int j = 5; j < 7; j++)
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

void Paladin::skill1()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create(this, "skillwaterdragon1 (1).png", "skillwaterdragon1", 19, 3.0f, getColor(), Damage::SKILL1);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::One;
		pos.y += ds[(int)getDirection()][1] * Radius::One;
		skill->setPosition(pos);
		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL1))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Paladin::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		setStatus(Status::SKILL3);
		{
			auto skill = SkillBase::create(this, "skillwaterdragonL (1).png", "skillwaterdragonL", 21, 3.0f, getColor(), Damage::SKILL2);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x -= Radius::Three;
			skill->setPosition(pos);
			skill->setScale(1.5);
		}
		{
			auto skill = SkillBase::create(this, "skillwaterdragonR (1).png", "skillwaterdragonR", 21, 3.0f, getColor(), Damage::SKILL2);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += Radius::Two;
			skill->setPosition(pos);
			skill->setScale(1.5);
		}
		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Paladin::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
			{
				auto target = _attackTargetList.at(i);
				target->beAttack(this->getDamage());
				if (target->getNowHPValue() <= 0.0)
				{
					addEXP(target->getKillExperience());
					addMoney(target->getKillMoney());
				}
			}
		}
		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL3))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
			auto skill = SkillBase::create(this, "skillblackdragon (1).png", "skillblackdragon", 19, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
			auto pos = this->getPosition();
			pos.x += ds[(int)getDirection()][0] * Radius::Three;
			pos.y += ds[(int)getDirection()][1] * Radius::Three;
			skill->setPosition(pos);
		}), NULL);
		this->runAction(sequence);
	}
}

void Paladin::setStatus(Status status)
{

	this->_status = status;
	if ((int)status > 7)
		return;
	std::string animation = _roleName + "_";
	animation += _animationNames.at(int(status)) + "_";
	Direction direction = Direction::RIGHTDOWN;
	switch (status)
	{

	case Status::ATTACKING:
	case Status::DEAD:
	case Status::BEINGHIT:
	case Status::SKILL1:
	case Status::SKILL2:
	{
		if (int(_direction) >= 4)
		{
			direction = _direction;
		}
		else
		{
			int dd[] = { 4,6,3,3 };
			direction = Player::Direction((int)_direction + dd[(int)_direction]);
		}
		break;
	}
	case Status::STANDING:
	case Status::MOVING:
	{
		direction = _direction;
		break;
	}
	case Status::SKILL3:
	{
		switch (_direction)
		{
		case Direction::LEFT:
		case Direction::UP:
		case Direction::LEFTUP:
		case Direction::LEFTDOWN:
		{
			direction = Direction::LEFTUP;
			break;
		}
		case Direction::RIGHT:
		case Direction::DOWN:
		case Direction::RIGHTDOWN:
		case Direction::RIGHTUP:
		{
			direction = Direction::RIGHTDOWN;
			break;
		}
		}
		break;
	}

	}
	if ((int)direction < 0 || (int)direction>7)
		direction = Direction::RIGHTDOWN;

	std::string directionName[]{ "left","right","up","down","leftdown","leftup","rightdown","rightup" };
	animation += directionName[int(direction)];

	AnimationLoader::runAnimation(animation, this);
}

Ranger* Ranger::create(const std::string& id, int color)
{
	auto ranger = new(std::nothrow) Ranger();
	if (ranger&&ranger->initWithRole(4, color))
	{
		ranger->_id = id;
		ranger->autorelease();
		return ranger;
	}
	CC_SAFE_DELETE(ranger);
	return nullptr;
}

bool Ranger::init(int role, int color)
{
	if (!Player::init(role, color))
		return false;
	setAttackRadius(PLAYER_ATTACK_RADIUS);


	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 8,8,4,7,4,16,13,5 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
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

void Ranger::skill1()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create(this, "skilllight (1).png", "skilllight", 18, 3.0f, getColor(), Damage::SKILL1);
		this->addChild(skill, -1);
		auto sequence = Sequence::create(DelayTime::create(1.4f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);

		}), NULL);
		this->runAction(sequence);
	}
}

void Ranger::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		auto skill = SkillBase::create(this, "skillknife (1).png", "skillknife", 21, 3.0f, getColor(), Damage::SKILL2);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::Two;
		pos.y += ds[(int)getDirection()][1] * Radius::Two;
		skill->setPosition(pos);


		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Ranger::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		{
			auto skill = SkillBase::create(this, "skillstrike (1).png", "skillstrike", 20, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x -= Radius::Three;
			skill->setPosition(pos);
			skill->setScale(1.5);
		}
		{
			auto skill = SkillBase::create(this, "skillstrike (1).png", "skillstrike", 20, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += Radius::Three;
			skill->setPosition(pos);
			skill->setScale(1.5);
			skill->setFlippedX(true);
		}
		auto sequence = Sequence::create(DelayTime::create(1.4f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}



Cavalier* Cavalier::create(const std::string& id, int color)
{
	auto cavalier = new(std::nothrow) Cavalier();
	if (cavalier&&cavalier->initWithRole(5, color))
	{
		cavalier->_id = id;
		cavalier->autorelease();
		return cavalier;
	}
	CC_SAFE_DELETE(cavalier);
	return nullptr;

}

bool Cavalier::init(int role, int color)
{
	if (!Player::init(role, color))
		return false;
	setAttackRadius(PLAYER_ATTACK_RADIUS);


	std::string animationNames[] = { "move","move","attack","move","move","skill","skill1","skill2" };
	_animationNames.assign(animationNames, animationNames + 8);

	std::string directions[] = { "up","down","left","right","leftdown","leftup","rightdown","rightup" };

	int animationNum[] = { 16,16,16,16,16,15,16,26 };
	_animationFrameNum.assign(animationNum, animationNum + 8);
	for (int i = 1; i < 3; i++)
	{
		for (int j = 4; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	for (int i = 5; i < 7; i++)
	{
		for (int j = 4; j < 8; j++)
		{
			std::string animationName = _roleName + "_" + animationNames[i] + "_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationFrameNum.at(i));
		}

	}
	{
		int i = 7;
		for (int j = 5; j < 7; j++)
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

void Cavalier::skill1()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL1)
	{
		stopMove();
		setStatus(Status::SKILL1);
		auto skill = SkillBase::create(this, "skilldragonsun (1).png", "skilldragonsun", 17, 3.0f, getColor(), Damage::SKILL1);
		GameMap::getCurrentMap()->addSprite(skill);

		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
		auto pos = this->getPosition();
		pos.x += ds[(int)getDirection()][0] * Radius::One;
		pos.y += ds[(int)getDirection()][1] * Radius::One;
		skill->setPosition(pos);

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL1))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Cavalier::skill2()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL2)
	{
		stopMove();
		setStatus(Status::SKILL2);
		int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4 - _attackTargetList.size(); i++)
		{
			auto skill = SkillBase::create(this, "skillfire (1).png", "skillfire", 19, 3.0f, getColor(), Damage::SKILL2);
			GameMap::getCurrentMap()->addSprite(skill);

			auto pos = this->getPosition();
			pos.x += ds[i][0] * Radius::Two;
			pos.y += ds[i][1] * Radius::Two;
			skill->setPosition(pos);


		}
		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL2))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Cavalier::skill3()
{
	if (_isSkill&&getStatus() != Status::DEAD&&getStatus() != Status::SKILL3)
	{
		stopMove();
		setStatus(Status::SKILL3);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() >= 0.0)
			{
				auto target = _attackTargetList.at(i);
				target->beAttack(this->getDamage());
				if (target->getNowHPValue() <= 0.0)
				{
					addEXP(target->getKillExperience());
					addMoney(target->getKillMoney());
				}
			}
		}

		auto sequence = Sequence::create(DelayTime::create(_animationFrameNum.at(int(Status::SKILL3))*0.1f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
			auto skill = SkillBase::create(this, "skilldragonflower (1).png", "skilldragonflower", 19, 3.0f, getColor(), Damage::SKILL3);
			GameMap::getCurrentMap()->addSprite(skill);

			int ds[][2] = { {-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1} };
			auto pos = this->getPosition();
			pos.x += ds[(int)getDirection()][0] * Radius::Three;
			pos.y += ds[(int)getDirection()][1] * Radius::Three;
			skill->setPosition(pos);
		}), NULL);
		this->runAction(sequence);
	}
}

void Cavalier::setStatus(Status status)
{

	this->_status = status;
	if ((int)status > 7)
		return;
	std::string animation = _roleName + "_";
	animation += _animationNames.at(int(status)) + "_";
	Direction direction = Direction::RIGHTDOWN;
	switch (status)
	{

	case Status::ATTACKING:
	case Status::DEAD:
	case Status::BEINGHIT:
	case Status::SKILL1:
	case Status::SKILL2:
	case Status::STANDING:
	case Status::MOVING:
	{
		if (int(_direction) >= 4)
		{
			direction = _direction;
		}
		else
		{
			int dd[] = { 4,6,3,3 };
			direction = Player::Direction((int)_direction + dd[(int)_direction]);
		}
		break;
	}
	case Status::SKILL3:
	{
		switch (_direction)
		{
		case Direction::LEFT:
		case Direction::UP:
		case Direction::LEFTUP:
		case Direction::LEFTDOWN:
		{
			direction = Direction::LEFTUP;
			break;
		}
		case Direction::RIGHT:
		case Direction::DOWN:
		case Direction::RIGHTDOWN:
		case Direction::RIGHTUP:
		{
			direction = Direction::RIGHTDOWN;
			break;
		}
		}
		break;
	}

	}
	if ((int)direction < 0 || (int)direction>7)
		direction = Direction::RIGHTDOWN;

	std::string directionName[]{ "left","right","up","down","leftdown","leftup","rightdown","rightup" };
	animation += directionName[int(direction)];

	AnimationLoader::runAnimation(animation, this);
}