#include "boundary.h"


gds::Boundary::Boundary(gds::Cell *parent)
    : ElementBase(parent)
{

}

gds::Boundary::~Boundary()
{

}

QVector<QPoint> gds::Boundary::points() const
{
    return _points;
}

void gds::Boundary::setPoints(QVector<QPoint> &pts)
{
    if (pts.size() < 4) {
        throw std::runtime_error("Boundary should have a minimum of 4 coordinates.");
    }
    if (pts[0].x() != pts.back().x() || pts[0].y() != pts.back().y()) {
        throw std::runtime_error("The first and last coordinates of a boundary must coincide.");
    }

    _points.clear();
    _points = pts;

    // 将_bbox标记为失效
    _bbox.reset(nullptr);
}

void gds::Boundary::calculateBBox()
{
    if (_points.isEmpty()) {
        _bbox.reset(new QRect(QPoint(0, 0), QPoint(0, 0)));
    }

    // 重新计算Boundary的boundingRect
    int x1 = _points[0].x();
    int y1 = _points[0].y();
    int x2 = _points[0].x();
    int y2 = _points[0].y();

    for (auto p : _points) {
        x1 = x1 < p.x() ? x1 : p.x();
        y1 = y1 < p.y() ? y1 : p.y();
        x2 = x2 > p.x() ? x2 : p.x();
        y2 = y2 > p.y() ? y2 : p.y();
    }

    _bbox.reset(new QRect(QPoint(x1, y1), QPoint(x2, y2)));
}
