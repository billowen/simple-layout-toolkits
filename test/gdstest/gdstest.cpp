#include <QtTest>
#include "gdstest.h"
#include "boundary.h"
#include "path.h"
#include "layout.h"
#include "cell.h"
#include "cellreference.h"
#include "transform.h"
#include <QTransform>

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

void GdsTest::cellReference_boundingRect()
{
    gds::Layout layout("db");
    gds::Cell *cell1 = layout.createCell("cell1");
    gds::Cell *cell2 = layout.createCell("cell2");
    gds::Boundary *b1 = cell1->createBoundary();
    QVector<QPoint> pts;
    pts << QPoint(0, 0) << QPoint(5, 0) << QPoint(5, 5) << QPoint(0, 5) << QPoint(0, 0);
    b1->setPoints(pts);
    gds::CellReference *ref = cell2->createCellReference();
    ref->setRefCell("cell1");
    layout.buildCellLink();
    ref->setOrigin(QPoint(1, 1));
    QCOMPARE(cell2->boundingRect(), QRect(QPoint(1, 1), QPoint(6, 6)));
}

void GdsTest::layout_deleteCell()
{
    gds::Layout layout("db");
    gds::Cell *cell1 = layout.createCell("cell1");
    gds::Cell *cell2 = layout.createCell("cell2");
    gds::Boundary *b1 = cell1->createBoundary();
    QVector<QPoint> pts;
    pts << QPoint(0, 0) << QPoint(5, 0) << QPoint(5, 5) << QPoint(0, 5) << QPoint(0, 0);
    b1->setPoints(pts);
    gds::CellReference *ref = cell2->createCellReference();
    ref->setRefCell("cell1");
    layout.buildCellLink();

    layout.deleteCell("cell1");
    QCOMPARE(cell2->references().size(), 0);
}

void GdsTest::cell_removeReference()
{
    gds::Layout layout("db");
    gds::Cell *cell1 = layout.createCell("cell1");
    gds::Cell *cell2 = layout.createCell("cell2");
    gds::Boundary *b1 = cell1->createBoundary();
    QVector<QPoint> pts;
    pts << QPoint(0, 0) << QPoint(5, 0) << QPoint(5, 5) << QPoint(0, 5) << QPoint(0, 0);
    b1->setPoints(pts);
    gds::CellReference *ref = cell2->createCellReference();
    ref->setRefCell("cell1");
    layout.buildCellLink();

    cell2->deleteReference(ref);
    QCOMPARE(cell1->referBy().size(), 0);
}

void GdsTest::transform()
{
    QTransform translateTransform(1, 0, 0, 1, 1, 0);
    const double PI = std::atan(1.0) * 4;
    double angle = PI * 90 / 180.0;
    double cosa = std::cos(angle);
    double sina = std::sin(angle);
    QTransform rotateTransform(cosa, sina, -sina, cosa, 0, 0);

    QTransform transform = translateTransform * rotateTransform;

    QPoint p = QPoint(1, 0) * transform;
    QCOMPARE(p, QPoint(0, 2));
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
