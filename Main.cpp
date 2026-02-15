#include <Windows.h>
#include <iostream>
#include "Trig.h"
using namespace std;

void mainLoop()
{
	cout << "© 2021 Meiware.net\nvisually reads pixels and simulates key press\nEND to terminate, hold Q to activate\n";

	COLORREF* pOldPixels = new COLORREF[PIXEL_COUNT], * pNewPixels = new COLORREF[PIXEL_COUNT];

	while (!GetAsyncKeyState(VK_END))
	{
		HDC hDC = GetDC(nullptr); //get handle of device context (active screen)

		if (!hDC)
			return;

		POINT cursor;
		GetCursorPos(&cursor);

		if (!GetAsyncKeyState('Q'))
			getPixels(hDC, cursor, pOldPixels, PIXEL_COUNT); //assign old pixels
		else
		{
			getPixels(hDC, cursor, pNewPixels, PIXEL_COUNT); //assign new pixels

			if (isOutOfThreshold(getAveragePixelColor(pNewPixels, PIXEL_COUNT), getAveragePixelColor(pNewPixels, PIXEL_COUNT), THRESHOLD)) //compare old and current pixels
				attack();
		}

		ReleaseDC(nullptr, hDC); //cleanup
		Sleep(5);
	}

	delete[] pNewPixels; //free from heap
	delete[] pOldPixels;
}

int main()
{
	mainLoop();

	return 0;
}