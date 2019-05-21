#pragma once
#include "cocos2d.h"

class GameMap:public cocos2d::Layer
{
private:
	std::vector<std::vector<int>> mapInfo;
	cocos2d::TMXTiledMap * tileMap;
	cocos2d::TMXLayer * collidable;
	cocos2d::TMXObjectGroup* objectLayer;
	cocos2d::ValueMap player_red;
	cocos2d::ValueMap player_blue;
	cocos2d::ValueMap tower_red;
	cocos2d::ValueMap tower_blue;
	cocos2d::ValueMap store_red;
	cocos2d::ValueMap store_blue;
public:
	enum Type 
	{NONE, Player_Red, Player_Blue, Tower_Red, Tower_Blue, Soldier_Red, Solider_Blue };

	virtual bool init();
	void setMap(const std::string& mapName);
	static GameMap * getCurrentMap();

	cocos2d::Vec2 tileCoordToPosition(const cocos2d::Vec2 & coord);
	cocos2d::Vec2 positionToTileCoord(const cocos2d::Vec2 & pos);
	cocos2d::Vec2 centrePos(const cocos2d::Vec2 & pos);
	cocos2d::Size getMapSize();
	cocos2d::Size getTileSize();
	bool isCanAssess(const cocos2d::Vec2 & coord);
	void addSprite(cocos2d::Sprite* sprite,Type type);
	void addSprite(cocos2d::Sprite * sprite, int zOrder);

	CREATE_FUNC(GameMap);
};

