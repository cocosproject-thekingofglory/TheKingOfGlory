#include "Manager.h"

USING_NS_CC;

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

bool Manager::init()
{
	if (!Layer::init())
	{
		return false;
	}
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
		auto soldier_red = createSoldier(RED_SOLDIER_FILENAME, RED);
		soldier_red->init();
		soldier_red->startMove();
		soldier_red->setPosition(RED_BIRTH_POINT);
		//soldier_red->setScale(2.0);
		this->addChild(soldier_red);

		auto soldier_blue = createSoldier(BLUE_SOLDIER_FILENAME, BLUE);
		soldier_blue->init();
		soldier_blue->startMove();
		soldier_blue->setPosition(BLUE_BIRTH_POINT);
		//soldier_blue->setScale(2.0);
		this->addChild(soldier_blue);
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
		}

		//寻找攻击和被攻击目标
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				for (int k = 0; k < _soldierList[i ^ 1].size(); k++)
				{
					if (insideAttack(_soldierList[i ^ 1].at(k), _soldierList[i].at(j)))
					{
						_soldierList[i].at(j)->addAttackTarget(_soldierList[i ^ 1].at(k));
						_soldierList[i ^ 1].at(k)->addBeAttackTarget(_soldierList[i].at(j));
						break;
					}
				}
			}
		}


		for (int i = 0; i < 2; i++)
		{
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

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < _soldierList[i].size(); j++)
			{
				if (_soldierList[i].at(j)->getNowHPValue() <= 0.0)
				{
					_soldierList[i].eraseObject(_soldierList[i].at(j));

				}
			}
		}



	}

}

bool Manager::insideAttack(SpriteBase* beAttack,SpriteBase* attack)
{
	float dx = beAttack->getPosition().x -attack->getPosition().x;
	float dy = beAttack->getPosition().y - attack->getPosition().y;
	float attackRadius = attack->getAttackRadius();
	return dx * dx + dy * dy <= attackRadius * attackRadius;
}