#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <iostream>

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

extern HBITMAP	theOldFrontBitMap, theOldBackBitMap;
extern HWND		ghwnd;
extern RECT		screenRect;
extern HDC		backHDC, frontHDC, bitmapHDC;	//Hardware device contexts for the Buffers

#endif