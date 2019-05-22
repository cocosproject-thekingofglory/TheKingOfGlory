#include "CountDown.h"
USING_NS_CC;


CountDown * CountDown::create(const std::string& filename, const std::string& text, const std::string& fontFilePath,
	float fontSize, int delay, bool isMark, const std::function<void(void)>& callback)
{
	auto countDown = new (std::nothrow) CountDown();
	if (countDown&&countDown->initWithFile(filename)&&countDown->init(text,fontFilePath,fontSize,delay,isMark,callback))
	{
		countDown->autorelease();
		return countDown;
	}
	CC_SAFE_DELETE(countDown);
	return nullptr;
}

bool CountDown::init(const std::string & text, const std::string & fontFilePath, float fontSize, int delay, bool isMark, const std::function<void(void)>&callback)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - this->getContentSize().height / 2));

	std::string Text = text;
	Text.append(StringUtils::format("%d s", delay));
	_label = Text::create(Text, fontFilePath, fontSize);
	Size contentSize = this->getContentSize();
	_label->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2));
	this->addChild(_label);
	

	_text = text;
	_time = delay;
	
	if (isMark)
	{
		auto mask = Sprite::create("Pictures/UI/Mask.png");
		mask->setPosition(Vec2(contentSize.width / 2, contentSize.height - mask->getContentSize().height *0.45));
		this->addChild(mask, -1);
	}

	_callback = callback;

	schedule(CC_CALLBACK_0(CountDown::updateText, this), 1.0f, "UpdateText");

	return true;
}

void CountDown::updateText()
{
	_time--;
	std::string Text = _text;
	Text.append(StringUtils::format("%d s", _time));
	_label->setText(Text);

	if (_time <= 0)
	{
		unschedule("UpdateText");
		_callback();
		this->removeFromParentAndCleanup(true);
	}
	
}
