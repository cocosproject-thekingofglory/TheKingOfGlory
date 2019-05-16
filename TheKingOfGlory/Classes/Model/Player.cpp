#include"Player.h"
#include<ctime>

USING_NS_CC;

//roleֵͬenum����
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

//��ʼ����Ϣ
bool Player::init(int role)
{
	_status = Status::STANDING;
	_direction = Direction::NONE;
	cocos2d::Size size = this->getContentSize();

	//����ê��? ����******
	this->setAnchorPoint(Vec2(0.5, 0.5));

	initWithRole(role);
	std::string curName = _roleName;
	/*_type = type*/

	//�ڴ˶��嶯���� ֡�� ʾ����
	int animationFrameNum[5] = { 4, 4, 4, 2, 4 };
	int animationFrameNum2[5] = { 3, 3, 3, 2, 0 };
	int animationFrameNum3[5] = { 1, 5, 4, 2, 0 };

	//setup according to PlayerType ����ְҵ
	switch (role)
	{
	case 0:
		//�ڴ����ö��������ٶȵ� ʾ����
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

	//����sprite��ʹ��plist
	/*CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("player1-1.plist");
	CCSprite* sprite = CCSprite:createWithSpriteFrameName("player1-1.plist");*/     //ʹ��֡����ʱ
	CCSprite* sprite = CCSprite::create(curName);
	sprite->setPosition(ccp(100, 100));  //***
	this->addChild(sprite);

	std::string animationNames[] = { "stand","walk","run" };
	_animationNames.assign(animationNames, animationNames + 3);
	this->addAnimation();

	cocos2d::Size size = this->getContentSize();
	log("size: %f,%f", size.width, size.height);

	//���㴥����Ѱ·
	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(Player::onTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

	return true;
}

//ֻ�ǻ������
bool Player::initWithRole(int role)
{
	//����·��
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
	//check if already loaded, ����֡����
	auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s", _name.c_str(),
		_animationNames[0])->getCString());
	if (animation)
		return;

	for (int i = 0; i < _animationNum; i++)
	{
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);  //����

		//put frames into animation
		for (int j = 0; j < _animationFrameNum[i]; j++) {
			auto curName = String::createWithFormat("%s-%d-%d.png", _name.c_str(), i + 1, j + 1)->getCString;
			auto cur = SpriteFrameCache::getInstance()->getSpriteFrameByName(curName);     //����Texture
			animation->addSpriteFrame(curName);
		}

		//put the animation into cache
		AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s", _name.c_str(),
			_animationNames[i].c_str())->getCString());
	}
}

//�ظ�����
void Player::playAnimation(int index)
{
	auto action = this->getActionByTag(index);
	if (action)
		return;

	for (int i = 0; i < 5; i++) {    //��������
		this->stopActionByTag(i);
	}
	if (index < 0 || index >= _animationNum)
	{
		log("illegal animation index!");
		return;
	}

	//�ɸ���
	auto str = String::createWithFormat("%s-%s", _name.c_str(), _animationNames[index].c_str())->getCString();
	auto animation = AnimationCache::getInstance()->getAnimation(str);

	auto animate = RepeatForever::create(Animate::create(animation));
	animate->setTag(index);
	this->runAction(animate);
}

//����
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

//ͬ����ϵ�ж�������ת

//���㴥��,Ѱ·
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

//�붯���й�
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
		//������
	}
}

bool Player::isLocal()
{
	return _isLocal;
}

