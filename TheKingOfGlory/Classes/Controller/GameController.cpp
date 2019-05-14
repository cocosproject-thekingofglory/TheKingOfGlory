#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool GameController::init()
{
	if (!Layer::init())
		return false;
	
	map = nullptr;

	createTouchListener();
	createKeyListener();

	this->scheduleUpdate();

	return true;
}

void GameController::setMap(GameMap * map)
{
	if(map) this->map = map;
	map->setScale(1.0 / 11.0);
}

void GameController::createTouchListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	listener->onTouchEnded =[=](cocos2d::Touch * touch, cocos2d::Event * event) {
		auto touchLocation = touch->getLocation();
		auto nodeLocation = map->convertToNodeSpace(touchLocation);
		if (map->isCanAssess(map->positionToTileCoord(nodeLocation)))
		{
			log("Can Assess");
		}
		else
		{
			log("Can not Assess");
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
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		{
			map->setScale(map->getScale()*1.1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_K)
		{
			map->setScale(map->getScale()/1.1);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("UpdateMenu");
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_T)
		{
			soldier->stopAnimation(soldier);
			soldier->runAnimation("warrior_walk_up", soldier);
			soldier->setPosition(soldier->getPositionX(), soldier->getPositionY() + 100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_G)
		{
			soldier->stopAnimation(soldier);
			soldier->runAnimation("warrior_walk_down", soldier);
			soldier->setPosition(soldier->getPositionX(), soldier->getPositionY() -100);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_F)
		{
			soldier->stopAnimation(soldier);
			soldier->runAnimation("warrior_walk_left", soldier);
			soldier->setPosition(soldier->getPositionX()-100, soldier->getPositionY() );
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_H)
		{
			soldier->stopAnimation(soldier);
			soldier->runAnimation("warrior_walk_right", soldier);
			soldier->setPosition(soldier->getPositionX()+100, soldier->getPositionY() );
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::KEYBOARD);
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameOver", (void*)true);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::onEnter()
{
	Layer::onEnter();
	initGame();
}

void GameController::update(float delta)
{
	isResult(delta);
}

void GameController::isResult(float delta)
{
}

void GameController::toOver(bool isWin)
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::KEYBOARD);
	SimpleAudioEngine::getInstance()->playEffect(isWin?"Sounds/Win.wav": "Sounds/Lose.wav");
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameOver",(void*)isWin);
}

void GameController::initGame()
{
	soldier = Soldier::create();
	soldier->setScale(5);
	soldier->runAnimation("warrior_walk_down", soldier);
	map->addSprite(soldier, GameMap::Type::Player_Red);
}
