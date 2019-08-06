#ifndef GDSTEST_H
#define GDSTEST_H

#include <QObject>

class GdsTest : public QObject
{
    Q_OBJECT
public:
    GdsTest();
    ~GdsTest();

private slots:
    void initTestCase() {}
    void cleanupTestCase() {}
    void boundary_setPoints();
    void boundary_boundingRect();
    void path_setPath();
    void path_boundingRect();
    void cellReference_boundingRect();
    void layout_deleteCell();
    void cell_removeReference();

    void transform();
};



#endif // GDSTEST_H
