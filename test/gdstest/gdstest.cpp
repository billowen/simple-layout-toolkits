#include <QtTest>
#include "gdstest.h"
#include "boundary.h"
#include "path.h"

GdsTest::GdsTest()
{

}

GdsTest::~GdsTest()
{

}

void GdsTest::boundary_boundingRect()
{
    gds::Boundary boundary(nullptr);

    QVector<QPoint> pts = { QPoint(0, 0), QPoint(5, 0), QPoint(5, 5), QPoint(0, 0)};
    boundary.setPoints(pts);
    QCOMPARE(boundary.boundingRect(),  QRect(QPoint(0, 0), QPoint(5, 5)));
}

void GdsTest::path_setPath()
{
    gds::Path path(nullptr);

    // 验证当有效point少于2个时, 是否成功抛出异常
    QVector<QPoint> pts = {QPoint(0, 0)};
    QVERIFY_EXCEPTION_THROWN(path.setPath(pts), std::runtime_error);

    pts = {QPoint(0, 0), QPoint(0, 0)};
    QVERIFY_EXCEPTION_THROWN(path.setPath(pts), std::runtime_error);

    // 验证当出现任意角度的走线时, 是否成功抛出异常
    pts = {QPoint(0, 0), QPoint(0, 5), QPoint(1, 6)};
    QVERIFY_EXCEPTION_THROWN(path.setPath(pts), std::runtime_error);
}

void GdsTest::path_boundingRect()
{
    gds::Path path(nullptr);

    QVector<QPoint> pts = {QPoint(0, 0), QPoint(5, 0), QPoint(5, 5)};
    path.setPath(pts);
    path.setWidth(2);

    QCOMPARE(path.boundingRect(), QRect(QPoint(0, -1), QPoint(6, 5)));

    path.setPathType(1);
    QCOMPARE(path.boundingRect(), QRect(QPoint(-1, -1), QPoint(6, 6)));
}

void GdsTest::boundary_setPoints()
{
    gds::Boundary boundary(nullptr);

    // Boundary::setPoints(const QVector<QPoint> &pts) expect pts has minimum 4 points;
    QVector<QPoint> pts = {QPoint(0, 0), QPoint(5, 0)};
    QVERIFY_EXCEPTION_THROWN(boundary.setPoints(pts), std::runtime_error);

    // Boundary::setPoints(const QVector<QPoint> &pts) expect the last and fist coordinates coincide.
    pts = {QPoint(0, 0), QPoint(5, 0), QPoint(5, 5), QPoint(10, 5)};
    QVERIFY_EXCEPTION_THROWN(boundary.setPoints(pts), std::runtime_error);
}
