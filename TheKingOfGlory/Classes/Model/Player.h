#ifndef __MODEL_PLAYER_H__
#define __MODEL_PLAYER_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"SpriteBase.h"
#include"AnimationLoader.h"

USING_NS_CC;
using namespace ui;

const float PLAYER_ATTACK_RADIUS = 5.0;
const float PLAYER_DAMAGE = 5.0;
const float PLAYER_HPVALUE = 50.0;


class Player :public Sprite
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
		NONE
	};

	enum AnimationType {
		STANDING,
		MOVING,
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
		"Warrior",
		"Mage",
		"Archer"
	};

	static Player* createPlayer(const std::string& id, int role);

	bool init(int role);//初始化一些条件
	bool initWithRole(int role);//只是初始化名字

	void setStatus(Status);
	Status getStatus();

	void isLocal(bool a);//？
	bool isLocal();

	void setLifeValue(int lifeValue) { _lifeValue = lifeValue; }
	int getLifeValue() { return _lifeValue; }

	void setHP(LoadingBar* HP) { _HP = HP; }
	LoadingBar* getHP() { return _HP; }

	void setHPInterval(float HPInterval) { _HPInterval = HPInterval; }//血条更新值
	int getHPInterval() { return _HPInterval; }

	void setMove(bool move) { _move = move; }
	bool isMove() { return _move; }

	void setCanAttack(bool canAttack) { _isCanAttack = canAttack; }
	bool isCanAttack() { return _isCanAttack; }

	void setMoveCount(int moveCount) { _moveCount = moveCount; }
	int getMoveCount() { return _moveCount; }

	Animate* getAnimateByType(AnimationType type);

	void Player::addAnimation(const std::string & animationName, float delay, int animationFrameNum);
	// load animation only when it's not loaded

	void Player::playAnimation(const std::string& animationName, int index);//参数待补充，Repeat the selected animation forever

	void Player::initStatus(Player::Status status);

	bool _isMove;
	bool _isAttack;

	void moveTo(Vec2 toPosition);
	void onWalk(Vec2 position);
	void stopMove();

	void attack(const void* enemy);//参数待补充
	void stopAttack();

	void beHit(int attack);
	int getAttack() { return _attack; }

private:
	std::string _id;
	std::string _roleName;
	PlayerType _type;

	Status _status;
	time_t directions[4];
	Direction _direction;

	float _speed;

	int _lifeValue;
	LoadingBar* _HP;
	float _HPInterval;// 血条的更新量

	bool _isLocal;

	bool _move;
	int _moveCount;

	bool _isCanAttack;
	int _attack;

	int _animationNum;
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

	EventListenerTouchOneByOne* _listener;
};
#endif
