#include "referencebase.h"


gds::ReferenceBase::ReferenceBase(gds::Cell *parent)
{
    _parent = parent;
    _refCell = "";
    _origin = QPoint(0, 0);
    _rotation = 0;
    _magnification = 0;
    _xReflection = false;
}

gds::ReferenceBase::~ReferenceBase()
{

}

gds::Cell *gds::ReferenceBase::parent() const
{
    return _parent;
}

QString gds::ReferenceBase::refCell() const
{
    return _refCell;
}

QPoint gds::ReferenceBase::origin() const
{
    return _origin;
}

double gds::ReferenceBase::rotation() const
{
    return _rotation;
}

double gds::ReferenceBase::magnification() const
{
    return _magnification;
}

bool gds::ReferenceBase::xReflection() const
{
    return _xReflection;
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
