#pragma once
#include "cocos2d.h"
#include "Model/SpriteBase.h"
#include "Player.h"

class Home:public SpriteBase
{
public:
	static Home* create(const std::string& fileName,int color );
	bool init(int color);
	Vector<Player*>& getRecoverList() { return _recoverList; }
	void addRecoverPlayer(Player* player) { _recoverList.pushBack(player); }
	bool isAtHome(Player* player);
	void recoverPlayer();

private:
	Vector<Player*> _recoverList;
};

