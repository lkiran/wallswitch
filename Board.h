#ifndef Board_h
#define Board_h

#include <Esp.h>

class Board
{
private:
	static String MAC;

public:
	static String getMacAddress(void);
};

#endif