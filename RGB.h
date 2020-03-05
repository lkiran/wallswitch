#ifndef RGB_h
#define RGB_h

class RGB
{
public:
    RGB(byte red = 0, byte green = 0, byte blue = 0)
    {
        this->redValue = red;
        this->greenValue = green;
        this->blueValue = blue;
    }

    byte getRed()
    {
        return this->redValue;
    }

    byte getGreen()
    {
        return this->greenValue;
    }

    byte getBlue()
    {
        return this->blueValue;
    }


protected:
    byte redValue;
    byte greenValue;
    byte blueValue;
};

class RGBA : public RGB
{
public:
    RGBA(RGB color) : RGB(color)
    {
        this->alpha = 1;
    }

    RGBA(byte red = 0, byte green = 0, byte blue = 0, double alpha = 1) : RGB(red, green, blue)
    {
        this->alpha = alpha;
    }

    RGB toRGB(void)
    {
        return RGB(this->redValue * this->alpha, this->greenValue * this->alpha, this->blueValue * this->alpha);
    }

private:
    double alpha;
};

#endif

const RGB white(255, 255, 255);
const RGB red(255, 0, 0);
const RGB green(0, 255, 0);
const RGB blue(0, 0, 255);
const RGB cyan(0, 255, 255);
const RGB magenta(255, 0, 255);
const RGB yellow(255, 255, 0);
const RGB black(0, 0, 0);