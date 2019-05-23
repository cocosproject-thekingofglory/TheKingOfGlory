#include "Manager.h"
#include "Controller/GameController.h"
#include "UI/CountDown.h"

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

	auto sequence = Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]()
	{
		auto redhome = Home::create("Pictures/GameItem/redhome.png", RED);
		redhome->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(redhome, GameMap::Type::Player_Red);
		redhome->setZOrder(0);
		_homeList.pushBack(redhome);

		auto bluehome = Home::create("Pictures/GameItem/redhome.png", BLUE);
		bluehome->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(bluehome, GameMap::Type::Player_Blue);
		bluehome->setZOrder(0);
		_homeList.pushBack(bluehome);

		auto tower_blue_1 = createTower(BLUE_TOWER_FILENAME, BLUE);
		tower_blue_1->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(tower_blue_1, GameMap::Type::Tower_Blue);

		auto tower_red_1 = createTower(RED_TOWER_FILENAME,RED);
		tower_red_1->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(tower_red_1, GameMap::Type::Tower_Red);

		playerManager = PlayerManager::create();
		this->addChild(playerManager, -1);
	
		auto countDown = CountDown::create("Pictures/UI/TopBar.png", "Game start after ", "fonts/arial.ttf", 32, 5, false,
			[=]() {		
			for (auto pair : playerManager->getPlayerList())
			{
				auto player = pair.second;
				player->setMove(true);
				player->setAttack(true);
			}
			schedule(CC_CALLBACK_0(Manager::scheduleCreateSoldier, this), 2.0f, "CreateSoldier");
			schedule(CC_CALLBACK_0(Manager::scheduleTowerAttack, this), 0.5f, "TowertAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleAttack, this), 1.0f, "UpdateAttack");
			schedule(CC_CALLBACK_0(Manager::AIHero, this), 2.0f, "PlayerAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleHomeRecover, this), 1.0f, "Home");
			schedule(CC_CALLBACK_0(Manager::scheduleDeadDetect, this), 1.0f, "DeadDetect");
		});
		cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(countDown,2);

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

		//删塔
		for (auto tower : _towerList[i])
		{
			if (tower->getNowHPValue() <= 0.0)
			{
				tower->destroy();
				unschedule( "CreateSoldier");
				unschedule( "TowertAttack");
				unschedule( "UpdateAttack");
				unschedule( "PlayerAttack");
				unschedule("Home");
				unschedule( "DeadDetect");
				playerManager->getLocalPlayer()->setMove(false);
				playerManager->getLocalPlayer()->setAttack(false);
				playerManager->getLocalPlayer()->setStatus(Player::Status::STANDING);

				auto sequence = Sequence::create(DelayTime::create(6.0f), CallFunc::create([=]() {
					bool isWin;
					if (tower->getColor() == playerManager->getLocalPlayer()->getColor())
						isWin = false;
					else
						isWin = true;
					_towerList[i].eraseObject(tower);
					tower->removeFromParentAndCleanup(true);
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ToOver", (void*)isWin);
				}),NULL);
				this->runAction(sequence);
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

void Manager::scheduleHomeRecover()
{
	for (auto& home : _homeList)
	{
		home->getRecoverList().clear();
		for (auto pair : playerManager->getPlayerList())
		{
			auto player = pair.second;
			if (home->getColor() == player->getColor())
			{
				if (home->isAtHome(player))
					home->getRecoverList().pushBack(player);
			}
		}
	}

}



void Manager::AIHero()
{
	
	for (auto pair : playerManager->getPlayerList())
	{
		auto player = pair.second;
		if (!player->isLocal() && player->getStatus() != Player::Status::DEAD)
		{
			if ((player->getNowHPValue()/player->getHPValue()) <0.5 )
			{
				if(player->getColor()==BLUE)
					player->startMove(GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Player_Blue));
				else
					player->startMove(GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Player_Red));

			}
			else
			{
				if (player->getAttackTarget().size())
				{
					player->attack();
				}
				else
				{
					if (_towerList[player->getColor() ^ 1].size())
						player->startMove(_towerList[player->getColor() ^ 1].front()->getPosition());
				}

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