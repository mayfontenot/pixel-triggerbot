#include "Trig.h"

const int PIXELS_SQRT = 4, THRESHOLD = 16, DELAY_MIN = 5, DELAY_MAX = 10;

void getPixels(HDC hDC, POINT pos, COLORREF *pPixels, int pixelsSQRT)
{
	int index = 0;
	int halfOfSQRT = pixelsSQRT / 2;

	for (int x = -halfOfSQRT; x < halfOfSQRT; x++)
		for (int y = -halfOfSQRT; y < halfOfSQRT; y++)
			pPixels[index++] = GetPixel(hDC, pos.x + x, pos.y + y);
}

COLORREF getAveragePixelColor(COLORREF *pPixels, int size)
{
	int tempR = 0, tempG = 0, tempB = 0;

	for (int i = 0; i < size; i++)
	{
		tempR += (int)GetRValue(pPixels[i]);
		tempG += (int)GetGValue(pPixels[i]);
		tempB += (int)GetBValue(pPixels[i]);
	}

	return RGB(tempR / size, tempG / size, tempB / size);
}

bool isOutOfThreshold(COLORREF pixel1, COLORREF pixel2, int threshold)
{
	return (int)GetRValue(pixel1) > (int)GetRValue(pixel2) + threshold || (int)GetRValue(pixel1) < (int)GetRValue(pixel2) - threshold || (int)GetGValue(pixel1) > (int)GetGValue(pixel2) + threshold || (int)GetGValue(pixel1) < (int)GetGValue(pixel2) - threshold || (int)GetBValue(pixel1) > (int)GetBValue(pixel2) + threshold || (int)GetBValue(pixel1) < (int)GetBValue(pixel2) - threshold;
}

void fire()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	Sleep(rand() % (DELAY_MAX - DELAY_MIN + 1) + DELAY_MIN); //random sleep to appear human

	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}