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
		SKILL1 = 10,
		SKILL2 = 10,
		SKILL3 = 10
	};
	enum Radius
	{
		One = 1000,
		Two = 200,
		Three = 1000,
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
		One = 200,
		Two = 300,
		Three = 300,
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
		One = 200,
		Two = 200,
		Three = 300,
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
		One = 300,
		Two = 300,
		Three = 300,
	};

public:
	static Cavalier* create(const std::string& id, int color);

	virtual bool init(int role, int color);
	void skill1();
	void skill2();
	void skill3();
	void setStatus(Status status);

};