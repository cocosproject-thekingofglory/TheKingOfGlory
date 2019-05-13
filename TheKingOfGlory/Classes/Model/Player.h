#ifndef __MODEL_PLAYER_H__
#define __MODEL_PLAYER_H__

#include"cocos2d.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


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
		WAKING,
		RUNING
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
		WALKING,
		RUNING
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

	bool init(int role);
	bool initWithRole(int role);

	void setStatus(Status);
	Status getStatus();

	void isLocal(bool a);
	bool isLocal();

	void setLifeValue(int lifeValue) { _lifeValue = lifeValue; }
	int getLifeValue() { return _lifeValue; }

	void setHP(LoadingBar* HP) { _HP = HP; }
	LoadingBar* getHP() { return _HP; }

	//血条更新值
	void setHPInterval(float HPInterval) { _HPInterval = HPInterval; }
	int getHPInterval() { return _HPInterval; }

	void setMove(bool move) { _move = move; }
	bool isMove() { return _move; }

	void setMoveCount(int moveCount) { _moveCount = moveCount; }
	int getMoveCount() { return _moveCount; }

	bool onTouch(Touch* touch, Event* event);

	Animate* getAnimateByType(AnimationType type);

	void addAnimation();

	void playAnimation(int index);//参数待补充


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

	int _animationNum;
	std::vector<int> _animationFrameNum;
	std::vector<std::string> _animationNames;

	EventListenerTouchOneByOne* _listener;
};
#endif
