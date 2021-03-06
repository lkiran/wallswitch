#include "Board.h"

void Board::mac2String(byte ar[])
{
    for (byte i = 0; i < 6; ++i)
    {
        char buf[3];
        sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
        Board::MAC += buf;
        if (i < 5)
            Board::MAC += ':';
    }
}

String Board::MAC = emptyString;

String &Board::getMacAddress(void)
{
    if (Board::MAC.length() == 0)
    {
        uint64_t chipid = ESP.getEfuseMac();
        mac2String((byte *)&chipid);
    }
    return Board::MAC;
}