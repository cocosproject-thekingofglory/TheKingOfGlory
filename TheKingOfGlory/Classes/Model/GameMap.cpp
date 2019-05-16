#include "GameMap.h"
USING_NS_CC;


bool GameMap::init()
{
	this->setName("map");
	return true;	
}

void GameMap::setMap(const std::string& mapName)
{
	std::string path = "Pictures/GameItem/map/" + mapName + ".tmx";
	tileMap = TMXTiledMap::create(path);
	this->addChild(tileMap, -1);

	collidable = tileMap->getLayer("collidable");
	//collidable->setVisible(false);
	objectLayer = tileMap->getObjectGroup("objects");

	player_red = objectLayer->getObject("player_red");
	player_blue = objectLayer->getObject("player_blue");
	tower_red = objectLayer->getObject("tower_red");
	tower_blue = objectLayer->getObject("tower_blue");
	store_red = objectLayer->getObject("store_red");
	store_blue = objectLayer->getObject("store_blue");

	mapInfo.resize(getMapSize().width);
	for (int i = 0; i < getMapSize().width; i++)
	{
		mapInfo.at(i).resize(getMapSize().height);
	}

	for (int i = 0; i < getMapSize().width; i++)
	{
		for (int j = 0; j < getMapSize().height; j++)
		{
			int tileGid = collidable->getTileGIDAt(Vec2(i,j));
			if (tileGid)
			{
				Value properties = tileMap->getPropertiesForGID(tileGid);
				ValueMap map = properties.asValueMap();
				std::string value = map.at("collidable").asString();
				if (value.compare("true") == 0)
				{
					mapInfo.at(i).at(j) = 1;
				}
			}

		}
	}
	

}

Vec2 GameMap::tileCoordToPosition(const Vec2 & coord)
{
	auto mapSize = tileMap->getMapSize();
	auto tileSize = tileMap->getTileSize();

	int x = coord.x * tileSize.width + tileSize.width / 2;
	int y = (mapSize.height - coord.y) * tileSize.height - tileSize.height / 2;
	return Vec2(x, y);
}

Vec2 GameMap::positionToTileCoord(const Vec2 & pos)
{
	Size mapSize = tileMap->getMapSize();
	Size tileSize = tileMap->getTileSize();
	int x = pos.x / tileSize.width;
	int y = (mapSize.height * tileSize.height - pos.y) / tileSize.height;
	// edge case
	x = MIN(MAX(0, x), mapSize.width - 1);
	y = MIN(MAX(0, y), mapSize.height - 1);
	return Vec2(x, y);
}

Vec2 GameMap::centrePos(const Vec2 & pos)
{
	return tileCoordToPosition(positionToTileCoord(pos));
}

cocos2d::Size GameMap::getMapSize()
{
	return tileMap->getMapSize();
}

cocos2d::Size GameMap::getTileSize()
{
	return tileMap->getTileSize();
}

bool GameMap::isCanAssess(const cocos2d::Vec2 & coord)
{
	return coord.x >= 0 && coord.x < getMapSize().width
		&&coord.y >= 0 && coord.y < getMapSize().height
		&& ((mapInfo.at(coord.x).at(coord.y) == 1) ? false : true);
}

void GameMap::addSprite(cocos2d::Sprite * sprite,Type type)
{
	if(tileMap)
		tileMap->addChild(sprite);
	if (type == Player_Red)
	{
		sprite->setPosition(Vec2(player_red.at("x").asFloat(), player_red.at("y").asFloat()));
		
	}
	else if (type == Player_Blue)
	{
		sprite->setPosition(Vec2(player_blue.at("x").asFloat(), player_blue.at("y").asFloat()));
	}
}

GameMap * GameMap::getCurrentMap()
{
	auto map = dynamic_cast<GameMap*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("map"));
	if (map)
	{
		return map;
	}
	return nullptr;
}
