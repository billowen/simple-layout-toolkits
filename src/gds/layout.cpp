#include "layout.h"

gds::Layout::Layout(const QString &name, short version)
{
    _name = name;
    _version = version;
    _unit = 1e-6;
    _precision = 1e-9;
    time_t now = time(nullptr);
    _createdAt = now;
    _modifiedAt = now;
}

QString gds::Layout::name() const
{
    return _name;
}

short gds::Layout::version() const
{
    return _version;
}

double gds::Layout::unit() const
{
    return _unit;
}

double gds::Layout::precision() const
{
    return _precision;
}

time_t gds::Layout::createdAt() const
{
    return _createdAt;
}

time_t gds::Layout::modifiedAt() const
{
    return _modifiedAt;
}

gds::Cell *gds::Layout::cell(const QString &name) const
{
    if (_cellIdx.contains(name) && _cellIdx[name] < _cells.size()) {
        return _cells[_cellIdx[name]].get();
    } else {
        return nullptr;
    }
}

void gds::Layout::setName(const QString &name)
{
    _name = name;
}

void gds::Layout::setUnit(double unit)
{
    _unit = unit;
}

void gds::Layout::setPrecision(double precision)
{
    _precision = precision;
}

void gds::Layout::setCreatedAt(time_t time)
{
    _createdAt = time;
}

void gds::Layout::setModifiedAt(time_t time)
{
    _modifiedAt = time;
}
