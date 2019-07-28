#include "transform.h"
#include <cmath>


gds::Transform::Transform()
{
    _matrix[0][0] = 1;
    _matrix[0][1] = 0;
    _matrix[0][2] = 0;
    _matrix[1][0] = 0;
    _matrix[1][1] = 1;
    _matrix[1][2] = 0;
    _matrix[2][0] = 0;
    _matrix[2][1] = 0;
    _matrix[2][2] = 1;
}

gds::Transform::~Transform()
{

}

gds::Transform &gds::Transform::scale(double xScale, double yScale)
{
    _matrix[0][0] *= xScale;
    _matrix[1][0] *= xScale;
    _matrix[2][0] *= xScale;
    _matrix[0][1] *= yScale;
    _matrix[1][1] *= yScale;
    _matrix[2][1] *= yScale;

    return *this;
}

gds::Transform &gds::Transform::translate(double x, double y)
{
    double tmp[][3] = { {0,0,0},{0,0,0},{0,0,0} };
    tmp[0][0] = _matrix[0][0] + _matrix[0][2] * x;
    tmp[1][0] = _matrix[1][0] + _matrix[1][2] * x;
    tmp[2][0] = _matrix[2][0] + _matrix[2][2] * x;
    tmp[0][1] = _matrix[0][1] + _matrix[0][2] * y;
    tmp[1][1] = _matrix[1][1] + _matrix[1][2] * y;
    tmp[2][1] = _matrix[2][1] + _matrix[2][2] * y;
    tmp[0][2] = _matrix[0][2];
    tmp[1][2] = _matrix[1][2];
    tmp[2][2] = _matrix[2][2];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _matrix[i][j] = tmp[i][j];
        }
    }

    return *this;
}

gds::Transform &gds::Transform::rotate(double degrees)
{
    const double PI = std::atan(1.0) * 4;
    double angle = PI * degrees / 180.0;
    double tmp[][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

    tmp[0][0] = _matrix[0][0] * std::cos(angle) - _matrix[0][1] * std::sin(angle);
    tmp[0][1] = _matrix[0][0] * std::cos(angle) + _matrix[0][1] * std::sin(angle);
    tmp[0][2] = _matrix[0][2];
    tmp[1][0] = _matrix[1][0] * std::cos(angle) - _matrix[1][1] * std::sin(angle);
    tmp[1][1] = _matrix[1][0] * std::cos(angle) + _matrix[1][1] * std::sin(angle);
    tmp[1][2] = _matrix[1][2];
    tmp[2][0] = _matrix[2][0] * std::cos(angle) - _matrix[2][1] * std::sin(angle);
    tmp[2][1] = _matrix[2][0] * std::cos(angle) + _matrix[2][1] * std::sin(angle);
    tmp[2][2] = _matrix[2][2];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _matrix[i][j] = tmp[i][j];
        }
    }

    return *this;
}

QPoint gds::Transform::map(const QPoint &p)
{
    QPoint ret;
    ret.setX(p.x() * _matrix[0][0] + p.y() * _matrix[1][0]);
    ret.setY(p.x() * _matrix[1][0] + p.y() * _matrix[1][1]);

    return ret;
}
