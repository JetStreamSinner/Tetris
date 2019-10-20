#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <random>
#include <QDir>
#include <QMediaPlayer>

#include "TetrixShape.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    using CellsMatrix = QVector<QPoint>;

    QMediaPlayer * player;
    QTimer timer;
    TetrixShape current_shape;
    CellsMatrix freezing_cells;
    ShapeType next_shape_type;
    int score_count = 0;
    int game_speed = 300;
    
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

    void initMediaPlayer();
    void initTimer();
    void initWindow();

    // Draw field bounds
    void drawField ( QPainter& painter );
    // Draw field grid
    void drawFieldGrid ( QPainter& painter );
    void drawShape ( QPainter& painter, const TetrixShape& shape );
    void drawInfo ( QPainter&  painter );
    void drawFreezingCells ( QPainter& painter );
    void addToFreeze ( const TetrixShape& shape );
    void resetGameField();
    ShapeType generateNextShapeType();
    
    bool freezeCondition();
    bool collisionCondition();
    bool rightBoundCondition();
    bool leftBoundCondition();
    bool lowBoundCondition();
    bool checkLossCondition();
    void removeFilledRows();

private slots:
    // Update gaming state
    void updateState();
    void updateMedia();

public:
    explicit MainWindow ( const int min_width, const int min_height, QMainWindow * parent = nullptr );

    void paintEvent ( QPaintEvent * event ) override;
    void keyPressEvent (QKeyEvent * event) override;
};

static QString tetrisBackgroundImagePath()
{
    return QDir::toNativeSeparators("/home/alex/Projects/Tetris/Images/tetris_background_img.png");
}

static QString tetrisBlockImagePath()
{
    return QDir::toNativeSeparators("/home/alex/Projects/Tetris/Images/tetris_block_img.png");
}

static QString applicationBackgroundImagePath()
{
    return QDir::toNativeSeparators("/home/alex/Projects/Tetris/Images/application_background.png");  
}

static QImage tetrisBlockImage()
{
    return QImage(tetrisBlockImagePath());
}

static QImage tetrisBackgroundImage()
{
    return QImage(tetrisBackgroundImagePath());
}

static QString tetrisMainThemeSoundPath()
{
    return QDir::toNativeSeparators("/home/alex/Projects/Tetris/Sound/main_sound.mp3");
}



#endif
