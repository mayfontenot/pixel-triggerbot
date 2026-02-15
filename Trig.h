#pragma once
#include <Windows.h>

extern const int PIXELS_SQRT, THRESHOLD, DELAY_MIN, DELAY_MAX;

void getPixels(HDC, POINT, COLORREF*, int);
COLORREF getAveragePixelColor(COLORREF*, int);
bool isOutOfThreshold(COLORREF, COLORREF, int);
void fire();