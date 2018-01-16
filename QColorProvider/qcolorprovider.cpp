#include "qcolorprovider.h"
#include "ui_qcolorprovider.h"
#include <QDebug>

//------------Constants------------//

#ifndef INITIAL_CLR
#define INITIAL_CLR 127
#endif

#ifndef TITLE_DEFAULT
#define TITLE_DEFAULT "Color Widget"
#endif

//--------------------------------//

QColorProvider::QColorProvider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QColorProvider)
{
    ui->setupUi(this);

    //Defaults
    _color.setRgb(INITIAL_CLR, INITIAL_CLR, INITIAL_CLR);
    _title = TITLE_DEFAULT;
    _checkable = false;
    setTitle(_title);

    connect(this, &QColorProvider::colorUpdated, this, &QColorProvider::synch);
}

QColorProvider::~QColorProvider()
{
    delete ui;
}

void QColorProvider::on_r_slider_sliderMoved(int position)
{
    _color.setRed(position);
    emit colorUpdated();
}

void QColorProvider::on_r_spin_valueChanged(int arg1)
{
    _color.setRed(arg1);
    emit colorUpdated();
}

void QColorProvider::on_g_slider_sliderMoved(int position)
{
    _color.setGreen(position);
    emit colorUpdated();
}

void QColorProvider::on_g_spin_valueChanged(int arg1)
{
    _color.setGreen(arg1);
    emit colorUpdated();
}

void QColorProvider::on_b_slider_sliderMoved(int position)
{
    _color.setBlue(position);
    emit colorUpdated();
}

void QColorProvider::on_b_spin_valueChanged(int arg1)
{
    _color.setBlue(arg1);
    emit colorUpdated();
}

void QColorProvider::on_random_btn_clicked()
{
    int red_rand = qrand() % 256,
        green_rand = qrand() % 256,
        blue_rand = qrand() % 256;

    _color.setRgb(red_rand, green_rand, blue_rand);
    emit colorUpdated();
}

void QColorProvider::on_color_pickr_btn_clicked()
{

}

void QColorProvider::synch()
{
    int r = _color.red();
    int g = _color.green();
    int b = _color.blue();

    if (r != ui->r_slider->value())
        ui->r_spin->setValue(r);
    if (g != ui->g_slider->value())
        ui->g_spin->setValue(g);
    if (b != ui->b_slider->value())
        ui->b_spin->setValue(b);

    updateMirrorView(r, g, b);
}

void QColorProvider::updateMirrorView(int r,int g,int b)
{
    QString style = "background-color: rgb(" + QString::number(r) + ","
            + QString::number(g) + "," + QString::number(b) + ");";

    //qDebug() << style;

    ui->mirror_label->setStyleSheet(style);
}

int QColorProvider::getStep(int index)
{
    int step;
    switch (index) {
    case 0:
        step = 1;
        break;
    case 1:
        step = 3;
        break;
    case 2:
        step = 5;
        break;
    case 3:
        step = 10;
        break;
    }

    qDebug() << "Index - " << index << "; Step - " << step << ";";
    return step;
}

bool QColorProvider::clickable() const
{
    return _checkable;
}

void QColorProvider::setCheckable(bool checkable)
{
    _checkable = checkable;
   ui->Box->setCheckable(_checkable);
}

QString QColorProvider::title() const
{
    return _title;
}

void QColorProvider::setTitle(const QString &title)
{
    _title = title;
    ui->Box->setTitle(_title);
}

QColor QColorProvider::color() const
{
    return _color;
}


//TODO Fix single-step customizing
void QColorProvider::on_r_step_combo_activated(int index)
{
    ui->r_slider->setSingleStep( getStep(index) );
    ui->r_spin->setSingleStep( getStep(index) );
    qDebug() << ui->r_slider->singleStep();
}

void QColorProvider::on_g_step_combo_activated(int index)
{
    ui->g_slider->setSingleStep( getStep(index) );
    ui->g_spin->setSingleStep( getStep(index) ) ;
    qDebug() << ui->g_slider->singleStep();
}

void QColorProvider::on_b_step_combo_activated(int index)
{
    ui->b_slider->setSingleStep( getStep(index) );
    ui->b_spin->setSingleStep( getStep(index) );
    qDebug() << ui->b_slider->singleStep();
}
