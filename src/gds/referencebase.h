#ifndef GDS_REFERENCEBASE_H
#define GDS_REFERENCEBASE_H
#include <QString>
#include <QPoint>
#include <QRect>

namespace gds {
class Cell;

/**
 * @brief The base class for cell refenernces.
 */
class ReferenceBase
{
public:
    explicit ReferenceBase(Cell *parent);
    virtual ~ReferenceBase();

    Cell * parent();
    QString refCell();
    QPoint origin();
    double rotation();
    double magnification();
    bool xReflection();
    QRect boundingRect();
    Cell * referTo();

    void setRefCell(const QString &cellName);
    void setOrigin(const QPoint &origin);
    void setRotation(double degree);
    void setMagnification(double mag);
    void setXReflection(bool flag);
    void setReferTo(Cell * referTo);
    void setBBoxOutdate();

protected:
    virtual void calculateBoundingRect() = 0;

    Cell *_parent;
    QString _refCell;
    QPoint _origin;
    double _rotation, _magnification;
    bool _xReflection;
    Cell* _referTo;

    bool _bboxOutdate;
    QRect _bbox;
};
}




#endif // REFERENCEBASE_H
