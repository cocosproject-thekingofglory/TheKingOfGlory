#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
USING_NS_CC;
using namespace CocosDenshion;



void GameScene::onEnter()
{
	Layer::onEnter();
	//GameAudio::getInstance()->playBgm("Sounds/Game.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/GameBgm.mp3", true);
}

void GameScene::createMap()
{
	//添加地图
/*	auto map = GameMap::create();
	map->setMap("town_10");
	map->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(map, -1);
	*/
	auto background = Sprite::create("Pictures/Background/WhiteBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}

void GameScene::createMenu()
{
	//添加菜单
	auto menuItem = MenuItemImage::create(
		"Pictures/UI/SettingNormal.png",
		"Pictures/UI/SettingSelected.png",
		CC_CALLBACK_1(GameScene::menuCallback, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2(visible_Size.width*0.95, visible_Size.height*0.95));
	this->addChild(menu);
	menuRect= Rect(menu->getPosition().x - menuItem->getContentSize().width / 2,
		menu->getPosition().y - menuItem->getContentSize().height / 2,
		menuItem->getContentSize().width + menuItem->getContentSize().width / 2,
		menuItem->getContentSize().height + menuItem->getContentSize().height / 2);
}

void GameScene::menuCallback(cocos2d::Ref * pSender)
{
	menu = Sprite::create("Pictures/UI/Menu.png");
	menu->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(menu);

	Color4B text_Color= Color4B(0,0,0,100);
	std::string text_Font = "fonts/UnifrakturCook-Bold.ttf";
	float text_Size = 28;
	//添加菜单图片
	Size menuSize = menu->getContentSize();
	float menuBottom = visible_Size.height / 2 - menuSize.height / 2;

	//添加继续游戏按钮
	continueButton = Sprite::create("Pictures/UI/button.png");
	continueButton->setPosition(Vec2(visible_Size.width/2,menuBottom+menuSize.height*0.8));
	this->addChild(continueButton);

	//添加继续游戏文字
	continueLabel = Label::createWithTTF("Continue", text_Font, text_Size);
	continueLabel->setTextColor(text_Color);
	continueLabel->setPosition(continueButton->getPosition());
	this->addChild(continueLabel);

	//添加游戏设置按钮
	settingButton = Sprite::create("Pictures/UI/button.png");
	settingButton->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.6));
	this->addChild(settingButton);

	//添加游戏设置文字
	settingLabel = Label::createWithTTF("Setting", text_Font, text_Size);
	settingLabel->setTextColor(text_Color);
	settingLabel->setPosition(settingButton->getPosition());
	this->addChild(settingLabel);

	//添加重新开始按钮
	restartButton = Sprite::create("Pictures/UI/button.png");
	restartButton->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.4));
	this->addChild(restartButton);

	//添加重新开始文字
	restartLabel = Label::createWithTTF("Restart", text_Font, text_Size);
	restartLabel->setTextColor(text_Color);
	restartLabel->setPosition(restartButton->getPosition());
	this->addChild(restartLabel);

	//添加返回主菜单按钮
	returnButton = Sprite::create("Pictures/UI/button.png");
	returnButton->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.2));
	this->addChild(returnButton);

	//添加返回主菜单文字
	returnLabel = Label::createWithTTF("Return", text_Font, text_Size);
	returnLabel->setTextColor(text_Color);
	returnLabel->setPosition(returnButton->getPosition());
	this->addChild(returnLabel);

	menuListener->setEnabled(true);

}

void GameScene::menuOnTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto touchLocation = touch->getLocation();
	auto nodeLocation = this->convertToNodeSpace(touchLocation);

	if (this->rectOfSprite(continueButton).containsPoint(nodeLocation)||
		menuRect.containsPoint(nodeLocation))
	{
		menuListener->setEnabled(false);
		this->removeChild(menu,true);
		this->removeChild(continueButton, true);
		this->removeChild(settingButton, true);
		this->removeChild(restartButton, true);
		this->removeChild(returnButton, true);
		this->removeChild(continueLabel, true);
		this->removeChild(settingLabel, true);
		this->removeChild(restartLabel, true);
		this->removeChild(returnLabel, true);
	}
	else if (this->rectOfSprite(settingButton).containsPoint(nodeLocation))
	{
	}
	else if (this->rectOfSprite(restartButton).containsPoint(nodeLocation))
	{
		menuListener->setEnabled(false);
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	}
	else if (this->rectOfSprite(returnButton).containsPoint(nodeLocation))
	{
		menuListener->setEnabled(false);
		Director::getInstance()->replaceScene(TransitionFade::create(1,	StartScene::createScene()));
	}
}

cocos2d::Rect GameScene::rectOfSprite(cocos2d::Sprite * sprite)
{
	return Rect(sprite->getPosition().x - sprite->getContentSize().width / 2,
		sprite->getPosition().y - sprite->getContentSize().height / 2,
		sprite->getContentSize().width ,
		sprite->getContentSize().height );
}

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;
	visible_Size = Director::getInstance()->getVisibleSize();

	menuListener = EventListenerTouchOneByOne::create();
	menuListener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	menuListener->onTouchEnded = CC_CALLBACK_2(GameScene::menuOnTouchEnded, this);
	menuListener->setSwallowTouches(true);
	menuListener->setEnabled(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(menuListener, -1);



	createMap();
	createMenu();

	return true;
}
