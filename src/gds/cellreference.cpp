#include "cellreference.h"
#include "transform.h"
#include <limits>


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

    Transform transform;
    if (_xReflection) {
        transform = transform.scale(1, -1);
    }
    transform = transform
            .scale(_magnification, _magnification)
            .rotate(_rotation)
            .translate(_origin.x(), _origin.y());

    int width = _bbox.right() - _bbox.left();
    int height = _bbox.bottom() - _bbox.top();

    QVector<QPoint> pts;
    QPoint topLeft = _bbox.topLeft();
    pts.push_back(topLeft);
    pts.push_back(QPoint(_bbox.left() + width, _bbox.top()));
    pts.push_back(QPoint(_bbox.left(), _bbox.top() + height));
    pts.push_back(QPoint(_bbox.left() + width, _bbox.top() + height));

    int tlx = std::numeric_limits<int>::max();
    int tly = std::numeric_limits<int>::max();
    int brx = std::numeric_limits<int>::min();
    int bry = std::numeric_limits<int>::min();

    for (auto p : pts)
    {
        QPoint tmp = transform.map(p);
        tlx = std::min(tlx, tmp.x());
        tly = std::min(tly, tmp.y());
        brx = std::max(brx, tmp.x());
        bry = std::max(bry, tmp.y());
    }

    _bbox = QRect(QPoint(tlx, tly), QPoint(brx, bry));
}
