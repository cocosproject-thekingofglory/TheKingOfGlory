#include "StatusList.h"

bool StatusList::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	this->setScale(3.0);

	auto _closeButton = Button::create("Pictures/Store/closeButton1.png");
	//_closeButton = Sprite::createWithSpriteFrameName("closeButton1.png");
	_closeButton->setScale(0.5);
	_closeButton->setScaleX(1.3);
	_closeButton->setEnabled(true);
	_closeButton->setSwallowTouches(true);

	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			remove();
		}
	});
	_closeButton->setPosition(Vec2(160, 200));

	this->addChild(_closeButton,40);
	auto localPlayer= Manager::getInstance()->playerManager->getLocalPlayer();

	float mid = 90;
	std::string context = "Level : ";
	context.append(StringUtils::format("%d", localPlayer->getLevel()));
	auto text1 = createText(context);
	text1->setPosition(Vec2(mid, text1->getContentSize().height * 15));
	this->addChild(text1, 40);
	
	context = "HP : ";
	context.append(StringUtils::format("%.2f / %.2f", localPlayer->getNowHPValue(), localPlayer->getHPValue()));
	auto text2 = createText(context);
	text2->setPosition(Vec2(mid, text2->getContentSize().height * 14));
	this->addChild(text2, 40);

	context = "EXP : ";
	context.append(StringUtils::format("%d / %d", localPlayer->getNowEXPValue(), localPlayer->getEXPValue()));
	auto text3 = createText(context);
	text3->setPosition(Vec2(mid, text3->getContentSize().height * 13));
	this->addChild(text3, 40);

	context = "Damage : ";
	context.append(StringUtils::format("%.0f", localPlayer->getDamage()));
	auto text4 = createText(context);
	text4->setPosition(Vec2(mid, text4->getContentSize().height * 12));
	this->addChild(text4, 40);

	context = "Defend : ";
	context.append(StringUtils::format("%.2f", localPlayer->getDefend()));
	auto text5 = createText(context);
	text5->setPosition(Vec2(mid, text5->getContentSize().height * 11));
	this->addChild(text5, 40);

	context = "Defend : ";
	context.append(StringUtils::format("%.2f", localPlayer->getDefend()));
	auto text6 = createText(context);
	text6->setPosition(Vec2(mid, text6->getContentSize().height * 10));
	this->addChild(text6, 40);

	context = "Money : ";
	context.append(StringUtils::format("%d", localPlayer->getMoney()));
	auto text7 = createText(context);
	text7->setPosition(Vec2(mid, text7->getContentSize().height * 9));
	this->addChild(text7, 40);


	auto equipmentList = Manager::getInstance()->playerManager->getLocalPlayer()->getEquipmentList();
	for (int i = 0; i < equipmentList.size(); i++)
	{
		equipmentList.at(i)->setScale(0.2);
		equipmentList.at(i)->setPosition(Vec2(40 + 20 * i, 70));
		this->addChild(equipmentList.at(i), 40);

		auto _sellButton = Button::create("Pictures/Store/sellButton.png");
		_sellButton->setScale(0.2);
		_sellButton->setEnabled(true);
		_sellButton->setSwallowTouches(true);

		_sellButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				sell(equipmentList.at(i));
				_sellButton->setEnabled(false);
				_sellButton->removeFromParent();
			}
		});
		_sellButton->setPosition(Vec2(40 + 20 * i, 50));
		this->addChild(_sellButton, 40);
	}
	return true;
}

StatusList*StatusList::createStatusList()
{
	auto bg = new StatusList();
	if (bg&& bg->init() && bg->initWithSpriteFrameName(BG_FILENAME))
	{
		bg->autorelease();
		return bg;
	}
	CC_SAFE_DELETE(bg);
	return nullptr;
}

Text* StatusList::createText(std::string context)
{
	auto text = Text::create(context, "fonts/ConcertOne-Regular.ttf", 15);
	text->setScaleX(0.5);
	return text;
}

void StatusList::remove()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParent();
	hasList = false;
}

void StatusList::sell(EquipmentBase*equip)
{
	auto _localplayer = Manager::getInstance()->playerManager->getLocalPlayer();
	_localplayer->addMoney(equip->getCostMoney() / 2);
	log("sell a equipment.");
	_localplayer->removeEquipment(equip);
	_localplayer->addDamage(-equip->getDamage());
	_localplayer->addDefend(-equip->getDefend());
	_localplayer->addHPValue(-equip->getHP());
	equip->removeFromParent();
}

