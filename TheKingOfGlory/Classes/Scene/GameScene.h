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
	cocos2d::Label* bgmLabel;
	cocos2d::Label* effectLabel;
	cocos2d::Label* exitLabel;
	cocos2d::ui::CheckBox* musicCheckBox;
	cocos2d::ui::CheckBox* effectCheckBox;
	cocos2d::EventListenerTouchOneByOne* menuListener;
	cocos2d::Rect menuRect;
	cocos2d::ui::Button* statusButton;
	std::pair<int, cocos2d::ui::Text*> blueRank;
	std::pair<int, cocos2d::ui::Text*> redRank;
	std::pair<int, cocos2d::ui::Text*> gameTime;

	void onEnter();
	void createMenuButton();
	void createStatusButton();
	void createTime();
	void updateMenu();
	void createMenu();
	void removeMenu();
	void createResultBox(cocos2d::EventCustom* event);
	void createRank();
	void updateRank(cocos2d::EventCustom* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Rect rectOfLabel(cocos2d::Label* label);
public:
	static cocos2d::Scene* createScene(Client* client, Server*server = nullptr);
	static GameScene* create(Client* client, Server*server);
	virtual bool init(Client* client, Server*server );
	

};
