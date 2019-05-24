#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Skill:public cocos2d::ui::Button
{
public:
	std::function<void(void)> onTouch;

	static Skill* create(const std::string& skillName,const std::string& skillPicture,float CDTime, const std::string& offFile= "Pictures/GameItem/skillMask.png");
	virtual bool init(const std::string& skillName, const std::string& onFile,const std::string& offFile, float CDTime);
	virtual void onPressStateChangedToPressed() {}

	const std::string& getSkillName() { return _skillName; }
	void setSkillName(const std::string& skillName) { _skillName = skillName; }

	void setOn(bool isOn);
	bool isOn() { return _isOn; }

	void touch();

private:
	std::string _skillName;
	bool _isOn;
	float _chillDown;
	float _time;
	cocos2d::ProgressTimer* progress;
	cocos2d::EventListenerTouchOneByOne* listener;

	void chillDown();

};

