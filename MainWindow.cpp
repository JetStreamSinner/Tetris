#include <QPainter>
#include "MainWindow.h"


MainWindow::MainWindow ( const int min_width, const int min_height, QMainWindow * parent ) : QMainWindow(parent)
{
    const auto timeout_time = 200;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateStates()));
    timer.start(timeout_time);
    
    current_shape.setCoordinate(default_x, default_y);
    current_shape.setType(FigureType::I_type);
    
    setFixedSize(min_width, min_height);
    
}

void MainWindow::updateStates ( )
{
    auto checkCollision = [&]()
    {
        const auto x = current_shape.coord().x();
        const auto y = current_shape.coord().y() + 1;
        for (auto& shape : fixed_shapes)
        {
            if (shape.coord().x() == x && shape.coord().y() == y)
            {
                return true;
            }
        }
        return false;
    };
    
    // If current shape reached end of game field or other shape than fixed her
    if (current_shape.coord().y() == row_count - 1 || checkCollision())
    {
        fixed_shapes.append(current_shape);
        current_shape.setCoordinate(default_x, default_y);
    }
    else
    {
        const auto next_x = current_shape.coord().x();
        const auto next_y = current_shape.coord().y() + 1;
        current_shape.setCoordinate(next_x, next_y);
    }
    update();
}

void MainWindow::drawShape ( QPainter& painter, Shape& shape )
{
    const auto x = shape.coord().x() * side_size + delta_x;
    const auto y = shape.coord().y() * side_size + delta_y;
    
    const auto rect_width  = side_size;
    const auto rect_height = side_size;
    
    QBrush brush(Qt::red);
    painter.setBrush(brush);
    
    painter.drawRect(x, y, rect_width, rect_height);
}


void MainWindow::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);
    
    drawField(painter);
    drawInfo (painter);
    drawShape(painter, current_shape);
    drawFixedShapes(painter);
    drawGrid(painter);
}



void MainWindow::drawInfo ( QPainter& painter )
{
    /* Function draw information about scores count at screen */
    const auto x = delta_x + row_count * side_size + delta_x;
    const auto y = delta_y;
    const auto rect_width  = 200;
    const auto rect_height = 50;
    QRect drawing_rect(x, y, rect_width, rect_height);
    
    const auto point_size = 18;
    QFont font = painter.font();
    font.setPointSize(point_size);
    painter.setFont(font);
    
    QTextOption option = QTextOption(Qt::AlignHCenter);
    
    painter.drawText(drawing_rect, "Scores", option);
}

void MainWindow::drawFixedShapes ( QPainter& painter )
{
    for (auto& shape : fixed_shapes)
    {
        drawShape(painter, shape);
    }
}


void MainWindow::drawField ( QPainter& painter )
{
    /* Draw game field border at screen */
                      /* x coordinate */                   /* y coordinate */
    const QPoint up_left   (0 + delta_x,                            0 + delta_y);
    const QPoint up_right  (0 + delta_x + side_size * column_count, 0 + delta_y);
    const QPoint down_left (0 + delta_x,                            side_size * row_count + delta_y);
    const QPoint down_right(0 + delta_x + side_size * column_count, side_size * row_count + delta_y);
    
    painter.drawLine(up_left,    up_right);
    painter.drawLine(up_left,    down_left);
    painter.drawLine(down_left,  down_right);
    painter.drawLine(down_right, up_right);
    
}

void MainWindow::drawGrid ( QPainter& painter )
{
    /* Draw game field grid at screen */
    
    // Vertical
    
    for (auto i = 1; i < column_count; i++)
    {
        const QPoint up  (delta_x + i * side_size, delta_y);
        const QPoint down(delta_x + i * side_size, side_size * row_count + delta_y);
        
        painter.drawLine(up, down);
    }
    
    // Horizontal
    
    for (auto i = 1; i < row_count; i++)
    {
        const QPoint left (delta_x,                         i * side_size + delta_y);
        const QPoint right(side_size * column_count + delta_x, i * side_size + delta_y);
        
        painter.drawLine(left, right);
    }
}

void MainWindow::keyPressEvent ( QKeyEvent* event )
{
    const auto pressed_key = event->key();
    const auto shape_coords = current_shape.coord();
    auto current_shape_x = shape_coords.x();

    switch (pressed_key)
    {
        case Qt::Key_Left:
            current_shape_x = current_shape_x - 1 < 0 ? current_shape_x : current_shape_x - 1;
            current_shape.setCoordinate(current_shape_x, shape_coords.y());
            break;
        case Qt::Key_Right:
            current_shape_x = current_shape_x + 1 > column_count - 1 ? current_shape_x : current_shape_x + 1;
            current_shape.setCoordinate(current_shape_x, shape_coords.y());
            break;
        case Qt::Key_Down:
            break;
    }
}


