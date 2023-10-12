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
    fSlider = new QSlider(Qt::Horizontal, this);
    s = new QDoubleSpinBox(this);
    sSlider = new QSlider(Qt::Horizontal, this);
    t = new QDoubleSpinBox(this);
    tSlider = new QSlider(Qt::Horizontal, this);

    sSlider->setTickInterval(1);
    tSlider->setTickInterval(1);

    blockSignals(true);
    f->setValue(first);
    fSlider->setValue(first);
    s->setValue(second);
    sSlider->setValue(second);
    t->setValue(third);
    tSlider->setValue(third);
    blockSignals(false);
    //connect(f, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
    //        ,this, editedF());
    connect(f, SIGNAL(valueChanged(double)), this, SLOT(editedF(double)));
    connect(s, SIGNAL(valueChanged(double)), this, SLOT(editedS(double)));
    connect(t, SIGNAL(valueChanged(double)), this, SLOT(editedT(double)));
    connect(fSlider, SIGNAL(valueChanged(int)), this, SLOT(editedFS(int)));
    connect(sSlider, SIGNAL(valueChanged(int)), this, SLOT(editedSS(int)));
    connect(tSlider, SIGNAL(valueChanged(int)), this, SLOT(editedTS(int)));
    //connect(t, &QDoubleSpinBox::valueChanged, this, &BasicColor::editedT);
    fLayout->addWidget(fLabel);
    fLayout->addWidget(f);
    sLayout->addWidget(sLabel);
    sLayout->addWidget(s);
    tLayout->addWidget(tLabel);
    tLayout->addWidget(t);
    layout->addLayout(fLayout);
    layout->addWidget(fSlider);
    layout->addLayout(sLayout);
    layout->addWidget(sSlider);
    layout->addLayout(tLayout);
    layout->addWidget(tSlider);

    trans = { {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
             {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'a'},
             {11, 'b'}, {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'} };
}

void BasicColor::blockSignals(bool b)
{
    f->blockSignals(b);
    s->blockSignals(b);
    t->blockSignals(b);
    fSlider->blockSignals(b);
    sSlider->blockSignals(b);
    tSlider->blockSignals(b);
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
    fSlider->setValue(op.first);
    sSlider->setValue(op.second);
    tSlider->setValue(op.third);
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
    sSlider->blockSignals(true);
    sSlider->setValue(second);
    sSlider->blockSignals(false);
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
    tSlider->blockSignals(true);
    tSlider->setValue(third);
    tSlider->blockSignals(false);
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
    fSlider->blockSignals(true);
    fSlider->setValue(first);
    fSlider->blockSignals(false);
    emit edited();
}

void BasicColor::editedSS(int)
{
    double temp = sSlider->value();
    if (temp == second)
    {
        return;
    }

    second = temp;
    s->blockSignals(true);
    s->setValue(second);
    s->blockSignals(false);
    emit edited();
}

void BasicColor::editedTS(int)
{
    double temp = tSlider->value();
    if (temp == third)
    {
        return;
    }

    third = temp;
    t->blockSignals(true);
    t->setValue(third);
    t->blockSignals(false);
    emit edited();
}

void BasicColor::editedFS(int)
{
    double temp = fSlider->value();
    qDebug()<<temp;
    if (temp == first)
    {
        return;
    }

    first = temp;
    f->blockSignals(true);
    f->setValue(first);
    f->blockSignals(false);
    emit edited();
}
