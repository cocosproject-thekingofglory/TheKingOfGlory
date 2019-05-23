#include"Player.h"
#include<ctime>
#include<cmath>
#include "GameMap.h"
#include "UI/CountDown.h"


USING_NS_CC;

//role值同enum分类，为0，1,2

Player* Player::createPlayer(const std::string& id, int role,int color) 
{
	auto player = new (std::nothrow) Player();
	if (player&&player->initWithRole(role,color))
	{
		player->_id = id;
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;


}

//初始化信息，对这个角色初始化信息
bool Player::init(int role,int color)
{
	setHPBar();
	setEXPBar();

	setColor(color);
	setSpeed(PLAYER_MOVE_SPEED);
	setHPValue(PLAYER_HPVALUE);
	setNowHPValue(PLAYER_HPVALUE);
	setAttackRadius(PLAYER_ATTACK_RADIUS);
	setDamage(PLAYER_DAMAGE);
	setAttackInterval(PLAYER_ATTACK_INTERVAL);
	setDefend(PLAYER_DEFEND);
	//金钱、经验
	setNowEXPValue(PLAYER_INITIAL_EXP);
	setEXPValue(PLAYER_LEVEL_UP_EXP);
	setLevel(PLAYER_INITIAL_LEVEL);

	setMoney(PLAYER_INITIAL_MONEY);

	_isMove = false;
	_isAttack = false;
	_isSkill = false;

	
	this->setScale(2);

	std::string animationNames[] = { "move","attack","dead","behit","stand" };
	_animationNames.assign(animationNames, animationNames + 5);

	std::string directions[] = {"up","down","left","right","leftdown","leftup","rightdown","rightup"};

	//对某一个动作,加载动作，delay也需要考虑，不止0.2f
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			_animationNum = 10;
			break;
		case 1:
			_animationNum = 8;
			break;
		case 2:
			_animationNum = 7;
			break;
		case 3:
			_animationNum = 4;
			break;
		case 4:
			_animationNum = 10;
			break;
		}
		for (int j = 0; j < 8; j++)
		{
			std::string animationName = _roleName +"_" +animationNames[i]+"_" + directions[j];
			AnimationLoader::loadAnimation(animationName, 0.1f, _animationNum);
		}

	}

	setDirection(Direction::RIGHTUP);
	setStatus(Player::Status::STANDING);


	return true;
}

//只是获得名字
bool Player::initWithRole(int role,int color)
{
	//设置路径
	_roleName = std::string(roleName[role]);

	auto file = _roleName + "_stand_down (1).png";

	if (this->initWithSpriteFrameName(file) && this->init(role,color))

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
		animation += "move_";
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


//血条问题仍要讨论
bool Player::attack()
{
	if (_isAttack&&getStatus()!=Status::ATTACKING)
	{
		stopMove();
		setStatus(Status::ATTACKING);
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
	if (!(getStatus() == Status::DEAD || getStatus() == Status::BEINGHIT))
	{
		float nowHP = getNowHPValue();
		nowHP -= damage * (1 - getDefend());
		setNowHPValue(MAX(nowHP, 0));
		updateHPBar();
		if (nowHP <= 0.0)
		{
			for (int i = 0; i < _beAttackTargetList.size(); i++)
			{
				_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
			}
			setStatus(Status::DEAD);
			auto sequence = Sequence::create(DelayTime::create(0.7f), CallFunc::create([=]() {
				this->stopAnimation(this);
				std::string frameName = _roleName + "_dead_";
				switch (getDirection())
				{
				case Direction::DOWN:
				{
					frameName += "down";
				}
				break;
				case Direction::UP:
				{
					frameName += "up";
				}
				break;
				case Direction::LEFT:
				{
					frameName += "left";
				}
				break;
				case Direction::RIGHT:
				{
					frameName += "right";
				}
				break;
				case Direction::LEFTDOWN:
				{
					frameName += "leftdown";
				}
				break;
				case Direction::LEFTUP:
				{
					frameName += "leftup";
				}
				break;
				case Direction::RIGHTDOWN:
				{
					frameName += "rightdown";
				}
				break;
				case Direction::RIGHTUP:
				{
					frameName += "rightup";
				}
				break;
				}
				frameName += " (7).png";
				this->setSpriteFrame(frameName);
				if (isLocal())
				{
					auto countDown = CountDown::create("Pictures/UI/TopBar.png", "Rvival after ", "fonts/arial.ttf", 32, 15, true,
						[=]() {
						revival();
					});
					cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(countDown, 2);
				}
				else
				{
					auto sequence = Sequence::create(DelayTime::create(15), [=]() {
						revival();
					}, NULL);
					this->runAction(sequence);
				}

			}), NULL);
			this->runAction(sequence);
		}
		else
		{
			setStatus(Status::BEINGHIT);
			auto sequence = Sequence::create(DelayTime::create(0.4f), CallFunc::create([=]() {
				this->setStatus(Status::STANDING);
			}), NULL);
			this->runAction(sequence);
		}
		return nowHP;
	}
	return getNowHPValue();
}

void Player::startMove(Vec2 destination)
{
	if (_isMove)
	{
		//设置一个大目的地和小目的地，大目的地为实际目的地，将大目的地分为小目的地
		if (isLocal())
		{
			//本地英雄使用寻路算法
			auto pathArithmetic = PathArithmetic::create();
			auto map = GameMap::getCurrentMap();
			path = pathArithmetic->getPath(map->positionToTileCoord(getPosition()), map->positionToTileCoord(destination), map->getGridVector());
			if (path.size())
			{
				moveStep = 0;
				setBigDestination(destination);
				setSmallDestination(getPosition());
				setStatus(Status::MOVING);
				schedule(CC_CALLBACK_0(Player::move, this), "move");
			}
		}
		else
		{
			srand(time(NULL));
			setBigDestination(destination);
			setSmallDestination(destination);
			setStatus(Status::MOVING);
			schedule(CC_CALLBACK_0(Player::move, this), "move");
		}

	}
}

void Player::judgeDirection(float dx, float dy)
{
	if (dx < 0)
	{
		if (dy == 0)
			setDirection(Direction::LEFT);
		else if (dy < 0)
			setDirection(Direction::LEFTDOWN);
		else
			setDirection(Direction::LEFTUP);
	}
	else if (dx > 0)
	{
		if (dy == 0)
			setDirection(Direction::RIGHT);
		else if (dy < 0)
			setDirection(Direction::RIGHTDOWN);
		else
			setDirection(Direction::RIGHTUP);
	}
	else
	{
		if (dy <= 0)
			setDirection(Direction::DOWN);
		else
			setDirection(Direction::UP);
	}
}

void Player::randomSmallDestination()
{
	float dx = rand() % 600 - 300;
	float dy = rand() % 600 - 300;
	setSmallDestination(Vec2(getPositionX() + dx, getPositionY() + dy));

}

void Player::revival()
{


	_isMove = true;
	_isAttack = true;
	_isSkill = false;


	setDirection(Direction::RIGHTUP);
	setStatus(Player::Status::STANDING);

	setNowHPValue(PLAYER_HPVALUE);
	updateHPBar();

	if (getColor() == RED)
		GameMap::getCurrentMap()->setSpritePosition(this, GameMap::Type::Player_Red);
	else
		GameMap::getCurrentMap()->setSpritePosition(this, GameMap::Type::Player_Blue);

	if (this->isLocal())
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ViewCenter");
}

void Player::move()
{
	if (getStatus() == Status::MOVING)
	{
		auto position = this->getPosition();

		//到达大目的地，停止移动
		if (position.equals(getBigDestination()))
		{
			stopMove();
			return;
		}
		if (isLocal())
		{
			//将寻路算法求得的路径中的每步设为小目的地，小目的地的移动采用直线移动
			if (moveStep >= path.size())
			{
				stopMove();
				return;
			}
			if (path.size())
			{

				if (position.equals(getSmallDestination()))
				{
					auto point = path.at(moveStep++);
					Vec2 coord = Vec2(point->getX(), point->getY());
					setSmallDestination(GameMap::getCurrentMap()->tileCoordToPosition(coord));
				}

				Vec2 smallDestination = getSmallDestination();

				int flagX = (position.x < smallDestination.x) ? 1 : -1, flagY = (position.y < smallDestination.y) ? 1 : -1;

				float dx = flagX * MIN(getSpeed(), fabs(smallDestination.x - position.x));
				float dy = flagY * MIN(getSpeed(), fabs(smallDestination.y - position.y));

				judgeDirection(dx, dy);


				Vec2 target = Vec2(position.x + dx, position.y + dy);
				this->setPosition(target);

				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ViewCenter");
			}
		}
		else
		{
			//直线移动，遇到障碍物则在小范围内随机移动，再继续向目的地移动

			if (position.equals(getSmallDestination()))
			{
				setSmallDestination(getBigDestination());
			}

			Vec2 smallDestination = getSmallDestination();

			int flagX = (position.x < smallDestination.x) ? 1 : -1, flagY = (position.y < smallDestination.y) ? 1 : -1;

			float dx = flagX * MIN(getSpeed(), fabs(smallDestination.x - position.x));
			float dy = flagY * MIN(getSpeed(), fabs(smallDestination.y - position.y));

			judgeDirection(dx, dy);


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
}

void Player::setHPBar()
{
	if(getColor()==BLUE)
		_HPBar = LoadingBar::create("Pictures/GameItem/greenBar.png");
	else if(getColor()==RED)
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");

	_HPBar->setScale(0.1);
	_HPBar->setDirection(LoadingBar::Direction::LEFT);

	_HPBar->setPercent(100);

	Vec2 HPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.3);

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

//金钱、经验
void Player::setEXPBar()
{
	_EXPBar = LoadingBar::create("Pictures/GamesItem/redBar.png");

	_EXPBar->setScale(0.1);
	_EXPBar->setDirection(LoadingBar::Direction::LEFT);

	_EXPBar->setPercent(0);

	Vec2 EXPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.1);

	_EXPBar->setPosition(EXPpos);

	this->addChild(_EXPBar);
}

void Player::updateEXPBar()
{
	//log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	if (_EXPBar != NULL)
	{
		//log("######################");
		_EXPBar->setPercent((float)100.0*getNowEXPValue() / getEXPValue());
	}
}

void Player::updateLevel()
{
	if (_level < PLAYER_MAX_LEVEL)
	{
		_level++;
		addDamage(PLAYER_LEVEL_UP_DAMAGE);
		addDefend(PLAYER_LEVEL_UP_DEFEND);
	}
}

void Player::addEXP(int addEXP)
{
	if (getLevel() < PLAYER_MAX_LEVEL)
	{
		_nowEXP += addEXP;
		while (_nowEXP >= _EXP)
		{
			_nowEXP -= _EXP;
			updateLevel();
		}
		updateEXPBar();
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
