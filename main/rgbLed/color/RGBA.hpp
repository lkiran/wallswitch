#pragma once
#include "RGB.hpp"
using namespace std;

extern "C"
class RGBA : public RGB
{
public:
    RGBA(RGB color);
    RGBA(int red, int green, int blue, double alpha);
    RGB toRGB(void);

private:
    double alpha;
};