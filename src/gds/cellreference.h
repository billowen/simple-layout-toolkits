#ifndef GDS_CELLREFERENCE_H
#define GDS_CELLREFERENCE_H
#include "cell.h"
#include "referencebase.h"

namespace gds {

class CellReference : public ReferenceBase
{
public:
    CellReference(Cell *parent);
    virtual ~CellReference();

protected:
    virtual void calculateBoundingRect();

};
}




#endif // CELLREFERENCE_H
