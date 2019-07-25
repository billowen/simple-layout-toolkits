#include "elementbase.h"
#include "cell.h"

gds::ElementBase::ElementBase(gds::Cell *parent)
{
    _parent = parent;
}

gds::ElementBase::~ElementBase()
{

}

gds::Cell * gds::ElementBase::parent() const
{
    return _parent;
}

gds::Layer gds::ElementBase::layer() const
{
    return _layer;
}

QRect gds::ElementBase::boundingRect()
{
    if (_bbox == nullptr) {
        calculateBBox();
    }

    return *_bbox;
}

void gds::ElementBase::invalidBBox()
{
    _bbox.reset(nullptr);
}
