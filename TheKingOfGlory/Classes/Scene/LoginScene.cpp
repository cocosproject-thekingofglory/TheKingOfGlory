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

	//播放背景音乐
	GameAudio::getInstance()->playBgm("Sounds/LoginBgm.mp3");

}

void LoginScene::createBackground()
{
	//添加背景图
	auto background = Sprite::create("Pictures/Background/LoginBackground.png");
	background->setPosition(Vec2(visible_Size.width / 2, visible_Size.height / 2));
	this->addChild(background, -1);
}

void LoginScene::createLoginButton()
{
	//创建登录按钮
	auto loginButton = ui::Button::create("Pictures/UI/button_normal.png", "Pictures/UI/button_selected.png");
	loginButton->setTitleText("Login");
	loginButton->setTitleFontSize(32);
	loginButton->setPosition(Vec2(visible_Size.width / 2, visible_Size.height*0.35f));
	loginButton->setOpacity(233);

	//按下登录按钮，如果文本框为空，则弹出对话框警告，否则保存用户名，切换场景
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
			//播放点击音效
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
	//创建文本输入框
	usernameBG = Sprite::create("Pictures/UI/input_normal.png");
	usernameBG->setScale(1.2f);
	usernameBG->setOpacity(200);

	usernameInput = ui::TextField::create("Input Username","fonts/arial.ttf",24);
	usernameInput->setString(UserDefault::getInstance()->getStringForKey("username", ""));
	usernameInput->setColor(Color3B::BLACK);
	usernameInput->setCursorChar('|');
	usernameInput->setCursorEnabled(true);
	usernameInput->setMaxLength(15);
	usernameInput->setMaxLengthEnabled(true);
	usernameInput->setPosition(usernameBG->getContentSize() / 2);
	usernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));
	usernameInput->setTouchSize(usernameBG->getContentSize());
	usernameInput->setTouchAreaEnabled(true);

	usernameBG->addChild(usernameInput);

	usernameBG->setScale(1.5);
	usernameBG->setPosition(Vec2(visible_Size.width / 2,
		visible_Size.height*0.35 + usernameBG->getContentSize().height * 2));

	addChild(usernameBG);
}


void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
	//文本框状态改变时更换图片
	switch (event) {
	case ui::TextField::EventType::ATTACH_WITH_IME:
		usernameBG->setTexture("Pictures/UI/input_active.png");
		break;
	case ui::TextField::EventType::DETACH_WITH_IME:
		usernameBG->setTexture("Pictures/UI/input_normal.png");
		break;
	}
}

