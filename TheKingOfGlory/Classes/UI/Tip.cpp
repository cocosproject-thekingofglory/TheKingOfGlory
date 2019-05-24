#include "Tip.h"
USING_NS_CC;

Tip * Tip::create(const std::string & textContent, float delay, Color4B color, float fontSize, const std::string & fontName)
{
	Tip *tip = new (std::nothrow) Tip;
	if (tip && tip->init(textContent,delay ,color,fontName, fontSize))
	{
		tip->autorelease();
		return tip;
	}
	CC_SAFE_DELETE(tip);
	return nullptr;
}

bool Tip::init(const std::string & textContent, float delay,Color4B color, const std::string & fontName, float fontSize)
{
	if (!Text::init(textContent, fontName, fontSize))
		return false;
	this->setTextColor(color);

	scheduleOnce(CC_CALLBACK_0(Tip::destroy,this), delay,"Destroy");
	return true;
}

void Tip::destroy()
{
	this->removeFromParentAndCleanup(true);
}
