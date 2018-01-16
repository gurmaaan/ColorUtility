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

#include <QColorDialog>
#include <QScreen>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QDebug>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_left_color_picker_clicked();

private:
    Ui::MainWindow *ui;
    void calculateSize();
    void initUI();

    int _lAreaW = 0, _lAreaH = 0,
        _rAreaW = 0, _rAreaH = 0;
    int _combW;
};

#endif // MAINWINDOW_H
