#include "EquipmentBase.h"
#include "../../Manager/Manager.h"

bool EquipmentBase::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}
	setId(id);

	createListener();

	setHP(HP[_id - 1000]);
	setDamage(DAMAGE[_id - 1000]);
	setDefend(DEFEND[_id - 1000]);
	setCostMoney(MONEY[_id - 1000]);
	
	return true;
}

EquipmentBase* EquipmentBase::createWithSpriteFrameName(const std::string& filename, int id)
{
	auto sprite = new EquipmentBase();
	if (sprite  && sprite->init(id))
	{
		if (sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}

	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


void EquipmentBase::createListener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EquipmentBase::onTouchBegin, this);
	listener->onTouchEnded = CC_CALLBACK_2(EquipmentBase::onTouchEnded, this);
	listener->setEnabled(false);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10);
}

bool EquipmentBase::onTouchBegin(Touch*touch, Event*event)
{
	Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
	if (rect.containsPoint(touchPos))
	{
		return true;
	}
	return false;
}

void EquipmentBase::onTouchEnded(Touch*touch, Event*event)
{
	if (_hasbg)return;
	_hasbg = true;

	auto parent = this->getParent();

	auto& bg = _bg;
	bg = Sprite::createWithSpriteFrameName("bot_frame.png");
	bg->setScaleX(0.7);
	bg->setScaleY(3.0);
	bg->setPosition(Vec2(parent->getContentSize().width / 2, parent->getContentSize().height / 2));
	parent->addChild(bg, 40);

	auto _closeButton = Button::create("Pictures/Store/closeButton1.png");
	_closeButton->setScale(1.3);
	_closeButton->setScaleX(1.3);
	_closeButton->setPosition(Vec2(bg->getContentSize().width - _closeButton->getContentSize().width
		, bg->getContentSize().height - _closeButton->getContentSize().height));
	_closeButton->setEnabled(true);
	_closeButton->setSwallowTouches(false);

	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			removeBg();
		}
	});
	bg->addChild(_closeButton);


	int id = _id - 1000;
	std::string context = "HP + ";
	context.append(StringUtils::format("%.0f", HP[id]));
	auto text4 = createText(context);
	text4->setPosition(Vec2(bg->getContentSize().width / 2, text4->getContentSize().height * 7));
	bg->addChild(text4, 40);

	context = "DAMAGE + ";
	context.append(StringUtils::format("%.0f", DAMAGE[id]));
	auto text3 = createText(context);
	text3->setPosition(Vec2(bg->getContentSize().width / 2, text3->getContentSize().height * 6));
	bg->addChild(text3, 40);

	context = "DEFEND + ";
	context.append(StringUtils::format("%.2f", DEFEND[id]));
	auto text2 = createText(context);
	text2->setPosition(Vec2(bg->getContentSize().width / 2, text2->getContentSize().height * 5));
	bg->addChild(text2, 40);

	context = "MONEY";
	context.append(StringUtils::format("  %d", MONEY[id]));
	auto text1 = createText(context);
	text1->setPosition(Vec2(bg->getContentSize().width / 2, text1->getContentSize().height * 4));
	bg->addChild(text1, 40);

	//auto sprite = Sprite::createWithSpriteFrameName("text_sm_goumai.png");
	auto buyButton = Button::create("Pictures/Store/text_sm_goumai.png");
	buyButton->setScaleX(2.0);
	buyButton->setPosition(Vec2(bg->getContentSize().width / 2, text1->getContentSize().height * 2.5));
	buyButton->setEnabled(true);
	buyButton->setSwallowTouches(false);

	buyButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			buy();
		}
	});
	bg->addChild(buyButton, 40);
}

Text* EquipmentBase::createText(std::string context)
{
	auto text=Text::create(context, "arial.ttf", 20);
	text->setScaleX(1.5);
	return text;
}

void EquipmentBase::removeBg()
{
	if (!_hasbg)return;
	_hasbg = false;

	_bg->removeAllChildrenWithCleanup(true);
	this->getParent()->removeChild(_bg, true);
}

void EquipmentBase::buy()
{
	auto _localplayer = Manager::getInstance()->playerManager->getLocalPlayer();
	if (_localplayer->getEquipmentCnt() < PLAYER_MAX_EQUIPMENT_CNT)
	{
		if (_localplayer->getMoney() >= getCostMoney())
		{
			_localplayer->addMoney(-getCostMoney());
			log("buy a equipment.");
			_localplayer->addEquipment(this, _id);
			_localplayer->addDamage(getDamage());
			_localplayer->addDefend(getDefend());
			_localplayer->addHPValue(getHP());
			_localplayer->addEquipment(this, _id);
		}
		else
		{
			/*钱不够的提示*/
			log("You don't have enough money!");
		}
	}
	else
	{
		/*装备栏已满的提示*/
		log("You already have three equipments!");
	}
}