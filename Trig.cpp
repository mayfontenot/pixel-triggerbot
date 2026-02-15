#include "Trig.h"

const int PIXEL_COUNT = 4, THRESHOLD = 16;

void getPixels(HDC hDC, POINT pos, COLORREF *pPixels, int size)
{
	int index = 0;

	for (int x = -1; x < 2; x += 2)
		for (int y = -1; y < 2; y += 2)
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

void attack()
{
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

	SendInput(1, &input, sizeof(INPUT));
}