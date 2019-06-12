#include "Manager.h"
#include "Controller/GameController.h"
#include "UI/CountDown.h"
#include "Model/User.h"
#include "../Model/store/EquipmentBase.h"

USING_NS_CC;


Soldier* Manager::createSoldier(const std::string &filename, const int color, int path)
{
	auto soldier = Soldier::createWithSpriteFrameName(filename, color);
	if (soldier)
	{
		soldier->addPath(GameMap::getCurrentMap()->getSoldierPath(color).at(path));
		_soldierList[color].pushBack(soldier);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

GunCar* Manager::createGunCar(const std::string &filename, const int color,int path)
{
	auto guncar = GunCar::createWithSpriteFrameName(filename, color);
	if (guncar)
	{
		guncar->addPath(GameMap::getCurrentMap()->getSoldierPath(color).at(path));
		_guncarList[color].pushBack(guncar);
		return guncar;
	}
	CC_SAFE_DELETE(guncar);
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

Store* Manager::createStore(const std::string &filename, const int color)
{
	auto store = Store::createWithSpriteFrameName(filename, color);
	if (store)
	{
		_towerList[color].pushBack(store);
		return store;
	}
	CC_SAFE_DELETE(store);
	return nullptr;
}


bool Manager::init()
{
	if (!Layer::init())
		return false;
	this->setName("Manager");
	isOnline = UserDefault::getInstance()->getBoolForKey("Network");
	if (isOnline)
		mode = static_cast<Mode>(UserDefault::getInstance()->getIntegerForKey("Mode"));

	auto sequence = Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]()
	{

		//血泉
		auto redhome = Home::create("Pictures/GameItem/redhome.png", RED);
		//redhome->setScale(0.5);
		GameMap::getCurrentMap()->addSprite(redhome, GameMap::Type::Player_Red);
		redhome->setZOrder(0);
		_homeList.pushBack(redhome);

		auto bluehome = Home::create("Pictures/GameItem/bluehome.png", BLUE);
		//bluehome->setScale(0.5);
		GameMap::getCurrentMap()->addSprite(bluehome, GameMap::Type::Player_Blue);
		bluehome->setZOrder(0);
		_homeList.pushBack(bluehome);
		//防御塔
		auto tower_blue_1 = createTower(BLUE_TOWER_FILENAME, BLUE);
		tower_blue_1->setScale(0.3);
		GameMap::getCurrentMap()->addSprite(tower_blue_1, GameMap::Type::Tower_Blue);

		auto tower_red_1 = createTower(RED_TOWER_FILENAME, RED);
		tower_red_1->setScale(0.3);
		GameMap::getCurrentMap()->addSprite(tower_red_1, GameMap::Type::Tower_Red);
		if (isOnline&&mode == Mode::Five)
		{
			for (int i = 1; i < 6; i++)
			{
				auto tower_blue = createTower(BLUE_TOWER_FILENAME, BLUE);
				tower_blue->setScale(0.3);
				GameMap::getCurrentMap()->addTower(tower_blue, BLUE, i);
				auto tower_red = createTower(RED_TOWER_FILENAME, RED);
				tower_red->setScale(0.3);
				GameMap::getCurrentMap()->addTower(tower_red, RED, i);
			}
		}

		//商店
		auto store_blue = createStore(BLUE_STORE_FILENAME, BLUE);
		store_blue->setScale(1);
		GameMap::getCurrentMap()->addSprite(store_blue, GameMap::Type::Solider_Blue);

		auto store_red = createStore(RED_STORE_FILENAME, RED);
		store_red->setScale(1);
		GameMap::getCurrentMap()->addSprite(store_red, GameMap::Type::Soldier_Red);

		auto buff_blue = Tower::createWithSpriteFrameName(BLUE_BUFF_FILENAME, YELLOW, SpriteBase::BLUEBUFF);
		buff_blue->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_blue, GameMap::Type::Buff_Blue);
		_wildMonsterList.pushBack(buff_blue);

		auto buff_red = Tower::createWithSpriteFrameName(RED_BUFF_FILENAME, YELLOW, SpriteBase::REDBUFF);
		buff_red->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_red, GameMap::Type::Soldier_Red);
		_wildMonsterList.pushBack(buff_red);

		playerManager = PlayerManager::create();
		this->addChild(playerManager, -1);

		if (isOnline)
		{
			static_cast<GameController*>(Director::getInstance()->getRunningScene()->
				getChildByName("GameScene")->getChildByName("GameController"))->
				gameClient->sendMessage("Init " + User::getInstance()->getName() + " " + std::to_string(User::getInstance()->getRole()));
		}


		auto countDown = CountDown::create("Pictures/UI/TopBar.png", "Game start after ", "fonts/arial.ttf", 32, 5, false,
			[=]() {
			for (auto pair : playerManager->getPlayerList())
			{
				auto player = pair.second;
				player->setMove(true);
				player->setAttack(true);
				player->setSkill(true);
			}
			time_AI = 1;
			time_soldier = 1;
			time_gunCar = 1;
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("GameStart");
			schedule(CC_CALLBACK_0(Manager::scheduleCreateSoldier, this), 1.0f, "CreateSoldier");
			schedule(CC_CALLBACK_0(Manager::scheduleCreateGunCar, this), 1.0f, "CreateGunCar");
			schedule(CC_CALLBACK_0(Manager::scheduleCreateWildMonster, this), 1.0f, "CreateWildMonster");
			schedule(CC_CALLBACK_0(Manager::scheduleWildMonsterAttack, this), 2.0f, "WildMonstertAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleTowerAttack, this), 0.5f, "TowertAttack");
			if (!isOnline)
				schedule(CC_CALLBACK_0(Manager::AIHero, this), 0.5f, "PlayerAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleSoldierAttack, this), 1.0f, "UpdateSoldierAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleGunCarAttack, this), 1.0f, "UpdateGunCarAttack");
			schedule(CC_CALLBACK_0(Manager::scheduleHomeRecover, this), 1.0f, "Home");
			schedule(CC_CALLBACK_0(Manager::scheduleDeadDetect, this), 1.0f, "DeadDetect");
			schedule(CC_CALLBACK_0(Manager::scheduleBuffDetect, this), 10.0f, "BuffDetect");
		});
		cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->addChild(countDown, 2);

	}), NULL);
	this->runAction(sequence);


	return true;
}

void Manager::scheduleSoldierAttack()
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
			//打兵
			for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
			{
				if (insideAttack(_soldierList[i ^ 1].at(k), _soldierList[i].at(j)))
				{
					_soldierList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
					_soldierList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
					break;
				}
			}
			//打塔
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
			//打炮车
			for (int k = 0; k < _guncarList[i ^ 1].size(); k++)
			{
				if (insideAttack(_guncarList[i ^ 1].at(k), _soldierList[i].at(j))
					&& _guncarList[i ^ 1].at(k)->getNowHPValue() > 0)
				{
					_soldierList[i].at(j)->addAttackTarget(_guncarList[i ^ 1].at(k));
					_guncarList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
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
				//break;
			}
		}
		for (auto tower : _towerList[player1->getColor() ^ 1])
		{
			if (insideAttack(tower, player1) && tower->getNowHPValue() > 0)
			{
				player1->addAttackTarget(tower);
				tower->addBeAttackTarget(player1);
				//break;
			}
		}
		for (auto car : _guncarList[player1->getColor() ^ 1])
		{
			if (insideAttack(car, player1) && car->getNowHPValue() > 0)
			{
				player1->addAttackTarget(car);
				car->addBeAttackTarget(player1);
				//break;
			}
		}
		for (auto wild : _wildMonsterList)
		{
			if (insideAttack(wild, player1) && wild->getNowHPValue() > 0)
			{
				player1->addAttackTarget(wild);
				wild->addBeAttackTarget(player1);
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
void Manager::scheduleGunCarAttack()
{

	//清空攻击和被攻击列表
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _guncarList[i].size(); j++)
		{

			_guncarList[i].at(j)->getAttackTarget().clear();
			_guncarList[i].at(j)->getBeAttackTarget().clear();
		}
	}

	//寻找攻击和被攻击目标
	for (int i = 0; i < 2; i++)
	{
		//为炮车找
		for (int j = 0; j < _guncarList[i].size(); j++)
		{
			for (auto pair : playerManager->getPlayerList())
			{
				auto player = pair.second;
				if (player->getColor() != _guncarList[i].at(j)->getColor() &&
					insideAttack(player, _guncarList[i].at(j)) && player->getNowHPValue() > 0)
				{
					_guncarList[i].at(j)->addAttackTarget(player);
					player->addBeAttackTarget(_guncarList[i].at(j));
				}

			}
			for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
			{
				if (_guncarList[i].at(j)->insideAttack(_soldierList[i ^ 1].at(k)))
				{
					_guncarList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
					_soldierList[i ^ 1].at(k)->addBeAttackTarget(_guncarList[i].at(j));
					break;
				}
			}
			//打炮车
			for (int k = 0; k < _guncarList[i ^ 1].size(); k++)
			{
				if (_guncarList[i].at(j)->insideAttack(_soldierList[i ^ 1].at(k)))
				{
					_soldierList[i].at(j)->addAttackTarget(_guncarList[i ^ 1].at(k));
					_guncarList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
					break;
				}
			}

		}

	}



	for (int i = 0; i < 2; i++)
	{
		//炮车攻击
		for (int j = 0; j < _guncarList[i].size(); j++)
		{
			//进行攻击就停止移动
			if (_guncarList[i].at(j)->attack())
			{
				_guncarList[i].at(j)->stopMove();
			}
			else
			{
				_guncarList[i].at(j)->startMove();
			}
		}

	}


}
void Manager::scheduleWildMonsterAttack()
{
	for (int j = 0; j < _wildMonsterList.size(); j++)
	{
		_wildMonsterList.at(j)->getAttackTarget().clear();
		_wildMonsterList.at(j)->getBeAttackTarget().clear();
	}
	for (int j = 0; j < _wildMonsterList.size(); j++)
	{
		for (auto pair : playerManager->getPlayerList())
		{
			auto player = pair.second;
			if (_wildMonsterList.at(j)->insideAttack(player) &&
				player->getNowHPValue() > 0)
			{
				_wildMonsterList.at(j)->addAttackTarget(player);
				player->addBeAttackTarget(_wildMonsterList.at(j));
			}

		}
	}
	for (int j = 0; j < _wildMonsterList.size(); j++)
	{
		if (_wildMonsterList.at(j)->attack())
		{
			_wildMonsterList.at(j)->runAttackAnimation();
			_wildMonsterList.at(j)->stopStandAnimation();
		}
		else
		{
			_wildMonsterList.at(j)->stopAttackAnimation();
			_wildMonsterList.at(j)->runStandAnimation();
		}
	}
}

void Manager::scheduleCreateSoldier()
{
	time_soldier++;
	//if (time_soldier < 3)
		//return;
	time_soldier = 0;
	if (isOnline&&mode == Mode::Five)
	{
		if (_soldierList[RED].size() < 30)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto soldier_red = createSoldier(RED_SOLDIER_FILENAME, RED, i);
				soldier_red->startMove();
				GameMap::getCurrentMap()->addSprite(soldier_red, GameMap::Type::Soldier_Red);
			}


		}
		if (_soldierList[BLUE].size() < 30)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto soldier_blue = createSoldier(BLUE_SOLDIER_FILENAME, BLUE, i);
				soldier_blue->startMove();
				GameMap::getCurrentMap()->addSprite(soldier_blue, GameMap::Type::Solider_Blue);
			}
		}
	}
	else
	{
		if (_soldierList[RED].size() < 10)
		{
			auto soldier_red = createSoldier(RED_SOLDIER_FILENAME, RED, 0);
			soldier_red->startMove();
			GameMap::getCurrentMap()->addSprite(soldier_red, GameMap::Type::Soldier_Red);

		}
		if (_soldierList[BLUE].size() < 10)
		{
			auto soldier_blue = createSoldier(BLUE_SOLDIER_FILENAME, BLUE, 0);
			soldier_blue->startMove();
			GameMap::getCurrentMap()->addSprite(soldier_blue, GameMap::Type::Solider_Blue);
		}
	}

}

void Manager::scheduleCreateGunCar()
{
	time_gunCar++;
	if (time_gunCar < 10)
		return;
	time_gunCar = 0;
	if (isOnline&&mode == Mode::Five)
	{
		if (_soldierList[RED].size() < 15)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto guncar_blue = createGunCar(BLUE_GUNCAR_FILENAME, BLUE, i);
				guncar_blue->startMove();
				GameMap::getCurrentMap()->addSprite(guncar_blue, GameMap::Type::Solider_Blue);
			}


		}
		if (_soldierList[BLUE].size() < 15)
		{
			for (int i = 0; i < 3; ++i)
			{
				auto guncar_red = createGunCar(RED_GUNCAR_FILENAME, RED, 0);
				guncar_red->startMove();
				GameMap::getCurrentMap()->addSprite(guncar_red, GameMap::Type::Soldier_Red);
			}
		}
	}
	else
	{
		if (_guncarList[BLUE].size() < 5)
		{
			auto guncar_blue = createGunCar(BLUE_GUNCAR_FILENAME, BLUE, 0);
			guncar_blue->startMove();
			GameMap::getCurrentMap()->addSprite(guncar_blue, GameMap::Type::Solider_Blue);

		}
		if (_guncarList[RED].size() < 5)
		{
			auto guncar_red = createGunCar(RED_GUNCAR_FILENAME, RED, 0);
			guncar_red->startMove();
			GameMap::getCurrentMap()->addSprite(guncar_red, GameMap::Type::Soldier_Red);

		}
	}



}

void Manager::scheduleCreateWildMonster()
{
	if (_wildMonsterList.size() == 2)return;
	if (_wildMonsterList.size() == 0)
	{
		auto buff_blue = Tower::createWithSpriteFrameName(BLUE_BUFF_FILENAME, YELLOW, SpriteBase::BLUEBUFF);
		buff_blue->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_blue, GameMap::Type::Buff_Blue);
		_wildMonsterList.pushBack(buff_blue); 

		auto buff_red = Tower::createWithSpriteFrameName(RED_BUFF_FILENAME, YELLOW, SpriteBase::REDBUFF);
		buff_red->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_red, GameMap::Type::Buff_Red);
		_wildMonsterList.pushBack(buff_red);
	}
	else if (_wildMonsterList.at(0)->getType() == SpriteBase::REDBUFF)
	{
		auto buff_blue = Tower::createWithSpriteFrameName(BLUE_BUFF_FILENAME, YELLOW, SpriteBase::BLUEBUFF);
		buff_blue->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_blue, GameMap::Type::Buff_Blue);
		_wildMonsterList.pushBack(buff_blue); 
	}
	else
	{
		auto buff_red = Tower::createWithSpriteFrameName(RED_BUFF_FILENAME, YELLOW, SpriteBase::REDBUFF);
		buff_red->setScale(1.5);
		GameMap::getCurrentMap()->addSprite(buff_red, GameMap::Type::Buff_Red);
		_wildMonsterList.pushBack(buff_red);
	}
}


void Manager::scheduleDeadDetect()
{
	for (int i = 0; i < _wildMonsterList.size(); i++)
	{
		if (_wildMonsterList.at(i)->getNowHPValue() <= 0.0)
		{
			auto wild = _wildMonsterList.at(i);

			Vector<BulletBase*> bulletList = wild->getBeAttackBullet();

			for (auto bullet : bulletList)
			{
				bullet->removeFromMap(bullet);
			}

			wild->removeFromParentAndCleanup(true);
			_wildMonsterList.eraseObject(wild);
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
		for (int j = 0; j < _guncarList[i].size(); j++)
		{
			if (_guncarList[i].at(j)->getNowHPValue() <= 0.0)
			{
				auto guncar = _guncarList[i].at(j);

				Vector<BulletBase*> bulletList = guncar->getBeAttackBullet();

				for (auto bullet : bulletList)
				{
					bullet->removeFromMap(bullet);
				}

				guncar->removeFromParentAndCleanup(true);
				_guncarList[i].eraseObject(guncar);
			}
		}

		//删塔
		for (auto tower : _towerList[i])
		{
			if (tower->getNowHPValue() <= 0.0)
			{
				tower->destroy();
				auto sequence = Sequence::create(DelayTime::create(6.0f), CallFunc::create([=]() {
					_towerList[i].eraseObject(tower);
					//tower->removeFromParentAndCleanup(true);
				}), NULL);
				this->runAction(sequence);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (_towerList[i].empty())
		{
			unschedule("CreateSoldier");
			unschedule("CreateGunCar");
			unschedule("CreateWildMonster");
			unschedule("TowertAttack");
			unschedule("UpdateSoldierAttack");
			unschedule("UpdateGunCarAttack");
			unschedule("WildMonstertAttack");
			unschedule("PlayerAttack");
			unschedule("Home");
			unschedule("DeadDetect");
			unschedule("BuffDetect");
			playerManager->getLocalPlayer()->setMove(false);
			playerManager->getLocalPlayer()->setAttack(false);
			playerManager->getLocalPlayer()->setSkill(false);
			playerManager->getLocalPlayer()->setStatus(Player::Status::STANDING);
			bool isWin;
			if (i == playerManager->getLocalPlayer()->getColor())
				isWin = false;
			else
				isWin = true;
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ToOver", (void*)isWin);
			break;
		}
	}

}

void Manager::scheduleBuffDetect()
{
	for (auto pair : playerManager->getPlayerList())
	{
		auto player = pair.second;
		if (player->blue_buffExist)
		{
			player->blue_buffExist = false;
			player->addDefend(-BLUE_BUFF_ADD_DEFEND);
			std::string stip;
			stip.append(StringUtils::format("Lose Blue Buff!!!"));
			auto tip = Tip::create(stip, 1.0, Color4B::BLUE);
			tip->setPosition(Vec2(player->getContentSize().width / 2, player->getContentSize().height / 2));
			Vec2 to = Vec2(player->getContentSize().width / 2, player->getContentSize().height);
			auto moveup = MoveTo::create(1.0, to);
			tip->runAction(moveup);
			player->addChild(tip);
		}
		if (player->red_buffExist)
		{
			player->red_buffExist = false;
			player->addDamage(-RED_BUFF_ADD_DAMAGE);
			std::string stip;
			stip.append(StringUtils::format("Lose Red Buff!!!"));
			auto tip = Tip::create(stip, 1.0, Color4B::RED);
			tip->setPosition(Vec2(player->getContentSize().width / 2, player->getContentSize().height / 2));
			Vec2 to = Vec2(player->getContentSize().width / 2, player->getContentSize().height);
			auto moveup = MoveTo::create(1.0, to);
			tip->runAction(moveup);
			player->addChild(tip);
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
					_towerList[i].at(j)->insideAttack(player) && player->getNowHPValue() > 0)
				{
					_towerList[i].at(j)->addAttackTarget(player);
					player->addBeAttackTarget(_towerList[i].at(j));
				}

			}
			for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
			{
				if (_towerList[i].at(j)->insideAttack(_soldierList[i ^ 1].at(k)))
				{
					_towerList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
					_soldierList[i ^ 1].at(k)->addBeAttackTarget(_towerList[i].at(j));
					break;
				}
			}

			for (int k = 0; k < _guncarList[i ^ 1].size(); k++)
			{
				if (_towerList[i].at(j)->insideAttack(_guncarList[i ^ 1].at(k)))
				{
					_towerList[i].at(j)->addAttackTarget(_guncarList[i ^ 1].at(k));
					_guncarList[i ^ 1].at(k)->addBeAttackTarget(_towerList[i].at(j));
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
			if (_towerList[i].at(j)->getNowHPValue())
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
	time_AI++;
	for (auto pair : playerManager->getPlayerList())
	{
		auto player = pair.second;
		if (!player->isLocal() && player->getStatus() != Player::Status::DEAD)
		{
			if ((player->getNowHPValue() / player->getHPValue()) < 0.5)
			{
				if (player->getColor() == BLUE)
					player->startMove(GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Player_Blue));
				else
					player->startMove(GameMap::getCurrentMap()->getObjectPosition(GameMap::Type::Player_Red));

			}
			else
			{
				if (player->getAttackTarget().size())
				{
					player->attack();
					if (time_AI % 50 == 0)
					{
						if ((player->getNowHPValue() / player->getHPValue()) < 0.5)
							player->skillRecover();
					}
					if (time_AI % 30 == 0)
					{
						time_AI = 50;
						int n = rand() % 3;
						switch (n)
						{
						case 0:player->skill1(); break;
						case 1:player->skill2(); break;
						case 3:player->skill3(); break;
						}
					}
					if (time_AI >= 15000)
						time_AI = 1;
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
	auto manager = dynamic_cast<Manager*>(cocos2d::Director::getInstance()->getRunningScene()->
		getChildByName("GameScene")->getChildByName("GameController")->getChildByName("Manager"));
	return manager;
}
