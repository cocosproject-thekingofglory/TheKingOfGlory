#include "GameController.h"
USING_NS_CC;

bool GameController::init()
{
	if (!Layer::init())
		return false;
	
	map = nullptr;

	createTouchListener();
	createKeyListener();

	

	return true;
}

void GameController::setMap(GameMap * map)
{
	if(map) this->map = map;
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
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::onEnter()
{
	Layer::onEnter();
	initGame();
}

void GameController::initGame()
{
	auto sprite = Sprite::create("Pictures/player.png");
	sprite->setScale(10);
	map->addSprite(sprite, GameMap::Type::Player_Blue);
}
