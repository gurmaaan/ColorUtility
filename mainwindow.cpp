#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    QObject::connect(ui->bg_area_widget, SIGNAL(colorUpdated(QColor)), this, SLOT(repaintBgGroup(QColor)));
    QObject::connect(ui->right_area_widget, SIGNAL(colorUpdated(QColor)), this, SLOT(repaintRightGroup(QColor)));
    QObject::connect(ui->left_area_widget, SIGNAL(colorUpdated(QColor)), this, SLOT(repaintLeftGroup(QColor)));

    calculateSize();
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genGraphics()
{
    int gw = ui->graphicsView->width(),
        gh = ui->graphicsView->height();

    scene->setSceneRect(0, 0, gw, gh);

    repaintBgGroup(ui->bg_area_widget->color());
    groupBG->setZValue(0);

    repaintLeftGroup(ui->left_area_widget->color());
    groupLeft->setZValue(1);

    repaintRightGroup(ui->right_area_widget->color());
    groupRight->setZValue(1);
}

void MainWindow::clearGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void MainWindow::repaintBgGroup(const QColor &color)
{
    clearGroup(groupBG);

    QPen penBg(color);
    int gw = scene->width(),
        gh = scene->height();

    for (int i = 0; i < gh; i++)
    {
        groupBG->addToGroup(scene->addLine(0, i, gw, i, penBg));
    }
}

void MainWindow::repaintRightGroup(const QColor &color)
{
    //qDebug() << "Right";
    clearGroup(groupRight);
    int sw = scene->width(),
        sh = scene->height();

    int comb = ui->combination_slider->value();

    QPen penR(color);

    for (int i = 0; i < _rAreaH; i++)
    {
        if(!(i%2))
        {
            int x1 = sw/2 - comb / 2; // середина сцены - пол области объединения
            int y1 = ((sh - _rAreaH) / 2) + i; //высота сцены - выцсота области пополам - первая координата х
            int x2 = sw/2 + _rAreaW;
            int y2 = y1;
            groupRight->addToGroup(scene->addLine(x1, y1, x2, y2, penR));
        }
    }
}

void MainWindow::repaintLeftGroup(const QColor &color)
{
    //qDebug() << "Left";
    clearGroup(groupLeft);
    int sw = scene->width(),
        sh = scene->height();

    int comb = ui->combination_slider->value();

    QPen penL(color);
    for (int i = 0; i < ui->left_h_spin->value(); i++)
    {
        if (i % 2)
        {
            int x1 = sw/2  - _lAreaW; // середина сцены - пол области объединения
            int y1 = ((sh - _rAreaH) / 2) + i; //высота сцены - выцсота области пополам - первая координата х
            int x2 = sw/2 + comb /2;
            int y2 = y1;
            groupLeft->addToGroup(scene->addLine(x1, y1, x2, y2, penL));
        }
    }
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

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->graphicsView->setMinimumHeight( ui->right_h_spin->value() );
    ui->graphicsView->setMinimumWidth( ui->right_w_spin->value() + ui->left_w_spin->value() );

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    groupLeft = new QGraphicsItemGroup();
    groupRight = new QGraphicsItemGroup();
    groupBG = new QGraphicsItemGroup();

    scene->addItem(groupLeft);
    scene->addItem(groupRight);
    scene->addItem(groupBG);

    QTimer::singleShot(50, this, &genGraphics);
}

void MainWindow::on_combination_slider_sliderMoved(int position)
{
    repaintBgGroup(ui->bg_area_widget->color());
    repaintLeftGroup(ui->left_area_widget->color());
    repaintRightGroup(ui->right_area_widget->color());
}
