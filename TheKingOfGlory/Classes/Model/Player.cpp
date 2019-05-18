#include"Player.h"

#include "GameMap.h"
#include<ctime>
#include<cmath>

USING_NS_CC;

//role值同enum分类，为0，1,2

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

	_isMove = true;
	_isAttack = true;
	_isSkill = false;

	setHPBar();

	this->setScale(10);

	std::string animationNames[] = { "stand","walk","attack","dead","beinghit","skill" };
	_animationNames.assign(animationNames, animationNames + 5);

	std::string directions[] = {"up","down","left","right"};

	//对某一个动作,加载动作，delay也需要考虑，不止0.2f
	for (int i = 0; i < 3; i++)
	{
		if (i == 0 || i == 1)
			_animationNum = 10;
		else
			_animationNum = 8;
		for (int j = 0; j < 4; j++)
		{
			std::string animationName = _roleName +"_" +animationNames[i]+"_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationNum);
		}

	}

	setDirection(Direction::DOWN);
	setStatus(Player::Status::STANDING);


	log("\nHahah\n");

	return true;
}

//只是获得名字
bool Player::initWithRole(int role)
{
	//设置路径
	_roleName = std::string(roleName[role]);

	auto file = _roleName + "_stand_down_01.png";

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
		animation += "behight_";
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


//血条问题仍要讨论
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
		if (path->updatePath(getPosition(), destination))
		{
			setDestination(destination);
			setStatus(Status::MOVING);
			schedule(CC_CALLBACK_0(Player::move, this), "move");
		}
	}
}

void Player::move()
{
	if (getStatus() == Status::MOVING)
	{
		/*auto position = this->getPosition();

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
			stopMove();*/

		auto position = this->getPosition();

		if (position.equals(getDestination()))
		{
			stopMove();
			return;
		}

		Vec2 target = path->getNextPos();
		float dx = target.x - position.x;
		float dy = target.y - position.y;

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

void Player::updateHPBar()
{
	if (_HPBar != NULL)
	{
		log("Percent:%f", 100.0*getNowHPValue() / getHPValue());
		_HPBar->setPercent(100.0*getNowHPValue() / getHPValue());
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
