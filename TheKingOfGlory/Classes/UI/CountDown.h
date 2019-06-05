#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using cocos2d::ui::Text;

class CountDown:public cocos2d::Sprite
{
public:
	static CountDown* create(const std::string& filename,const std::string& text,const std::string& fontFilePath,
	float fontSize,int delay,bool isMark,const std::function<void(void)>& callback);
	virtual bool init(const std::string& text, const std::string& fontFilePath,float fontSize,int delay,bool isMark, const std::function<void(void)>&callback);
private:
	bool isMark;
	Text* _label;
	int _time;
	std::string _text;
	std::function<void(void)> _callback;

	void updateText();
};
