#include "Laba1Gui.h"
#include <fstream>

Laba1Gui::Laba1Gui(QWidget* parent)
    : QMainWindow(parent), hex(new QLineEdit("#000000", this)), ui(new Ui::Laba1Gui),
    rgb(new RGB(nullptr)), cmyk(new CMYK(nullptr)), xyz(new XYZ(nullptr)), lab(new Lab(nullptr)),
    hsv(new HSV(nullptr)), hsl(new HSL(nullptr))
{
    ui->setupUi(this);

    this->setFixedSize(720, 480);

    QWidget* mainWidget = new QWidget;
    layout = new QVBoxLayout(mainWidget);
    QPushButton* chooseClr = new QPushButton("Choose color", this);
    connect(chooseClr, SIGNAL(clicked()), SLOT(openColorDialog()));
    chooseClr->setFixedSize(this->width() / 2, this->height() * 0.3);
    layout->addWidget(chooseClr);

    QLabel* hexLabel = new QLabel("HEX:", this);
    hex->setFixedWidth(this->width() / 2);
    connect(hex, &QLineEdit::textEdited, this, &Laba1Gui::changeNow);
    Hex temp(hex->text());
    temp.toRGB(rgb);
    temp.toCMYK(cmyk);
    temp.toXYZ(xyz);
    temp.toLab(lab);
    temp.toHSV(hsv);
    temp.toHSL(hsl);

    layout->addStretch();
    layout->addWidget(hexLabel);
    layout->addWidget(hex);

    this->setCentralWidget(mainWidget);
    std::ifstream variants("C:\\pkg\\laba1\\Laba1Gui\\variants.txt");
    std::string var;
    comboBox = new QComboBox;
    while (getline(variants, var))
    {
        comboBox->addItem(QString::fromStdString(var));
    }

    variants.close();
    connect(comboBox, SIGNAL(activated(int)), this, SLOT(changeCurrent(int)));
    layout->addWidget(comboBox);
    mainWidget->setLayout(layout);

    changeCurrent(0);
}

Laba1Gui::~Laba1Gui()
{
    delete ui;
}

void Laba1Gui::paintEvent(QPaintEvent* e)
{
    QPainter paint(this);
    paint.begin(this);
    QBrush brush(QColor(hex->text()));
    QPen pen(Qt::NoPen);
    paint.setBrush(brush);
    paint.setPen(pen);

    paint.drawRect(QRect(QPoint(this->width() * 0.6, 0.1 * this->height()), QPoint(this->width() * 0.95, 0.45 * this->height())));
    paint.end();
}

void Laba1Gui::changeNow()
{
    changeColors(nullptr);
    this->update();
}

void Laba1Gui::changeCurrent(int)
{
    rgb->close();
    cmyk->close();
    xyz->close();
    lab->close();
    hsv->close();
    hsl->close();

    QStringList vars = (comboBox->currentText()).split(" ");
    QHBoxLayout* layColors = new QHBoxLayout();
    for (auto item : vars)
    {
        if (item == "RGB")
        {
            rgb->show();
            //rgb = new RGB(nullptr, now.red(), now.green(), now.blue());
            layColors->addWidget(rgb);
            QObject::connect(rgb, &RGB::edited, std::bind(&Laba1Gui::changeColors, this, rgb));
        }
        else if (item == "CMYK")
        {
            cmyk->show();
            layColors->addWidget(cmyk);
            QObject::connect(cmyk, &CMYK::edited, std::bind(&Laba1Gui::changeColors, this, cmyk));
        }
        else if (item == "XYZ")
        {
            xyz->show();
            layColors->addWidget(xyz);
            QObject::connect(xyz, &XYZ::edited, std::bind(&Laba1Gui::changeColors, this, xyz));
        }
        else if (item == "LAB")
        {
            lab->show();
            layColors->addWidget(lab);
            QObject::connect(lab, &Lab::edited, std::bind(&Laba1Gui::changeColors, this, lab));
        }
        else if (item == "HSV")
        {
            hsv->show();
            layColors->addWidget(hsv);
            QObject::connect(hsv, &HSV::edited, std::bind(&Laba1Gui::changeColors, this, hsv));
        }
        else if (item == "HLS")
        {
            hsl->show();
            layColors->addWidget(hsl);
            QObject::connect(hsl, &HSL::edited, std::bind(&Laba1Gui::changeColors, this, hsl));
        }

    }

    layout->addLayout(layColors);
}

void Laba1Gui::changeColors(BasicColor* bc)
{
    if (bc == nullptr)
    {
        Hex temp(hex->text());
        temp.toRGB(rgb);
        temp.toCMYK(cmyk);
        temp.toXYZ(xyz);
        temp.toLab(lab);
        temp.toHSV(hsv);
        temp.toHSL(hsl);

        return;
    }
    else if (dynamic_cast<RGB*>(bc) != nullptr)
    {
        hex->setText(rgb->toHex());
        *cmyk = rgb->toCMYK();
        *xyz = rgb->toXYZ();
        *lab = rgb->toLab();
        *hsv = rgb->toHSV();
        *hsl = rgb->toHSL();
    }
    else if (dynamic_cast<CMYK*>(bc) != nullptr)
    {
        hex->setText(cmyk->toHex());
        *rgb = cmyk->toRGB();
        *xyz = cmyk->toXYZ();
        *lab = cmyk->toLab();
        *hsv = cmyk->toHSV();
        *hsl = cmyk->toHSL();
    }
    else if (dynamic_cast<XYZ*>(bc) != nullptr)
    {
        hex->setText(xyz->toHex());
        *rgb = xyz->toRGB();
        *cmyk = xyz->toCMYK();
        *lab = xyz->toLab();
        *hsv = xyz->toHSV();
        *hsl = xyz->toHSL();
    }
    else if (dynamic_cast<Lab*>(bc) != nullptr)
    {
        hex->setText(lab->toHex());
        *rgb = lab->toRGB();
        *cmyk = lab->toCMYK();
        *xyz = lab->toXYZ();
        *hsv = lab->toHSV();
        *hsl = lab->toHSL();
    }
    else if (dynamic_cast<HSV*>(bc) != nullptr)
    {
        hex->setText(hsv->toHex());
        *rgb = hsv->toRGB();
        *cmyk = hsv->toCMYK();
        *lab = hsv->toLab();
        *xyz = hsv->toXYZ();
        *hsl = hsv->toHSL();
    }
    else if (dynamic_cast<HSL*>(bc) != nullptr)
    {
        hex->setText(hsl->toHex());
        *rgb = hsl->toRGB();
        *cmyk = hsl->toCMYK();
        *lab = hsl->toLab();
        *xyz = hsl->toXYZ();
        *hsv = hsl->toHSV();
    }

    this->update();
}

void Laba1Gui::openColorDialog()
{
    QColorDialog* dialog = new QColorDialog(QColor(hex->text()));
    QColor temp = QColorDialog::getColor(QColor(hex->text()), dialog, "Choose color");
    if (temp.isValid())
    {
        hex->setText(temp.name());
    }

    changeNow();
}
