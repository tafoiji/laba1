#ifndef BASICCOLOR_H
#define BASICCOLOR_H

#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "QDoubleSpinBox"
#include <QSlider>
#include <QDebug>

class BasicColor : public QWidget
{
    Q_OBJECT
protected:
    friend class Hex;

    void blockSignals(bool b);

    double first;
    double second;
    double third;

    std::map<int, QChar> trans;

    virtual QString toHex() = 0;

    QDoubleSpinBox* f;
    QDoubleSpinBox* s;
    QDoubleSpinBox* t;
    QSlider* fSlider;
    QSlider* sSlider;
    QSlider* tSlider;
    QLabel* fLabel;
    QLabel* sLabel;
    QLabel* tLabel;
    QVBoxLayout* layout;
public:
    BasicColor(QWidget* parent = nullptr, double first = 0., double second = 0., double third = 0.);
    virtual ~BasicColor();

    BasicColor& operator=(const BasicColor& op);
public slots:
    void editedF(double);
    void editedS(double);
    void editedT(double);

    void editedFS(int);
    void editedSS(int);
    void editedTS(int);
signals:
    void edited();
};

#endif
