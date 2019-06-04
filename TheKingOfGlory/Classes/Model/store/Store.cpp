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

	_bg = Sprite::createWithSpriteFrameName("bg_shop.png");
	_bg->setScaleY(0.6);
	_bg->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	
	Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(_bg, 1);
	
	_closeButton = Button::create("Pictures/Store/closeButton1.png");
	_closeButton->setScale(2);
	_closeButton->setPosition(Vec2(_bg->getContentSize().width - _closeButton->getContentSize().width / 2
		, _bg->getContentSize().height - _closeButton->getContentSize().height));
	_closeButton->setEnabled(true);
	_closeButton->setSwallowTouches(false);


	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			removeBg();
		}
	});
	_bg->addChild(_closeButton,4);

	auto Title = Sprite::createWithSpriteFrameName("shop_title_bg.png");
	Title->setPosition(Vec2(_bg->getContentSize().width / 2
		, _bg->getContentSize().height - Title->getContentSize().height));
	_bg->addChild(Title);

	std::string tip = "Click to see details";
	auto Tip = Text::create(tip, "arial.ttf", 15);
	Tip->setScale(2);
	Tip->setPosition(Vec2(_bg->getContentSize().width / 2
		, _bg->getContentSize().height - Title->getContentSize().height*2));
	_bg->addChild(Tip);
	
	float sy = _bg->getContentSize().height - Title->getContentSize().height * 2;
	float dis = _bg->getContentSize().width / 6;
	for (int i = 1; i <= EQUIPMENT_CNT; i++)
	{
		std::string equipName;
		equipName.append(StringUtils::format("%d.png", i+1000));
		auto equip = EquipmentBase::createWithSpriteFrameName(equipName, i + 1000);
		//equip->setScale(0.5);
		equip->setPosition(Vec2(dis*(i % 5 +1), sy - equip->getContentSize().height * 2 * (((i - 1) / 5) + 1)));
			
		equip->listener->setEnabled(true);
		_bg->addChild(equip, 5, equipName);
		_equipmentList.pushBack(equip);
	}

	if (!VIP)
	{
		VIP = true;
		_vipButton = Button::create("Pictures/Store/text_be_vip.png");
		_vipButton->setScale(2);
		_vipButton->setPosition(Vec2(_bg->getContentSize().width / 2, _vipButton->getContentSize().height));
		_vipButton->setEnabled(true);
		_vipButton->setSwallowTouches(false);

		_vipButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				auto vipSprite = Sprite::createWithSpriteFrameName("vip.png");
				vipSprite->setPosition(Vec2(_bg->getContentSize().width / 2, _bg->getContentSize().height / 2));
				vipSprite->setScale(0.8);
				_bg->addChild(vipSprite, 400);
				EQUIPMENT_CNT = 15;//点充值多5件装备
				auto sequence = Sequence::create(DelayTime::create(3.0f), CallFunc::create([=]()
				{
					_bg->removeChild(vipSprite, true);
				}), NULL);
				this->runAction(sequence);
			}
		});
		_bg->addChild(_vipButton, 4);
	}

}

void Store::removeBg()
{
	if (!_hasbg)return;
	_hasbg = false;

	for (int i = 0; i < _equipmentList.size(); i++)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_equipmentList.at(i)->listener);
	}
	_equipmentList.clear();
	_bg->removeAllChildrenWithCleanup(true);
	Director::getInstance()->getRunningScene()->getChildByName("GameScene")->removeChild(_bg, true);
}
