#ifndef GDS_LAYOUT_H
#define GDS_LAYOUT_H
#include <QString>
#include <ctime>
#include <memory>
#include <vector>
#include <QMap>
#include "cell.h"

namespace gds {
/**
 * @brief The container holding all the gdsii data (GDSII: LIBRARY)
 */
class Layout
{
public:
    explicit Layout(const QString &name, short version = 0x0258);

    QString name() const;
    short version() const;
    double unit() const;
    double precision() const;
    time_t createdAt() const;
    time_t modifiedAt() const;
    Cell * cell(const QString &name) const;

    void setName(const QString &name);
    void setUnit(double unit);
    void setPrecision(double precision);
    void setCreatedAt(time_t time);
    void setModifiedAt(time_t time);

    /**
     * @brief Create a new cell in layout and the cell will be
     * initialized with specific name;
     * @param name Cell name.
     * @return The pointer of the cell instance.
     */
    Cell * createCell(const QString &name);
    /**
     * @brief Delete a cell.
     * @param name Cell name
     */
    void deleteCell(const QString &name);

    void buildCellLink();
private:
    QString _name;
    short _version;
    double _unit, _precision;

    time_t _createdAt, _modifiedAt;
    std::vector<std::unique_ptr<Cell> > _cells;
};

}




#endif // LAYOUT_H
