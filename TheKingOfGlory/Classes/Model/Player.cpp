#include"Player.h"
#include<ctime>
#include<cmath>

USING_NS_CC;

//role值同enum分类
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

//初始化信息
bool Player::init(int role)
{
	_status = Status::STANDING;
	_direction = Direction::NONE;
	_speed = 100;

	cocos2d::Size size = this->getContentSize();
	log("size: %f,%f", size.width, size.height);

	initWithRole(role);
	std::string curName = _roleName;


	setAttackRadius(PLAYER_ATTACK_RADIUS);
	setHPValue(PLAYER_HPVALUE);
	setDamage(PLAYER_DAMAGE);

	this->initWithSpriteFrameName(_roleName);
	//帧缓存,使用plist
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameItem/Player/" + _roleName + "/default.plist");
	Sprite* sprite = Sprite::createWithSpriteFrameName("GameItem/Player/" + _roleName + "/default.plist");
	sprite->setPosition(ccp(100, 100));//***
	this->addChild(sprite);

	std::string animationNames[] = { "standing","moving","dead","beinghit","skill" };
	_animationNames.assign(animationNames, animationNames + 5);

	//对某一个动作
	this->addAnimation(animationNames[0],0.2f,_animationNum);

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

void Player::addAnimation(const std::string& animationName, float delay, int num)
{

	/*AnimationLoader::loadAnimation(animationName, delay, num);*/
	//check if already loaded
	auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _roleName.c_str(),animationName)->getCString());
	if (animation)
		return;

	auto animation = Animation::create();
	for (int i = 0; i < num; i++)
	{
		std::string name = animationName;
		name.append(StringUtils::format("_%02d", i)).append(".png");//名称
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);

	animationCache->addAnimation(animation, animationName);
}

void Player::playAnimation(const std::string& animationName, int index)
{
	auto action = this->getActionByTag(index);
	if (action)
		return;

	auto animation = AnimationLoader::getAnimation(animationName);
	if (animation != nullptr)
	{
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);

		auto flag = AnimationLoader::getFlag(animationName);
		repeat->setFlags(flag);

		this->runAction(repeat);
	}
}

//与动作有关,待修...***
void Player::setStatus(Player::Status status)
{
	this->_status = status;
	//Or do animation here:
	switch (_status)
	{
	case Player::Status::STANDING:
	{

	}
		break;
	case Player::Status::MOVING:
		break;
	case Player::Status::DEAD:
		break;
	case Player::Status::BEINGHIT:
	{
		log("onBeingHit: Enter BeingHit");
		auto func = [&]()
		{
			
		}
		auto animate = getAnimateByType(BEINGHIT);
		auto wait = DelayTime::create(0.6f);
		auto callback = CallFunc::create(func);
		auto seq = Sequence::create(wait, animate, callback, nullptr);
	}
		break;
	case Player::Status::SKILL:
		break;
	default:
		break;
	}

}

Player::Status Player::getStatus()
{
	return this->_status;
}

void Player::moveTo(Vec2 toPosition)
{
	if (_isMove)
	{
		auto _position = getPosition();
		float dx = toPosition.x - _position.x;
		float dy = toPosition.y - _position.y;
		float dist = sqrt(dx*dx + dy * dy);
		float interval = dist / (getSpeed());
		auto moveTo = MoveTo::create(interval, toPosition);
		moveTo->setTag(1);
		this->runAction(moveTo);
		LoadingBar *HP = getHP();
		HP->runAction(moveTo);
	}
}

void Player::stopMove()
{
	if (_isMove)
	{
		_isMove = false;
		this->stopActionByTag(1);
		LoadingBar *HP = getHP();
		HP->stopActionByTag(1);
	}
}

void Player::isLocal(bool a)
{
	this->_isLocal = a;
	if (a)
	{
		//待补充
	}
}

bool Player::isLocal()
{
	return _isLocal;
}