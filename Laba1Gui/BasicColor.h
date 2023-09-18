#ifndef BASICCOLOR_H
#define BASICCOLOR_H

#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class BasicColor : public QWidget
{
    Q_OBJECT
protected:
    friend class Hex;

    double first;
    double second;
    double third;

    std::map<int, QChar> trans;

    virtual QString toHex() = 0;

    QLineEdit* f;
    QLineEdit* s;
    QLineEdit* t;
    QLabel* fLabel;
    QLabel* sLabel;
    QLabel* tLabel;
    QVBoxLayout* layout;
public:
    BasicColor(QWidget* parent = nullptr, double first = 0., double second = 0., double third = 0.);
    virtual ~BasicColor();

    BasicColor& operator=(const BasicColor& op);
public slots:
    void editedF();
    void editedS();
    void editedT();
signals:
    void edited();
};

#endif
