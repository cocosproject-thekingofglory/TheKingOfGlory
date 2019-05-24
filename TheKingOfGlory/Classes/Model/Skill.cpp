#include "Skill.h"
USING_NS_CC;
using namespace ui;



Skill * Skill::create(const std::string & skillName, const std::string & skillPicture, float CDTime, const std::string& offFile)
{
	auto skill = new (std::nothrow) Skill();
	if (skill && skill->init(skillName, skillPicture,offFile,CDTime))
	{
		skill->autorelease();
		return skill;
	}
	CC_SAFE_DELETE(skill);
	return nullptr;
}

bool Skill::init(const std::string & skillName, const std::string& skillPicture,const std::string & offFile, float CDTime)
{
	if (!Button::init(skillPicture))
		return false;
	
	this->ignoreContentAdaptWithSize(true);

	setSkillName(skillName);
	_chillDown = CDTime*10.0f;
	Size contentSize = this->getContentSize();

	auto barSprite = Sprite::create(offFile);
	progress = ProgressTimer::create(barSprite);
	progress->setPercentage(0.0);
	progress->setMidpoint(Point(0.5f, 0.5f));
	progress->setType(ProgressTimer::Type::RADIAL);
	progress->setReverseDirection(true);
	progress->setPosition(Vec2(contentSize.width/2,contentSize.height/2));
	this->addChild(progress);

	setOn(true);

	this->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
			this->touch();
	});

	return true;
}

void Skill::setOn(bool isOn)
{
	_isOn = isOn;
	if (isOn)
		progress->setPercentage(0);
	else
		progress->setPercentage(100.0f);
}

void Skill::touch()
{
	if (_isOn)
	{
		onTouch();
		setOn(false);
		_time = 0;
		schedule(CC_CALLBACK_0(Skill::chillDown,this), 0.1f, "ChillDown");
	}
}


void Skill::chillDown()
{
	_time++;
	progress->setPercentage(100.0-100.0*_time / _chillDown);
	if (_time >= _chillDown)
	{
		unschedule("ChillDown");
		setOn(true);
	}
}
