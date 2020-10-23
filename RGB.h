#ifndef RGB_h
#define RGB_h

#include <Arduino.h>

class RGB
{
public:
	RGB();
	RGB(String code);
	RGB(int red, int green, int blue);
	bool operator==(const RGB &rhs) const;
	bool operator!=(const RGB &rhs) const;

	int getRed();
	int getGreen();
	int getBlue();

	static RGB white;
	static RGB red;
	static RGB green;
	static RGB blue;
	static RGB cyan;
	static RGB magenta;
	static RGB yellow;
	static RGB black;

protected:
	int redValue;
	int greenValue;
	int blueValue;
};

class RGBA : public RGB
{
public:
	RGBA(RGB color);
	RGBA(int red, int green, int blue, double alpha);
	RGB toRGB(void);

private:
	double alpha;
};

#endif