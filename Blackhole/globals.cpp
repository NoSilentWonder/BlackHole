#include "globals.h"

HBITMAP		theOldFrontBitMap, theOldBackBitMap;
HWND		ghwnd;
RECT		screenRect;
HDC			backHDC, frontHDC, bitmapHDC;	//Hardware device contexts for the Buffers