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

	Sprite * bg = Sprite::create("Pictures/Background/HelpBackground.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, -1);

	auto *chnStrings = Dictionary::createWithContentsOfFile("fonts/Text.xml");
	const char *str1 = ((String*)chnStrings->objectForKey("line1"))->getCString();
	auto helpLabel = createLabel(str1);
	helpLabel->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(helpLabel);

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

	backButton->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.2f);
	static_cast<Label*>(backButton->getLabel())->enableGlow(Color4B(0, 0, 0, 255 * 0.6f));

	buttons->addChild(backButton, 1);
	buttons->setPosition(0, 0);

	return buttons;
}

void HelpScene::onEnter()
{
	Layer::onEnter();
	GameAudio::getInstance()->playBgm("Sound/HelpScene.mp3");
}

void HelpScene::menuOkCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

cocos2d::Label * HelpScene::createLabel(const char * text)
{
	auto label = Label::createWithTTF(fontToUTF8(text), "fonts/arial.ttf", 64);
	label->enableShadow(Color4B::WHITE, Size(10, 10), 2);
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
