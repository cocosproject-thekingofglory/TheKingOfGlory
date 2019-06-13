#include "HelpScene.h"
#include "Util/GameAudio.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite * bg = Sprite::create("Pictures/Background/WhiteBackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, -1);


	auto label1 = createLabel("God travels across the boundless universe in an ark.");
	label1->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.8f));
	label1->setColor(Color3B::BLACK);
	auto label2 = createLabel("They use powerful force in the universe to create heroes.");
	label2->setPosition(Vec2(visibleSize.width * 0, visibleSize.height * 0.74f));
	label2->setColor(Color3B::BLACK);
	auto label3 = createLabel("To survive or to destroy, the road ahead is changeable.");
	label3->setPosition(Vec2(visibleSize.width * 0.06f, visibleSize.height * 0.68f));
	label3->setColor(Color3B::BLACK);
	auto label4 = createLabel("Go fight! Heros.");
	label4->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.62f));
	label4->setColor(Color3B::BLACK);
	auto label5 = createLabel("Operational mode:");
	auto label6 = createLabel("Mouse Click: Move,Attack,LaunchSkill");
	auto label7 = createLabel("Key Q: SkillOne");
	auto label8 = createLabel("Key W: SkillTwo");
	auto label9 = createLabel("Key E: SkillThree");
	label5->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.55f));
	label6->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.45f));
	label7->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.40f));
	label8->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.35f));
	label9->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.30f));
	label5->setColor(Color3B::BLACK);
	label6->setColor(Color3B::BLACK);
	label7->setColor(Color3B::BLACK);
	label8->setColor(Color3B::BLACK);
	label9->setColor(Color3B::BLACK);

	this->addChild(label1);
	this->addChild(label2);
	this->addChild(label3);
	this->addChild(label4);
	this->addChild(label5);
	this->addChild(label6);
	this->addChild(label7);
	this->addChild(label8);
	this->addChild(label9);

	auto label = createLabel("Key A: Attack");
	label->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.40f));
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	label = createLabel("Key R: SkillRecover");
	label->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.35f));
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	label = createLabel("Key S: SkillSpeedUp");
	label->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.30f));
	label->setColor(Color3B::BLACK);
	this->addChild(label);

	addChild(createText());

	return true;
}

cocos2d::Menu* HelpScene::createText()
{
	const auto buttons = Menu::create();

	const auto backButton = MenuItemLabel::create(
		Label::createWithTTF("BACK", "fonts/UnifrakturCook-Bold.ttf", 64),
		CC_CALLBACK_1(HelpScene::menuOkCallback, this));

	const auto visibleSize = Director::getInstance()->getVisibleSize();

	backButton->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.15f);
	static_cast<Label*>(backButton->getLabel())->enableGlow(Color4B(0, 0, 0, 255 * 0.6f));
	static_cast<Label*>(backButton->getLabel())->setColor(Color3B(173 ,216,230));

	buttons->addChild(backButton, 1);
	buttons->setPosition(0, 0);

	return buttons;
}

void HelpScene::onEnter()
{
	Layer::onEnter();
	GameAudio::getInstance()->playBgm("Sounds/HelpScene.mp3");
}

void HelpScene::menuOkCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

cocos2d::Label * HelpScene::createLabel(const char * text)
{
	auto label = Label::createWithTTF(fontToUTF8(text), "fonts/Courgette-Regular.ttf", 40);
	label->setColor(Color3B::WHITE);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	return label;
}

char *HelpScene::fontToUTF8(const char* font)
{
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len + 1];
	std::memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *str = new char[len + 1];
	std::memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)delete[]wstr;
	return str;
}
