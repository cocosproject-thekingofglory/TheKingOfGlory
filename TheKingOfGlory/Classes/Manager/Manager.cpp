#include "Manager.h"
#include "Controller/GameController.h"

USING_NS_CC;

Manager* Manager::_instance;


Soldier* Manager::createSoldier(const std::string &filename, const int color)
{
	auto soldier = Soldier::createWithSpriteFrameName(filename, color);
	if (soldier)
	{
		_soldierList[color].pushBack(soldier);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

Monster* Manager::createMonster(const std::string &filename, const int color)
{
	auto monster = Monster::createWithSpriteFrameName(filename, color);
	if (monster)
	{
		_monsterList[color].pushBack(monster);
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return nullptr;
}

Tower* Manager::createTower(const std::string &filename, const int color)
{
	auto tower = Tower::createWithSpriteFrameName(filename, color);
	if (tower)
	{
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

	auto sequence = Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]()
	{


		auto tower_blue_1 = createTower(BLUE_TOWER_FILENAME, BLUE);
		tower_blue_1->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(tower_blue_1, GameMap::Type::Tower_Blue);
		log("bluePos:x:%f  y:%f", tower_blue_1->getPosition().x, tower_blue_1->getPosition().y);

		auto tower_red_1 = createTower(RED_TOWER_FILENAME,RED);
		tower_red_1->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(tower_red_1, GameMap::Type::Tower_Red);
		log("redPos:x:%f  y:%f", tower_red_1->getPosition().x, tower_red_1->getPosition().y);

		schedule(CC_CALLBACK_0(Manager::scheduleCreateSoldier, this), 2.0f, "CreateSoldier");
		schedule(CC_CALLBACK_0(Manager::scheduleCreateMonster, this), 1.8f, "CreateMonster");
		schedule(CC_CALLBACK_0(Manager::scheduleTowerAttack, this), 0.3f, "TowertAttack");
		schedule(CC_CALLBACK_0(Manager::scheduleAttack, this), 1.0f, "UpdateAttack");
		schedule(CC_CALLBACK_0(Manager::schedulePlayer, this), 1.0f, "PlayerAttack");
		schedule(CC_CALLBACK_0(Manager::scheduleDeadDetect, this), 1.0f, "DeadDetect");
	}), NULL);
	this->runAction(sequence);

	return true;
}

void Manager::scheduleAttack()
{



	//清空攻击和被攻击列表
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _soldierList[i].size(); j++)
		{
			_soldierList[i].at(j)->getAttackTarget().clear();
			_soldierList[i].at(j)->getBeAttackTarget().clear();

		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _monsterList[i].size(); j++)
		{
			_monsterList[i].at(j)->getAttackTarget().clear();
			_monsterList[i].at(j)->getBeAttackTarget().clear();

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
				if (player->getColor() != _soldierList[i].at(j)->getColor() &&
					insideAttack(_soldierList[i].at(j), player) && _soldierList[i].at(j)->getNowHPValue() > 0)
				{
					player->addAttackTarget(_soldierList[i].at(j));
					_soldierList[i].at(j)->addBeAttackTarget(player);
				}
				if (player->getColor() != _soldierList[i].at(j)->getColor() &&
					insideAttack(player, _soldierList[i].at(j)) && player->getNowHPValue() > 0)
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
				if (insideAttack(_towerList[i ^ 1].at(k), _soldierList[i].at(j))
					&& _towerList[i ^ 1].at(k)->getNowHPValue() > 0)
				{
					_soldierList[i].at(j)->addAttackTarget(_towerList[i ^ 1].at(k));
					_towerList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
					break;
				}
			}

		}

	}

	for (int i = 0; i < 2; i++)
	{
		//为野怪找
		for (int j = 0; j < _monsterList[i].size(); j++)
		{
			for (auto pair : playerManager->getPlayerList())
			{
				auto player = pair.second;
				if (player->getColor() != _monsterList[i].at(j)->getColor() &&
					insideAttack(_monsterList[i].at(j), player) && _monsterList[i].at(j)->getNowHPValue() > 0)
				{
					player->addAttackTarget(_monsterList[i].at(j));
					_monsterList[i].at(j)->addBeAttackTarget(player);
				}
				if (player->getColor() != _monsterList[i].at(j)->getColor() &&
					insideAttack(player, _monsterList[i].at(j)) && player->getNowHPValue() > 0)
				{
					_monsterList[i].at(j)->addAttackTarget(player);
					player->addBeAttackTarget(_monsterList[i].at(j));
				}

			}

		}

	}

	//为英雄找
	for (auto pair1 : playerManager->getPlayerList())
	{
		auto player1 = pair1.second;
		for (auto pair2 : playerManager->getPlayerList())
		{
			auto player2 = pair2.second;
			if (player1->getColor() != player2->getColor() && insideAttack(player2, player1))
			{
				player1->addAttackTarget(player2);
				player2->addBeAttackTarget(player1);
				break;
			}
		}
		for (auto tower : _towerList[player1->getColor() ^ 1])
		{
			if (insideAttack(tower, player1) && tower->getNowHPValue() > 0)
			{
				player1->addAttackTarget(tower);
				tower->addBeAttackTarget(player1);
				break;
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

	}



}

void Manager::scheduleCreateSoldier()
{
	if (_soldierList[RED].size() < 10)
	{
		auto soldier_red = createSoldier(RED_SOLDIER_FILENAME, RED);
		soldier_red->startMove();
		GameMap::getCurrentMap()->addSprite(soldier_red, GameMap::Type::Soldier_Red);

	}

	if (_soldierList[BLUE].size() < 10)
	{
		auto soldier_blue = createSoldier(BLUE_SOLDIER_FILENAME, BLUE);
		soldier_blue->startMove();
		GameMap::getCurrentMap()->addSprite(soldier_blue, GameMap::Type::Solider_Blue);

	}
}

//待补充
void Manager::scheduleCreateMonster()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _monsterList[i].size; j++)
		{

		}
	}
}

void Manager::scheduleDeadDetect()
{
	//从列表中删除死去的兵和塔
	for (int i = 0; i < 2; i++)
	{
		//删兵
		for (int j = 0; j < _soldierList[i].size(); j++)
		{
			if (_soldierList[i].at(j)->getNowHPValue() <= 0.0)
			{
				auto soldier = _soldierList[i].at(j);

				Vector<BulletBase*> bulletList = soldier->getBeAttackBullet();

				for (auto bullet : bulletList)
				{
					bullet->removeFromMap(bullet);
				}

				soldier->removeFromParentAndCleanup(true);
				_soldierList[i].eraseObject(soldier);
			}
		}

		//删野
		for (int j = 0; j < _monsterList[i].size(); j++)
		{
			if (_monsterList[i].at(j)->getNowHPValue() <= 0.0)
			{
				auto monster = _monsterList[i].at(j);

				monster->removeFromParentAndCleanup(true);
				_monsterList[i].eraseObject(monster);
			}
		}

		//删塔
		for (auto tower : _towerList[i])
		{
			if (tower->getNowHPValue() <= 0.0)
			{
				tower->destroy();
				bool isWin;
				if (tower->getColor() == playerManager->getLocalPlayer()->getColor())
					isWin = false;
				else
					isWin = true;
				//_towerList[i].eraseObject(tower);
				//tower->removeFromParentAndCleanup(true);
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ToOver", (void*)isWin);
			}
		}
	}
}

void Manager::scheduleTowerAttack()
{
	//清空攻击和被攻击列表
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _towerList[i].size(); j++)
		{
			_towerList[i].at(j)->getAttackTarget().clear();
			_towerList[i].at(j)->getBeAttackTarget().clear();
		}
	}

	//寻找攻击和被攻击目标
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _towerList[i].size(); j++)
		{
			for (auto pair : playerManager->getPlayerList())
			{
				auto player = pair.second;
				if (player->getColor() != _towerList[i].at(j)->getColor() &&
					insideAttack(player, _towerList[i].at(j)) && player->getNowHPValue() > 0)
				{
					_towerList[i].at(j)->addAttackTarget(player);
					player->addBeAttackTarget(_towerList[i].at(j));
				}

			}
			for (int k = 0; k < _soldierList[i^1].size(); k++)
			{
				if (_towerList[i].at(j)->insideAttack(_soldierList[i^1].at(k)))
				{
					_towerList[i].at(j)->addAttackTarget(_soldierList[i^1].at(k));
					_soldierList[i^1].at(k)->addBeAttackTarget(_towerList[i].at(j));
					break;
				}
			}

		}


	}
	for (int i = 0; i < 2; i++)
	{
		//塔攻击
		for (int j = 0; j < _towerList[i].size(); j++)
		{
			_towerList[i].at(j)->attack();
		}
	}

}

void Manager::schedulePlayer()
{
	for (auto pair : playerManager->getPlayerList())
	{
		auto player = pair.second;
		if (!player->isLocal() && player->getStatus() != Player::Status::DEAD)
		{
			if (player->getAttackTarget().size())
			{
				player->attack();
			}
			else
			{
				if(_towerList[player->getColor() ^ 1].size())
				player->startMove(_towerList[player->getColor() ^ 1].front()->getPosition());
			}
		}
	}
}

bool Manager::insideAttack(SpriteBase* beAttack, SpriteBase* attack)
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