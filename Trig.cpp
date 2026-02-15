#include "Trig.h"

const int PIXELS_SQRT = 4, THRESHOLD = 16, DELAY_MIN = 4, DELAY_MAX = 8;

void getPixels(HDC hDC, POINT pos, COLORREF *pPixels, int pixelsSQRT)
{
	int index = 0;
	int halfOfSQRT = pixelsSQRT / 2;

	for (int x = -halfOfSQRT; x < halfOfSQRT; x++)
		for (int y = -halfOfSQRT; y < halfOfSQRT; y++)
			pPixels[index++] = GetPixel(hDC, pos.x + x, pos.y + y);
}

COLORREF getAveragePixelColor(COLORREF *pPixels, int size) //calculate average RGB values of pixels
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

bool isOutOfThreshold(COLORREF oldPixels, COLORREF newPixels, int threshold)
{
	return (int)GetRValue(oldPixels) > (int)GetRValue(newPixels) + threshold || (int)GetRValue(oldPixels) < (int)GetRValue(newPixels) - threshold || (int)GetGValue(oldPixels) > (int)GetGValue(newPixels) + threshold || (int)GetGValue(oldPixels) < (int)GetGValue(newPixels) - threshold || (int)GetBValue(oldPixels) > (int)GetBValue(newPixels) + threshold || (int)GetBValue(oldPixels) < (int)GetBValue(newPixels) - threshold;
}

void fire()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	Sleep(rand() % DELAY_MIN + 1);

	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}