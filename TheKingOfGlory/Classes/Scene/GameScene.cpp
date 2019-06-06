#include "GameScene.h"
#include "Util/GameAudio.h"
#include "StartScene.h"
#include "SettingsScene.h"
#include "Model/GameMap.h"
#include "Controller/GameController.h"
#include "../Model/StatusList.h"
USING_NS_CC;
using namespace CocosDenshion;



void GameScene::onEnter()
{
	Layer::onEnter();
	GameAudio::getInstance()->playBgm("Sounds/GameBgm.mp3");
}

void GameScene::createStatusButton()
{
	statusButton = Button::create("Pictures/StatusList/statusButton.png");
	statusButton->setScaleX(2.0);
	statusButton->setPosition(Vec2(this->getContentSize().width - statusButton->getContentSize().width * 2
		, this->getContentSize().height / 4 * 3));
	statusButton->setEnabled(false);
	statusButton->setSwallowTouches(true);

	statusButton->addTouchEventListener([=](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (hasList)return;
			auto list =StatusList::createStatusList();
			list->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
			this->addChild(list, 4);
		}
	});
	this->addChild(statusButton, 4);
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
	this->addChild(menu,4);
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
	this->addChild(menu,4);

	Color4B text_Color = Color4B(255, 255, 255, 255);
	std::string text_Font = "fonts/UnifrakturCook-Bold.ttf";
	float text_Size = 28;

	Size menuSize = menu->getContentSize();
	float menuBottom = visible_Size.height / 2 - menuSize.height / 2;

	//添加继续游戏文字
	continueLabel = Label::createWithTTF("Continue", text_Font, text_Size);
	continueLabel->setTextColor(text_Color);
	continueLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.8));
	this->addChild(continueLabel, 4);

	//添加音乐设置文字
	bgmLabel = Label::createWithTTF("Bgm", text_Font, text_Size);
	bgmLabel->setTextColor(text_Color);
	bgmLabel->setPosition(Vec2(visible_Size.width *0.48, menuBottom + menuSize.height*0.6));
	this->addChild(bgmLabel, 4);
	
	musicCheckBox = ui::CheckBox::create("Pictures/UI/checkbox_normal.png", "Pictures/UI/checkbox_active.png");
	musicCheckBox->setPosition(Vec2(visible_Size.width *0.53, menuBottom + menuSize.height*0.6));
	musicCheckBox->setSelected(GameAudio::getInstance()->getBgmOn());
	musicCheckBox->addEventListener([=](Ref*, ui::CheckBox::EventType type)
	{
		GameAudio::getInstance()->setBgmOn(type == ui::CheckBox::EventType::SELECTED);
	});
	this->addChild(musicCheckBox,4);


	//添加音效设置文字
	effectLabel = Label::createWithTTF("Effect", text_Font, text_Size);
	effectLabel->setTextColor(text_Color);
	effectLabel->setPosition(Vec2(visible_Size.width *0.48, menuBottom + menuSize.height*0.4));
	this->addChild(effectLabel, 4);

	effectCheckBox = ui::CheckBox::create("Pictures/UI/checkbox_normal.png", "Pictures/UI/checkbox_active.png");
	effectCheckBox->setPosition(Vec2(visible_Size.width *0.53, menuBottom + menuSize.height*0.4));
	effectCheckBox->setSelected(GameAudio::getInstance()->getEffectOn());
	effectCheckBox->addEventListener([=](Ref*, ui::CheckBox::EventType type)
	{
		GameAudio::getInstance()->setEffectOn(type == ui::CheckBox::EventType::SELECTED);
	});
	this->addChild(effectCheckBox, 4);
	
	//添加退出游戏文字
	exitLabel = Label::createWithTTF("Exit", text_Font, text_Size);
	exitLabel->setTextColor(text_Color);
	exitLabel->setPosition(Vec2(visible_Size.width / 2, menuBottom + menuSize.height*0.2));
	this->addChild(exitLabel, 4);

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
	this->removeChild(bgmLabel, true);
	this->removeChild(effectLabel, true);
	this->removeChild(exitLabel, true);
	this->removeChild(musicCheckBox, true);
	this->removeChild(effectCheckBox, true);
	hasMenu = false;
}

void GameScene::createResultBox(EventCustom* event)
{
	bool isWin = static_cast<bool>(event->getUserData());
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto box = Sprite::create("Pictures/UI/Resultbox.png");
	box->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(box, 4);

	Size boxSize = box->getContentSize();

	auto resultText = ui::Text::create((isWin ? "You Win!" : "You Lose!"), "fonts/Lobster-Regular.ttf", 48);
	resultText->setColor(Color3B(0, 0, 255));
	resultText->setPosition(Vec2(boxSize.width / 2, boxSize.height*0.7));


	auto returnButton = ui::Button::create("Pictures/UI/button.png");
	returnButton->setScale(1.2);
	returnButton->setTitleFontName("fonts/Marker Felt.ttf");
	returnButton->setTitleText("Exit");
	returnButton->setTitleColor(Color3B(255, 250, 205));
	returnButton->setTitleFontSize(24);
	returnButton->setPosition(Vec2(boxSize.width*0.5, boxSize.height*0.3));
	returnButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
		}
	});

	box->addChild(resultText, 4);
	box->addChild(returnButton, 4);

	auto VsText = Text::create("VS", "fonts/arial.ttf", 32);
	VsText->setPosition(Vec2(visible_Size.width/2, visible_Size.height/2));
	VsText->setColor(Color3B::WHITE);
	this->addChild(VsText,4);

	auto redText = Text::create(std::to_string(redRank.first), "fonts/arial.ttf", 32);
	redText->setPosition(Vec2(visible_Size.width*0.45, visible_Size.height/2));
	redText->setColor(Color3B::RED);
	this->addChild(redText,4);

	auto blueText = Text::create(std::to_string(blueRank.first), "fonts/arial.ttf", 32);
	blueText->setPosition(Vec2(visible_Size.width*0.55, visible_Size.height/2));
	blueText->setColor(Color3B::BLUE);
	this->addChild(blueText,4);

}

void GameScene::createRank()
{
	auto bg = Sprite::create("Pictures/UI/rankBg.png");
	bg->setPosition(Vec2(visible_Size.width*0.8, visible_Size.height*0.96));
	this->addChild(bg);

	auto VsText = Text::create("VS", "fonts/arial.ttf", 32);
	VsText->setPosition(Vec2(visible_Size.width*0.8, visible_Size.height*0.96));
	VsText->setColor(Color3B::WHITE);
	this->addChild(VsText);

	redRank.first = 0;
	auto& redText = redRank.second;
	redText = Text::create("0", "fonts/arial.ttf", 32);
	redText->setPosition(Vec2(visible_Size.width*0.75, visible_Size.height*0.96));
	redText->setColor(Color3B::RED);
	this->addChild(redText);

	blueRank.first = 0;
	auto& blueText = blueRank.second;
	blueText = Text::create("0", "fonts/arial.ttf", 32);
	blueText->setPosition(Vec2(visible_Size.width*0.85, visible_Size.height*0.96));
	blueText->setColor(Color3B::BLUE);
	this->addChild(blueText);
}

void GameScene::updateRank(cocos2d::EventCustom * event)
{
	bool isRed = static_cast<bool>(event->getUserData());
	if (isRed)
	{
		redRank.first++;
		redRank.second->setText(std::to_string(redRank.first));
	}
	else
	{
		blueRank.first++;
		blueRank.second->setText(std::to_string(blueRank.first));
	}
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
	else if (this->rectOfLabel(exitLabel).containsPoint(nodeLocation))

	{
		Director::getInstance()->end();
	}
	else if (musicCheckBox->getBoundingBox().containsPoint(nodeLocation))
	{
		musicCheckBox->setSelected(!musicCheckBox->getSelectedState());
		GameAudio::getInstance()->setBgmOn(musicCheckBox->getSelectedState());
	}
	else if (effectCheckBox->getBoundingBox().containsPoint(nodeLocation))
	{
		effectCheckBox->setSelected(!effectCheckBox->getSelectedState());
		GameAudio::getInstance()->setEffectOn(effectCheckBox->getSelectedState());
	}
}

cocos2d::Rect GameScene::rectOfLabel(cocos2d::Label * label)
{
	return Rect(label->getPosition().x - label->getContentSize().width / 2,
		label->getPosition().y - label->getContentSize().height / 2,
		label->getContentSize().width,
		label->getContentSize().height);
}

cocos2d::Scene * GameScene::createScene(Client* client, Server*server )
{
	auto scene = Scene::create();
	auto layer = GameScene::create(client,server);
	layer->setName("GameScene");
	scene->addChild(layer);
	return scene;
}

GameScene * GameScene::create(Client * client, Server * server)
{
	GameScene *gamescene = new (std::nothrow) GameScene();
	if (gamescene && gamescene->init(client, server))
	{
		gamescene->autorelease();
		return gamescene;
	}
	CC_SAFE_DELETE(gamescene);

	return nullptr;
}

bool GameScene::init(Client* client, Server*server)
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

	auto gameStartListener = EventListenerCustom::create("GameStart", [=](cocos2d::EventCustom* event) {
		statusButton->setEnabled(true);
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameStartListener, 1);


	//创建自定义事件监听器，用于打开关闭菜单
	auto updateMenuListener = EventListenerCustom::create("UpdateMenu", CC_CALLBACK_0(GameScene::updateMenu, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(updateMenuListener, 1);

	//创建自定义事件监听器，游戏结束时弹出对话框
	auto gameOverListener = EventListenerCustom::create("GameOver", CC_CALLBACK_1(GameScene::createResultBox, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameOverListener, 1);


	auto rankUpdateListener = EventListenerCustom::create("UpdateRank", CC_CALLBACK_1(GameScene::updateRank, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(rankUpdateListener, 1);

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

	auto gameController = GameController::create(client,server);

	gameController->setMap(map);
	this->addChild(gameController, -1);

	createMenuButton();
	createStatusButton();
	createRank();

	return true;
}