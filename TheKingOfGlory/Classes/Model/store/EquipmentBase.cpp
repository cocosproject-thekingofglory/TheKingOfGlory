#include "EquipmentBase.h"
#include "../../Manager/Manager.h"

bool EquipmentBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	createListener();

	setHP(HP[_id - 1000]);
	setDamage(DAMAGE[_id - 1000]);
	setDefend(DEFEND[_id - 1000]);

	return true;
}

EquipmentBase* EquipmentBase::createWithSpriteFrameName(const std::string& filename)
{
	auto equip = new EquipmentBase();
	if (equip && equip->initWithSpriteFrameName(filename) && equip->init())
	{
		equip->autorelease();
		return equip;
	}
	CC_SAFE_DELETE(equip);
	return nullptr;
}

void EquipmentBase::createListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EquipmentBase::onTouchBegin, this);
	listener->onTouchEnded = CC_CALLBACK_2(EquipmentBase::onTouchEnded, this);
	listener->setEnabled(true);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10);
}

bool EquipmentBase::onTouchBegin(Touch*touch, Event*event)
{
	Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, _size.width, _size.height);
	if (rect.containsPoint(touchPos))
	{
		return true;
	}
	return false;
}

void EquipmentBase::onTouchEnded(Touch*touch, Event*event)
{
	auto player = Manager::getInstance()->playerManager->getLocalPlayer();
	if (player->getMoney() >= getCostMoney())
	{
		player->addMoney(-getCostMoney());
		//player->addEquipment(this);
	}
	else
	{
		/*钱不够的提示*/
	}
}