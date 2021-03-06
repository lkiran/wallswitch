#ifndef Board_h
#define Board_h

#include <Esp.h>

class Board
{
private:
	static String MAC;
	static void mac2String(byte ar[]);

public:
	static String &getMacAddress(void);
};

#endif