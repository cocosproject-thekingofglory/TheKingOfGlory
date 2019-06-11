#include "LoginScene.h"
#include "Util/GameAudio.h"
#include "StartScene.h"
#include "Model/User.h"

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
	createLoginButton();
	initUserBox();



	return true;
}

void LoginScene::onEnter()
{
	Layer::onEnter();

	//鎾斁鑳屾櫙闊充箰
	GameAudio::getInstance()->playBgm("Sounds/LoginBgm.mp3");

}

void LoginScene::createBackground()
{
	//娣诲姞鑳屾櫙鍥?
	auto background = Sprite::create("Pictures/Background/LoginBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}

void LoginScene::createLoginButton()
{
	//鍒涘缓鐧诲綍鎸夐挳
	auto loginButton = ui::Button::create("Pictures/UI/button_normal.png", "Pictures/UI/button_selected.png");
	loginButton->setTitleText("Login");
	loginButton->setTitleFontSize(32);
	loginButton->setPosition(Vec2(visible_Size.width / 2, visible_Size.height*0.35f));
	loginButton->setOpacity(233);

	//鎸変笅鐧诲綍鎸夐挳锛屽鏋滄枃鏈涓虹┖锛屽垯寮瑰嚭瀵硅瘽妗嗚鍛婏紝鍚﹀垯淇濆瓨鐢ㄦ埛鍚嶏紝鍒囨崲鍦烘櫙
	loginButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) return;
		auto username = usernameInput->getString();
		if (username.empty())
		{
			MessageBox("Username can't be empty", "Alert");
		}
		else
		{
			//鎾斁鐐瑰嚮闊虫晥
			GameAudio::getInstance()->playEffect("Sounds/LoginClick.wav");
			username.substr(0, 16);
			UserDefault::getInstance()->setStringForKey("username", username);
			User::getInstance()->setName(username);
			Director::getInstance()->replaceScene(TransitionFade::create(1.2f, StartScene::createScene()));
		}
	});
	this->addChild(loginButton);
}

void LoginScene::initUserBox()
{
	//鍒涘缓鏂囨湰杈撳叆妗?
	usernameBG = Sprite::create("Pictures/UI/input_normal.png");
	usernameBG->setScale(1.2f);
	usernameBG->setOpacity(200);

	usernameInput = ui::TextField::create("Input Username", "fonts/arial.ttf", 24);
	usernameInput->setString(UserDefault::getInstance()->getStringForKey("username", ""));
	usernameInput->setColor(Color3B::BLACK);
	usernameInput->setCursorChar('|');
	usernameInput->setCursorEnabled(true);
	usernameInput->setMaxLength(15);
	usernameInput->setMaxLengthEnabled(true);
	usernameInput->setPosition(usernameBG->getContentSize() / 2);
	usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

	usernameBG->addChild(usernameInput);

	usernameBG->setScale(1.5);
	usernameBG->setPosition(Vec2(visible_Size.width / 2,
		visible_Size.height*0.35 + usernameBG->getContentSize().height * 2));

	addChild(usernameBG);
}


void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
	//鏂囨湰妗嗙姸鎬佹敼鍙樻椂鏇存崲鍥剧墖
	switch (event) {
	case ui::TextField::EventType::ATTACH_WITH_IME:
		usernameBG->setTexture("Pictures/UI/input_active.png");
		break;
	case ui::TextField::EventType::DETACH_WITH_IME:
		usernameBG->setTexture("Pictures/UI/input_normal.png");
		break;
	}
}
