#include"Player.h"
#include<ctime>

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
	cocos2d::Size size = this->getContentSize();

	//设置锚点? 待修******
	this->setAnchorPoint(Vec2(0.5, 0.5));

	initWithRole(role);
	std::string curName = _roleName;
	/*_type = type*/

	//在此定义动作数 帧数 示例：
	int animationFrameNum[5] = { 4, 4, 4, 2, 4 };
	int animationFrameNum2[5] = { 3, 3, 3, 2, 0 };
	int animationFrameNum3[5] = { 1, 5, 4, 2, 0 };

	//setup according to PlayerType 区别职业
	switch (role)
	{
	case 0:
		//在此设置动作数、速度等 示例：
		_animationNum = 5;
		_animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
		_speed = 100;
		break;
	case 1:
		_animationNum = 4;
		_animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
		_speed = 100;
		break;
	case 2:
		_animationNum = 4;
		_animationFrameNum.assign(animationFrameNum3, animationFrameNum3 + 5);
		_speed = 100;
		break;
	}

	//创建sprite，使用plist
	/*CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("player1-1.plist");
	CCSprite* sprite = CCSprite:createWithSpriteFrameName("player1-1.plist");*/     //使用帧缓存时
	CCSprite* sprite = CCSprite::create(curName);
	sprite->setPosition(ccp(100, 100));  //***
	this->addChild(sprite);

	std::string animationNames[] = { "stand","walk","run" };
	_animationNames.assign(animationNames, animationNames + 3);
	this->addAnimation();

	cocos2d::Size size = this->getContentSize();
	log("size: %f,%f", size.width, size.height);

	//单点触摸，寻路
	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(Player::onTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	return true;
}

//只是获得名字
bool Player::initWithRole(int role)
{
	//设置路径
	_roleName = std::string(roleName[role]);
	auto file = "GameItem/Player/" + _roleName + "/default.png";

	if (this->initWithFile(file) && this->init())
	{
		// do something here
		return true;
	}
	return false;
}

void Player::addAnimation()
{
	//check if already loaded, 动画帧缓存
	auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _name.c_str(),
		_animationNames[0])->getCString());
	if (animation)
		return;

	for (int i = 0; i < _animationNum; i++)
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);  //待定

		//put frames into animation
		for (int j = 0; j < _animationFrameNum[i]; j++) {
			auto curName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i + 1, j + 1)->getCString;
			auto cur = SpriteFrameCache::getInstance()->getSpriteFrameByName(curName);     //纹理？Texture
			animation->addSpriteFrame(curName);
		}

		//put the animation into cache
		AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s", _name.c_str(),
			_animationNames[i].c_str())->getCString());
	}
}

//重复播放
void Player::playAnimation(int index)
{
	auto action = this->getActionByTag(index);
	if (action)
		return;

	for (int i = 0; i < 5; i++) {    //次数待定
		this->stopActionByTag(i);
	}
	if (index < 0 || index >= _animationNum)
	{
		log("illegal animation index!");
		return;
	}

	//可复用
	auto str = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[index].c_str())->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(str);

	auto animate = RepeatForever::create(Animate::create(animation));
	animate->setTag(index);
	this->runAction(animate);
}

//复用
Animate* Player::getAnimateByType(AnimationType type)
{
	if (type < 0 || type >= _animationNum)
	{
		return nullptr;
	}
	auto str = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[type].c_str())->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(str);

	auto animate = Animate::create(animation);
	animate->setTag(type);
	return animate;
}

//同理复用系列动作，翻转

//单点触摸,寻路
bool Player::onTouch(Touch* touch, Event* event)
{
	auto pos = this->convertToNodeSpace(touch->getLocation());
	//log("Touching: *f, %f...", pos.x, pos.y);

	auto size = this->getContentSize();
	auto rect = Rect(size.width / 2, 0, size.width, size.height);

	if (rect.containsPoint(pos))
	{
		NotificationCenter::getInstance()->postNotification("click", this);
		//log("touched!");
		return true;
	}
	//log("untouched!");
	return false;
}

//与动作有关
void Player::setStatus(Player::Status status)
{
	this->_status = status;

	//Or do animation here:

}

Player::Status Player::getStatus()
{
	return this->_status;
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

