#include "Board.h"

String mac2String(byte ar[])
{
    String s;
    for (byte i = 0; i < 6; ++i)
    {
        char buf[3];
        sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
        s += buf;
        if (i < 5)
            s += ':';
    }
    return s;
}

String Board::MAC = "";

String Board::getMacAddress(void)
{
    if (Board::MAC.length() == 0)
    {
        uint64_t chipid = ESP.getEfuseMac();
        Board::MAC = mac2String((byte *)&chipid);
    }
    return Board::MAC;
}