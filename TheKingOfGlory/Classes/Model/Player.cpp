#include"Player.h"

#include "GameMap.h"
#include<ctime>
#include<cmath>

USING_NS_CC;


Player* Player::createPlayer(const std::string& id, int role) 
{
	auto player = new (std::nothrow) Player();
	if (player&&player->initWithRole(role))
	{
		player->_id = id;
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;


}

//初始化信息，对这个角色初始化信息
bool Player::init(int role)
{
	setSpeed(PLAYER_MOVE_SPEED);
	setHPValue(PLAYER_HPVALUE);
	setNowHPValue(PLAYER_HPVALUE);
	setAttackRadius(PLAYER_ATTACK_RADIUS);
	setDamage(PLAYER_DAMAGE);
	setAttackInterval(PLAYER_ATTACK_INTERVAL);
	setNowEXPValue(PLAYER_INITIAL_EXP);
	setEXPValue(PLAYER_INITIAL_EXP);
	setNowLevel(PLAYER_INITIAL_LEVEL);

	_isMove = true;
	_isAttack = true;
	_isSkill = false;


	setHPBar();
	setEXPBar();
	setLevel();

	this->setScale(10);

	std::string animationNames[] = { "stand","move","attack","dead","behit","skill","strikefly" };
	_animationNames.assign(animationNames, animationNames + 7);

	std::string directions[] = {"up","down","left","right","rightup","leftup","leftdown","rightdown"};

	//对某一个动作,加载动作，delay也需要考虑，不止0.2f
	for (int i = 0; i < 7; i++)
	{
		if (i == 0 || i == 1)
			_animationNum = 10;
		else
			_animationNum = 8;
		for (int j = 0; j < 8; j++)
		{
			std::string animationName = _roleName +"_" +animationNames[i]+"_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationNum);
		}

	}

	setDirection(Direction::DOWN);
	setStatus(Player::Status::STANDING);

	return true;
}

//只是获得名字
bool Player::initWithRole(int role)
{
	//设置路径
	_roleName = std::string(roleName[role]);

	auto file = _roleName + "_stand_down(01).png";

	if (this->initWithSpriteFrameName(file) && this->init(role))

	{
		// do something here
		return true;
	}
	return false;
}


//与动作有关,设置状态，传入状态，初始化动画,状态读取
void Player::setStatus(Player::Status status)
{
	this->_status = status;
	std::string animation=_roleName+"_";
	//Or do animation here:
	switch (_status)
	{
	case Player::Status::STANDING:
	{
		animation += "stand_";
	}
		break;
	case Player::Status::MOVING:
	{
		animation += "walk_";
	}
		break;
	case Player::Status::ATTACKING:
	{
		animation += "attack_";
	}
	break;
	case Player::Status::DEAD:
	{
		animation += "dead_";
	}
		break;
	case Player::Status::BEINGHIT:
	{
		animation += "behit_";
	}
		break;
	case Player::Status::SKILL:
	{
		animation += "skill_";
	}
		break;
	default:
		break;
	}
	switch (getDirection())
	{
	case Direction::DOWN:
	{
		animation += "down";
	}
	break;
	case Direction::UP:
	{
		animation += "up";
	}
	break;
	case Direction::LEFT:
	{
		animation += "left";
	}
	break;
	case Direction::RIGHT:
	{
		animation += "right";
	}
	break;
	case Direction::LEFTDOWN:
	{
		animation += "leftdown";
	}
	break;
	case Direction::LEFTUP:
	{
		animation += "leftup";
	}
	break;
	case Direction::RIGHTDOWN:
	{
		animation += "rightdown";
	}
	break;
	case Direction::RIGHTUP:
	{
		animation += "rightup";
	}
	break;
	}
	AnimationLoader::runAnimation(animation, this);
}


Player::Status Player::getStatus()
{
	return this->_status;
}


void Player::stopMove()
{
	if (_isMove)
	{
		setStatus(Player::Status::STANDING);
		unschedule("move");
	}
}



bool Player::attack()
{
	if (_isAttack&&getStatus()!=Status::ATTACKING)
	{
		stopMove();
		setStatus(Status::ATTACKING);
		for (int i = _attackTargetList.size() - 1; i >= 0; i--)
		{
			if (_attackTargetList.at(i)->getNowHPValue() > 0.0)
			{
				if (_attackTargetList.at(i)->getType() == SpriteBase::SOLDIER)
				{
					auto target = dynamic_cast<Soldier *>(_attackTargetList.at(i));
					target->beAttack(this->getDamage());
					if (beAttack(this->getDamage()) == 0.0)
					{
						setNowEXPValue(SOLDIER_EXPVALUE);
						setEXPValue(SOLDIER_EXPVALUE);
						setNowLevel(getNowLevel());
						if (this->getNowEXPValue > 100.0)
						{
							setNowEXPValue(-100.0);
							updateEXPBar();
						}
					}
				}
			}
		}
		auto sequence = Sequence::create(DelayTime::create(0.8f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
	return true;
}

void Player::stopAttack()
{
	if (_isAttack)
	{
		setStatus(Status::STANDING);
	}
}

void Player::skill(const void* enemy)
{
	_status = (Status)SKILL;
	_isSkill = true;
	if (_isSkill)
	{
		AnimationLoader::runAnimation(_roleName+"skill", this);
		_isSkill = false;
	}
}

float Player::beAttack(const float damage)
{

	float nowHP = getNowHPValue();
	nowHP -= damage;
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	if (nowHP <= 0.0)
	{
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
		setStatus(Status::DEAD);
		auto sequence = Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameOver", (void*)false);
		}), NULL);
		this->runAction(sequence);
	}
	else
	{
		setStatus(Status::BEINGHIT);
		auto sequence = Sequence::create(DelayTime::create(0.8f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
	return nowHP;
}

void Player::startMove(Vec2 destination)
{
	if (_isMove)
	{
		log("move");
		setDestination(destination);
		setStatus(Status::MOVING);
		schedule(CC_CALLBACK_0(Player::move, this), "move");
	}
}

void Player::move()
{
	if (getStatus() == Status::MOVING)
	{
		auto position = this->getPosition();

		if (position.equals(getDestination()))
		{
			stopMove();
			return;
		}

		int flagX = (position.x < _destination.x) ? 1 : -1, flagY = (position.y < _destination.y) ? 1 : -1;

		float dx = flagX * MIN(getSpeed(), fabs(_destination.x - position.x));
		float dy = flagY * MIN(getSpeed(), fabs(_destination.y - position.y));

		if (dx < 0)
			setDirection(Direction::LEFT);
		else if (dx > 0)
			setDirection(Direction::RIGHT);
		else
		{
			if (dy <= 0)
				setDirection(Direction::DOWN);
			else
				setDirection(Direction::UP);
		}


		Vec2 target = Vec2(position.x + dx, position.y + dy);

		auto map = GameMap::getCurrentMap();

		if (map->isCanAssess(map->positionToTileCoord(target)))
			this->setPosition(target);
		else
			stopMove();
	}
}

void Player::setHPBar()
{
	_HPBar = LoadingBar::create("Pictures/GameItem/planeHP.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(100);

	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);

	_HPBar->setPosition(HPpos);

	this->addChild(_HPBar);
}

void Player::setEXPBar()
{
	_EXPBar = LoadingBar::create("Pictures/GamesItem/planeEXP.png");

	_EXPBar->setScale(0.1);
	_EXPBar->setDirection(LoadingBar::Direction::LEFT);

	_EXPBar->setPercent(100);

	Vec2 EXPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize.height*1.1);

	_EXPBar->setPosition(EXPpos);

	this->addChild(_EXPBar);
}

void Player::updateHPBar()
{
	if (_HPBar != NULL)
	{
		log("Percent:%f", 100.0*getNowHPValue() / getHPValue());
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
	}

}

void Player::updateEXPBar()
{
	if (_EXPBar != NULL)
	{
		log("Percent:%f", getNowEXPValue());
		_EXPBar->setPercent(getNowEXPValue());
	}
}

void Player::isLocal(bool a)
{
	this->_isLocal = a;


}

bool Player::isLocal()
{
	return _isLocal;
}
