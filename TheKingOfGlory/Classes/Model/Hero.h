#pragma once
#include"Model/Player.h"

USING_NS_CC;


class Warrior :public Player
{
private:
	enum Damage
	{
		SKILL1 = 10,
		SKILL2=10,
		SKILL3=20
	};
	enum Radius
	{
		One = 200,
		Two = 150,
		Three = 200
	};
public:
	static Warrior* create(const std::string& id,  int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();

};

class Aviator :public Player
{
private:
	enum Damage
	{
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 15
	};
	enum Radius
	{
		One = 1000,
		Two = 200,
		Three = 200
	};
public:
	static Aviator* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();

};

class Mage :public Player
{
private:
	enum Damage
	{
		SKILL1 = 50,
		SKILL2 = 80,
		SKILL3 = 100
	};

public:
	static Mage* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();

};