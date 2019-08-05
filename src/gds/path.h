#ifndef GDS_PATH_H
#define GDS_PATH_H
#include "elementbase.h"
#include <QRect>
#include <QPoint>

namespace gds {

class Cell;

/**
 * @brief An unfilled polygonal line (GDSII: PATH)
 */
class Path : public ElementBase
{
public:
    explicit Path(Cell *parent);
    virtual ~Path();

    QVector<QPoint> path() const;
    int width() const;
    int pathType() const;

    void setPath(const QVector<QPoint> &points);
    void setWidth(int width);
    void setPathType(int pathType);

protected:
    void calculateBBox();

private:
    QVector<QPoint> _path;
    int _width;
    int _pathType;
};

}



#endif // PATH_H
