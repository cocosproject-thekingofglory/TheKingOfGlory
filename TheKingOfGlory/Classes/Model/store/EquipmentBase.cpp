#include "EquipmentBase.h"
#include "../../Manager/Manager.h"

bool EquipmentBase::init(int id)
{
	if (!Sprite::init())
	{
		return false;
	}
	setId(id);

	createListener();

	setHP(HP[_id - 1000]);
	setDamage(DAMAGE[_id - 1000]);
	setDefend(DEFEND[_id - 1000]);
	setCostMoney(MONEY[_id - 1000]);
	
	return true;
}

EquipmentBase* EquipmentBase::createWithSpriteFrameName(const std::string& filename, int id)
{
	auto sprite = new EquipmentBase();
	if (sprite  && sprite->init(id))
	{
		if (sprite->initWithSpriteFrameName(filename))
		{
			sprite->autorelease();
			return sprite;
		}

	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


void EquipmentBase::createListener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EquipmentBase::onTouchBegin, this);
	listener->onTouchEnded = CC_CALLBACK_2(EquipmentBase::onTouchEnded, this);
	listener->setEnabled(false);
	listener->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10);
}

bool EquipmentBase::onTouchBegin(Touch*touch, Event*event)
{
	Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
	if (rect.containsPoint(touchPos))
	{
		return true;
	}
	return false;
}

void EquipmentBase::onTouchEnded(Touch*touch, Event*event)
{
	auto _localplayer = Manager::getInstance()->playerManager->getLocalPlayer();
	if (_localplayer->getEquipmentCnt() < PLAYER_MAX_EQUIPMENT_CNT)
	{
		if (_localplayer->getMoney() >= getCostMoney())
		{
			_localplayer->addMoney(-getCostMoney());
			log("buy a equipment.");
			//player->addEquipment(this);
			_localplayer->addDamage(getDamage());
			_localplayer->addDefend(getDefend());
			_localplayer->addHPValue(getHP());
			_localplayer->addEquipment(this, _id);
		}
		else
		{
			/*钱不够的提示*/
		}
	}
	else
	{
		/*装备栏已满的提示*/
	}
}
