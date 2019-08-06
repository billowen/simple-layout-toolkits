#include "cell.h"
#include "layout.h"
#include "referencebase.h"
#include "elementbase.h"
#include "boundary.h"
#include "path.h"
#include "cellreference.h"
#include <limits>

gds::Cell::Cell(gds::Layout *parent)
{
    _parent = parent;
    _name = "";
    _bboxOutdate = true;
    _bbox = QRect(QPoint(0, 0), QPoint(0, 0));
}

gds::Cell::Cell(gds::Layout *parent, const QString &name)
{
    _parent = parent;
    _name = name;
    _bboxOutdate = true;
    _bbox = QRect(QPoint(0, 0), QPoint(0, 0));
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
    if (_bboxOutdate) {
        calculateBBox();
    }

    return _bbox;
}

gds::Boundary *gds::Cell::createBoundary()
{
    _elements.push_back(std::unique_ptr<ElementBase>(new Boundary(this)));
    return dynamic_cast<Boundary*>(_elements.back().get());
}

gds::Path *gds::Cell::createPath()
{
    _elements.push_back(std::unique_ptr<ElementBase>(new Boundary(this)));
    return dynamic_cast<Path*>(_elements.back().get());
}

gds::CellReference *gds::Cell::createCellReference()
{
    _references.push_back(std::unique_ptr<ReferenceBase>(new CellReference(this)));
    return dynamic_cast<CellReference*>(_references.back().get());
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

QSet<gds::ReferenceBase *> gds::Cell::referBy()
{
    return _referBy;
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

void gds::Cell::calculateBBox()
{
    if (_elements.size() == 0 && _references.size() == 0) {
        _bbox = QRect(QPoint(0, 0), QPoint(0, 0));
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

    _bbox = QRect(QPoint(tlx, tly), QPoint(brx, bry));
}
