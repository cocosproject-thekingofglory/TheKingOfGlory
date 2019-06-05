#include "StartScene.h"
#include "ui/CocosGUI.h"
#include "Util/GameAudio.h"
#include "GameScene.h"
#include "SettingsScene.h"
USING_NS_CC;
using namespace CocosDenshion;


void StartScene::onEnter()
{
	Layer::onEnter();

	//播放背景音乐
	GameAudio::getInstance()->playBgm("Sounds/StartBgm.mp3");

}

void StartScene::createBackground()
{
	//添加背景图
	auto background = Sprite::create("Pictures/Background/StartBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}

void StartScene::createPlayButton()
{
	//创建开始游戏按钮
	auto PlayButton=MenuItemLabel::create(Label::createWithTTF("Play",text_Font, text_Size),
		[=](Ref* pSender) {
		GameAudio::getInstance()->playEffect("Sounds/ButtonClick.wav");
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
		});
	PlayButton->setColor(label_Color);
	auto menu = Menu::createWithItem(PlayButton);
	menu->setPosition(Vec2(visible_Size.width*0.2, visible_Size.height*0.6));
	this->addChild(menu);
}

void StartScene::createSettingButton()
{
	//创建游戏设置按钮
	auto SettingButton= MenuItemLabel::create(Label::createWithTTF("Setting", text_Font, text_Size),
		[](Ref* pSender) {
		GameAudio::getInstance()->playEffect("Sounds/ButtonClick.wav");
		Director::getInstance()->pushScene(TransitionFade::create(1, SettingsScene::createScene()));
	});
	SettingButton->setColor(label_Color);
	auto menu = Menu::createWithItem(SettingButton);
	menu->setPosition(Vec2(visible_Size.width*0.2, visible_Size.height*0.46));
	this->addChild(menu);
}

void StartScene::createHelpButton()
{
	//创建游戏帮助按钮
	auto HelpButton = MenuItemLabel::create(Label::createWithTTF("Help", text_Font, text_Size),
		[](Ref* pSender) {
		GameAudio::getInstance()->playEffect("Sounds/ButtonClick.wav");
	//	Director::getInstance()->pushScene(TransitionFade::create(1, HelpScene::createScene()));
	});
	HelpButton->setColor(label_Color);
	auto menu = Menu::createWithItem(HelpButton);
	menu->setPosition(Vec2(visible_Size.width*0.2, visible_Size.height*0.32));
	this->addChild(menu);
}

void StartScene::createExitButton()
{
	//创建退出游戏按钮
	auto ExitButton = MenuItemLabel::create(Label::createWithTTF("Exit", text_Font, text_Size),
		[](Ref* pSender) {
		Director::getInstance()->end();
	});
	ExitButton->setColor(label_Color);
	auto menu = Menu::createWithItem(ExitButton);
	menu->setPosition(Vec2(visible_Size.width*0.2, visible_Size.height*0.18));
	this->addChild(menu);
}


cocos2d::Scene * StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
		return false;

	visible_Size = Director::getInstance()->getVisibleSize();

	text_Font = "fonts/UnifrakturCook-Bold.ttf";
	label_Color = Color3B(255,255,255);
	text_Size = 64;

	createBackground();
	createPlayButton();
	createSettingButton();
	createHelpButton();
	createExitButton();



	return true;
}
