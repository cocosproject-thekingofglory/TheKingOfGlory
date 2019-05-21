#include "GameScene.h"
#include "Util/GameAudio.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "SettingsScene.h"
#include "Model/GameMap.h"
#include "Controller/GameController.h"
USING_NS_CC;
using namespace CocosDenshion;



void GameScene::onEnter()
{
	Layer::onEnter();
	GameAudio::getInstance()->playBgm("Sounds/GameBgm.mp3");
}


void GameScene::createMenuButton()
{
	//添加菜单按钮
	auto menuItem = MenuItemImage::create(
		"Pictures/UI/SettingNormal.png",
		"Pictures/UI/SettingSelected.png",
		CC_CALLBACK_0(GameScene::createMenu, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2(visible_Size.width*0.95, visible_Size.height*0.95));
	this->addChild(menu);
	menuRect = Rect(menu->getPosition().x - menuItem->getContentSize().width / 2,
		menu->getPosition().y - menuItem->getContentSize().height / 2,
		menuItem->getContentSize().width + menuItem->getContentSize().width / 2,
		menuItem->getContentSize().height + menuItem->getContentSize().height / 2);
}

void GameScene::updateMenu()
{
	//更新菜单，接收到UpdateMenu事件是响应
	if (hasMenu)
		removeMenu();
	else
		createMenu();
}

void GameScene::createMenu()
{
	if (hasMenu)
		return;
	//添加菜单图片
	menu = Sprite::create("Pictures/UI/Menu1.png");
	menu->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(menu);

	Color4B text_Color = Color4B(255, 255, 255, 255);
	std::string text_Font = "fonts/UnifrakturCook-Bold.ttf";
	float text_Size = 28;

	Size menuSize = menu->getContentSize();
	float menuBottom = visible_Size.height / 2 - menuSize.height / 2;

	//添加继续游戏文字
	continueLabel = Label::createWithTTF("Continue", text_Font, text_Size);
	continueLabel->setTextColor(text_Color);
	continueLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.8));
	this->addChild(continueLabel);

	//添加游戏设置文字
	settingLabel = Label::createWithTTF("Setting", text_Font, text_Size);
	settingLabel->setTextColor(text_Color);
	settingLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.6));
	this->addChild(settingLabel);

	//添加重新开始文字
	restartLabel = Label::createWithTTF("Restart", text_Font, text_Size);
	restartLabel->setTextColor(text_Color);
	restartLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.4));
	this->addChild(restartLabel);

	//添加返回主菜单文字
	returnLabel = Label::createWithTTF("Main Menu", text_Font, text_Size);
	returnLabel->setTextColor(text_Color);
	returnLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.2));
	this->addChild(returnLabel);

	menuListener->setEnabled(true);
	hasMenu = true;

}

void GameScene::removeMenu()
{
	if (!hasMenu)
		return;
	//停用菜单事件监听器，删除菜单
	menuListener->setEnabled(false);
	this->removeChild(menu, true);
	this->removeChild(continueLabel, true);
	this->removeChild(settingLabel, true);
	this->removeChild(restartLabel, true);
	this->removeChild(returnLabel, true);
	hasMenu = false;
}

void GameScene::createResultBox(EventCustom* event)
{
	bool isWin = static_cast<bool>(event->getUserData());
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto box = Sprite::create("Pictures/UI/Resultbox.png");
	box->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(box);

	Size boxSize = box->getContentSize();

	auto resultText = ui::Text::create((isWin ? "You Win!" : "You Lose!"), "fonts/Lobster-Regular.ttf", 48);
	resultText->setColor(Color3B(0, 0, 255));
	resultText->setPosition(Vec2(boxSize.width / 2, boxSize.height*0.7));

	auto restartButton = ui::Button::create("Pictures/UI/button.png");
	restartButton->setScale(1.2);
	restartButton->setTitleFontName("fonts/Marker Felt.ttf");
	restartButton->setTitleText("Restart");
	restartButton->setTitleColor(Color3B(255, 250, 205));
	restartButton->setTitleFontSize(20);
	restartButton->setPosition(Vec2(boxSize.width*0.3, boxSize.height*0.3));
	restartButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
		}
	});

	auto returnButton = ui::Button::create("Pictures/UI/button.png");
	returnButton->setScale(1.2);
	returnButton->setTitleFontName("fonts/Marker Felt.ttf");
	returnButton->setTitleText("Main Menu");
	returnButton->setTitleColor(Color3B(255, 250, 205));
	returnButton->setTitleFontSize(18);
	returnButton->setPosition(Vec2(boxSize.width*0.7, boxSize.height*0.3));
	returnButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::createScene()));
		}
	});

	box->addChild(resultText);
	box->addChild(restartButton);
	box->addChild(returnButton);

}

void GameScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto touchLocation = touch->getLocation();
	auto nodeLocation = this->convertToNodeSpace(touchLocation);

	if (this->rectOfLabel(continueLabel).containsPoint(nodeLocation) ||
		menuRect.containsPoint(nodeLocation))
	{
		removeMenu();
	}
	else if (this->rectOfLabel(settingLabel).containsPoint(nodeLocation))
	{
		//停用菜单事件监听器，删除菜单,进入游戏设置界面
		removeMenu();
		Director::getInstance()->pushScene(TransitionFade::create(1, SettingsScene::createScene()));
	}
	else if (this->rectOfLabel(restartLabel).containsPoint(nodeLocation))
	{
		//停用菜单事件监听器，重新开始游戏
		menuListener->setEnabled(false);
		hasMenu = false;
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	}
	else if (this->rectOfLabel(returnLabel).containsPoint(nodeLocation))
	{
		//停用菜单事件监听器，返回主菜单
		menuListener->setEnabled(false);
		hasMenu = false;
		Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::createScene()));
	}
}

cocos2d::Rect GameScene::rectOfLabel(cocos2d::Label * label)
{
	return Rect(label->getPosition().x - label->getContentSize().width / 2,
		label->getPosition().y - label->getContentSize().height / 2,
		label->getContentSize().width,
		label->getContentSize().height);
}

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	layer->setName("GameScene");
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

	visible_Size = Director::getInstance()->getVisibleSize();

	//创建菜单事件监听器，先不启用
	menuListener = EventListenerTouchOneByOne::create();
	menuListener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	menuListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	menuListener->setSwallowTouches(true);
	menuListener->setEnabled(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(menuListener, -1);

	//创建自定义事件监听器，用于打开关闭菜单
	auto updateMenuListener = EventListenerCustom::create("UpdateMenu", CC_CALLBACK_0(GameScene::updateMenu, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateMenuListener, 1);

	//创建自定义事件监听器，游戏结束时弹出对话框
	auto gameOverListener = EventListenerCustom::create("GameOver", CC_CALLBACK_1(GameScene::createResultBox, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameOverListener, 1);

	auto bg = Sprite::create("Pictures/Background/WhiteBackground.png");
	bg->setScale(100);
	this->addChild(bg, -2);

	//this->setAnchorPoint(Vec2::ZERO);
	log("visible:x:%f  y:%f", visible_Size.width, visible_Size.height);

	//添加地图
	auto map = GameMap::create();
	map->setMap("1v1");
	map->setPosition(Vec2::ZERO);
	map->setScale(0.5f);
	this->addChild(map, -1);

	auto gameController = GameController::create();
	gameController->setMap(map);
	this->addChild(gameController, -1, "GameController");

	createMenuButton();

	return true;
}