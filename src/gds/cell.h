#ifndef GDS_CELL_H
#define GDS_CELL_H
#include <QString>
#include <memory>
#include "elementbase.h"
#include "referencebase.h"

namespace gds {
class Layout;
/**
 * @brief A collection of drawing elements and references to other Cells (GDSII: STRUCTURE)
 */
class Cell
{
public:
    Cell(Layout *parent);

    Layout * parent() const;
    QString name() const;
    /**
     * @brief Get all drawing elements.
     * @return List of drawing elements.
     */
    QVector<ElementBase*> elements() const;
    /**
     * @brief Get all references.
     * @return List of references;
     */
    QVector<ReferenceBase*> references() const;

    void setName(const QString &name);

private:
    Layout *_parent;
    QString _name;

    std::vector<std::unique_ptr<ElementBase> > _elements;
    std::vector<std::unique_ptr<ReferenceBase> > _references;

};

}




#endif // CELL_H
