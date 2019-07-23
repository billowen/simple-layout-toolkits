#include "cell.h"

gds::Cell::Cell(gds::Layout *parent)
{
    _parent = parent;
    _name = "";
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
