#include"Player.h"
#include"AnimationLoader.h"
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
	_status = Status::STANDING;
	_direction = Direction::NONE;
	_speed = 100;
	_lifeValue = PLAYER_HPVALUE;

	cocos2d::Size size = this->getContentSize();
	log("size: %f,%f", size.width, size.height);

	initWithRole(role);
	std::string curName = _roleName;

	setLifeValue(PLAYER_HPVALUE);
	setAttackRadius(PLAYER_ATTACK_RADIUS);
	setDamage(PLAYER_DAMAGE);
	setAttackInterval(PLAYER_ATTACK_INTERVAL);

	_isMove = false;
	_isAttack = false;
	_isSkill = false;

	setHP();

	this->initWithSpriteFrameName(_roleName);
	//帧缓存,使用plist
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameItem/Player/" + _roleName + "/default.plist");
	Sprite* sprite = Sprite::createWithSpriteFrameName("GameItem/Player/" + _roleName + "/default.plist");
	sprite->setPosition(ccp(100, 100));
	this->addChild(sprite);

	std::string animationNames[] = { "standing","moving","attacking","dead","beinghit","skill" };
	_animationNames.assign(animationNames, animationNames + 5);

	//对某一个动作,加载动作，delay也需要考虑，不止0.2f
	for (int i = 0; i < 6; i++)
	{
		AnimationLoader::loadAnimation(animationNames[i], 0.2f, _animationNum);
	}

	return true;
}

//只是获得名字
bool Player::initWithRole(int role)
{
	//设置路径
	_roleName = std::string(roleName[role]);
	auto file = "GameItem/Player/" + _roleName + "/default.png";

	if (this->initWithFile(file) && this->init(role))
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
	Animation*animation = nullptr;
	//Or do animation here:
	switch (_status)
	{
	case Player::Status::STANDING:
	{
		animation = AnimationLoader::getAnimation(_animationNames[STANDING]);
	}
		break;
	case Player::Status::MOVING:
	{
		animation = AnimationLoader::getAnimation(_animationNames[MOVING]);
	}
		break;
	case Player::Status::ATTACKING:
	{
		animation = AnimationLoader::getAnimation(_animationNames[ATTACKING]);
	}
	case Player::Status::DEAD:
	{
		animation = AnimationLoader::getAnimation(_animationNames[DEAD]);
	}
		break;
	case Player::Status::BEINGHIT:
	{
		animation = AnimationLoader::getAnimation(_animationNames[BEINGHIT]);
	}
		break;
	case Player::Status::SKILL:
	{
		animation = AnimationLoader::getAnimation(_animationNames[SKILL]);
	}
		break;
	default:
		break;
	}
	if (animation)
	{
		AnimationLoader::stopAnimation(this);
		animation->setRestoreOriginalFrame(false);
		runAction(Animate::create(animation));
	}
}


Player::Status Player::getStatus()
{
	return this->_status;
}

void Player::moveTo(Vec2 toPosition)
{
	_status = (Status)MOVING;
	_isMove = true;
	if (_isMove)
	{
		auto _position = getPosition();
		float dx = toPosition.x - _position.x;
		float dy = toPosition.y - _position.y;
		float dist = sqrt(dx*dx + dy * dy);
		float interval = dist / (getSpeed());
		auto moveTo = MoveTo::create(interval, toPosition);
		moveTo->setTag(1);//锚点要考虑
		this->runAction(moveTo);

		LoadingBar *HP = getHP();
		HP->runAction(moveTo);
	}
}

//用于是否翻转
void Player::onMove(Vec2 toPosition)
{
}

void Player::stopMove()
{
	if (_isMove)
	{
		_status = (Status)STANDING;
		_isMove = false;
		this->stopActionByTag(1);

		LoadingBar *HP = getHP();
		HP->stopActionByTag(1);
	}
}


//血条问题仍要讨论
void Player::attack(const void* enemy)
{
	_status = (Status)ATTACKING;
	_isAttack = true;
	if (_isAttack)
	{
		AnimationLoader::runAnimation("attacking", this);
	}
}

void Player::stopAttack()
{
	_status = (Status)STANDING;
	if (_isAttack)
	{
		_isAttack = false;
		AnimationLoader::stopAnimation(this); //stange，此处貌似停掉所有动作
	}
}

void Player::skill(const void* enemy)
{
	_status = (Status)SKILL;
	_isSkill = true;
	if (_isSkill)
	{
		AnimationLoader::runAnimation("skill", this);
		_isSkill = false;
	}
}

void Player::beHit(int attack)
{
	_lifeValue -= attack;
	if (_lifeValue <= 0)
	{
		_lifeValue = 0;
		_status = (Status)DEAD;
		AnimationLoader::runAnimation("dead", this);

		return;
	}
	else
	{
		_status = (Status)BEINGHIT;
		AnimationLoader::runAnimation("behit", this);
	}
}

void Player::setHP()
{
	_HP = LoadingBar::create("hpBg1.png");

	_HP->setScale(0.1);
	_HP->setDirection(LoadingBar::Direction::LEFT);

	_HP->setPercent(100);
	Vec2 pos = this->getPosition();
	_HP->setPosition(Vec2(pos.x, pos.y + 30.0));
}


void Player::isLocal(bool a)
{
	this->_isLocal = a;
	if (a)
	{
		//待补充???
	}
}

bool Player::isLocal()
{
	return _isLocal;
}