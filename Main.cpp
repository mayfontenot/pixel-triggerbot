#include <Windows.h>
#include <iostream>
#include "Trig.h"
using namespace std;

void mainLoop()
{
	cout << "© 2021 Meiware.net\nEND to terminate, hold Q to activate\n";

	srand(time(0));

	COLORREF *pOldPixels = new COLORREF[PIXELS_SQRT * PIXELS_SQRT], *pNewPixels = new COLORREF[PIXELS_SQRT * PIXELS_SQRT];

	while (!GetAsyncKeyState(VK_END))
	{
		HDC hDC = GetDC(nullptr); //get handle of device context (active screen)

		if (!hDC)
		{
			cout << "Failed to get handle of Device Context!\n";
			continue; //continue to next iteration and try again
		}

		POINT cursor;
		GetCursorPos(&cursor);

		if (!GetAsyncKeyState('Q'))
			getPixels(hDC, cursor, pOldPixels, PIXELS_SQRT); //assign old pixels
		else
		{
			getPixels(hDC, cursor, pNewPixels, PIXELS_SQRT); //assign new pixels

			if (isOutOfThreshold(getAveragePixelColor(pOldPixels, PIXELS_SQRT * PIXELS_SQRT), getAveragePixelColor(pNewPixels, PIXELS_SQRT * PIXELS_SQRT), THRESHOLD)) //compare old and current pixels
				fire();
		}

		ReleaseDC(nullptr, hDC); //cleanup
		Sleep(rand() % (DELAY_MAX - DELAY_MIN + 1) + DELAY_MIN);
	}

	delete[] pNewPixels; //free from heap
	delete[] pOldPixels;
}

int main()
{
	mainLoop();

	return 0;
}

