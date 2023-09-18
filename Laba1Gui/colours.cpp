#include "colours.h"

using std::min;
using std::max;

double RGB::FXYZ(double x)
{
    if (x >= 0.04045)
    {
        return pow((x + 0.055) / 1.055, 2.4);
    }

    return x / 12.92;
}

RGB::RGB(QWidget* parent, int red, int green, int blue) :
    BasicColor(parent, red, green, blue)
{
    this->fLabel->setText("R: ");
    this->sLabel->setText("G: ");
    this->tLabel->setText("B: ");

    this->f->setMinimum(0);
    this->s->setMinimum(0);
    this->t->setMinimum(0);
    this->f->setMaximum(255);
    this->s->setMaximum(255);
    this->t->setMaximum(255);
}

RGB::RGB(const RGB& op)
{
    *this = op;
}

QString RGB::toHex()
{
    QString res = "#";
    if (first < 0 || first > 255 || second < 0 || second > 255 || third < 0 || third > 255)
    {
        return "";
    }

    res = res + trans[(int)first / 16] + trans[(int)first % 16] + trans[(int)second / 16]
          + trans[(int)second % 16] + trans[(int)third / 16] + trans[(int)third % 16];
    return res;
}

RGB& RGB::operator= (const RGB& op)
{
    (BasicColor&)*this = (const BasicColor&)op;

    return *this;
}

CMYK RGB::toCMYK()const
{
    double key = min(min(1. - (double)first / 255, 1. - (double)second / 255), 1. - (double)third / 255);
    if (1. - key == 0.)
    {
        return CMYK(nullptr, 0, 0, 0, 100);
    }

    double cyan = (1. - (double)first / 255 - key) / (1. - key);
    double magenta = (1. - (double)second / 255 - key) / (1. - key);
    double yellow = (1. - (double)third / 255 - key) / (1. - key);

    return CMYK(nullptr, cyan * 100, magenta * 100, yellow * 100, key * 100);
}


XYZ RGB::toXYZ()const
{
    double Rn = FXYZ((double)first / 255) * 100;
    double Gn = FXYZ((double)second / 255) * 100;
    double Bn = FXYZ((double)third / 255) * 100;

    double X = 0.412453 * Rn + 0.357580 * Gn + 0.180423 * Bn;
    double Y = 0.212671 * Rn + 0.715160 * Gn + 0.072169 * Bn;
    double Z = 0.019334 * Rn + 0.119193 * Gn + 0.950227 * Bn;

    return XYZ(nullptr, X, Y, Z);
}

Lab RGB::toLab()const
{

    return toXYZ().toLab();
}

HSV RGB::toHSV()const
{
    double CMax = max(max(first/255, second/255), third/255);
    double CMin = min(min(first/255, second/255), third/255);
    double delta = CMax - CMin;

    double hue;
    double v = CMax;
    double s;
    if (CMax == 0)
    {
        s = 0;
    }
    else
    {
        s = delta / CMax;
    }

    if (delta == 0)
    {
        hue = 0;
    }
    else if (CMax == first / 255)
    {

        hue = ((second/255 - third/255) / delta);

    }
    else if (CMax == second / 255)
    {
        hue = (third/255 - first/255) / delta + 2;
    }
    else if (CMax == third / 255)
    {
        hue = (first / 255 - second / 255) / delta + 4;
    }

    hue *= 60;
    if (hue < 0)
    {
        hue += 360;
    }

    return HSV(nullptr, hue, s * 100, v * 100);
}

HSL RGB::toHSL()const
{
    double r = first / 255;
    double g = second / 255;
    double b = third / 255;

    double CMax = max(max(r, g), b);
    double CMin = min(min(r, g), b);
    double delta = CMax - CMin, h = 0, s = 0, l = 0;

    if (delta == 0)
    {
        h = 0;
    }
    else if (CMax == r)
    {
        h = ((g - b) / delta) - (int)((g - b) / delta) / 6 * 6;
    }
    else if (CMax == g)
    {
        h = (b - r) / delta + 2;
    }
    else if (CMax == b)
    {
        h = (r - g) / delta + 4;
    }

    h = round(h * 60);
    while (h < 0)
    {
        h += 360;
    }

    l = (CMax + CMin) / 2;
    s = delta == 0 ? 0 : delta / (1 - abs(2 * l - 1));
    s *= 100;
    l *= 100;

    return HSL(nullptr, h, s, l);
}

void RGB::chekcUndo()
{
    if (0. > first || 255. < first)
    {
        //f->undo();
    }
    else if (0. > second || 255. < second)
    {
        //s->undo();
    }
    else if (0. > third || 255. < third)
    {
        //t->undo();
    }
}

RGB::~RGB() {}

CMYK::CMYK(QWidget* parent, double cyan, double magenta,
           double yellow, double key): BasicColor(parent, cyan, magenta,
                 yellow), key(key)
{
    this->fLabel->setText("C: ");
    this->sLabel->setText("M: ");
    this->tLabel->setText("Y: ");

    kLabel = new QLabel("K: ");
    k = new QDoubleSpinBox(this);
    k->blockSignals(true);
    k->setValue(key);
    k->blockSignals(false);
    QHBoxLayout* kLayout = new QHBoxLayout(this);
    kLayout->addWidget(kLabel);
    kLayout->addWidget(k);
    layout->addLayout(kLayout);

    this->f->setMinimum(0);
    this->s->setMinimum(0);
    this->t->setMinimum(0);
    this->f->setMaximum(100);
    this->s->setMaximum(100);
    this->t->setMaximum(100);
    this->k->setMinimum(0);
    this->k->setMaximum(100);

    connect(k, SIGNAL(valueChanged(double)), this, SLOT(editedK(double)));
    //connect(k, &QDoubleSpinBox::valueChanged, this, &CMYK::editedK);
}

CMYK::CMYK(const CMYK& op)
{
    *this = op;
}

QString CMYK::toHex()
{
    QString res = "#";
    res = res + trans[(int)(255 * (1. - first/100) * (1. - key/100)) / 16]
          + trans[(int)(255 * (1. - first/100) * (1. - key/100)) % 16]
          + trans[(int)(255 * (1. - second/100) * (1. - key/100)) / 16]
          + trans[(int)(255 * (1. - second/100) * (1. - key/100)) % 16]
          + trans[(int)(255 * (1. - third/100) * (1. - key/100)) / 16]
          + trans[(int)(255 * (1. - third/100) * (1. - key/100)) % 16];

    return res;
}

RGB CMYK::toRGB()const
{
    int r = (int)255 * (1. - first/100) * (1. - key/100);
    int g = (int)255 * (1. - second/100) * (1. - key/100);
    int b = (int)255 * (1. - third/100) * (1. - key/100);
    return RGB(nullptr, r, g, b);
}


XYZ CMYK::toXYZ()const
{
    if (1. - key / 100. == 0.)
    {
        return XYZ(nullptr, 0., 0., 0.);
    }

    return toRGB().toXYZ();

    /*return XYZ(nullptr, 0.4124564 * (1. - first / 100) * (1. - key / 100)
        + 0.3575761 * (1. - second / 100) * (1. - key / 100)
        + 0.1804375 * (1. - third / 100) * (1. - key / 100),
        0.2126729 * (1. - first / 100) * (1. - key / 100)
        + 0.7151522 * (1. - second / 100) * (1. - key / 100)
        + 0.0721750 * (1. - third / 100) * (1. - key / 100),
        0.0193339 * (1. - first / 100) * (1. - key / 100)
        + 0.1191920 * (1. - second / 100) * (1. - key / 100)
        + 0.9503041 * (1. - third / 100) * (1. - key / 100));*/
}

Lab CMYK::toLab()const
{
    return toXYZ().toLab();
}

HSV CMYK::toHSV()const
{
    return toRGB().toHSV();
}

HSL CMYK::toHSL()const
{
    return toRGB().toHSL();
}

CMYK& CMYK::operator= (const CMYK& op)
{
    (BasicColor&)*this = (const BasicColor&)op;
    key = op.key;
    kLabel = op.kLabel;
    k->blockSignals(true);
    k->setValue(op.key);
    k->blockSignals(false);

    return *this;
}

void CMYK::editedK(double)
{
    bool ok;
    int temp = k->value();
    if (temp==key)
    {
        return;
    }


    key = temp;
    emit edited();
}

void CMYK::chekcUndo()
{
    if (0. > first || 100. < first)
    {
        //f->undo();
    }
    else if (0. > second || 100. < second)
    {
        //s->undo();
    }
    else if (0. > third || 100. < third)
    {
        //t->undo();
    }
    else if (0. > key || 100. < key)
    {
        //k->undo();
    }
}

CMYK::~CMYK() {}

XYZ::XYZ(QWidget* parent, double x, double y, double z) :
    BasicColor(parent, x, y, z)
{
    this->fLabel->setText("X: ");
    this->sLabel->setText("Y: ");
    this->tLabel->setText("Z: ");

    this->f->setMinimum(0);
    this->s->setMinimum(0);
    this->t->setMinimum(0);
    this->f->setMaximum(95.047);
    this->s->setMaximum(100);
    this->t->setMaximum(108.883);
}

XYZ::XYZ(const XYZ& op)
{
    *this = op;
}

QString XYZ::toHex()
{
    return toRGB().toHex();
}

XYZ& XYZ::operator= (const XYZ& op)
{
    (BasicColor&)*this = (const BasicColor&)op;

    return *this;
}

double XYZ::FRGB(double x)
{
    if (x >= 0.0031308)
    {
        return 1.055 * pow(x, 1. / 2.4) - 0.055;
    }

    return x * 12.92;
}

double XYZ::FLab(double x)
{
    if (x >= 0.008856)
    {
        return pow(x, 1. / 3);
    }

    return 7.787 * x + 16./116;
}

RGB XYZ::toRGB()const
{
    double Rn = 3.2406 * first / 100 - 1.5372 * second / 100 - 0.4986 * third / 100;
    Rn = FRGB(Rn);
    if (Rn > 1)
    {
        Rn = 1;
    }
    if (Rn < 0)
    {
        Rn = 0;
    }
    double Gn = -0.9689 * first / 100 + 1.8758 * second / 100 + 0.0415 * third / 100;
    Gn = FRGB(Gn);
    if (Gn > 1)
    {
        Gn = 1;
    }
    if (Gn < 0)
    {
        Gn = 0;
    }
    double Bn = 0.0557 * first / 100 - 0.2040 * second / 100 + 1.0570 * third / 100;
    Bn = FRGB(Bn);
    if (Bn > 1)
    {
        Bn = 1;
    }
    if (Bn < 0)
    {
        Bn = 0;
    }

    return RGB(nullptr, Rn * 255, Gn * 255, Bn * 255);
}

CMYK XYZ::toCMYK()const
{
    return toRGB().toCMYK();
}

Lab XYZ::toLab()const
{
    const double Xw = 95.047;
    const double Yw = 100;
    const double Zw = 108.883;

    return Lab(nullptr, 116. * FLab(second / Yw) - 16.,
               500. * (FLab(first / Xw) - FLab(second / Yw)),
               200. * (FLab(second / Yw) - FLab(third / Zw)));
}

HSV XYZ::toHSV()const
{
    return toRGB().toHSV();
}

HSL XYZ::toHSL()const
{

    return toRGB().toHSL();
}

void XYZ::chekcUndo()
{
    if (0. > first || 95.047 < first)
    {
        //f->undo();
    }
    else if (0. > second || 100. < second)
    {
        //s->undo();
    }
    else if (0. > third || 108.883 < third)
    {
        //t->undo();
    }
}

XYZ::~XYZ() {}

Lab::Lab(QWidget* parent, double L, double a, double b) :
    BasicColor(parent, L, a, b)
{
    this->fLabel->setText("L: ");
    this->sLabel->setText("a: ");
    this->tLabel->setText("b: ");

    this->f->setMinimum(0);
    this->s->setMinimum(-128);
    this->t->setMinimum(-128);
    this->f->setMaximum(100);
    this->s->setMaximum(128);
    this->t->setMaximum(128);
}

Lab::Lab(const Lab& op)
{
    *this = op;
}

QString Lab::toHex()
{
    return toRGB().toHex();
}

Lab& Lab::operator= (const Lab& op)
{
    (BasicColor&)*this = (const BasicColor&)op;

    return *this;
}

double Lab::FLab(double x)
{
    if (pow(x, 3.) >= 0.008856)
    {
        return pow(x, 3.);
    }

    return (x - 16./116) / 7.787;
}

RGB Lab::toRGB()const
{
    return toXYZ().toRGB();
}

CMYK Lab::toCMYK()const
{
    return toXYZ().toCMYK();
}

XYZ Lab::toXYZ()const
{
    const double Xw = 95.047;
    const double Yw = 100;
    const double Zw = 108.883;

    return XYZ(nullptr, FLab(second / 500 + (first + 16.) / 116.) * Xw,
               FLab((first + 16.) / 116.) * Yw,
               FLab((first + 16.) / 116. - third / 200.) * Zw);
}

HSV Lab::toHSV()const
{
    return toXYZ().toHSV();
}

HSL Lab::toHSL()const
{

    return toXYZ().toHSL();
}



Lab::~Lab() {};

void Lab::chekcUndo()
{
    if (0. > first || 100. < first)
    {
        //f->undo();
    }
    else if (-128. > second || 128. < second)
    {
        //s->undo();
    }
    else if (-128. > third || 128. < third)
    {
        //t->undo();
    }
}

HSV::HSV(QWidget* parent, double hue, double s, double v) :
    BasicColor(parent, hue, s, v)
{
    this->fLabel->setText("H: ");
    this->sLabel->setText("S: ");
    this->tLabel->setText("V: ");

    this->f->setMinimum(0);
    this->s->setMinimum(0);
    this->t->setMinimum(0);
    this->f->setMaximum(359.99);
    this->s->setMaximum(100);
    this->t->setMaximum(100);
}

HSV::HSV(const HSV& op)
{
    *this = op;
}

QString HSV::toHex()
{
    return toRGB().toHex();
}

HSV& HSV::operator= (const HSV& op)
{
    (BasicColor&)*this = (const BasicColor&)op;

    return *this;
}

RGB HSV::toRGB()const
{
    double c = second / 100 * third / 100;
    double x = c * (1. - abs((first - (int)(first / 120) * 120) / 60 - 1));
    double m = third / 100 - c;

    double R, G, B;
    if (first >= 0 && first < 60)
    {
        R = c;
        G = x;
        B = 0.;
    }
    else if (first >= 60 && first < 120)
    {
        R = x;
        G = c;
        B = 0.;
    }
    else if (first >= 120 && first < 180)
    {
        R = 0.;
        G = c;
        B = x;
    }
    else if (first >= 180 && first < 240)
    {
        R = 0.;
        G = x;
        B = c;
    }
    else if (first >= 240 && first < 300)
    {
        R = x;
        G = 0.;
        B = c;
    }
    else if (first >= 300 && first < 360)
    {
        R = c;
        G = 0.;
        B = x;
    }

    return RGB(nullptr, (R + m) * 255, (G + m) * 255, (B + m) * 255);
}

CMYK HSV::toCMYK()const
{
    return toRGB().toCMYK();
}

XYZ HSV::toXYZ()const
{
    return toRGB().toXYZ();
}

Lab HSV::toLab()const
{
    return toRGB().toLab();
}

HSL HSV::toHSL()const
{

    return toRGB().toHSL();
}

HSV::~HSV() {}

void HSV::chekcUndo()
{
    if (0. > first || 360 <= first)
    {
        //f->undo();
    }
    else if (0. > second || 100. < second)
    {
        //s->undo();
    }
    else if (0. > third || 100. < third)
    {
        //t->undo();
    }
}

HSL::HSL(QWidget* parent, double h, double s, double l) :
    BasicColor(parent, h, s, l)
{
    this->fLabel->setText("H: ");
    this->sLabel->setText("S: ");
    this->tLabel->setText("L: ");

    this->f->setMinimum(0);
    this->s->setMinimum(0);
    this->t->setMinimum(0);
    this->f->setMaximum(359.99);
    this->s->setMaximum(100);
    this->t->setMaximum(100);
}

HSL::HSL(const HSL& op)
{
    *this = op;
}

QString HSL::toHex()
{
    return toRGB().toHex();
}

HSL& HSL::operator= (const HSL& op)
{
    (BasicColor&)*this = (const BasicColor&)op;

    return *this;
}

RGB HSL::toRGB()const
{
    double c = (1. - abs(2 * third / 100 - 1)) * second / 100;
    double x = c * (1. - abs((first - (int)(first / 120) * 120) / 60 - 1));
    double m = third / 100 - c / 2;

    double R, G, B;
    if (first >= 0 && first < 60)
    {
        R = c;
        G = x;
        B = 0.;
    }
    else if (first >= 60 && first < 120)
    {
        R = x;
        G = c;
        B = 0.;
    }
    else if (first >= 120 && first < 180)
    {
        R = 0.;
        G = c;
        B = x;
    }
    else if (first >= 180 && first < 240)
    {
        R = 0.;
        G = x;
        B = c;
    }
    else if (first >= 240 && first < 300)
    {
        R = x;
        G = 0.;
        B = c;
    }
    else if (first >= 300 && first < 360)
    {
        R = c;
        G = 0.;
        B = x;
    }

    return RGB(nullptr, (R + m) * 255, (G + m) * 255, (B + m) * 255);
}

CMYK HSL::toCMYK()const
{
    return toRGB().toCMYK();
}

XYZ HSL::toXYZ()const
{
    return toRGB().toXYZ();
}

Lab HSL::toLab()const
{
    return toRGB().toLab();
}

HSV HSL::toHSV()const
{

    return toRGB().toHSV();
}

void HSL::chekcUndo()
{
    if (0. > first || 360 <= first)
    {
        //f->undo();
    }
    else if (0. > second || 100. < second)
    {
        //s->undo();
    }
    else if (0. > third || 100. < third)
    {
        //t->undo();
    }
}

HSL::~HSL() {}
