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
const int PLAYER_ATTACK_INTERVAL = 200;

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
		"Warrior",
		"Mage",
		"Archer"
	};

	static Player* createPlayer(const std::string& id, int role);

	bool init(int role);//初始化一些条件
	bool initWithRole(int role);//只是初始化名字

	void setStatus(Status);//设置状态
	Status getStatus();//获取五种状态

	void isLocal(bool a);//？
	bool isLocal();

	void setLifeValue(int lifeValue) { _lifeValue = lifeValue; }
	int getLifeValue() { return _lifeValue; }

	void setHP();
	LoadingBar* getHP() { return _HP; }

	void setHPInterval(float HPInterval) { _HPInterval = HPInterval; }//血条更新值
	int getHPInterval() { return _HPInterval; }

	void setAttackRadius(float radius) { _attackRadius = radius; }
	int getAttackRadius() { return _attackRadius; }

	void setAttackInterval(int attackInterval) { _attackInterval = attackInterval; }
	int getAttackInterval() { return _attackInterval; }

	int getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }

	void setMove(bool move) { _move = move; }//是否移动
	bool isMove() { return _move; }

	void setMoveCount(int moveCount) { _moveCount = moveCount; }//移动次数计数
	int getMoveCount() { return _moveCount; }

	void setCanAttack(bool canAttack) { _isCanAttack = canAttack; }//是否攻击
	bool isCanAttack() { return _isCanAttack; }

	uint8_t getSpeed() { return _speed; }
	float getRealSpeed() { return 0.8f + _speed * 0.3f; }
	void setSpeed(uint8_t speed) {this->_speed; }

	Animate* getAnimateByType(AnimationType type);//通过类型获取到动作

	/*void addAnimation(const std::string & animationName, float delay, int animationFrameNum);
	// load animation only when it's not loaded，通过动作名字，对应动作名字的帧数，缓存添加动作

	void playAnimation(const std::string& animationName, int index);//参数待补充，Repeat the selected animation forever*/

	void moveTo(Vec2 toPosition);
	void onMove(Vec2 position);
	void stopMove();

	void attack(const void* enemy);//参数待补充
	void stopAttack();

	void skill(const void* enemy);

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
	float _damage;
	float _attackRadius;
	int _attackInterval;

	bool _isLocal;
	bool _isMove;
	bool _isAttack;
	bool _isSkill;

	bool _move;
	int _moveCount;

	bool _isCanAttack;
	int _attack;

	int _animationNum = 5;//动作次数？同动作帧数，需分别定义？
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

};
#endif
