#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    calculateSize();
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_left_color_picker_clicked()
{
    QColorDialog::getColor(Qt::gray, this);
}

void MainWindow::calculateSize()
{
    const int screen_w = QApplication::desktop()->width();
    const int sw = qApp->screens().at(0)->geometry().width();
    const int screen_h = QApplication::desktop()->height();
    const int sh = qApp->screens().at(0)->geometry().height();

    ui->screen_w_spin->setMaximum(screen_w);
    ui->screen_w_spin->setValue(sw);
    ui->screen_h_spin->setMaximum(screen_h);
    ui->screen_h_spin->setValue(sh);

    _lAreaH = sh / 4; _rAreaH = sh / 4;
    _lAreaW = sw / 4; _rAreaW = sw / 4;
    _combW = _lAreaW + _rAreaW;

    ui->left_h_spin->setMaximum(_lAreaH);
    ui->left_h_spin->setValue(_lAreaH);

    ui->right_h_spin->setMaximum(_rAreaH);
    ui->right_h_spin->setValue(_rAreaH);

    ui->left_w_spin->setMaximum(_lAreaW);
    ui->left_w_spin->setValue(_lAreaW);

    ui->right_w_spin->setMaximum(_rAreaW);
    ui->right_w_spin->setValue(_rAreaW);

    int curStep = ui->combination_slider->tickInterval();
    int n = ui->combination_slider->maximum() / curStep;

    ui->combination_slider->setMaximum(_combW);
    int newMax = ui->combination_slider->maximum();
    ui->combination_slider->setTickInterval( newMax / n);
    ui->combination_spin->setMaximum(_combW);
    ui->combination_max->setText( QString::number(newMax) );
}

void MainWindow::initUI()
{
    ui->left_area_widget->setTitle(LEFT_TITLE);
    ui->right_area_widget->setTitle(RIGHT_TITLE);
    ui->bg_area_widget->setTitle(BG_TITLE);
}
