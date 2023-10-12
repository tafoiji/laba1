#include "Hex.h"

Hex::Hex(QString str):hex(str)
{
    trans = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
             {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'a', 10},
             {'b', 11 }, { 'c', 12}, {'d', 13}, { 'e', 14}, { 'f', 15} };
}

void Hex::toRGB(RGB* rgb)
{
    if (rgb == nullptr)
    {
        return;
    }

    rgb->first = trans[hex[1]] * 16 + trans[hex[2]];
    rgb->second = trans[hex[3]] * 16 + trans[hex[4]];
    rgb->third = trans[hex[5]] * 16 + trans[hex[6]];
    rgb->blockSignals(true);
    rgb->f->setValue(rgb->first);
    rgb->s->setValue(rgb->second);
    rgb->t->setValue(rgb->third);
    rgb->fSlider->setValue(rgb->first);
    rgb->sSlider->setValue(rgb->second);
    rgb->tSlider->setValue(rgb->third);
    rgb->blockSignals(false);
}

void Hex::toCMYK(CMYK* cmyk)
{
    if (cmyk == nullptr)
    {
        return;
    }

    cmyk->key = 1. - std::max(std::max((double)(trans[hex[1]] * 16
                                                 + trans[hex[2]]) / 255, (double)(trans[hex[3]] * 16 +
                                                 trans[hex[4]]) / 255), (double)(trans[hex[5]] * 16
                                        + trans[hex[6]]) / 255);

    if (1. - cmyk->key == 0.)
    {
        cmyk->first = 0;
        cmyk->second = 0;
        cmyk->third = 0;
    }
    else
    {
        cmyk->first = ((1. - (double)(trans[hex[1]] * 16 +
                                       trans[hex[2]]) / 255 - cmyk->key) / (1. - cmyk->key)) * 100;
        cmyk->second = ((1. - (double)(trans[hex[3]] * 16 +
                                        trans[hex[4]]) / 255 - cmyk->key) / (1. - cmyk->key)) * 100;
        cmyk->third = ((1. - (double)(trans[hex[5]] * 16 +
                                       trans[hex[6]]) / 255 - cmyk->key) / (1. - cmyk->key)) * 100;
    }

    cmyk->key *= 100;
    cmyk->blockSignals(true);
    cmyk->f->setValue(cmyk->first);
    cmyk->s->setValue(cmyk->second);
    cmyk->t->setValue(cmyk->third);
    cmyk->fSlider->setValue(cmyk->first);
    cmyk->sSlider->setValue(cmyk->second);
    cmyk->tSlider->setValue(cmyk->third);
    cmyk->blockSignals(false);
    cmyk->k->blockSignals(true);
    cmyk->k->setValue(cmyk->key);
    cmyk->k->blockSignals(false);
    cmyk->kSlider->blockSignals(true);
    cmyk->kSlider->setValue(cmyk->key);
    cmyk->kSlider->blockSignals(false);

}

void Hex::toXYZ(XYZ* xyz)
{
    RGB item = xyz->toRGB();
    toRGB(&item);
    *xyz = item.toXYZ();
}

void Hex::toLab(Lab* lab)
{
    RGB item = lab->toRGB();
    toRGB(&item);
    *lab = item.toLab();
}

void Hex::toHSV(HSV* hsv)
{
    RGB item = hsv->toRGB();
    toRGB(&item);
    *hsv = item.toHSV();
}

void Hex::toHSL(HSL* hsl)
{
    RGB item = hsl->toRGB();
    toRGB(&item);
    *hsl = item.toHSL();
}
