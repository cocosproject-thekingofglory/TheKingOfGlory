#include "GameController.h"
#include "Util/GameAudio.h"

USING_NS_CC;
using namespace CocosDenshion;

bool GameController::init()
{
	if (!Layer::init())
		return false;
	this->setName("GameController");
	map = nullptr;


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
			auto localplayer = manager->playerManager->getLocalPlayer();
			if(localplayer&&localplayer->getStatus()!=Player::Status::DEAD)
				localplayer->startMove(nodeLocation);
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
	auto skill1 = Skill::create("Skill1", "Pictures/GameItem/warrior_skill1.png", 0.1f);
	skill1->setPosition(Vec2(visibleSize.width*0.9,visibleSize.height*0.1));
	skill1->setScale(0.8);
	skill1->onTouch = [=]() 
	{
			manager->playerManager->getLocalPlayer()->attack(); 
	};
	_skillList.pushBack(skill1);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill1);
	skill1->setEnabled(false);

	auto skill2 = Skill::create("Skill2", "Pictures/GameItem/warrior_skill2.png", 15.0f);
	skill2->setPosition(Vec2(visibleSize.width*0.78, visibleSize.height*0.05));
	skill2->setScale(0.8);
	skill2->onTouch = [=]()
	{
		manager->playerManager->getLocalPlayer()->skill1();
	};
	_skillList.pushBack(skill2);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill2);
	skill2->setEnabled(false);

	auto skill3 = Skill::create("Skill3", "Pictures/GameItem/warrior_skill3.png", 20.0f);
	skill3->setPosition(Vec2(visibleSize.width*0.815, visibleSize.height*0.185));
	skill3->setScale(0.8);
	skill3->onTouch = [=]()
	{
		manager->playerManager->getLocalPlayer()->skill2();
	};
	_skillList.pushBack(skill3);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill3);
	skill3->setEnabled(false);

	auto skill4 = Skill::create("Skill4", "Pictures/GameItem/warrior_skill4.png", 50.0f);
	skill4->setPosition(Vec2(visibleSize.width*0.92, visibleSize.height*0.235));
	skill4->setScale(0.8);
	skill4->onTouch = [=]()
	{
		manager->playerManager->getLocalPlayer()->skill3();
	};
	_skillList.pushBack(skill4);
	cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(skill4);
	skill4->setEnabled(false);

}

void GameController::onEnter()
{
	Layer::onEnter();
}

void GameController::update(float delta)
{
	isResult(delta);
}

void GameController::isResult(float delta)
{
}

void GameController::toOver(cocos2d::EventCustom* event)
{
	bool isWin = static_cast<bool>(event->getUserData());
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::KEYBOARD);
	GameAudio::getInstance()->playEffect(isWin?"Sounds/Win.wav": "Sounds/Lose.wav");
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameOver",(void*)isWin);
}

void GameController::initGame(float delta)
{
	manager = Manager::create();
	this->addChild(manager, -1,"Manager");

	addSkill();
}
