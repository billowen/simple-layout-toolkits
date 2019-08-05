#ifndef GDS_TRANSFORM_H
#define GDS_TRANSFORM_H
#include <QPoint>

namespace gds {

class Transform
    {
    public:
        Transform();
        ~Transform();

        Transform &scale(double xScale, double yScale);
        Transform &translate(double x, double y);
        Transform &rotate(double degrees);

        QPoint map(const QPoint &p);
    private:
        double _matrix[3][3];
    };

}




#endif // TRANSFORM_H
