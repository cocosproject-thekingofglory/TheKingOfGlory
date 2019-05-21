#pragma once



#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"Model/SpriteBase.h"
#include "Model/Soldier.h"

USING_NS_CC;
using namespace ui;

const float PLAYER_ATTACK_RADIUS = 5.0;
const float PLAYER_DAMAGE = 10.0;
const float PLAYER_HPVALUE = 200.0;
const float PLAYER_MOVE_SPEED = 10.0;
const int PLAYER_ATTACK_INTERVAL = 200;

const float PLAYER_INITIAL_EXP = 100.0;
const float PLAYER_LEVELUP_EXP = 100.0;
const int PLAYER_MAX_LEVEL = 15;
const int PLAYER_INITIAL_LEVEL = 1;


class Player :public SpriteBase
{
public:
	/**
	 * create Player with role
	 * @return Player Object
	 */

	enum class Status : std::int8_t
	{
		STANDING,
		MOVING,
		ATTACKING,
		DEAD,
		BEINGHIT,
		SKILL
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
		"mage",
		"archer"
	};

	static Player* createPlayer(const std::string& id, int role);


	bool init(int role);//初始化一些条件
	bool initWithRole(int role);//只是初始化名字

	void setStatus(Status);//设置状态
	Status getStatus();//获取五种状态

	void isLocal(bool a);
	bool isLocal();

	void setHPBar();
	void updateHPBar();

	void setEXPBar();
	void updateEXPBar();

	void setLevel();
	void updateLevel();

	void setMove(bool move) { _move = move; }//是否能移动
	bool isMove() { return _move; }

	void setDirection(Direction direction) {
		if (_direction != direction) _direction = direction,setStatus(getStatus());	}
	Direction getDirection() { return _direction; }


	float getSpeed() { return _speed; }
	void setSpeed(float speed) {_speed=speed; }

	void stopMove();

	bool attack();
	void stopAttack();

	void skill(const void* enemy);

	float beAttack(const float damage);

	void setDestination(Vec2 destination) { _destination = destination; }
	Vec2 getDestination() { return _destination; }

	void startMove(Vec2 destination);

private:
	std::string _id;
	std::string _roleName;
	PlayerType _type;

	Status _status;
	time_t directions[4];
	Direction _direction;

	float _speed;

	bool _isLocal;
	bool _isMove;
	bool _isAttack;
	bool _isSkill;

	bool _move;


	Vec2 _destination;

	int _animationNum = 8;//动作次数？同动作帧数，需分别定义？
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

	void move();

};
