#pragma once
#include "cocos2d.h"
#include "UI/CocosGUI.h"
#include "Network/Server.h"
#include "Network/Client.h"

class GameScene:public cocos2d::Layer
{
private:
	bool hasMenu;
	cocos2d::Size visible_Size;
	cocos2d::Sprite* menu;
	cocos2d::Label* continueLabel;
	cocos2d::Label* settingLabel;
	cocos2d::Label* restartLabel;
	cocos2d::Label* returnLabel;
	cocos2d::EventListenerTouchOneByOne* menuListener;
	cocos2d::Rect menuRect;
	cocos2d::ui::Button* statusButton;

	void onEnter();
	void createMenuButton();
	void createStatusButton();
	void updateMenu();
	void createMenu();
	void removeMenu();
	void createResultBox(cocos2d::EventCustom* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Rect rectOfLabel(cocos2d::Label* label);
public:
	static cocos2d::Scene* createScene(Client* client, Server*server = nullptr);
	static GameScene* create(Client* client, Server*server);
	virtual bool init(Client* client, Server*server );
	

};
