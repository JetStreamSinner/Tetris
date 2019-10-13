#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
private:
    static const auto row_count    = 20;
    static const auto column_count = 10;
    static const auto side_size    = 25;
    static const auto delta_x      = 30;
    static const auto delta_y      = 30;

    
    // Draw field bounds
    void drawField ( QPainter& painter );
    void drawFieldGrid ( QPainter& painter );
    
    void drawInfo ( QPainter&  painter );

public:
    MainWindow ( const int min_width, const int min_height, QMainWindow * parent = nullptr );

    void paintEvent ( QPaintEvent * event );
};


#endif
