#include "path.h"

gds::Path::Path(gds::Cell *parent)
    : ElementBase (parent)
{
    _width = 0;
    _pathType = 0;
}

gds::Path::~Path()
{

}

QVector<QPoint> gds::Path::path() const
{
    return _path;
}

int gds::Path::width() const
{
    return _width;
}

int gds::Path::pathType() const
{
    return _pathType;
}

void gds::Path::setPath(const QVector<QPoint> &pts)
{
    for (auto i = 1; i < pts.size(); i++) {
        if (pts[i].x() != pts[i-1].x() && pts[i].y() != pts[i-1].y()) {
            throw std::runtime_error("The path should run vertical or horizontal.");
        }
    }

    // 移除重复点
    QVector<QPoint> tmp;
    for (auto i = 0; i <pts.size(); i++) {
        if (tmp.size() > 0 && tmp.back().x() == pts[i].x() && tmp.back().y() == pts[i].y()) {
            continue;
        }
        tmp.push_back(pts[i]);
    }
    if (tmp.size() < 2) {
        throw std::runtime_error("Path should have a minimum of 2 coordinates.");
    }

    // 移除冗余点
    _path.clear();
    for (auto pt : tmp) {
        if (_path.size() >= 2) {
            int n = _path.size();
            if (pt.x() == _path[n-1].x()
                    && pt.x() == _path[n-2].x()
                    && (pt.y() - _path[n-1].y()) * (_path[n-1].y() * _path[n-2].y()) >= 0) {
                _path[n-1] = pt;
            } else if (pt.y() == _path[n-1].y() && pt.y() == _path[n-2].y()
                       && (pt.x() - _path[n-1].x()) * (_path[n-1].x() * _path[n-2].x()) >= 0) {
                _path[n-1] = pt;
            } else {
                _path.push_back(pt);
            }
        } else {
            _path.push_back(pt);
        }
    }

    invalidBBox();
}

void gds::Path::setWidth(int width)
{
    _width = width;
    invalidBBox();
}

void gds::Path::setPathType(int pathType)
{
    _pathType = pathType;
    invalidBBox();
}

void gds::Path::calculateBBox()
{
    if (_width == 0 || _path.size() < 2) {
        _bbox.reset(new QRect(QPoint(0, 0), QPoint(0, 0)));
    }

    int width = std::abs(_width);

    int llx = _path[0].x();
    int lly = _path[0].y();
    int urx = _path[0].x();
    int ury = _path[0].y();
    for (auto pt : _path) {
        llx = pt.x() < llx ? pt.x() : llx;
        lly = pt.y() < lly ? pt.y() : lly;
        urx = pt.x() > urx ? pt.x() : urx;
        ury = pt.y() > ury ? pt.y() : ury;
    }

    // extend the path
    for (auto i = 1; i < _path.size(); i++) {
        if (_path[i - 1].x() == _path[i].x())
        {
            llx = int(_path[i].x() - width / 2.0) < llx ? int(_path[i].x() - width / 2.0) : llx;
            urx = int(_path[i].x() + width / 2.0) > urx ? int(_path[i].x() + width / 2.0) : urx;
        }
        else
        {
            lly = int(_path[i].y() - width / 2.0) < lly ? int(_path[i].y() - width / 2.0) : lly;
            ury = int(_path[i].y() + width / 2.0) > ury ? int(_path[i].y() + width / 2.0) : ury;
        }
    }

    // extend the end point
    if (_pathType > 0)
    {
        if (_path[0].x() == _path[1].x())
        {
            if (_path[0].y() < _path[1].y())
                lly = int(_path[0].y() - width / 2.0) < lly ? int(_path[0].y() - width / 2.0) : lly;
            else
                ury = int(_path[0].y() + width / 2.0) > ury ? int(_path[0].y() + width / 2.0) : ury;
        }
        else
        {
            if (_path[0].x() < _path[1].x())
                llx = int(_path[0].x() - width / 2.0) < llx ? int(_path[0].x() - width / 2.0) : llx;
            else
                urx = int(_path[0].x() + width / 2.0) > urx ? int(_path[0].x() + width / 2.0) : urx;
        }
        int n = _path.size();
        if (_path[n - 2].x() == _path[n - 1].x())
        {
            if (_path[n - 1].y() < _path[n - 2].y())
                lly = int(_path[n - 1].y() - width / 2.0) < lly ? int(_path[n - 1].y() - width / 2.0) : lly;
            else
                ury = int(_path[n - 1].y() + width / 2.0) > ury ? int(_path[n - 1].y() + width / 2.0) : ury;
        }
        else
        {
            if (_path[n - 1].x() < _path[n - 2].x())
                llx = int(_path[n - 1].x() - width / 2.0) < llx ? int(_path[n - 1].x() - width / 2.0) : llx;
            else
                urx = int(_path[n - 1].x() + width / 2.0) > urx ? int(_path[n - 1].x() + width / 2.0) : urx;
        }
    }

    _bbox.reset(new QRect(QPoint(llx, lly), QPoint(urx, ury)));
}
