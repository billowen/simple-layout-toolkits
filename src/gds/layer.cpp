#include "layer.h"

gds::Layer::Layer()
{
    _layer = _datatype = -1;
}

gds::Layer::Layer(int layer, int datatype)
{
    _layer = layer;
    _datatype = datatype;
}

int gds::Layer::layer() const
{
    return _layer;
}

int gds::Layer::datatype() const
{
    return _datatype;
}


