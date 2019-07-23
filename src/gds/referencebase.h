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
    ReferenceBase(Cell *parent);
    virtual ~ReferenceBase();

    Cell * parent() const;
    QString refCell() const;
    QPoint origin() const;
    double rotation() const;
    double magnification() const;
    bool xReflection() const;
    virtual QRect boundingRect() = 0;

    void setRefCell(const QString &cellName);
    void setOrigin(const QPoint &origin);
    void setRotation(double degree);
    void setMagnification(double mag);
    void setXReflection(bool flag);

private:
    Cell *_parent;
    QString _refCell;
    QPoint _origin;
    double _rotation, _magnification;
    bool _xReflection;
};
}




#endif // REFERENCEBASE_H
