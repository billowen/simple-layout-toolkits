#ifndef GDS_BOUNDARY_H
#define GDS_BOUNDARY_H
#include <QRect>
#include <QVector>
#include "elementbase.h"

namespace gds {

class Cell;

/**
 * @brief A filled polygon (GDSII: BOUNDARY)
 */
class Boundary : public ElementBase
{
public:
    Boundary(Cell *parent);
    virtual ~Boundary();

    QVector<QPoint> points() const;

    void setPoints(QVector<QPoint> &pts);

protected:
    virtual void calculateBBox();

    QVector<QPoint> _points;


};

}


#endif // BOUNDARY_H
