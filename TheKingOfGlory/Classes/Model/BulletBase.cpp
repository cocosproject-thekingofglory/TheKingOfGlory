#include "BulletBase.h"
#include "Manager/Manager.h"



BulletBase* BulletBase::create(SpriteBase*attacker, SpriteBase*beAttacker, std::string animationName,std::string spriteName, float speed)
{
	auto bullet = new BulletBase();
	if (bullet&&bullet->initWithSpriteFrameName(spriteName))
	{
		bullet->setColor(attacker->getColor());
		bullet->setDamage(attacker->getDamage());
		bullet->setSpeed(speed);
		bullet->setAttack(attacker);
		bullet->setBeAttack(beAttacker);

		beAttacker->addBeAttackBullet(bullet);
		
		initAnimation(animationName, bullet);
		bullet->setAnimationName(animationName);

		bullet->runAnimation(animationName, bullet);
		bullet->schedule(CC_CALLBACK_0(BulletBase::move,bullet), "move");
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void BulletBase::initAnimation(std::string animationName, BulletBase*bullet)
{
	/*
	¶¯»­ÃüÃûwei"move_01.png"
	*/

	const float delay = 0.1;
	bullet->loadAnimation(animationName, delay, 1);

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
	if (collisionDetection())
	{
		_beAttacker->beAttack(_damage);
		removeFromMap(this);
		return ;
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
