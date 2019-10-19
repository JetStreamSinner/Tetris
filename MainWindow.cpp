#include <QPainter>
#include <algorithm>
#include <QDebug>
#include <QMediaPlayer>
#include "MainWindow.h"

MainWindow::MainWindow ( const int min_width, const int min_height, QMainWindow * parent ) : QMainWindow ( parent ),
    current_shape ( ShapeType::t_type, QPoint ( begining_x, begining_y ) ), engine ( device() )
{
    
    setFixedSize ( min_width, min_height );

    const auto update_time = 250;
    connect ( &timer, SIGNAL ( timeout() ), this, SLOT ( updateState() ) );
    timer.start ( update_time );
}

bool MainWindow::collisionCondition()
{

    for ( auto & vertex : freezing_cells ) {
        for ( auto & shape_vertex : current_shape.shapePoints() ) {
            if ( vertex.x() == shape_vertex.x() && vertex.y() == shape_vertex.y() ) {
                return false;
            }
        }
    }
    return true;
}

bool MainWindow::lowBoundCondition()
{
    for ( auto& vertex : current_shape.shapePoints() ) {
        if ( vertex.y() > row_count - 1 ) {
            return false;
        }
    }
    return true;
}

bool MainWindow::freezeCondition()
{
    for ( auto& vertex : current_shape.shapePoints() ) {
        if ( vertex.y() == row_count - 1 ) {
            return true;
        }
        for ( auto& freezing_vertex : freezing_cells ) {
            if ( vertex.y() + 1 == freezing_vertex.y() && vertex.x() == freezing_vertex.x() ) {
                return true;
            }
        }
    }
    return false;
}

void MainWindow::removeFilledRows()
{
    QVector<int> row_sums ( row_count, 0 );

    for ( auto row_index = 0; row_index < row_count; row_index++ ) {

        // Count vertex at one row
        int vertex_count = 0;
        std::for_each ( freezing_cells.begin(), freezing_cells.end(), [&] ( QPoint& point ) {
            if ( point.y() == row_index ) {
                vertex_count++;
            }
        } );

        // If row is filled than remove it
        if ( vertex_count == column_count ) {

            auto new_end = std::remove_if ( freezing_cells.begin(), freezing_cells.end(), [&] ( QPoint& point ) -> bool {
                return point.y() == row_index;
            } );
            freezing_cells.erase ( new_end, freezing_cells.end() );

            std::for_each ( freezing_cells.begin(), freezing_cells.end(), [&] ( QPoint& point ) {
                if ( point.y() < row_index ) {
                    point.ry()++;
                }
            } );
        }
    }

}

void MainWindow::updateState()
{
    // If shape was derrive to other shape or low bound of field
    if ( freezeCondition() ) {
        // Freeze her
        addToFreeze ( current_shape );

        // And reset by input new random shape type and default coordinates
        const auto low_bound = 0;
        const auto up_bound = 6;
        std::uniform_int_distribution<int> distribution ( low_bound, up_bound );
        const auto next_shape = static_cast<ShapeType> ( distribution ( engine ) );
        const QPoint base_point ( begining_x, begining_y );
        current_shape.resetShape ( next_shape, base_point );
    }

    current_shape.yChanging ( 1 );
    removeFilledRows();
    update();
}

void MainWindow::drawFreezingCells ( QPainter& painter )
{
    painter.save();
    const QColor painter_color ( Qt::red );
    const QBrush painter_brush ( painter_color );
    painter.setBrush ( painter_brush );

    for ( auto& vertex : freezing_cells ) {
        const auto x = vertex.x() * side_size + delta_x;
        const auto y = vertex.y() * side_size + delta_y;

        const QRect drawing_rect ( x, y, side_size, side_size );
        painter.drawRect ( drawing_rect );
    }

    painter.restore();
}


void MainWindow::addToFreeze ( const TetrixShape& shape )
{
    for ( auto& vertex : shape.shapePoints() ) {
        freezing_cells.push_back ( vertex );
    }
}



void MainWindow::paintEvent ( QPaintEvent * event )
{
    QPainter painter ( this );
    drawField ( painter );
    drawFieldGrid ( painter );
    drawShape ( painter, current_shape );
    drawFreezingCells ( painter );
}

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
    auto pressed_key = event->key();
    switch ( pressed_key ) {
    case Qt::Key_Left:
        if ( !leftBoundCondition() ) {
            current_shape.xChanging ( -1 );
        }
        break;
    case Qt::Key_Right:
        if ( !rightBoundCondition() ) {
            current_shape.xChanging ( 1 );
        }
        break;
    case Qt::Key_Space:
        if ( !leftBoundCondition() || !rightBoundCondition() ) {
            current_shape.rotate();
        }
        if ( !collisionCondition() || !lowBoundCondition() ) {
            current_shape.reverse_rotate();
        }
        break;
    }
    update();
}

bool MainWindow::leftBoundCondition()
{
    for ( auto& vertex : current_shape.shapePoints() ) {
        if ( vertex.x() - 1 < 0 ) {
            return true;
        }

        for ( auto& freezing_vertex : freezing_cells ) {
            if ( vertex.y() == freezing_vertex.y() && vertex.x() - 1 == freezing_vertex.x() ) {
                return true;
            }
        }
    }

    return false;
}

bool MainWindow::rightBoundCondition()
{
    for ( auto& vertex : current_shape.shapePoints() ) {
        if ( vertex.x() + 1 > column_count - 1 ) {
            return true;
        }

        for ( auto& freezing_vertex : freezing_cells ) {
            if ( vertex.y() == freezing_vertex.y() && vertex.x() + 1 == freezing_vertex.x() ) {
                return true;
            }
        }
    }

    return false;
}



void MainWindow::drawInfo ( QPainter& painter )
{

}

void MainWindow::drawShape ( QPainter& painter, const TetrixShape& shape )
{
    painter.save();
    const QColor painter_color ( Qt::red );
    const QBrush painter_brush ( painter_color );
    painter.setBrush ( painter_brush );

    for ( auto& vertex : shape.shapePoints() ) {
        const auto x = vertex.x() * side_size + delta_x;
        const auto y = vertex.y() * side_size + delta_y;

        const QRect drawing_rect ( x, y, side_size, side_size );
        painter.drawRect ( drawing_rect );
    }

    painter.restore();
}


void MainWindow::drawFieldGrid ( QPainter& painter )
{
    // Draw horizontal lines
    for ( auto i = 0; i < row_count; i++ ) {
        const QPoint left_point ( delta_x, i * side_size + delta_y );
        const QPoint right_point ( delta_x + column_count * side_size, i * side_size + delta_y );
        painter.drawLine ( left_point, right_point );
    }

    // Draw vertical lines
    for ( auto i = 0; i < column_count; i++ ) {
        const QPoint up_point ( delta_x + i * side_size, delta_y );
        const QPoint down_point ( delta_x + i * side_size, delta_y + side_size * row_count );
        painter.drawLine ( up_point, down_point );
    }
}


void MainWindow::drawField ( QPainter& painter )
{
    // Side of the quad in field at px
    const auto side_size = 25;

    const auto delta_x = 30;
    const auto delta_y = 30;

    QPoint up_left ( 0 + delta_x, 0 + delta_y );
    QPoint up_right ( 0 + delta_x + side_size * column_count, 0 + delta_y );
    QPoint down_left ( 0 + delta_x, side_size * row_count + delta_y );
    QPoint down_right ( 0 + delta_x + side_size * column_count, side_size * row_count + delta_y );

    painter.drawLine ( up_left,    up_right );
    painter.drawLine ( up_left,    down_left );
    painter.drawLine ( down_left,  down_right );
    painter.drawLine ( down_right, up_right );
}



