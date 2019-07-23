#ifndef GDS_LAYER_H
#define GDS_LAYER_H

namespace gds {
class Layer
{
public:
    Layer();
    Layer(int layer, int datatype);

    int layer() const;
    int datatype() const;

private:
    int _layer, _datatype;
};

}




#endif // LAYER_H
