#pragma once
#include <Windows.h>

extern const int PIXEL_COUNT, THRESHOLD;

void getPixels(HDC, POINT, COLORREF*, int);
COLORREF getAveragePixelColor(COLORREF*, int);
bool isOutOfThreshold(COLORREF, COLORREF, int);
void attack();