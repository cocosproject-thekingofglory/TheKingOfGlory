#pragma once
#include "cocos2d.h"

class GameMap;


class Grid : public cocos2d::Ref {
public:
	static Grid* create(int x, int y) {
		Grid* g = new Grid();
		if (g && g->initWithPoint(x, y))
		{
			g->autorelease();
			return g;
		}
		CC_SAFE_DELETE(g);
		return nullptr;
	}
	bool initWithPoint(int x, int y) {
		_x = x;
		_y = y;
		_canAssess = true;
		return true;
	}
	void setX(int x) { _x = x; }
	int getX() { return _x; }

	void setY(int y) { _y = y; }
	int getY() { return _y; }

	void setAssess(bool canAssess) { _canAssess = canAssess; }
	bool isCanAssess() { return _canAssess; }
private:
	int _x;
	int _y;
	bool _canAssess;
};


class PointDelegate : public cocos2d::Ref {
private:
	float _x;
	float _y;
public:
	static PointDelegate* create(float x, float y) {
		PointDelegate* p = new PointDelegate();
		if (p && p->initPoint(x, y)) {
			p->autorelease();
			return p;
		}
		CC_SAFE_DELETE(p);
		return nullptr;
	}
	bool initPoint(float x, float y) {
		_x = x;
		_y = y;
		return true;
	}
	void setX(float x) { _x = x; }
	float getX() { return _x; }

	void setY(float y) { _y = y; }
	float getY() { return _y; }

};


class PathArithmetic : public cocos2d::Ref
{
private:
	cocos2d::Vector<PointDelegate*> _invalidPoints;
	cocos2d::Vector<PointDelegate*> _pathPoints;

	int searchtimes;
public:
	static PathArithmetic* create() {
		PathArithmetic* p = new PathArithmetic();
		if (p) {
			p->autorelease();
		}
		else {
			CC_SAFE_DELETE(p);
		}
		return p;
	}
	cocos2d::Vector<PointDelegate*> getPath(cocos2d::Vec2 from, cocos2d::Vec2 to, std::vector<cocos2d::Vector<Grid*>> gridVector);
	bool findValidGrid(cocos2d::Vec2 from, cocos2d::Vec2 to, std::vector<cocos2d::Vector<Grid*>> gridVector);
	bool isCheck(cocos2d::Vec2 point, std::vector<cocos2d::Vector<Grid*>> gridVector);
};
