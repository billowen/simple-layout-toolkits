#ifndef GDS_CELLREFERENCE_H
#define GDS_CELLREFERENCE_H
#include "cell.h"
#include "referencebase.h"

namespace gds {

/**
 * @brief A simple reference to another Cell (GDSII: SREF)
 */
class CellReference : public ReferenceBase
{
public:
    explicit CellReference(Cell *parent);
    virtual ~CellReference();

protected:
    virtual void calculateBoundingRect();

};
}




#endif // CELLREFERENCE_H
