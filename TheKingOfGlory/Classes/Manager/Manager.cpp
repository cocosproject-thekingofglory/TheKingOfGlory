#include "Manager.h"
#include "Controller/GameController.h"

USING_NS_CC;

Manager* Manager::_instance;


Soldier* Manager::createSoldier(const std::string &filename, const int color)
{
	auto soldier = Soldier::createWithSpriteFrameName(filename);
	if (soldier)
	{	
		soldier->setColor(color);
		_soldierList[color].pushBack(soldier);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}


Tower* Manager::createTower(const std::string &filename, const int color)
{
	auto tower = Tower::createWithSpriteFrameName(filename);
	if (tower)
	{
		tower->setColor(color);
		_towerList[color].pushBack(tower);

		return tower;
	}
	CC_SAFE_DELETE(tower);
	return nullptr;
}


bool Manager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	playerManager = PlayerManager::create();
	this->addChild(playerManager, -1);

	auto tower_red_1=createTower(RED_TOWER_FILENAME, RED);
	tower_red_1->init();
	tower_red_1->setScale(1.5);
	GameMap::getCurrentMap()->addSprite(tower_red_1, GameMap::Type::Player_Red);
	//if (map == nullptr)log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	//else log("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	auto tower_blue_1 = createTower(BLUE_TOWER_FILENAME, BLUE);
	//GameMap::getCurrentMap()->addSprite(tower_blue_1, GameMap::Type::Tower_Blue);

	scheduleUpdate();
	return true;
}

void Manager::update(float dt)
{
	static int count_AppearSoldier = 0;
	count_AppearSoldier++;
	//生成小兵
	if (count_AppearSoldier%SOLDIER_APPEAR_INTERVAL == 0)
	{
		count_AppearSoldier = 0;
		if (_soldierList[RED].size() < 1)
		{
			auto soldier_red = createSoldier(RED_SOLDIER_FILENAME, RED);
			soldier_red->init();
			soldier_red->startMove();
			soldier_red->setScale(5);
			GameMap::getCurrentMap()->addSprite(soldier_red, GameMap::Type::Player_Red);

		}

		if (_soldierList[BLUE].size() < 1)
		{
			auto soldier_blue = createSoldier(BLUE_SOLDIER_FILENAME, BLUE);
			soldier_blue->init();
			soldier_blue->startMove();
			soldier_blue->setScale(5);
			GameMap::getCurrentMap()->addSprite(soldier_blue, GameMap::Type::Player_Blue);

		}


	}

	
	static int count_AttackSoldier = 0;
	count_AttackSoldier++;
	if (count_AttackSoldier%SOLDIER_UPDATE_INTERVAL == 0)
	{
		count_AttackSoldier = 0;

		//清空攻击和被攻击列表
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				_soldierList[i].at(j)->getAttackTarget().clear();
				_soldierList[i].at(j)->getBeAttackTarget().clear();

			}
			for (int j = 0; j < _towerList[i].size(); j++)
			{
				_towerList[i].at(j)->getAttackTarget().clear();
				_towerList[i].at(j)->getBeAttackTarget().clear();
			}
		}
		for (auto pair : playerManager->getPlayerList())
		{
			auto player = pair.second;
			player->getBeAttackTarget().clear();
			player->getAttackTarget().clear();
		}
		
		//寻找攻击和被攻击目标
		for (int i = 0; i < 2; i++)
		{
			//为兵找
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				for (auto pair : playerManager->getPlayerList())
				{
					auto player = pair.second;
					if (insideAttack(_soldierList[i].at(j), player))
					{
						player->addAttackTarget(_soldierList[i].at(j));
						_soldierList[i].at(j)->addBeAttackTarget(player);
					}
					if (insideAttack(player, _soldierList[i].at(j)))
					{
						_soldierList[i].at(j)->addAttackTarget(player);
						player->addBeAttackTarget(_soldierList[i].at(j));
					}

				}
				for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
				{
					if (insideAttack(_soldierList[i ^ 1].at(k), _soldierList[i].at(j)))
					{
						_soldierList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
						_soldierList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
						break;
					}
				}
				for (int k = 0; k < _towerList[i ^ 1].size(); k++)
				{
					if (insideAttack(_towerList[i ^ 1].at(k), _soldierList[i].at(j)))
					{
						_soldierList[i].at(j)->addAttackTarget(_towerList[i ^ 1].at(k));
						_towerList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
						break;
					}
				}
				
			}
			
			//为塔找
			for (int j = 0; j < _towerList[i].size(); j++)
			{
				for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
				{
					if (_towerList[i].at(j)->insideAttack(_soldierList[i^1].at(k)))
					{
						_towerList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
						_soldierList[i ^ 1].at(k)->addBeAttackTarget(_towerList[i].at(j));
						break;
					}
				}
			}

		}


		

		for (int i = 0; i < 2; i++)
		{
			//兵攻击
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				//进行攻击就停止移动
				if (_soldierList[i].at(j)->attack())
				{
					_soldierList[i].at(j)->stopMove();
				}
				else
				{
					_soldierList[i].at(j)->startMove();
				}
			}

			//塔攻击
			for (int j = 0; j < _towerList[i].size(); j++)
			{
				_towerList[i].at(j)->attack();
			}
		}
		
		//从列表中删除死去的兵和塔
		for (int i = 0; i < 2; i++)
		{
			//删兵
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				if (_soldierList[i].at(j)->getNowHPValue() <= 0.0)
				{
					_soldierList[i].at(j)->removeFromParentAndCleanup(true);
					_soldierList[i].eraseObject(_soldierList[i].at(j));
				}
			}

			//删塔
			for (int j = 0; j < _towerList[i].size(); j++)
			{
				if (_towerList[i].at(j)->getNowHPValue() <= 0.0)
				{
					_towerList[i].at(j)->removeFromParentAndCleanup(true);
					_towerList[i].eraseObject(_towerList[i].at(j));
				}
			}
		}



	}
	
}

bool Manager::insideAttack(SpriteBase* beAttack,SpriteBase* attack)
{
	auto rect = attack->getBoundingBox();
	auto attackRect = Rect(rect.getMinX(), rect.getMinY(),
		rect.size.width + attack->getAttackRadius(), rect.size.height + attack->getAttackRadius());
	return attackRect.intersectsRect(beAttack->getBoundingBox());
}

Manager* Manager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = create();
	}
	return _instance;
}