#ifndef _TETRIX_SHAPE_H_
#define _TETRIX_SHAPE_H_

#include <QPoint>
#include <QVector>

enum class ShapeType { i_type, j_type, t_type, o_type, l_type, s_type, z_type };

class TetrixShape
{
private:
    using Vertices = QVector<QPoint>;

    static const auto vertices_count = 4;
    Vertices shape_vertices;
    ShapeType shape_type;
    int figure_state = 0;

    void makeShapeByBase();

    TetrixShape() = delete;
    void setShapeVertices ( const QPoint& point1, const QPoint& point2, const QPoint& point3 );


    bool checkLeftBound ();
    bool checkRightBound ();
    void makeRotate();
    
public:
    TetrixShape ( const TetrixShape& rhs ) = default;
    TetrixShape& operator= ( const TetrixShape& rhs ) = default;

    TetrixShape ( const ShapeType type, const QPoint& base_point );


    void resetShape ( const ShapeType type, const QPoint& base_point );
    void rotate();
    void reverse_rotate();
    

    void xChanging ( const int val );
    void yChanging ( const int val );

    QPoint basePoint() const;

    Vertices shapePoints() const;

};

#endif

