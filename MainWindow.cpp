#include <QPainter>
#include "MainWindow.h"


MainWindow::MainWindow(const int min_width, const int min_height, QMainWindow * parent)
{
    setFixedSize(min_width, min_height);
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    drawField(painter);
}

void MainWindow::drawInfo(QPainter& painter)
{
    
}


void MainWindow::drawField(QPainter& painter)
{
    // Side of the quad in field at px 
    const auto side_size = 25;
    
    const auto delta_x = 30;
    const auto delta_y = 30;
    
    QPoint up_left(0 + delta_x, 0 + delta_y);
    QPoint up_right(0 + delta_x + side_size * row_count, 0 + delta_y);
    QPoint down_left(0 + delta_x, height() - delta_y);
    QPoint down_right(0 + delta_x + side_size * row_count, height() - delta_y);
    
    painter.drawLine(up_left,    up_right);
    painter.drawLine(up_left,    down_left);
    painter.drawLine(down_left,  down_right);
    painter.drawLine(down_right, up_right);
    
}



