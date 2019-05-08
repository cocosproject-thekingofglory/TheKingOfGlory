#include "LoginScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;


cocos2d::Scene * LoginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
		return false;
	visible_Size = Director::getInstance()->getVisibleSize();

	createBackground();


	return true;
}

void LoginScene::onEnter()
{
	Layer::onEnter();

	//²¥·Å±³¾°ÒôÀÖ
	//GameAudio::getInstance()->playBgm("Sounds/StartBgm.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/StartBgm.mp3", true);

}

void LoginScene::createBackground()
{
	//Ìí¼Ó±³¾°
	auto background = Sprite::create("Pictures/Background/LoginBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}
