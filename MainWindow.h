#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include "Shape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    using ShapesList = QVector<Shape>;
    
    QTimer timer;
    ShapesList fixed_shapes;
    Shape current_shape;
    
    static const auto row_count = 20;
    static const auto column_count = 10;
    static const auto side_size = 25;
    static const auto delta_x = 30;
    static const auto delta_y = 30;
    static const auto default_x = column_count / 2;
    static const auto default_y = 1;
    
    void drawField ( QPainter& painter );
    void drawInfo ( QPainter& painter );
    void drawShape ( QPainter& painter, Shape& shape );
    void drawFixedShapes ( QPainter& painter );
    void drawGrid ( QPainter& painter );
    
    
private slots:
    void updateStates ( );
    
public:
    MainWindow ( const int min_width, const int min_height, QMainWindow * parent = nullptr );
    
    void paintEvent ( QPaintEvent * event ) override;
    void keyPressEvent ( QKeyEvent * event ) override;
};


#endif
