#include "BasicColor.h"

BasicColor::BasicColor(QWidget* parent, double first, double second, double third)
    : QWidget(parent), first(first), second(second), third(third)
{
    layout = new QVBoxLayout(this);
    QHBoxLayout* fLayout = new QHBoxLayout(this);
    QHBoxLayout* sLayout = new QHBoxLayout(this);
    QHBoxLayout* tLayout = new QHBoxLayout(this);
    fLabel = new QLabel("R: ", this);
    sLabel = new QLabel("G: ", this);
    tLabel = new QLabel("B: ", this);

    f = new QDoubleSpinBox(this);
    s = new QDoubleSpinBox(this);
    t = new QDoubleSpinBox(this);
    blockSignals(true);
    f->setValue(first);
    s->setValue(second);
    t->setValue(third);
    blockSignals(false);
    //connect(f, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
    //        ,this, editedF());
    connect(f, SIGNAL(valueChanged(double)), this, SLOT(editedF(double)));
    connect(s, SIGNAL(valueChanged(double)), this, SLOT(editedS(double)));
    connect(t, SIGNAL(valueChanged(double)), this, SLOT(editedT(double)));
    //connect(t, &QDoubleSpinBox::valueChanged, this, &BasicColor::editedT);
    fLayout->addWidget(fLabel);
    fLayout->addWidget(f);
    sLayout->addWidget(sLabel);
    sLayout->addWidget(s);
    tLayout->addWidget(tLabel);
    tLayout->addWidget(t);
    layout->addLayout(fLayout);
    layout->addLayout(sLayout);
    layout->addLayout(tLayout);

    trans = { {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
             {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'a'},
             {11, 'b'}, {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'} };
}

void BasicColor::blockSignals(bool b)
{
    f->blockSignals(b);
    s->blockSignals(b);
    t->blockSignals(b);
}

BasicColor::~BasicColor() {}

BasicColor& BasicColor::operator=(const BasicColor& op)
{
    first = op.first;
    second = op.second;
    third = op.third;
    fLabel->setText((op.fLabel)->text());
    sLabel->setText((op.sLabel)->text());
    tLabel->setText((op.tLabel)->text());
    blockSignals(true);
    f->setValue(op.first);
    s->setValue(op.second);
    t->setValue(op.third);
    blockSignals(false);

    return *this;
}

void BasicColor::editedS(double)
{
    double temp = s->value();
    if (temp == second)
    {
        return;
    }

    second = temp;
    emit edited();
}

void BasicColor::editedT(double)
{
    double temp = t->value();
    if (temp == third)
    {
        return;
    }

    third = temp;
    emit edited();
}

void BasicColor::editedF(double)
{
    double temp = f->value();
    if (f->value() == first)
    {
        return;
    }

    first = temp;
    emit edited();
}
