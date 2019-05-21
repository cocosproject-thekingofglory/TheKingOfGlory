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
	scheduleOnce(schedule_selector(GameController::initGame), 0.1f);

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
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	listener->onTouchEnded =[=](cocos2d::Touch * touch, cocos2d::Event * event) {
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}

void GameController::createKeyListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			map->setPositionY(map->getPositionY() - 100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			map->setPositionY(map->getPositionY() + 100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			map->setPositionX(map->getPositionX() +100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			map->setPositionX(map->getPositionX() -100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_T)
		{
			map->setPositionY(map->getPositionY() - 10);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_G)
		{
			map->setPositionY(map->getPositionY() + 10);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_F)
		{
			map->setPositionX(map->getPositionX() + 10);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_H)
		{
			map->setPositionX(map->getPositionX() - 10);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		{
			map->setScale(map->getScale()*1.1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_K)
		{
			map->setScale(map->getScale()/1.1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			manager->playerManager->getLocalPlayer()->attack();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpdateMenu");
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
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
}
