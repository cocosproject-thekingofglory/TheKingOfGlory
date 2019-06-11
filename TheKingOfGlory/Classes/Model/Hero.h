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
		One = 100,
		Two = 80,
		Three = 100
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
		Two = 120,
		Three = 150
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
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 10
	};
	enum Radius
	{
		One = 1000,
		Two = 100,
		Three = 500,
		Attack=600
	};

public:
	static Mage* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();
	void setStatus(Status status);

};

class Paladin :public Player
{
private:
	enum Damage
	{
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 20
	};
	enum Radius
	{
		One = 100,
		Two = 150,
		Three = 150,
	};

public:
	static Paladin* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();
	void setStatus(Status status);

};


class Ranger :public Player
{
private:
	enum Damage
	{
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 20
	};
	enum Radius
	{
		One = 100,
		Two = 100,
		Three = 150,
	};
public:
	static Ranger* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();

};


class Cavalier :public Player
{
private:
	enum Damage
	{
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 20
	};
	enum Radius
	{
		One = 150,
		Two = 150,
		Three = 150,
	};

public:
	static Cavalier* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();
	void setStatus(Status status);

};