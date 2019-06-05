#include "StoreScene.h"
#include "Util/GameAudio.h"

Scene* StoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StoreScene::create();
	scene->addChild(layer);
	return scene;
}


bool StoreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();

	Sprite * bg = Sprite::create("Pictures/Background/SettingBackground.png");
	bg->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	this->addChild(bg, 1);

	
	for (int i = 1; i <= EQUIPMENT_CNT; i++)
	{
		std::string equipName;
		equipName.append(StringUtils::format("%d.png", i + 1000));
		auto equip = EquipmentBase::createWithSpriteFrameName(equipName);
		equip->setPosition(Vec2(i % 5 * equip->getContentSize().width + 10.0,
			i / 5 * equip->getContentSize().height + 10.0));
		_equipmentList.pushBack(equip);
		this->addChild(equip);
	}
	
	//createCloseButton();
	addChild(createText());

	return true;
}

cocos2d::Menu* StoreScene::createText()
{
	const auto buttons = Menu::create();

	const auto backButton = MenuItemLabel::create(
		Label::createWithTTF("OK", "fonts/UnifrakturCook-Bold.ttf", 64),
		CC_CALLBACK_1(StoreScene::menuOkCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto baseY = visibleSize.height * 0.85f;

	backButton->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.2f);
	static_cast<Label*>(backButton->getLabel())->enableGlow(Color4B(0, 0, 0, 255 * 0.6f));

	buttons->addChild(backButton, 1);

	buttons->setPosition(0, 0);

	return buttons;
}

void StoreScene::menuOkCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

void StoreScene::createCloseButton()
{
	_closeButton = Button::create("Pictures/UI/Close.png");
	_closeButton->setScale(1);
	_closeButton->setPosition(Vec2(_visibleSize.width + _storeMenu->getContentSize().width - _closeButton->getContentSize().width,
		_visibleSize.height + _storeMenu->getContentSize().height - _closeButton->getContentSize().height));
	_closeButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			for (int i = 0; i < _equipmentList.size(); i++)
				_equipmentList.at(i)->listener->setEnabled(false);
			Director::getInstance()->popScene();
		}
	});
	this->addChild(_closeButton, 10);
}


void StoreScene::onEnter()
{
	Layer::onEnter();
}