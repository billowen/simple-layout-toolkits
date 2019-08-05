#include "referencebase.h"
#include "cell.h"


gds::ReferenceBase::ReferenceBase(gds::Cell *parent)
{
    _parent = parent;
    _refCell = "";
    _origin = QPoint(0, 0);
    _rotation = 0;
    _magnification = 0;
    _xReflection = false;
    _referTo = nullptr;
    _bboxOutdate = true;
    _bbox = QRect(QPoint(0, 0), QPoint(0, 0));
}

gds::ReferenceBase::~ReferenceBase()
{
    if (_referTo != nullptr) {
        _referTo->removeRefBy(this);
    }
}

gds::Cell *gds::ReferenceBase::referTo()
{
    return _referTo;
}

void gds::ReferenceBase::release()
{
    _parent->deleteReference(this);
}

gds::Cell *gds::ReferenceBase::parent()
{
    return _parent;
}

QString gds::ReferenceBase::refCell()
{
    return _refCell;
}

QPoint gds::ReferenceBase::origin()
{
    return _origin;
}

double gds::ReferenceBase::rotation()
{
    return _rotation;
}

double gds::ReferenceBase::magnification()
{
    return _magnification;
}

bool gds::ReferenceBase::xReflection()
{
    return _xReflection;
}

QRect gds::ReferenceBase::boundingRect()
{
    if (_bboxOutdate) {
        calculateBoundingRect();
    }

    return _bbox;
}

void gds::ReferenceBase::setRefCell(const QString &cellName)
{
    _refCell = cellName;
}

void gds::ReferenceBase::setOrigin(const QPoint &origin)
{
    _origin = origin;
}

void gds::ReferenceBase::setRotation(double degree)
{
    _rotation = degree;
}

void gds::ReferenceBase::setMagnification(double mag)
{
    _magnification = mag;
}

void gds::ReferenceBase::setXReflection(bool flag)
{
    _xReflection = flag;
}

void gds::ReferenceBase::setReferTo(gds::Cell *referTo)
{
    _referTo = referTo;
}

void gds::ReferenceBase::setBBoxOutdate()
{
    _bboxOutdate = true;
}
