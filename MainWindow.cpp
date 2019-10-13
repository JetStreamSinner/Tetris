#include <QPainter>
#include "MainWindow.h"


MainWindow::MainWindow ( const int min_width, const int min_height, QMainWindow * parent )
{
    setFixedSize ( min_width, min_height );
}

void MainWindow::paintEvent ( QPaintEvent * event )
{
    QPainter painter ( this );
    drawField ( painter );
    drawFieldGrid ( painter );
}

void MainWindow::drawInfo ( QPainter& painter )
{
    
}

void MainWindow::drawFieldGrid ( QPainter& painter )
{
    // Draw horizontal lines
    for ( auto i = 0; i < row_count; i++ ) {
        const QPoint left_point(delta_x, i * side_size + delta_y);
        const QPoint right_point(delta_x + column_count * side_size, i * side_size + delta_y);
        painter.drawLine(left_point, right_point);
    }

    // Draw vertical lines
    for ( auto i = 0; i < column_count; i++ ) {
        const QPoint up_point(delta_x + i * side_size, delta_y);
        const QPoint down_point(delta_x + i * side_size, delta_y + side_size * row_count);
        painter.drawLine(up_point, down_point);
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



