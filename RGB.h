#ifndef RGB_h
#define RGB_h

#include <stdint.h>

class RGB
{
public:
	RGB();
	RGB(const uint8_t red, uint8_t green, uint8_t blue);
	bool operator==(const RGB &rhs) const;
	bool operator!=(const RGB &rhs) const;

	uint8_t getRed();
	uint8_t getGreen();
	uint8_t getBlue();

	static RGB white;
	static RGB red;
	static RGB green;
	static RGB blue;
	static RGB cyan;
	static RGB magenta;
	static RGB yellow;
	static RGB black;

protected:
	uint8_t redValue;
	uint8_t greenValue;
	uint8_t blueValue;
};

class RGBA : public RGB
{
public:
	RGBA(RGB color);
	RGBA(const uint8_t red, const uint8_t green, const uint8_t blue, const double alpha);
	RGB toRGB(void);

private:
	double alpha;
};

#endif