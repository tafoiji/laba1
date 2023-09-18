#ifndef HEX_H
#define HEX_H

#include <QString>
#include "colours.h"

class Hex
{
private:
    QString hex;
    std::map<QChar, int> trans;
public:
    explicit Hex(QString str);
    void toRGB(RGB* rgb);
    void toCMYK(CMYK* cmyk);
    void toXYZ(XYZ* xyz);
    void toLab(Lab* lab);
    void toHSV(HSV* hsv);
    void toHSL(HSL* hsl);
};

#endif

