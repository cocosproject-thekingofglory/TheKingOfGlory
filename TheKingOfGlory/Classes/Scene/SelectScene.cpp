#include "SelectScene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "SelectPlayerScene.h"
#include "UI/Tip.h"
USING_NS_CC;
using namespace ui;

cocos2d::Scene * SelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createButton();

	UserDefault::getInstance()->setBoolForKey("Network", false);
	return true;
}

void SelectScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto background = Sprite::create("Pictures/Background/SelectBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

}

void SelectScene::createButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto offline = Button::create("Pictures/UI/brownButton.png");
	offline->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.63));
	offline->setTitleText("Offline Mode");
	offline->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	offline->setTitleFontSize(32);
	offline->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, SelectPlayerScene::createScene(nullptr)));

	});
	this->addChild(offline);

	auto online = Button::create("Pictures/UI/brownButton.png");
	online->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	online->setTitleText("Online Mode");
	online->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	online->setTitleFontSize(32);
	online->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, SelectModeScene::createScene()));

	});
	this->addChild(online);

	auto back = Button::create("Pictures/UI/brownButton.png");
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.37));
	back->setTitleText("Back");
	back->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	back->setTitleFontSize(32);
	back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::createScene()));

	});
	this->addChild(back);
}
cocos2d::Scene * SelectModeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectModeScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectModeScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createButton();

	return true;
}

void SelectModeScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto background = Sprite::create("Pictures/Background/SelectBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

}

void SelectModeScene::createButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto One = Button::create("Pictures/UI/brownButton.png");
	One->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.63));
	One->setTitleText("1v1 Mode");
	One->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	One->setTitleFontSize(32);
	One->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		UserDefault::getInstance()->setIntegerForKey("Mode", 1);
		Director::getInstance()->replaceScene(TransitionFade::create(1, OnlineScene::createScene()));

	});
	this->addChild(One);

	auto Five = Button::create("Pictures/UI/brownButton.png");
	Five->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Five->setTitleText("5v5 Mode");
	Five->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	Five->setTitleFontSize(32);
	Five->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		UserDefault::getInstance()->setIntegerForKey("Mode", 5);
		Director::getInstance()->replaceScene(TransitionFade::create(1, OnlineScene::createScene()));

	});
	this->addChild(Five);

	auto back = Button::create("Pictures/UI/brownButton.png");
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.37));
	back->setTitleText("Back");
	back->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	back->setTitleFontSize(32);
	back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, SelectScene::createScene()));

	});
	this->addChild(back);
}

cocos2d::Scene * OnlineScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OnlineScene::create();
	scene->addChild(layer);
	return scene;
}

bool OnlineScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createButton();

	UserDefault::getInstance()->setBoolForKey("Network", true);

	return true;
}

void OnlineScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Pictures/Background/SelectBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

}

void OnlineScene::createButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto server = Button::create("Pictures/UI/brownButton.png");
	server->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.63));
	server->setTitleText("Start As Server");
	server->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	server->setTitleFontSize(30);
	server->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, ServerScene::createScene()));

	});
	this->addChild(server);

	auto client = Button::create("Pictures/UI/brownButton.png");
	client->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	client->setTitleText("Start As Client");
	client->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	client->setTitleFontSize(30);
	client->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, ClientScene::createScene()));

	});
	this->addChild(client);

	auto back = Button::create("Pictures/UI/brownButton.png");
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.37));
	back->setTitleText("Back");
	back->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	back->setTitleFontSize(32);
	back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		Director::getInstance()->replaceScene(TransitionFade::create(1, SelectModeScene::createScene()));

	});
	this->addChild(back);
}

cocos2d::Scene * ServerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ServerScene::create();
	scene->addChild(layer);
	return scene;
}

bool ServerScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createButton();
	createInput();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	connectionMsg = Label::createWithTTF(" ","fonts/arial.ttf", 24);
	connectionMsg->setPosition(Vec2( visibleSize.width / 2,visibleSize.height*0.1));
	this->addChild(connectionMsg);

	return true;
}

void ServerScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Pictures/Background/SelectBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

}

void ServerScene::createButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto server = Button::create("Pictures/UI/brownButton.png");
	server->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.63));
	server->setTitleText("Start Server");
	server->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	server->setTitleFontSize(32);
	server->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (!gameServer)
		{
			int port = std::stoi(portInput->getString());
			gameServer = Server::create(port);
			gameClient = Client::create("127.0.0.1", port);
			log("create server and client on %d",port);
			schedule(CC_CALLBACK_0(ServerScene::connectionSchedule, this), 0.2f, "Connection");
		}

	});
	this->addChild(server);

	auto start = Button::create("Pictures/UI/brownButton.png");
	start->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	start->setTitleText("Start Game");
	start->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	start->setTitleFontSize(32);
	start->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (gameServer&&gameServer->connection_num() >= 2 * UserDefault::getInstance()->getIntegerForKey("Mode"))
		{
			gameServer->button_start();
			if (gameClient->getMessage() == "SelectHero")
				Director::getInstance()->replaceScene(TransitionSplitCols::create(1.0, SelectPlayerScene::createScene(gameClient, gameServer)));
			log("start game");

		}
		else
		{
			auto tip = Tip::create("Unable to start game,wait for more players", 2.0f, Color4B::WHITE);
			tip->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.15));
			this->addChild(tip);
		}
	});
	this->addChild(start);

	auto back = Button::create("Pictures/UI/brownButton.png");
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.37));
	back->setTitleText("Back");
	back->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	back->setTitleFontSize(32);
	back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (gameServer)
		{
			unscheduleAllCallbacks();
			gameServer->close();
			delete gameServer;
			gameServer = nullptr;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			gameServer->close();
			delete gameServer;
			gameServer = nullptr;
		}
		Director::getInstance()->replaceScene(TransitionFade::create(1, OnlineScene::createScene()));

	});
	this->addChild(back);
}

void ServerScene::createInput()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建文本输入框
	auto inputBG = Sprite::create("Pictures/UI/brownButton.png");

	portInput = ui::TextField::create("Input Port", "fonts/arial.ttf", 28);
	portInput->setString("8008");
	portInput->setCursorChar('|');
	portInput->setCursorEnabled(true);
	portInput->setMaxLength(5);
	portInput->setMaxLengthEnabled(true);
	portInput->setPosition(inputBG->getContentSize() / 2);
	portInput->setTouchSize(inputBG->getContentSize());
	portInput->setTouchAreaEnabled(true);

	inputBG->addChild(portInput);
	inputBG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.85));

	this->addChild(inputBG);
}

void ServerScene::connectionSchedule()
{
	if (gameServer->connection_num())
		connectionMsg->setString("Total connection num: " + std::to_string(gameServer->connection_num()));
	else
		connectionMsg->setString("Port already used, please change another one");
}

cocos2d::Scene * ClientScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ClientScene::create();
	scene->addChild(layer);
	return scene;
}

bool ClientScene::init()
{
	if (!Layer::init())
		return false;

	createBackground();
	createButton();
	createInput();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	connectionMsg = Label::createWithTTF("", "fonts/arial.ttf", 24);
	connectionMsg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.1));
	this->addChild(connectionMsg);

	return true;
}

void ClientScene::createBackground()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("Pictures/Background/SelectBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

}

void ClientScene::createButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto box = Sprite::create("Pictures/UI/buttonBox.png");
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box);

	auto join = Button::create("Pictures/UI/brownButton.png");
	join->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.57));
	join->setTitleText("Join Game");
	join->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	join->setTitleFontSize(32);
	join->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (!gameClient)
		{
			auto ip = ipInput->getString();
			int port = std::stoi(portInput->getString());
			log("ip:%s, port:%d", ip.c_str(), port);
			gameClient = Client::create(ip, port);
			schedule(CC_CALLBACK_0(ClientScene::startSchedule,this), 0.2f,"Start");	
		}
	});
	this->addChild(join);

	auto back = Button::create("Pictures/UI/brownButton.png");
	back->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.43));
	back->setTitleText("Back");
	back->setTitleFontName("Fonts/Quicksand-Bold.ttf");
	back->setTitleFontSize(32);
	back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		if (gameClient)
		{
			unscheduleAllSelectors();
			gameClient->close();
			delete gameClient;
			gameClient = nullptr;
		}
		Director::getInstance()->replaceScene(TransitionFade::create(1, OnlineScene::createScene()));

	});
	this->addChild(back);
}

void ClientScene::createInput()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	{
		auto inputBG = Sprite::create("Pictures/UI/brownButton.png");

		ipInput = ui::TextField::create("Input IP", "fonts/arial.ttf", 24);
		ipInput->setString("127.0.0.1");
		ipInput->setCursorChar('|');
		ipInput->setCursorEnabled(true);
		ipInput->setMaxLength(16);
		ipInput->setMaxLengthEnabled(true);
		ipInput->setPosition(inputBG->getContentSize() / 2);
		ipInput->setTouchSize(inputBG->getContentSize());
		ipInput->setTouchAreaEnabled(true);

		inputBG->addChild(ipInput);
		inputBG->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.85));

		this->addChild(inputBG);
	}

	{
		auto inputBG = Sprite::create("Pictures/UI/brownButton.png");

		portInput = ui::TextField::create("Input Port", "fonts/arial.ttf", 24);
		portInput->setString("8008");
		portInput->setCursorChar('|');
		portInput->setCursorEnabled(true);
		portInput->setMaxLength(5);
		portInput->setMaxLengthEnabled(true);
		portInput->setPosition(inputBG->getContentSize() / 2);
		portInput->setTouchSize(inputBG->getContentSize());
		portInput->setTouchAreaEnabled(true);

		inputBG->addChild(portInput);
		inputBG->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.85));

		inputBG->setScaleX(0.6f);
		portInput->setScaleX(1.0f / 0.6f);

		this->addChild(inputBG);
	}

}

void ClientScene::waitStart()
{
	if (gameClient->remainMessage())
	{
		if (gameClient->getMessage() == "SelectHero")
			Director::getInstance()->replaceScene(TransitionSplitCols::create(1, SelectPlayerScene::createScene(gameClient)));
	}


}

void ClientScene::startSchedule()
{
	if (gameClient->error())
	{
		unscheduleAllCallbacks();
		gameClient->close();
		delete gameClient;
		gameClient = nullptr;
		connectionMsg->setString("Cannot connect to the server, please try again");
		return;
	}
	switch ((timer_++ /16)% 4)
	{
	case 0: connectionMsg->setString("Connected, wait for server"); break;
	case 1: connectionMsg->setString("Connected, wait for server."); break;
	case 2: connectionMsg->setString("Connected, wait for server.."); break;
	case 3: connectionMsg->setString("Connected, wait for server..."); break;
	default: break;
	}
	if (gameClient->started())
		waitStart();
}
