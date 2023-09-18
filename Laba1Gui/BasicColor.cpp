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
    f = new QLineEdit(QString::number(first), this);
    s = new QLineEdit(QString::number(second), this);
    t = new QLineEdit(QString::number(third), this);
    connect(f, &QLineEdit::textEdited, this, &BasicColor::editedF);
    connect(s, &QLineEdit::textEdited, this, &BasicColor::editedS);
    connect(t, &QLineEdit::textEdited, this, &BasicColor::editedT);
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

BasicColor::~BasicColor() {}

BasicColor& BasicColor::operator=(const BasicColor& op)
{
    first = op.first;
    second = op.second;
    third = op.third;
    fLabel->setText((op.fLabel)->text());
    sLabel->setText((op.sLabel)->text());
    tLabel->setText((op.tLabel)->text());
    f->setText(QString::number(op.first));
    s->setText(QString::number(op.second));
    t->setText(QString::number(op.third));

    return *this;
}

void BasicColor::editedS()
{
    bool ok;
    double temp = (s->text()).toDouble(&ok);
    if (!ok)
    {
        //TO DO: Обработать MESSAGE
    }
    else
    {
        second = temp;
        emit edited();
    }
}

void BasicColor::editedT()
{
    bool ok;
    double temp = (t->text()).toDouble(&ok);
    if (!ok)
    {
        //TO DO: Обработать MESSAGE
    }
    else
    {
        third = temp;
        emit edited();
    }
}

void BasicColor::editedF()
{
    bool ok;
    double temp = (f->text()).toDouble(&ok);
    if (!ok)
    {
        //TO DO: Обработать MESSAGE
    }
    else
    {
        first = temp;
        emit edited();
    }
}
