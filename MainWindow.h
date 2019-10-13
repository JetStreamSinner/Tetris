#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // Row/Column count at playing field
    static const auto row_count    = 20;
    static const auto column_count = 10;

    // Size of cell side at playing field
    static const auto side_size    = 25;

    // Margin from window bounds
    static const auto delta_x      = 30;
    static const auto delta_y      = 30;


    // Draw field bounds
    void drawField ( QPainter& painter );

    // Draw field grid
    void drawFieldGrid ( QPainter& painter );

    void drawInfo ( QPainter&  painter );

public:
    explicit MainWindow ( const int min_width, const int min_height, QMainWindow * parent = nullptr );

    void paintEvent ( QPaintEvent * event ) override;
};


#endif
