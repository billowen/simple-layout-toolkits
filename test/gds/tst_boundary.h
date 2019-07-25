#ifndef TST_BOUNDARY_H
#define TST_BOUNDARY_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "boundary.h"
#include <QRect>
#include <QPoint>

using namespace testing;

TEST(Boundary, boundingRect)
{
    gds::Boundary boundary(nullptr);

    QVector<QPoint> pts = { QPoint(0, 0), QPoint(5, 0), QPoint(5, 5), QPoint(0, 0)};
    boundary.setPoints(pts);
    EXPECT_EQ(boundary.boundingRect(),  QRect(QPoint(0, 0), QPoint(5, 5)));
}

TEST(Boundary, setPoints)
{
    gds::Boundary boundary(nullptr);

    // Boundary::setPoints(const QVector<QPoint> &pts) expect pts has minimum 4 points;
    QVector<QPoint> pts = {QPoint(0, 0), QPoint(5, 0)};
    EXPECT_THROW(boundary.setPoints(pts), std::runtime_error);

    // Boundary::setPoints(const QVector<QPoint> &pts) expect the last and fist coordinates coincide.
    pts = {QPoint(0, 0), QPoint(5, 0), QPoint(5, 5), QPoint(10, 5)};
    EXPECT_THROW(boundary.setPoints(pts), std::runtime_error);
}

#endif // TST_BOUNDARY_H
