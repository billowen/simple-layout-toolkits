#ifndef TST_PATH_H
#define TST_PATH_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "path.h"
#include <QRect>
#include <QPoint>

using namespace testing;

TEST(Path, setPath)
{
    gds::Path path(nullptr);

    // 验证当有效point少于2个时, 是否成功抛出异常
    QVector<QPoint> pts = {QPoint(0, 0)};
    EXPECT_THROW(path.setPath(pts), std::runtime_error);

    pts = {QPoint(0, 0), QPoint(0, 0)};
    EXPECT_THROW(path.setPath(pts), std::runtime_error);

    // 验证当出现任意角度的走线时, 是否成功抛出异常
    pts = {QPoint(0, 0), QPoint(0, 5), QPoint(1, 6)};
    EXPECT_THROW(path.setPath(pts), std::runtime_error);
}

TEST(Path, boundingRect)
{
    gds::Path path(nullptr);

    QVector<QPoint> pts = {QPoint(0, 0), QPoint(5, 0), QPoint(5, 5)};
    path.setPath(pts);
    path.setWidth(2);

    EXPECT_EQ(path.boundingRect(), QRect(QPoint(0, -1), QPoint(6, 5)));

    path.setPathType(1);
    EXPECT_EQ(path.boundingRect(), QRect(QPoint(-1, -1), QPoint(6, 6)));
}

#endif // TST_PATH_H
