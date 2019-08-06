#include "cellreference.h"
#include "transform.h"
#include <limits>
#include <QTransform>
#include <cmath>


gds::CellReference::CellReference(gds::Cell *parent)
    : ReferenceBase (parent)
{

}

gds::CellReference::~CellReference()
{

}

void gds::CellReference::calculateBoundingRect()
{
    if (_referTo == nullptr) {
        throw std::runtime_error("Failed to get bbox of cell reference: failed to find the cell refered to.");
    }

    QRect cellBox = _referTo->boundingRect();
    if (cellBox == QRect(QPoint(0, 0), QPoint(0, 0))) {
        _bbox = QRect(QPoint(0, 0), QPoint(0, 0));
    }

    QTransform xReflectionTransform = _xReflection ? QTransform(1, 0, 0, -1, 0, 0) : QTransform(1, 0, 0, 1, 0, 0);
    QTransform scaleTransform = QTransform(_magnification, 0, 0, _magnification, 0, 0);
    const double PI = std::atan(1.0) * 4;
    double angle = PI * _rotation / 180.0;
    QTransform rotateTransform = QTransform(std::cos(angle), std::sin(angle), -std::sin(angle), std::cos(angle), 0, 0);
    QTransform translateTransform = QTransform(1, 0, 0, 1, _origin.x(), _origin.y());

    QTransform transform = xReflectionTransform * scaleTransform * rotateTransform * translateTransform;

    int width = cellBox.right() - cellBox.left();
    int height = cellBox.bottom() - cellBox.top();

    QVector<QPoint> pts;
    QPoint topLeft = cellBox.topLeft();
    pts.push_back(topLeft);
    pts.push_back(QPoint(cellBox.left() + width, cellBox.top()));
    pts.push_back(QPoint(cellBox.left(), cellBox.top() + height));
    pts.push_back(QPoint(cellBox.left() + width, cellBox.top() + height));

    int tlx = std::numeric_limits<int>::max();
    int tly = std::numeric_limits<int>::max();
    int brx = std::numeric_limits<int>::min();
    int bry = std::numeric_limits<int>::min();

    for (auto p : pts)
    {
        QPoint tmp = p * transform;
        tlx = std::min(tlx, tmp.x());
        tly = std::min(tly, tmp.y());
        brx = std::max(brx, tmp.x());
        bry = std::max(bry, tmp.y());
    }

    _bbox = QRect(QPoint(tlx, tly), QPoint(brx, bry));
}
