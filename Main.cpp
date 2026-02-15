#include <Windows.h>
#include <iostream>
#include "Trig.h"
using namespace std;

int main()
{
	SetConsoleTitle(L"Mayware Pixel Triggerbot v2026-02-15");
	cout << "© 2021 Mayware.net\nSimulates mouse press (no memory modification)\nEND to terminate, hold Q to activate\n";

	srand(time(0)); //seed the random so it is not predicted

	POINT cursor;
	HDC hDC = GetDC(nullptr);
	bool isHDCAcquired = false;
	COLORREF *pOldPixels = new COLORREF[PIXELS_SQRT * PIXELS_SQRT], *pNewPixels = new COLORREF[PIXELS_SQRT * PIXELS_SQRT]; //create new arrays on heap, later delete them

	while (!GetAsyncKeyState(VK_END))
	{
		GetCursorPos(&cursor);

		if (GetAsyncKeyState('Q'))
		{
			if (!isHDCAcquired) //if Q is pressed get DC, but only once until Q is released
			{
				if (hDC)
					ReleaseDC(nullptr, hDC); //free the handle of the DC if it is non-zero

				if (!(hDC = GetDC(nullptr))) //get handle of DC (active screen) and assign to hDC, if failure continue to next iteration and try again
				{
					cout << "Failed to get handle of Device Context!\n";
					Sleep(rand() % (DELAY_MAX - DELAY_MIN + 1) + DELAY_MIN); //avoid heavy CPU usage
					continue; //continue to next iteration and try again
				}

				isHDCAcquired = true; //tell the program to not acquire another DC
			}

			getPixels(hDC, cursor, pNewPixels, PIXELS_SQRT); //assign new pixels

			if (isOutOfThreshold(getAveragePixelColor(pOldPixels, PIXELS_SQRT * PIXELS_SQRT), getAveragePixelColor(pNewPixels, PIXELS_SQRT * PIXELS_SQRT), THRESHOLD)) //compare old and current pixels
				fire(); //simulate the mouse click
		}
		else if(hDC)
		{
			getPixels(hDC, cursor, pOldPixels, PIXELS_SQRT); //assign old pixels
			isHDCAcquired = false; //tell the program to acquire another DC handle
		}

		Sleep(rand() % (DELAY_MAX - DELAY_MIN + 1) + DELAY_MIN); //random sleep to appear human
	}

	if (hDC)
		ReleaseDC(nullptr, hDC); //free the handle of the DC if it is non-zero

	delete[] pNewPixels; //free from heap
	delete[] pOldPixels;

	return 0;
}