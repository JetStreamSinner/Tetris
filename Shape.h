#ifndef _Shape_H_
#define _Shape_H_
#include <QPoint>


enum class FigureType { J_type, I_type, O_type, L_type, Z_type, T_type, S_type };

class Shape
{
private:
    QPoint coordinate;
    FigureType type;
public:
    Shape() = default;
    Shape(const Shape& rhs) = default;
    Shape& operator=(const Shape& rhs) = default;
    
    Shape(QPoint coord, FigureType type);
    
    void setCoordinate(QPoint coord);
    void setCoordinate(const int x, const int y);
    void setType(FigureType type);
    
    FigureType getType();
    QPoint coord();
};

#endif
