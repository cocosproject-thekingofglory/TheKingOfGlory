#include "Store.h"
#include "../../Manager/Manager.h"

bool Store::init(int color)
{
	if (!Tower::init(color))
	{
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();

	createListener();

	return true;
}

Store* Store::createWithSpriteFrameName(const std::string& filename, int color)
{
	auto store = new Store();
	if (store && store->initWithSpriteFrameName(filename) && store->init(color))
	{
		store->autorelease();
		return store;
	}
	CC_SAFE_DELETE(store);
	return nullptr;
}

void Store::createListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Store::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Store::onTouchEnded, this);
	listener->setEnabled(true);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 9);
}
bool Store::onTouchBegan(Touch*touch, Event*event)
{
	Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
	if (rect.containsPoint(touchPos))
	{
		return true;
	}
	return false;
}
void Store::onTouchEnded(Touch*touch, Event*event)
{
	createBg();
}


void Store::createBg()
{
	if (_hasbg)return;
	_hasbg = true;

	_bg = Sprite::create("Pictures/UI/Menu1.png");
	//_bg->setPosition(Vec2(0, 0));
	_bg->setScaleX(3);
	//this->addChild(_bg,1);
	Manager::getInstance()->playerManager->getLocalPlayer()->addChild(_bg, 1);
	//createCloseButton();
	_closeButton = Button::create("Pictures/UI/Close.png");
	_closeButton->setScale(1);
	_closeButton->setPosition(Vec2(_bg->getContentSize().width - _closeButton->getContentSize().width
		, _bg->getContentSize().height - _closeButton->getContentSize().height));

	auto sequence = Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]()
	{
		schedule(CC_CALLBACK_0(Store::bgMove, this), 0.1f, "bgMove");
	}), NULL);
	this->runAction(sequence);

	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			removeBg();
		}
	});
	_bg->addChild(_closeButton,4);

	
	for (int i = 1; i <= EQUIPMENT_CNT; i++)
	{
		std::string equipName;
		equipName.append(StringUtils::format("%d.png", i+1000));
		auto equip = EquipmentBase::createWithSpriteFrameName(equipName, i + 1000);
		equip->setScale(0.5);
		equip->setPosition(Vec2(equip->getContentSize().width / 2 * (i % 5),
			equip->getContentSize().height / 2 * (i + 5) / 5));
		equip->listener->setEnabled(true);
		_bg->addChild(equip, 5, equipName);
		_equipmentList.pushBack(equip);
	}
	/*
	auto equip = EquipmentBase::createWithSpriteFrameName("1001.png", 1001);
	equip->setPosition(Vec2(0, 0));
		
	//equip->listener->setEnabled(true);
	//log("!!!!!!!!!!!%d %f %f", equip->getDamage(),equip->getHP(),equip->getDefend());
	equip->setScale(3);
	_bg->addChild(equip, 5);
	*/
}

void Store::removeBg()
{
	if (!_hasbg)return;
	_hasbg = false;

	unschedule("bgMove");
	for (int i = 0; i < _equipmentList.size(); i++)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_equipmentList.at(i)->listener);
	}
	_bg->removeAllChildrenWithCleanup(true);
	Manager::getInstance()->playerManager->getLocalPlayer()->removeChild(_bg, true);
	//this->removeChild(_bg, true);
}

void Store::bgMove()
{
	float x, y;
	Vec2 playerpos = Manager::getInstance()->playerManager->getLocalPlayer()->getPosition();
	Size mapsize = GameMap::getCurrentMap()->getMapSize();
	mapsize.width *= 60; mapsize.height *= 60;
	//log("%f %f %f", _visibleSize.width, mapsize.width, playerpos.x);
	if (playerpos.x <= _visibleSize.width / 2)
	{
		x = _visibleSize.width / 2 - playerpos.x;
	}
	else if (_visibleSize.width / 2 + playerpos.x >= mapsize.width)
	{
		x = mapsize.width - (_visibleSize.width / 2 - playerpos.x);
	}
	else x = 0;

	if (playerpos.y <= _visibleSize.height / 2)
	{
		y = _visibleSize.height / 2 - playerpos.y;
	}
	else if (_visibleSize.height / 2 + playerpos.y >= mapsize.height)
	{
		y = mapsize.height - (_visibleSize.height / 2 - playerpos.y);
	}
	else y = 0;
	_bg->setPosition(Vec2(x, y));
}