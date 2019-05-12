#pragma once
#include "cocos2d.h"

class GameMap:public cocos2d::Layer
{
private:
	std::vector<std::vector<int>> mapInfo;
	cocos2d::TMXTiledMap * tileMap;
	cocos2d::TMXLayer * collidable;
	cocos2d::TMXObjectGroup* objectLayer;
public:
	enum Type 
	{NONE, Player_Red, Player_Blue, Tower_Red, Tower_Blue, Soldier_Red, Solider_Blue };

	static GameMap* create();
	virtual bool init();
	void setMap(const std::string& mapName);
	cocos2d::Vec2 tileCoordToPosition(const cocos2d::Vec2 & coord);
	cocos2d::Vec2 positionToTileCoord(const cocos2d::Vec2 & pos);
	cocos2d::Vec2 centrePos(const cocos2d::Vec2 & pos);
	cocos2d::TMXTiledMap * 	getCurrentMap();
	cocos2d::Size getMapSize();
	cocos2d::Size getTileSize();
	bool isCanAssess(const cocos2d::Vec2 & coord);
//	void addPlayer();
//	void removePlayer();
//	void addTower();
//	void removeTower();
//	GameMap::Type at();
//	getPlayer();
//	getTower();
//	getSolider();


};

