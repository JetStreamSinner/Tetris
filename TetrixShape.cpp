#include <cmath>
#include <QDebug>
#include <algorithm>
#include "TetrixShape.h"
#include "ShapeStateProducer.h"

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

void TetrixShape::rotate()
{
    figure_state = figure_state == 3 ? 0 : figure_state + 1;
    makeRotate();
}

void TetrixShape::reverse_rotate()
{
    figure_state = figure_state == 0 ? 3 : figure_state - 1;
    makeRotate();
}

void TetrixShape::makeRotate()
{
    
    auto offsets_list = ShapeProducer::produceState ( figure_state, shape_type );
    const auto base_x = shape_vertices.at ( 0 ).x();
    const auto base_y = shape_vertices.at ( 0 ).y();


    for ( auto i = 0; i < shape_vertices.size(); i++ ) {
        shape_vertices[i].rx() = base_x + offsets_list[i].first;
        shape_vertices[i].ry() = base_y + offsets_list[i].second;
    }

    auto byX = [] ( const QPoint& point1, const QPoint& point2 ) {
        return point1.x() > point2.x();
    };

    if ( !checkLeftBound() ) {
        const auto minimal_x = std::min_element ( shape_vertices.begin(), shape_vertices.end(), byX )->x();
        const auto delta_x = minimal_x + 1;
        for ( auto& vertex : shape_vertices ) {
            vertex.rx() += delta_x;
        }
    }

    if ( !checkRightBound() ) {
        const auto field_width = 10;
        const auto maximal_x = std::max_element ( shape_vertices.begin(), shape_vertices.end(), byX )->x();
        const auto delta_x = field_width - maximal_x - 1;
        for ( auto& vertex : shape_vertices ) {
            vertex.rx() -= delta_x;
        }
    }

}


bool TetrixShape::checkLeftBound()
{
    for ( auto& vertex : shape_vertices ) {
        if ( vertex.x() < 0 ) {
            return false;
        }
    }
    return true;
}

bool TetrixShape::checkRightBound()
{
    const auto field_width = 10;
    for ( auto& vertex : shape_vertices ) {
        if ( vertex.x() > field_width - 1 ) {
            return false;
        }
    }
    return true;
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

