#include"SelectPlayerScene.h"
#include "UI/CocosGUI.h"
#include"Util/GameAudio.h" 
#include "GameScene.h"
#include "Model/User.h"

USING_NS_CC;
using namespace ui;

Scene* SelectPlayerScene::createScene(Client* client, Server*server)
{
	auto scene = Scene::create();
	auto layer = SelectPlayerScene::create(client,server);
	scene->addChild(layer);
	return scene;
}

SelectPlayerScene * SelectPlayerScene::create(Client * client, Server * server)
{
	SelectPlayerScene *scene = new (std::nothrow) SelectPlayerScene();
	if (scene && scene->init(client, server))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);

	return nullptr;
}

bool SelectPlayerScene::init(Client* client, Server* server)
{
	if (!Layer::init())
	{
		return false;
	}
	isOnline = UserDefault::getInstance()->getBoolForKey("Network");
	_client = client;
	_server = server;

	selected = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Ìí¼Ó±³¾°Í¼Æ¬
	auto bg = Sprite::create("Pictures/Background/SelectBackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, -1);

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto textBg = Sprite::create("Pictures/UI/brownButton.png");
	textBg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.85));
	textBg->setScaleX(2.0);
	this->addChild(textBg);

	auto text = Text::create("Please Select Hero", "fonts/Quicksand-Bold.ttf", 40);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.85));
	this->addChild(text);

	connectionMsg = Label::createWithTTF("", "fonts/arial.ttf", 24);
	connectionMsg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.1));
	this->addChild(connectionMsg);

	std::string  text_Font= "Fonts/Quicksand-Bold.ttf";
	auto text_Size = 32;

	{
		auto warriorButton = Button::create("Pictures/UI/shortbrownButton.png");
		warriorButton->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.6));
		warriorButton->setTitleText("Warrior");
		warriorButton->setTitleFontName(text_Font);
		warriorButton->setTitleFontSize(text_Size);
		warriorButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(0);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;

		});
		this->addChild(warriorButton);
	}

	{
		auto aviatorButton = Button::create("Pictures/UI/shortbrownButton.png");
		aviatorButton->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.5));
		aviatorButton->setTitleText("Aviator");
		aviatorButton->setTitleFontName(text_Font);
		aviatorButton->setTitleFontSize(text_Size);
		aviatorButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(1);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;

		});
		this->addChild(aviatorButton);
	}

	{
		auto mageButton = Button::create("Pictures/UI/shortbrownButton.png");
		mageButton->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.4));
		mageButton->setTitleText("Mage");
		mageButton->setTitleFontName(text_Font);
		mageButton->setTitleFontSize(text_Size);
		mageButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(2);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;

		});
		this->addChild(mageButton);
	}

	{
		auto paladinButton = Button::create("Pictures/UI/shortbrownButton.png");
		paladinButton->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.6));
		paladinButton->setTitleText("Paladin");
		paladinButton->setTitleFontName(text_Font);
		paladinButton->setTitleFontSize(text_Size);
		paladinButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(3);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;
		});
		this->addChild(paladinButton);
	}

	{
		auto rangerButton = Button::create("Pictures/UI/shortbrownButton.png");
		rangerButton->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.5));
		rangerButton->setTitleText("Ranger");
		rangerButton->setTitleFontName(text_Font);
		rangerButton->setTitleFontSize(text_Size);
		rangerButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(4);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;

		});
		this->addChild(rangerButton);
	}

	{
		auto cavalierButton = Button::create("Pictures/UI/shortbrownButton.png");
		cavalierButton->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.4));
		cavalierButton->setTitleText("Cavalier");
		cavalierButton->setTitleFontName(text_Font);
		cavalierButton->setTitleFontSize(text_Size);
		cavalierButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type != ui::Widget::TouchEventType::ENDED) return;
			if (selected) return;
			User::getInstance()->setRole(5);
			if (isOnline)
			{
				client->sendMessage("SelectOK");
				schedule(CC_CALLBACK_0(SelectPlayerScene::startSchedule, this), 0.2f, "Start");
			}
			else
			{
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1, GameScene::createScene(nullptr)));
			}
			selected = true;

		});
		this->addChild(cavalierButton);
	}



	return true;
}

void SelectPlayerScene::startSchedule()
{
	switch ((timer_++ / 16) % 4)
	{
	case 0: connectionMsg->setString("Selected, wait for other to select"); break;
	case 1: connectionMsg->setString("Selected, wait for other to select."); break;
	case 2: connectionMsg->setString("Selected, wait for other to select.."); break;
	case 3: connectionMsg->setString("Selected, wait for other to select..."); break;
	default: break;
	}
	if (_client->remainMessage())
	{
		if (_client->getMessage() == "StartGame")
			Director::getInstance()->replaceScene(TransitionSplitCols::create(1.0, GameScene::createScene(_client, _server)));
	}
	
}