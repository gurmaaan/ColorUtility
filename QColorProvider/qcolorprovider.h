#ifndef QCOLORPROVIDER_H
#define QCOLORPROVIDER_H

#include <QWidget>
#include <QColor>
#include <QDebug>
#include <QColorDialog>

namespace Ui {
class QColorProvider;
}

class QColorProvider : public QWidget
{
    Q_OBJECT

public:
    explicit QColorProvider(QWidget *parent = 0);
    ~QColorProvider();

    QColor color() const;

    QString title() const;
    void setTitle(const QString &title);

    bool checkable() const;
    void setCheckable(bool checkable);

private slots:
    void on_r_slider_sliderMoved(int position);
    void on_r_spin_valueChanged(int arg1);
    void on_g_slider_sliderMoved(int position);
    void on_g_spin_valueChanged(int arg1);
    void on_b_slider_sliderMoved(int position);
    void on_b_spin_valueChanged(int arg1);

    void on_r_step_combo_activated(int index);
    void on_g_step_combo_activated(int index);
    void on_b_step_combo_activated(int index);

    void on_random_btn_clicked();
    void on_color_pickr_btn_clicked();

    void synch();

signals:
    void colorUpdated(const QColor &newColor);

private:
    Ui::QColorProvider *ui;

    QString _title;
    QColor _color;
    bool _checkable;

    void updateMirrorView(int r, int g, int b);
    int getStep(int index);
};

#endif // QCOLORPROVIDER_H
