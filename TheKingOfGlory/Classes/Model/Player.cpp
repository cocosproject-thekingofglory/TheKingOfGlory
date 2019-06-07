#include"Player.h"
#include<ctime>
#include<cmath>
#include "GameMap.h"
#include "UI/CountDown.h"
#include "SkillBase.h"


USING_NS_CC;

//role值同enum分类，为0，1,2

Player* Player::createPlayer(const std::string& id, int role, int color)
{
	auto player = new (std::nothrow) Player();
	if (player&&player->initWithRole(role, color))
	{
		player->_id = id;
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;


}

//初始化信息，对这个角色初始化信息
bool Player::init(int role, int color)
{
	setColor(color);

	setHPBar();
	setEXPBar();

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
	_direction = Direction::DOWN;
	_status = Status::STANDING;
	
	this->setScale(2);


	isOnline = UserDefault::getInstance()->getBoolForKey("Network");

	return true;
}

//只是获得名字
bool Player::initWithRole(int role, int color)
{
	_role = role;
	//设置路径
	_roleName = std::string(roleName[role]);

	auto file = _roleName;
	switch (role)
	{
	case 0: {file += "_stand_down (1).png"; break; }
	case 1: {file += "_move_down (1).png"; break; }
	case 2: {file += "_stand_rightup (1).png"; break; }
	case 3: {file += "_stand_rightup (1).png"; break; }
	case 4: {file += "_stand_rightup (1).png"; break; }
	case 5: {file += "_move_rightup (1).png"; break; }
	}

	if (this->initWithSpriteFrameName(file) && this->init(role, color))

	{
		return true;
	}
	return false;
}


//与动作有关,设置状态，传入状态，初始化动画,状态读取
void Player::setStatus(Player::Status status)
{

	this->_status = status;
	if ((int)status > 7)
		return;
	std::string animation = _roleName + "_";
	//Or do animation here:
	animation += _animationNames.at(int(status))+"_";

	std::string directionName[]{ "left","right","up","down","leftdown","leftup","rightdown","rightup" };
	animation += directionName[int(_direction)];

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
	if (_isAttack&&getStatus() != Status::ATTACKING)
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
				std::string frameName = _roleName +"_"+ _animationNames[(int)Status::DEAD]+"_";

				std::string directionName[]{ "left","right","up","down","leftdown","leftup","rightdown","rightup" };
				if (_role == 2 || _role == 3||_role==5)
					frameName += directionName[int(Direction::RIGHTDOWN)];
				else
					frameName += directionName[int(_direction)];

				frameName += " ("+std::to_string(_animationFrameNum[(int)Status::DEAD]) +").png";
				this->setSpriteFrame(frameName);
				bool isRed=!(getColor()==RED);
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpdateRank", (void*)isRed);
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

void Player::skillRecover()
{
	if (_isSkill&&getStatus() != Status::SKILLRECOVER)
	{
		stopMove();
		setStatus(Status::SKILLRECOVER);
		auto skill = SkillBase::create("skillrecover (1).png", "skillrecover", 18, 3.0f, this->getColor()^1, PLAYER_SKILLRECOVER_VALUE);
		GameMap::getCurrentMap()->addSprite(skill);
		skill->setPosition(this->getPosition());



		auto sequence = Sequence::create(DelayTime::create(1.8f), CallFunc::create([=]() {
			this->setStatus(Status::STANDING);
		}), NULL);
		this->runAction(sequence);
	}
}

void Player::startMove(Vec2 destination)
{
	if (_isMove)
	{
		//设置一个大目的地和小目的地，大目的地为实际目的地，将大目的地分为小目的地
		if (isOnline)
		{
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
				setBigDestination(destination);
				setSmallDestination(destination);
				setStatus(Status::MOVING);
				schedule(CC_CALLBACK_0(Player::move, this), "move");
			}
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
	_isSkill = true;


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
		if (isOnline)
		{
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

				if (isLocal())
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ViewCenter");
			}
		}
		else
		{
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
}

void Player::setHPBar()
{
	if(getColor()==RED)
		_HPBar = LoadingBar::create("Pictures/GameItem/redBar.png");
	else
		_HPBar = LoadingBar::create("Pictures/GameItem/greenBar.png");

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
	_EXPBar = LoadingBar::create("Pictures/GameItem/blueBar.png");

	_EXPBar->setScale(0.1);
	_EXPBar->setDirection(LoadingBar::Direction::LEFT);

	_EXPBar->setPercent(0);

	Vec2 EXPpos = Vec2(this->getPositionX() + this->getContentSize().width / 2,
		this->getPositionY() + this->getContentSize().height*1.235);

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
		addHPValue(PLAYER_LEVEL_UP_HPVALUE);
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

//装备
void Player::removeEquipment(EquipmentBase*equip)
{
	_equipmentList.eraseObject(equip);
}

void Player::isLocal(bool a)
{
	this->_isLocal = a;


}

bool Player::isLocal()
{
	return _isLocal;
}
