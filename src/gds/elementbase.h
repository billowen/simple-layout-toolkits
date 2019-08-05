#ifndef GDS_ELEMENTBASE_H
#define GDS_ELEMENTBASE_H
#include <QPoint>
#include <QRect>
#include <memory>
#include <QList>
#include "layer.h"

namespace gds {
class Cell;
/**
 * @brief The base class for geometric elements. Other drawing elements derive from this.
 */
class ElementBase
{
public:
    explicit ElementBase(Cell *parent);
    virtual ~ElementBase();

    Cell *parent() const;
    Layer layer() const;
    QRect boundingRect();

    void setLayer(const Layer &layer);
protected:
    void invalidBBox();
    virtual void calculateBBox() = 0;

    Cell *_parent;
    Layer _layer;
    std::unique_ptr<QRect> _bbox;
};
}



#endif // ELEMENTBASE_H
