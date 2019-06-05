#include "PathArithmetic.h"
#include <algorithm>
#include "Model/GameMap.h"
USING_NS_CC;
using namespace std;

// 寻路函数
Vector<PointDelegate*> PathArithmetic::getPath(Vec2 from, Vec2 to, vector<Vector<Grid*>> gridVector) {
	searchtimes = 0;
	if (findValidGrid(from, to, gridVector))
	{
		_pathPoints.reverse();
		return _pathPoints;
	}
	else
	{
		return Vector<PointDelegate*>();
	}
}


bool PathArithmetic::findValidGrid(Vec2 from, Vec2 to, vector<Vector<Grid*>> gridVector) {
	if (++searchtimes >= 40)
	{
		return false;
	}
	PointDelegate* fromDelegate = PointDelegate::create(from.x, from.y);
	_invalidPoints.pushBack(fromDelegate);
	Vector<PointDelegate*> points;
	points.pushBack(PointDelegate::create(from.x, from.y - 1));
	points.pushBack(PointDelegate::create(from.x, from.y + 1));
	points.pushBack(PointDelegate::create(from.x - 1, from.y));
	points.pushBack(PointDelegate::create(from.x + 1, from.y));
	points.pushBack(PointDelegate::create(from.x - 1, from.y - 1));
	points.pushBack(PointDelegate::create(from.x + 1, from.y + 1));
	points.pushBack(PointDelegate::create(from.x - 1, from.y + 1));
	points.pushBack(PointDelegate::create(from.x + 1, from.y - 1));
	Vector<PointDelegate*> temp;
	for (int i = 0; i < points.size(); i++) {
		PointDelegate* pd = points.at(i);
		Vec2 p = Vec2(pd->getX(), pd->getY());
		if (p.equals(to)) {
			_pathPoints.pushBack(pd);
			return true;
		}
		if (isCheck(p, gridVector)) {
			temp.pushBack(pd);
		}
	}
	std::sort(temp.begin(), temp.end(),
		[=](const Ref* obj1, const Ref* obj2) {
		PointDelegate* p1 = (PointDelegate*)obj1;
		PointDelegate* p2 = (PointDelegate*)obj2;
		double r1 = sqrt((p1->getX() - to.x) * (p1->getX() - to.x) + (p1->getY() - to.y) * (p1->getY() - to.y));
		double r2 = sqrt((p2->getX() - to.x) * (p2->getX() - to.x) + (p2->getY() - to.y) * (p2->getY() - to.y));
		return r1 < r2 ? -1 : 0;
	});
	for (int i = 0; i < temp.size(); i++) {
		PointDelegate* pd = temp.at(i);
		Vec2 p = Vec2(pd->getX(), pd->getY());
		bool flag = findValidGrid(p, to, gridVector);
		if (flag) {
			_pathPoints.pushBack(pd);
			return true;
		}
	}
	return false;
}

bool PathArithmetic::isCheck(Vec2 point, vector<Vector<Grid*>> gridVector) {
	if (point.x < 0 || point.y < 0) {
		return false;
	}
	PointDelegate* g = PointDelegate::create(point.x, point.y);
	for (int i = 0; i < _invalidPoints.size(); i++) {
		PointDelegate* pp = _invalidPoints.at(i);
		Vec2 t = Point(pp->getX(), pp->getY());
		if (point.equals(t)) {
			return false;
		}
	}
	if (point.x >= gridVector.size() || point.y >=gridVector.at(0).size()) {
		return false;
	}
	Vector<Grid*> tempX = gridVector.at((int)g->getX());
	Grid* grid = tempX.at((int)g->getY());
	if (point.x >= 0 && point.y >= 0 && grid->isCanAssess()) {
		return true;
	}
	return false;
}