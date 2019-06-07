#include "GameController.h"
#include "Util/GameAudio.h"
#include "Model/User.h"

USING_NS_CC;
using namespace CocosDenshion;

GameController * GameController::create(Client* client, Server*server)
{
	GameController *gamecontroller = new (std::nothrow) GameController();
	if (gamecontroller && gamecontroller->init(client, server))
	{
		gamecontroller->autorelease();
		return gamecontroller;
	}
	CC_SAFE_DELETE(gamecontroller);

	return nullptr;
}
bool GameController::init(Client* client, Server*server)
{
	if (!Layer::init())
		return false;
	this->setName("GameController");
	map = nullptr;
	isOnline = UserDefault::getInstance()->getBoolForKey("Network");
	gameClient = client;
	gameServer = server;

	createTouchListener();
	createKeyListener();
	scheduleOnce(schedule_selector(GameController::initGame), 1.5f);

	auto gameStartListener = EventListenerCustom::create("GameStart", [=](cocos2d::EventCustom* event) {
		touchListener->setEnabled(true);
		keyListener->setEnabled(true);
		for (auto& skill : _skillList)
		{
			skill->setEnabled(true);
		}
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameStartListener, 1);

	auto gameOverListener = EventListenerCustom::create("ToOver", CC_CALLBACK_1(GameController::toOver, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameOverListener, 1);

	if (isOnline)
	{
		CLIENT_ON(GameMsg::MsgType_MsgType_GameInit, GameController::onGameInit,gameClient);
		CLIENT_ON(GameMsg::MsgType_MsgType_PlayerMove, GameController::onPlayerMove, gameClient);
		CLIENT_ON(GameMsg::MsgType_MsgType_PlayerAttack, GameController::onPlayerAttack, gameClient);
		CLIENT_ON(GameMsg::MsgType_MsgType_PlayerSkill, GameController::onPlayerSkill, gameClient);
		CLIENT_ON(GameMsg::MsgType_MsgType_ChatMsg, GameController::onChatMsg, gameClient);

		schedule(CC_CALLBACK_0(GameController::processMsg,this),0.05f,"ProcessMsg");

	}

	return true;
}

void GameController::setMap(GameMap * map)
{
	if(map) this->map = map;
	map->setAnchorPoint(Vec2::ZERO);
	

}

void GameController::createTouchListener()
{
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	touchListener->onTouchEnded =[=](cocos2d::Touch * touch, cocos2d::Event * event) {
		auto touchLocation = touch->getLocation();
		auto nodeLocation = map->convertToNodeSpace(touchLocation);
		auto worldLocation = map->convertToWorldSpace(touchLocation);
		if (map->isCanAssess(map->positionToTileCoord(nodeLocation)))
		{
			if (isOnline)
			{
				flatbuffers::FlatBufferBuilder builder(1024);
				using namespace GameMsg;
				auto name = builder.CreateString(User::getInstance()->getName());
				auto pos = GameMsg::Point(nodeLocation.x, nodeLocation.y);
				auto playerMove = CreatePlayerMove(builder, name,&pos);
		
				auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerMove, Date::Date_playerMove, playerMove.Union());
				builder.Finish(msg);
				uint8_t* buff = builder.GetBufferPointer();
				size_t size = builder.GetSize();
				socket_message message((const char*)buff, size);
				gameClient->sendMessage(message);
				hasSend = true;
			}
			else
			{
				auto localplayer = manager->playerManager->getLocalPlayer();
				if (localplayer&&localplayer->getStatus() != Player::Status::DEAD)
					localplayer->startMove(nodeLocation);
			}

		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
	touchListener->setEnabled(false);
}

void GameController::createKeyListener()
{
	keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			if(getSkillList().size()>=1)
				getSkillList().at(0)->touch();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		{
			if (getSkillList().size() >= 2)
				getSkillList().at(1)->touch();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			if (getSkillList().size() >= 3)
				getSkillList().at(2)->touch();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_E)
		{
			if (getSkillList().size() >= 4)
				getSkillList().at(3)->touch();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_R)
		{
			if (getSkillList().size() >= 5)
				getSkillList().at(4)->touch();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpdateMenu");
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	keyListener->setEnabled(false);
}

void GameController::addSkill()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto role = User::getInstance()->getRole();
	std::string roleNames[] = { "warrior","aviator","aviator","aviator","aviator","aviator" };
	auto roleName = roleNames[role];
	auto skill1 = Skill::create("Skill1", "Pictures/GameItem/"+roleName+"_skill1.png", 0.1f);
	skill1->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.1));
	skill1->setScale(0.8);
	skill1->onTouch = [=]() 
	{
		if (isOnline)
		{
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto playerAttack = CreatePlayerAttack(builder, name);

			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerAttack, Date::Date_playerAttack, playerAttack.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			gameClient->sendMessage(message);
			hasSend = true;
		}
		else
			manager->playerManager->getLocalPlayer()->attack(); 
	};
	_skillList.pushBack(skill1);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill1);
	skill1->setEnabled(false);

	auto skill2 = Skill::create("Skill2", "Pictures/GameItem/" + roleName + "_skill2.png", 15.0f);
	skill2->setPosition(Vec2(visibleSize.width*0.78, visibleSize.height*0.05));
	skill2->setScale(0.8);
	skill2->onTouch = [=]()
	{
		if (isOnline)
		{
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto playerSkill = CreatePlayerSkill(builder, name,SkillType::SkillType_One);

			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerSkill, Date::Date_playerSkill, playerSkill.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			gameClient->sendMessage(message);
			hasSend = true;
		}
		else
		manager->playerManager->getLocalPlayer()->skill1();
	};
	_skillList.pushBack(skill2);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill2);
	skill2->setEnabled(false);

	auto skill3 = Skill::create("Skill3", "Pictures/GameItem/" + roleName + "_skill3.png", 20.0f);
	skill3->setPosition(Vec2(visibleSize.width*0.815, visibleSize.height*0.185));
	skill3->setScale(0.8);
	skill3->onTouch = [=]()
	{
		if (isOnline)
		{
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto playerSkill = CreatePlayerSkill(builder, name, SkillType::SkillType_Two);

			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerSkill, Date::Date_playerSkill, playerSkill.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			gameClient->sendMessage(message);
			hasSend = true;
		}
		else
			manager->playerManager->getLocalPlayer()->skill2();
	};
	_skillList.pushBack(skill3);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill3);
	skill3->setEnabled(false);

	auto skill4 = Skill::create("Skill4", "Pictures/GameItem/" + roleName + "_skill4.png", 50.0f);
	skill4->setPosition(Vec2(visibleSize.width*0.92, visibleSize.height*0.235));
	skill4->setScale(0.8);
	skill4->onTouch = [=]()
	{
		if (isOnline)
		{
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto playerSkill = CreatePlayerSkill(builder, name, SkillType::SkillType_Three);

			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerSkill, Date::Date_playerSkill, playerSkill.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			gameClient->sendMessage(message);
			hasSend = true;
		}
		else
			manager->playerManager->getLocalPlayer()->skill3();
	};
	_skillList.pushBack(skill4);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill4);
	skill4->setEnabled(false);

	auto skillRecover = Skill::create("SkillRecover", "Pictures/GameItem/skillrecover.png", 50.0f);
	skillRecover->setPosition(Vec2(visibleSize.width*0.67, visibleSize.height*0.05));
	skillRecover->setScale(0.8);
	skillRecover->onTouch = [=]()
	{
		if (isOnline)
		{
			flatbuffers::FlatBufferBuilder builder(1024);
			using namespace GameMsg;
			auto name = builder.CreateString(User::getInstance()->getName());
			auto playerSkill = CreatePlayerSkill(builder, name, SkillType::SkillType_Recover);

			auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_PlayerSkill, Date::Date_playerSkill, playerSkill.Union());
			builder.Finish(msg);
			uint8_t* buff = builder.GetBufferPointer();
			size_t size = builder.GetSize();
			socket_message message((const char*)buff, size);
			gameClient->sendMessage(message);
			hasSend = true;
		}
		else
			manager->playerManager->getLocalPlayer()->skillRecover();
	};
	_skillList.pushBack(skillRecover);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skillRecover);
	skillRecover->setEnabled(false);

}

void GameController::addChatBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	chatBox = ChatBox::create("Pictures/UI/chatbox.png",gameClient);
	chatBox->setPosition(Vec2(visibleSize.width *0.82, visibleSize.height*0.6));
	Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(chatBox,5);

	auto chatButton = ui::Button::create("Pictures/UI/chatbutton.png");
	chatButton->setPosition(Vec2(visibleSize.width*0.97, visibleSize.height /2));
	chatButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
			chatBox->update();
	});
	Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(chatButton,4);
}

void GameController::onEnter()
{
	Layer::onEnter();
}


void GameController::toOver(cocos2d::EventCustom* event)
{
	bool isWin = static_cast<bool>(event->getUserData());
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::KEYBOARD);
	GameAudio::getInstance()->playEffect(isWin?"Sounds/Win.wav": "Sounds/Lose.wav");
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameOver",(void*)isWin);
}

void GameController::sendEmptyMsg()
{
	if (!hasSend)
	{
		flatbuffers::FlatBufferBuilder builder(1024);
		using namespace GameMsg;

		auto msg = CreateMsg(builder, MsgType::MsgType_MsgType_None, Date::Date_NONE);
		builder.Finish(msg);
		uint8_t* buff = builder.GetBufferPointer();
		size_t size = builder.GetSize();
		socket_message message((const char*)buff, size);
		gameClient->sendMessage(message);
	}
	hasSend = false;
}

void GameController::processMsg()
{

	using namespace::GameMsg;
	if (gameClient->remainMessage())
	{

		auto msg=gameClient->getMessage();
		gameClient->onMessage(GetMsg(msg.c_str())->msg(), msg.c_str());
	}
}

void GameController::onGameInit(const void * msg)
{
	using namespace GameMsg;
	auto data = GetMsg(msg)->data_as_gameInit();
	srand(data->randSeed());
	auto players = data->players();
	for (auto player : *players)
	{
		auto name = player->name()->c_str();
		auto color = static_cast<int>(player->color());
		auto role = static_cast<int>(player->role());
		if (name == User::getInstance()->getName())
		{
			auto hero=manager->playerManager->createLocalPlayer(name, role, color);


			GameMap::getCurrentMap()->addSprite(hero,(color)?GameMap::Type::Player_Blue: GameMap::Type::Player_Red);
			GameMap::getCurrentMap()->addCenterSprite(hero);
		}
		else
		{
			auto hero = manager->playerManager->createPlayer(name, role, color);
			GameMap::getCurrentMap()->addSprite(hero, (color) ? GameMap::Type::Player_Blue : GameMap::Type::Player_Red);
		}
	}
	hasSend = true;
	schedule(CC_CALLBACK_0(GameController::sendEmptyMsg, this), 0.01f,"SendEmpty");

}

void GameController::onPlayerMove(const void * msg)
{

	auto data = GameMsg::GetMsg(msg)->data_as_playerMove();
	auto player = manager->playerManager->getPlayer(data->name()->c_str());
	auto pos = Vec2(data->pos()->x(), data->pos()->y());
	if (player&&player->getStatus() != Player::Status::DEAD)
		player->startMove(pos);

}

void GameController::onPlayerAttack(const void * msg)
{
	auto data = GameMsg::GetMsg(msg)->data_as_playerAttack();
	auto player = manager->playerManager->getPlayer(data->name()->c_str());
	if (player)
		player->attack();

}

void GameController::onPlayerSkill(const void * msg)
{
	auto data = GameMsg::GetMsg(msg)->data_as_playerSkill();
	auto player = manager->playerManager->getPlayer(data->name()->c_str());
	if (player)
	{
		switch (data->type())
		{
		case GameMsg::SkillType::SkillType_One:{player->skill1();break;}
		case GameMsg::SkillType::SkillType_Two:{player->skill2();break;}
		case GameMsg::SkillType::SkillType_Three:{player->skill3();break;}
		case GameMsg::SkillType::SkillType_Recover:{player->skillRecover();break;}
		}
	}
}

void GameController::onChatMsg(const void * msg)
{
	auto data = GameMsg::GetMsg(msg)->data_as_chatMsg();
	auto name = std::string(data->name()->c_str());
	auto chatmsg = std::string(data->msg()->c_str());
	ChatText *text;
	if (name == User::getInstance()->getName())
		text = ChatText::create("Pictures/UI/chatText_green.png", chatmsg, true);
	else
		text = ChatText::create("Pictures/UI/chatText_white.png", chatmsg, false);
	chatBox->addChatText(text);
	chatBox->setIndex(0);
	chatBox->updateLayout();
}

void GameController::initGame(float delta)
{
	manager = Manager::create();
	this->addChild(manager, -1,"Manager");
	addSkill();
	if(isOnline)
		addChatBox();
	
}
