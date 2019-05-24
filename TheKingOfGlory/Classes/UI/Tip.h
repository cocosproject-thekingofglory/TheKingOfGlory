#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using cocos2d::ui::Text;

class Tip:public Text
{
public:
	static Tip* create(const std::string &textContent,float delay,cocos2d::Color4B color=cocos2d::Color4B::GREEN, float fontSize = 24, const std::string &fontName= "fonts/arial.ttf");
	bool init(const std::string &textContent, float delay, cocos2d::Color4B color,const std::string &fontName, float fontSize);
private:
	void destroy();
};

