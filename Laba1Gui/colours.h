#ifndef COLOURS_H
#define COLOURS_H

#include <iostream>
#include <cmath>
#include <QtWidgets/QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "BasicColor.h"
#include <map>

class RGB;
class CMYK;
class XYZ;
class Lab;
class HSV;
class HSL;

class RGB: public BasicColor
{
    Q_OBJECT
private:
    static double FXYZ(double x);
public:
    RGB(QWidget* parent, int red = 0, int green = 0, int blue = 0);
    RGB(const RGB&);

    QString toHex()override;

    CMYK toCMYK()const;
    XYZ toXYZ()const;
    Lab toLab()const;
    HSV toHSV()const;
    HSL toHSL()const;

    RGB& operator= (const RGB& op);

    ~RGB();
};

class CMYK : public BasicColor
{
    Q_OBJECT
private:
    friend class Hex;
    double key;
    QLineEdit* k;
    QLabel* kLabel;
public:
    CMYK(QWidget* parent, double cyan = 0, double magenta = 0,
         double yellow = 0, double key = 0);

    CMYK(const CMYK&);

    QString toHex()override;

    CMYK& operator= (const CMYK& op);

    RGB toRGB()const;
    XYZ toXYZ()const;
    Lab toLab()const;
    HSV toHSV()const;
    HSL toHSL()const;

    ~CMYK();

public slots:
    void editedK();
};

class XYZ : public BasicColor
{
    Q_OBJECT
private:
    static double FRGB(double x);
    static double FLab(double x);
public:
    XYZ(QWidget* parent, double x = 0, double y = 0, double z = 0);
    XYZ(const XYZ&);

    QString toHex()override;

    CMYK toCMYK()const;
    RGB toRGB()const;
    Lab toLab()const;
    HSV toHSV()const;
    HSL toHSL()const;

    XYZ& operator= (const XYZ& op);

    ~XYZ();
};

class Lab : public BasicColor
{
    Q_OBJECT
private:
    //static double FRGB(double x);
    static double FLab(double x);
public:
    Lab(QWidget* parent, double L = 0, double a = 0, double b = 0);
    Lab(const Lab&);

    QString toHex()override;

    CMYK toCMYK()const;
    RGB toRGB()const;
    XYZ toXYZ()const;
    HSV toHSV()const;
    HSL toHSL()const;

    Lab& operator= (const Lab& op);

    ~Lab();
};

class HSV : public BasicColor
{
    Q_OBJECT
public:
    HSV(QWidget* parent, double h = 0, double s = 0, double v = 0);
    HSV(const HSV&);

    QString toHex()override;

    CMYK toCMYK()const;
    RGB toRGB()const;
    XYZ toXYZ()const;
    Lab toLab()const;
    HSL toHSL()const;

    HSV& operator= (const HSV& op);

    ~HSV();
};

class HSL : public BasicColor
{
    Q_OBJECT
public:
    HSL(QWidget* parent, double h = 0, double s = 0, double l = 0);
    HSL(const HSL&);

    QString toHex()override;

    CMYK toCMYK()const;
    RGB toRGB()const;
    XYZ toXYZ()const;
    Lab toLab()const;
    HSV toHSV()const;

    HSL& operator= (const HSL& op);

    ~HSL();
};

#endif
