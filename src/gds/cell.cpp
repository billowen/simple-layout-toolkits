#include "cell.h"
#include "layout.h"
#include "referencebase.h"
#include <limits>

gds::Cell::Cell(gds::Layout *parent)
{
    _parent = parent;
    _name = "";
}

gds::Cell::Cell(gds::Layout *parent, const QString &name)
{
    _parent = parent;
    _name = name;
}

gds::Cell::~Cell()
{
    foreach (ReferenceBase* ref, _referBy) {
        ref->release();
    }
}

gds::Layout *gds::Cell::parent() const
{
    return _parent;
}

QString gds::Cell::name() const
{
    return _name;
}

QVector<gds::ElementBase *> gds::Cell::elements() const
{
    QVector<gds::ElementBase *> list;
    for (auto &ptr : _elements) {
        list.push_back(ptr.get());
    }

    return list;
}

QVector<gds::ReferenceBase *> gds::Cell::references() const
{
    QVector<gds::ReferenceBase *> list;
    for (auto &ptr : _references) {
        list.push_back(ptr.get());
    }

    return list;
}

void gds::Cell::setName(const QString &name)
{
    _name = name;
}

QRect gds::Cell::boundingRect()
{
    if (_elements.size() == 0 && _references.size() == 0) {
        return QRect(QPoint(0, 0), QPoint(0, 0));
    }

    int tlx = std::numeric_limits<int>::max();
    int tly = std::numeric_limits<int>::max();
    int brx = std::numeric_limits<int>::min();
    int bry = std::numeric_limits<int>::min();

    for (auto & e : _elements) {
        QRect rect = e->boundingRect();
        QPoint topLeft = rect.topLeft();
        QPoint bottomRight = rect.bottomRight();
        tlx = std::min(tlx, topLeft.x());
        tly = std::min(tly, topLeft.y());
        brx = std::max(brx, bottomRight.x());
        bry = std::max(bry, bottomRight.y());
    }

    for (auto & e : _references) {
        QRect rect = e->boundingRect();
        QPoint topLeft = rect.topLeft();
        QPoint bottomRight = rect.bottomRight();
        tlx = std::min(tlx, topLeft.x());
        tly = std::min(tly, topLeft.y());
        brx = std::max(brx, bottomRight.x());
        bry = std::max(bry, bottomRight.y());
    }

    return QRect(QPoint(tlx, tly), QPoint(brx, bry));
}

void gds::Cell::deleteReference(gds::ReferenceBase *ref)
{
    int cnt = 0;
    for (auto &i : _references) {
        if (i.get() == ref) {
            _references.erase(_references.begin() + cnt);
            break;
        }
    }
}

void gds::Cell::deleteElement(gds::ElementBase *element)
{
    int cnt = 0;
    for (auto &i : _elements) {
        if (i.get() == element) {
            _elements.erase(_elements.begin() + cnt);
            break;
        }
    }
}

void gds::Cell::addRefBy(gds::ReferenceBase *ref)
{
    if (ref != nullptr) {
        _referBy.insert(ref);
    }
}

void gds::Cell::removeRefBy(gds::ReferenceBase *ref)
{
    _referBy.remove(ref);
}

void gds::Cell::buildCellLink()
{
    for (auto & ref : _references) {
        Cell *cell = _parent->cell(ref->refCell());
        if (cell != nullptr) {
            ref->setReferTo(cell);
            cell->addRefBy(ref.get());
        }
    }
}
