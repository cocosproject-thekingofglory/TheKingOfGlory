#include "Store.h"


bool Store::init(int color)
{
	if (!Tower::init(color))
	{
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();

	
	_storeMenu = Sprite::create("Pictures/UI/Menu1.png");
	_storeMenu->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));

	createCloseButton();

	float sx = _visibleSize.width - _storeMenu->getContentSize().width;
	float sy = _visibleSize.height - _storeMenu->getContentSize().height;
	for (int i = 1; i <= EQUIPMENT_CNT; i++)
	{
		std::string equipName;
		equipName.append(StringUtils::format("%d.png", i + 1000));
		auto equip = EquipmentBase::createWithSpriteFrameName(equipName);
		equip->setPosition(Vec2(sx + i % 3 * equip->getContentSize().width + 10.0,
			sy + i / 3 * equip->getContentSize().height + 10.0));
		_equipmentList.pushBack(equip);
	}

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
	createMenu();
}

void Store::createMenu()
{
	this->addChild(_storeMenu, 9);
	this->addChild(_closeButton, 10);
	
	for (int i = 0; i <= _equipmentList.size(); i++)
	{
		_storeMenu->addChild(_equipmentList.at(i),10);
	}
}


void Store::createCloseButton()
{
	_closeButton = Button::create("Pictures/UI/Close.png");
	_closeButton->setScale(1);
	_closeButton->setPosition(Vec2(_visibleSize.width + _storeMenu->getContentSize().width - _closeButton->getContentSize().width,
		_visibleSize.height + _storeMenu->getContentSize().height - _closeButton->getContentSize().height));
	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			for (int i = 0; i <= _equipmentList.size(); i++)
			{
				_storeMenu->removeChild(_equipmentList.at(i), false);
			}
			this->removeChild(_storeMenu, false);
		}
	});
}