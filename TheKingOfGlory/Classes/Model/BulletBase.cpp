#include "BulletBase.h"
#include "Manager/Manager.h"



BulletBase* BulletBase::create(SpriteBase*attacker, SpriteBase*beAttacker, const std::string& animationName, const std::string& spriteName, float speed)
{
	auto bullet = new BulletBase();
	if (bullet&&bullet->initWithSpriteFrameName(spriteName)&&bullet->init(attacker,beAttacker,animationName,speed))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void BulletBase::initAnimation(const std::string&animationName, BulletBase*bullet)
{
	/*
	¶¯»­ÃüÃûwei"move_01.png"
	*/

	const float delay = 0.1;
	bullet->loadAnimation(animationName, delay, 1);

}

bool BulletBase::init(SpriteBase * attacker, SpriteBase * beAttacker, const std::string& animationName, float speed)
{
	this->setColor(attacker->getColor());
	this->setDamage(attacker->getDamage());
	this->setSpeed(speed);
	this->setAttack(attacker);
	this->setBeAttack(beAttacker);

	beAttacker->addBeAttackBullet(this);

	initAnimation(animationName, this);
	this->setAnimationName(animationName);

	this->runAnimation(animationName, this);

	_times = 0;

	this->schedule(CC_CALLBACK_0(BulletBase::move, this), "move");

	return true;
}


bool BulletBase::removeFromMap(BulletBase*bullet)
{
	bullet->unschedule("move");
	bullet->stopAnimation(bullet);

	bullet->getBeAttack()->getBeAttackBullet().eraseObject(bullet);

	bullet->removeFromParentAndCleanup(true);
	return true;
}


void BulletBase::move()
{
	_times++;
	if (collisionDetection())
	{
		_beAttacker->beAttack(_damage);
		removeFromMap(this);
		return ;
	}
	if (_times > 100)
	{
		removeFromMap(this);
		return;
	}

	Vec2 bulletPos = this->getPosition();
	Vec2 aimPos = _beAttacker->getPosition();
	
	int flagX = (bulletPos.x < aimPos.x) ? 1 : -1, flagY = (bulletPos.y < aimPos.y) ? 1 : -1;

	float dx = flagX * MIN(getSpeed(), fabs(bulletPos.x - aimPos.x));
	float dy = flagY * MIN(getSpeed(), fabs(bulletPos.y - aimPos.y));

	this->setPosition(Vec2(bulletPos.x + dx, bulletPos.y + dy));
}



bool BulletBase::collisionDetection()
{
	return this->getBoundingBox().intersectsRect(_beAttacker->getBoundingBox());
}
