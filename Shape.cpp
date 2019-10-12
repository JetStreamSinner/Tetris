#include "Shape.h"

Shape::Shape(QPoint coord, FigureType type) : coordinate(coord), type(type)
{
}

void Shape::setCoordinate(QPoint coord)
{
    coordinate = coord;
}

void Shape::setCoordinate(const int x, const int y)
{
    coordinate.setX(x);
    coordinate.setY(y);
}

void Shape::setType(FigureType type)
{
    this->type = type;
}


QPoint Shape::coord()
{
    return coordinate;
}

FigureType Shape::getType()
{
    return type;
}

