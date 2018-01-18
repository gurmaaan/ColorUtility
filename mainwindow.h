#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef LEFT_TITLE
#define LEFT_TITLE "Левая область"
#endif

#ifndef RIGHT_TITLE
#define RIGHT_TITLE "Правая область"
#endif

#ifndef BG_TITLE
#define BG_TITLE "Фон"
#endif

#include <QScreen>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void genGraphics();

    void clearGroup(QGraphicsItemGroup *group);
    void repaintBgGroup(const QColor &color);
    void repaintRightGroup(const QColor &color);
    void repaintLeftGroup(const QColor &color);

private slots:
    void on_combination_slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    void calculateSize();
    void initUI();

    int _lAreaW = 0, _lAreaH = 0,
        _rAreaW = 0, _rAreaH = 0;
    int _combW;

    QGraphicsScene *scene;
    QGraphicsItemGroup *groupLeft;
    QGraphicsItemGroup *groupRight;
    QGraphicsItemGroup *groupBG;
};

#endif // MAINWINDOW_H
