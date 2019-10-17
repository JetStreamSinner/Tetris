#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <random>

#include "TetrixShape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    using CellsMatrix = QVector<QPoint>;

    QTimer timer;
    TetrixShape current_shape;
    CellsMatrix freezing_cells;
    
    // Random stuff
    std::random_device device;
    std::default_random_engine engine;
    
    // Row/Column count at playing field
    static const auto row_count = 20;
    static const auto column_count = 10;

    static const auto begining_x = column_count / 2;
    static const auto begining_y = 1;

    // Size of cell side at playing field
    static const auto side_size = 25;

    // Margin from window bounds
    static const auto delta_x = 30;
    static const auto delta_y = 30;


    // Draw field bounds
    void drawField ( QPainter& painter );

    // Draw field grid
    void drawFieldGrid ( QPainter& painter );

    void drawShape ( QPainter& painter, const TetrixShape& shape );

    void drawInfo ( QPainter&  painter );

    void drawFreezingCells ( QPainter& painter );

    void addToFreeze ( const TetrixShape& shape );
    
    bool freezeCondition();
    bool rightBoundCondition();
    bool leftBoundCondition();
    void removeFilledRows();

private slots:
    // Update gaming state
    void updateState();

public:
    explicit MainWindow ( const int min_width, const int min_height, QMainWindow * parent = nullptr );

    void paintEvent ( QPaintEvent * event ) override;
    void keyPressEvent (QKeyEvent * event) override;
};


#endif
