#include "WildMonster.h"
#include "GameMap.h"
#include "Manager/Manager.h"


bool WildMonster::init(int type)
{
	if (!Tower::init(YELLOW))
	{
		return false;
	}
	setColor(YELLOW);
	setAttackRadius(WILDMONSTER_ATTACK_RADIUS);
	setHPValue(WILDMONSTER_HPVALUE);
	setNowHPValue(WILDMONSTER_HPVALUE);
	setDamage(WILDMONSTER_DAMAGE);
	setAttackInterval(WILDMONSTER_ATTACK_INTERVAL);
	setDefend(WILDMONSTER_DEFEND);

	setKillExperience(WILDMONSTER_KILL_EXPRIENCE);
	setKillMoney(WILDMONSTER_KILL_MONEY);

	initAnimation();
	setHPBar();

	_originPos = BUFF_POS[type];
	_type = type;

	setScale(4.0);

	schedule(CC_CALLBACK_0(WildMonster::attack, this), 1.0, "WildMonsterAttack");
	return true;
}

WildMonster* WildMonster::createWithSpriteFrameName(const std::string& filename,int type)
{
	auto sprite = new WildMonster();
	if (sprite&&sprite->initWithSpriteFrameName(filename) && sprite->init(type))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool WildMonster::attack()
{
	for (auto pair : Manager::getInstance()->playerManager->getPlayerList())
	{
		auto player = pair.second;
		if (insideAttack(player) && player->getNowHPValue() > 0)
		{
			auto bullet = BulletBase::create(this, player, "bullet", "bullet (1).png");
			GameMap::getCurrentMap()->addChild(bullet);
			Vec2 pos = Vec2(getPosition().x + getContentSize().width / 2, getPosition().y + getContentSize().height / 2);
			bullet->setPosition(pos);
			return true;
		}
	}
	
	return false;
}

float WildMonster::beAttack(const float damage)
{
	float nowHP = getNowHPValue();
	nowHP -= damage;
	if (nowHP <= 0.0)
	{
		auto attacker = _beAttackTargetList.at(0);
		for (int i = 0; i < _beAttackTargetList.size(); i++)
		{
			_beAttackTargetList.at(i)->getAttackTarget().eraseObject(this, false);
		}
		auto parent = this->getParent();
		attacker->addDamage(BUFF_DAMAGE[_type]);
		attacker->addDefend(BUFF_DEFEND[_type]);
		auto sequence1 = Sequence::create(DelayTime::create(BUFF_EXIST_TIME), CallFunc::create([=]()
		{
			attacker->addDamage(-BUFF_DAMAGE[_type]);
			attacker->addDefend(-BUFF_DEFEND[_type]);

		}), NULL);
		attacker->runAction(sequence1);
		this->removeFromParent();
		unschedule("WildMonsterAttack");
		auto sequence2 = Sequence::create(DelayTime::create(BUFF_EXIST_TIME), CallFunc::create([=]()
		{
			setNowHPValue(getHPValue() - nowHP);
			parent->addChild(this);
			schedule(CC_CALLBACK_0(WildMonster::attack, this), 1.0, "WildMonsterAttack");
		}), NULL);
		this->runAction(sequence2);
	}
	setNowHPValue(MAX(nowHP, 0));
	updateHPBar();
	return nowHP;

}

/*
void WildMonster::initAnimation()
{
	const float delay = 0.1;
	loadAnimation("soldierMove", delay, 8);

	loadAnimation("soldierAttack", delay, 8);

}*/
