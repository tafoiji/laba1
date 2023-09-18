#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Laba1Gui.h"
#include <QColorDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "colours.h"
#include "Hex.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Laba1Gui; };
QT_END_NAMESPACE

class Laba1Gui : public QMainWindow
{
    Q_OBJECT

public:
    Laba1Gui(QWidget *parent = nullptr);
    ~Laba1Gui();

private:
    Ui::Laba1Gui *ui;
    QLineEdit* hex;
    QComboBox* comboBox;
    QVBoxLayout* layout;
    RGB* rgb;
    CMYK* cmyk;
    XYZ* xyz;
    Lab* lab;
    HSV* hsv;
    HSL* hsl;
protected:
    void paintEvent(QPaintEvent* e)override;
public slots:
    void openColorDialog();
    void changeNow();
    void changeCurrent(int);
    void changeColors(BasicColor*);
};
