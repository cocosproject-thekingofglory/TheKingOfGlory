#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"Model/SpriteBase.h"
#include "Model/Soldier.h"
#include "Util/PathArithmetic.h"
#include "store/EquipmentBase.h"

USING_NS_CC;
using namespace ui;

//基础属性
const float PLAYER_ATTACK_RADIUS = 10;
const float PLAYER_DAMAGE = 200.0;
const float PLAYER_HPVALUE = 200;
const float PLAYER_MOVE_SPEED = 10.0;
const int PLAYER_ATTACK_INTERVAL = 200;
const float PLAYER_DEFEND = 0.2;
//经验、金钱
const int PLAYER_INITIAL_EXP = 0;
const int PLAYER_LEVEL_UP_EXP = 8;
const int PLAYER_MAX_LEVEL = 15;
const int PLAYER_INITIAL_LEVEL = 1;
const int PLAYER_INITIAL_MONEY = 100;
//升级加属性
const float PLAYER_LEVEL_UP_DAMAGE = 5.0;
const float PLAYER_LEVEL_UP_DEFEND = 0.01;
const float PLAYER_LEVEL_UP_HPVALUE = 20;

class Player :public SpriteBase
{
public:

	enum class Status : std::int8_t
	{
		STANDING,
		MOVING,
		ATTACKING,
		DEAD,
		BEINGHIT,
		SKILL1,
		SKILL2,
		SKILL3

	};

	enum class Direction : std::int8_t
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		LEFTDOWN,
		LEFTUP,
		RIGHTDOWN,
		RIGHTUP,
		NONE
	};

	enum AnimationType {
		STANDING,
		MOVING,
		ATTACKING,
		DEAD,
		BEINGHIT,
		SKILL
	};

	enum PlayerType {
		WARRIOR,
		MAGE,
		ARCHER
	};

	char* roleName[3] = {
		"warrior",
		"aviator",
		"Archer"
	};

	static Player* createPlayer(const std::string& id, int role,int color);


	virtual bool init(int role,int color);//初始化一些条件
	bool initWithRole(int role,int color);//只是初始化名字

	void setStatus(Status);//设置状态
	Status getStatus();//获取五种状态

	void isLocal(bool a);//？
	bool isLocal();


	void setHPBar();
	void updateHPBar();

	void setMove(bool move) { _isMove = move; }//是否能移动
	bool isMove() { return _isMove; }

	void setDirection(Direction direction) {
		if (_direction != direction) _direction = direction,setStatus(getStatus());	}
	Direction getDirection() { return _direction; }


	float getSpeed() { return _speed; }
	void setSpeed(float speed) {_speed=speed; }

	void stopMove();

	bool attack();//参数待补充
	void stopAttack();

	void setAttack(bool isAttack) { _isAttack = isAttack; }

	void setSkill(bool isSkill) { _isSkill = isSkill; }

	virtual void skill1() {};
	virtual void skill2() {};
	virtual void skill3() {};

	virtual float beAttack(const float damage);

	void setSmallDestination(Vec2 destination) { _destination = destination; }
	Vec2 getSmallDestination() { return _destination; }

	void setBigDestination(Vec2 destination) { _Destination = destination; }
	Vec2 getBigDestination() { return _Destination; }

	void setRecover(bool recover) { _isRecover = recover; }
	bool getRecover() { return _isRecover; }

	void startMove(Vec2 destination);

	void judgeDirection(float dx, float dy);

	void randomSmallDestination();

	void revival();

	//金钱、经验
	void setEXPBar();
	LoadingBar* getEXPBar() { return _EXPBar; }
	void updateEXPBar();

	void setLevel(int level) { _level = level; }
	int getLevel() { return _level; }
	void updateLevel();

	void setEXPValue(int EXP) { _EXP = EXP; }
	int getEXPValue() { return _EXP; }

	void setNowEXPValue(int EXP) { _nowEXP = EXP; }
	int getNowEXPValue() { return _nowEXP; }
	void addEXP(int addEXP);

	void addMoney(int money) { _money += money; }
	int getMoney() { return _money; }
	void setMoney(int money) { _money = money; }

	//装备
	Vector<EquipmentBase*> getEquipmentList() { return _equipmentList; }

	void addEquipment(EquipmentBase*equip, int id) { _equipmentList.pushBack(equip); }
	void removeEquipment(EquipmentBase*equip);
	int getEquipmentCnt() { return _equipmentList.size(); }
protected:
	bool _isLocal;
	bool _isMove;
	bool _isAttack;
	bool _isSkill;
	bool _isRecover;

	std::string _id;
	std::string _roleName;
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

private:
	bool isOnline;

	PlayerType _type;

	Status _status;
	Direction _direction;

	float _speed;



	Vec2 _destination;
	Vec2 _Destination;
	Vector<PointDelegate*> path;

	int moveStep;


	void move();

	//金钱、经验
	int _money;
	int _EXP;
	int _nowEXP = 0;
	int _level;

	LoadingBar* _EXPBar;

	//装备
	Vector<EquipmentBase*>_equipmentList;
};

