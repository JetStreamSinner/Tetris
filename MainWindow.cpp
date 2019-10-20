#include <QPainter>
#include <algorithm>
#include <QDebug>
#include <QUrl>
#include <QMessageBox>
#include "MainWindow.h"

MainWindow::MainWindow ( const int min_width, const int min_height, QMainWindow * parent ) : QMainWindow ( parent ),
    current_shape ( ShapeType::t_type, QPoint ( begining_x, begining_y ) ), engine ( device() )
{
    next_shape_type = generateNextShapeType();
    setFixedSize ( min_width, min_height );
    initMediaPlayer();
    initTimer();
    initWindow();
}

void MainWindow::initMediaPlayer()
{
    player = new QMediaPlayer;
    player->setMedia ( QUrl::fromLocalFile ( tetrisMainThemeSoundPath() ) );
    player->setVolume ( 50 );
    player->play();
    connect ( player, SIGNAL ( mediaStatusChanged ( QMediaPlayer::MediaStatus ) ), this, SLOT ( updateMedia() ) );
}

void MainWindow::initTimer()
{
    const auto update_time = game_speed;
    connect ( &timer, SIGNAL ( timeout() ), this, SLOT ( updateState() ) );
    timer.start ( update_time );
}

void MainWindow::initWindow()
{
    QPixmap background_pixmap ( applicationBackgroundImagePath() );
    background_pixmap = background_pixmap.scaled ( size(), Qt::IgnoreAspectRatio );
    QPalette pal = palette();
    pal.setBrush ( QPalette::Background, background_pixmap );
    setPalette ( pal );
}

void MainWindow::updateMedia()
{
    player->play();
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

bool MainWindow::checkLossCondition()
{
    for ( auto& vertex : freezing_cells )
    {
        if (vertex.y() == begining_y)
        {
            return false;
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
            
            // Increment score count
            score_count += 10;
            
            // Speed up game
            game_speed -= 5;
            timer.setInterval(game_speed);
            
        }
    }

}

void MainWindow::resetGameField()
{
    // Clear freezing cells
    freezing_cells.clear();
    
    // Reset shape
    auto shape_type = generateNextShapeType();
    next_shape_type = generateNextShapeType();
    current_shape.resetShape( shape_type, QPoint( begining_x, begining_y ));
    
    // Reset timer
    game_speed = 300;
    timer.setInterval(game_speed);
    
    // Reset scores
    score_count = 0;
    
    // Reset player
    player->setPosition(0);
    player->play();
}


ShapeType MainWindow::generateNextShapeType()
{
    // And reset by input new random shape type and default coordinates
    const auto low_bound = 0;
    const auto up_bound = 6;
    std::uniform_int_distribution<int> distribution ( low_bound, up_bound );
    auto next_type = static_cast<ShapeType> ( distribution ( engine ) );
    return next_type;
}

void MainWindow::updateState()
{
    // If shape was derrive to other shape or low bound of field
    if ( freezeCondition() ) {
        // Freeze her
        addToFreeze ( current_shape );
        
        if ( !checkLossCondition() )
        {
            QMessageBox::information(this, "You lost", "Press any key to restart");
            resetGameField();
            return;
        }
        
        const QPoint base_point ( begining_x, begining_y );
        
        current_shape.resetShape ( next_shape_type, base_point );
        next_shape_type = generateNextShapeType();
    }

    current_shape.yChanging ( 1 );
    removeFilledRows();
    update();
}

void MainWindow::drawFreezingCells ( QPainter& painter )
{
    QImage tetris_block_image ( tetrisBlockImage() );

    for ( auto& vertex : freezing_cells ) {
        const auto x = vertex.x() * side_size + delta_x;
        const auto y = vertex.y() * side_size + delta_y;

        const QRect drawing_rect ( x, y, side_size, side_size );
        painter.drawImage ( drawing_rect, tetris_block_image );
    }

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
    drawInfo ( painter );
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
    const auto width_offset = delta_x + side_size * column_count;
    const auto height_offset = delta_y + side_size * row_count;


    const QColor painter_color ( Qt::blue );
    const QBrush painter_brush ( painter_color );
    painter.setBrush ( painter_brush );

    const auto font_size = 13;
    QFont font = painter.font();
    font.setPointSize ( font_size );

    const auto information_tables_offset = 50;

    const auto score_table_width = 200;
    const auto score_table_height = 50;
    QRect score_panel ( width_offset + information_tables_offset, delta_y, score_table_width, score_table_height );
    painter.drawText ( score_panel, QString("Score count: %0 ").arg(score_count) );

    const auto drawing_x = width_offset + information_tables_offset + 50;
    const auto drawing_y = delta_y + score_table_height + 50;

    painter.translate ( drawing_x, drawing_y );

    auto next_shape = TetrixShape(next_shape_type, QPoint (0, 0));

    for ( auto& vertex : next_shape.shapePoints() ) {
        QRect drawing_rect ( vertex.x() * side_size, vertex.y() * side_size, side_size, side_size );
        painter.drawImage ( drawing_rect, tetrisBlockImage() );
    }

    painter.resetTransform();
}

void MainWindow::drawShape ( QPainter& painter, const TetrixShape& shape )
{


    QImage tetris_block_image ( tetrisBlockImage() );
    for ( auto& vertex : shape.shapePoints() ) {
        const auto x = vertex.x() * side_size + delta_x;
        const auto y = vertex.y() * side_size + delta_y;

        const QRect drawing_rect ( x, y, side_size, side_size );
        painter.drawImage ( drawing_rect, tetris_block_image );
    }

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

    QRect drawing_rect ( up_left, down_right );
    painter.drawImage ( drawing_rect, tetrisBackgroundImage() );
}



