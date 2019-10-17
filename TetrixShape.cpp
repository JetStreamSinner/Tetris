#include <cmath>
#include "TetrixShape.h"

TetrixShape::TetrixShape ( const ShapeType type, const QPoint& base_point ) : shape_type ( type )
{
    shape_vertices.resize ( vertices_count );
    shape_vertices[0] = base_point;

    makeShapeByBase();
}

TetrixShape::Vertices TetrixShape::shapePoints() const
{
    return shape_vertices;
}

void TetrixShape::makeShapeByBase()
{
    const auto base_x = shape_vertices.at ( 0 ).x();
    const auto base_y = shape_vertices.at ( 0 ).y();

    QPoint point1;
    QPoint point2;
    QPoint point3;

    auto makePoint = [] ( const int x, const int y ) -> QPoint {
        return QPoint ( x, y );
    };


    switch ( shape_type ) {
    case ShapeType::i_type:
        point1 = makePoint ( base_x, base_y - 2 );
        point2 = makePoint ( base_x, base_y - 1 );
        point3 = makePoint ( base_x, base_y + 1 );
        break;
    case ShapeType::j_type:
        point1 = makePoint ( base_x, base_y - 1 );
        point2 = makePoint ( base_x, base_y + 1 );
        point3 = makePoint ( base_x - 1, base_y + 1 );
        break;
    case ShapeType::t_type:
        point1 = makePoint ( base_x, base_y - 1 );
        point2 = makePoint ( base_x + 1, base_y );
        point3 = makePoint ( base_x - 1, base_y );
        break;
    case ShapeType::o_type:
        point1 = makePoint ( base_x + 1, base_y );
        point2 = makePoint ( base_x + 1, base_y + 1 );
        point3 = makePoint ( base_x, base_y + 1 );
        break;
    case ShapeType::l_type:
        point1 = makePoint ( base_x, base_y - 1 );
        point2 = makePoint ( base_x, base_y + 1 );
        point3 = makePoint ( base_x + 1, base_y + 1 );
        break;
    case ShapeType::s_type:
        point1 = makePoint ( base_x + 1, base_y );
        point2 = makePoint ( base_x, base_y + 1 );
        point3 = makePoint ( base_x - 1, base_y + 1 );
        break;
    case ShapeType::z_type:
        point1 = makePoint ( base_x - 1, base_y );
        point2 = makePoint ( base_x, base_y + 1 );
        point3 = makePoint ( base_x + 1, base_y + 1 );
        break;
    }
    setShapeVertices ( point1, point2, point3 );
}

void TetrixShape::setShapeVertices ( const QPoint& point1, const QPoint& point2, const QPoint& point3 )
{
    if ( shape_vertices.size() < vertices_count ) {
        throw std::out_of_range ( "Broken class state" );
    }

    shape_vertices[1] = point1;
    shape_vertices[2] = point2;
    shape_vertices[3] = point3;

}


void TetrixShape::resetShape ( const ShapeType type, const QPoint& base_point )
{
    shape_vertices.clear();

    shape_vertices.resize ( vertices_count );
    shape_vertices[0] = base_point;
    shape_type = type;

    makeShapeByBase();
}

void TetrixShape::reverse()
{
    //
    // x_new = y_old
    // y_new = 1 - (x_old - (me - 2

    const auto x_field_offset = 10;
    const auto y_field_offset = 20;

    for ( auto& vertex : shape_vertices )
    {
        const auto current_x = vertex.x();
        const auto current_y = vertex.y();

        const auto x_vertex_offset = x_field_offset - current_x;
        const auto y_vertex_offset = y_field_offset - current_y;

        vertex.rx() = x_field_offset + current_x * cos ( M_PI_2 ) - current_y  * sin ( M_PI_2 );
        vertex.ry() = current_x  * sin ( M_PI_2 ) + current_y * cos ( M_PI_2 );
    }
}

void TetrixShape::xChanging ( const int val )
{
    for ( auto& vertex : shape_vertices ) {
        const int current_x = vertex.x();
        vertex.setX ( current_x + val );
    }
}

void TetrixShape::yChanging ( const int val )
{
    for ( auto& vertex : shape_vertices ) {
        const int current_y = vertex.y();
        vertex.setY ( current_y + val );
    }
}


QPoint TetrixShape::basePoint() const
{
    return shape_vertices.at ( 0 );
}

