#include "PathArithmetic.h"
#include <algorithm>
USING_NS_CC;



// 寻路函数
bool PathArithmetic::updatePath(Vec2 from, Vec2 to)
{
	auto map = GameMap::getCurrentMap();
	if (!_pathPoints.empty())
		_pathPoints.clear();
	if (!_invalidPoints.empty())
		_invalidPoints.clear();
	if (!(map->isCanAssess(map->positionToTileCoord(from)) && map->isCanAssess(map->positionToTileCoord(from))))
		return false;
	return findValidGrid(map->positionToTileCoord(from), map->positionToTileCoord(to), map->getGridVector());
}

// 查找有效路径函数
bool PathArithmetic::findValidGrid(Vec2 from, Vec2 to, std::vector<cocos2d::Vector<Grid*>> gridVector) {
	PointDelegate* fromDelegate = PointDelegate::create(from.x, from.y);
	_invalidPoints.push_back(fromDelegate);
	log("\nHHHHHHHHHHHHHHH\n");
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
			_pathPoints.push_back(pd);
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
			_pathPoints.push_back(pd);
			return true;
		}
	}
	return false;
}


bool PathArithmetic::isCheck(Vec2 point, std::vector<cocos2d::Vector<Grid*>> gridVector) {
	PointDelegate* g = PointDelegate::create(point.x, point.y);
	for (int i = 0; i < _invalidPoints.size(); i++) {
		PointDelegate* pp = _invalidPoints.at(i);
		Vec2 t = Point(pp->getX(), pp->getY());
		if (point.equals(t)) {
			return false;
		}
	}
	Vector<Grid*> tempX = gridVector.at((int)g->getX());
	Grid* grid = tempX.at((int)g->getY());
	if (grid->isCanAssess()) {
		return true;
	}
	return false;
}

Vec2 PathArithmetic::getNextPos()
{
	auto coord = _pathPoints.back();
	_pathPoints.pop_back();
	auto position = GameMap::getCurrentMap()->tileCoordToPosition(Vec2(coord->getX(), coord->getY()));
	return position;
}
