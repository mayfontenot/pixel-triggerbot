#pragma once
#include <Windows.h>

extern const int PIXELS_SQRT, THRESHOLD, DELAY_MIN, DELAY_MAX;

/// <summary>
/// Gets the specified number of pixels from the specified Device Context around the specified position and stores them to the specified array
/// </summary>
/// <param name="hDC">Handle of the Device Context</param>
/// <param name="pos">Position of the screen in which to get the pixels around</param>
/// <param name="pPixels">Array in which to store the pixels to</param>
/// <param name="pixelsSQRT">The square root of the size of the array, this is used to find the starting position of the screen and calculate the size of the array, this is faster than calculating the square root ourselves</param>
void getPixels(HDC hDC, POINT pos, COLORREF *pPixels, int pixelsSQRT);

/// <summary>
/// Calculates the average RGB values of the specified pixels
/// </summary>
/// <param name="pPixels">Array of the specified pixels</param>
/// <param name="size">Number of elements in the pixel array</param>
/// <returns>A pixel containing the average RGB values</returns>
COLORREF getAveragePixelColor(COLORREF *pPixels, int size);

/// <summary>
/// Checks if the pixels RGB values are within a certain threshold of eachother
/// </summary>
/// <param name="pixel1">The first pixel to compare</param>
/// <param name="pixel2">The 2nd pixel to compare</param>
/// <param name="threshold">RGB threshold from 0-255</param>
/// <returns>true if it is not within threshold, otherwise false</returns>
bool isOutOfThreshold(COLORREF pixel1, COLORREF pixel2, int threshold);

/// <summary>
/// Fires a simulated mouse button press and release with a randomized sleep to appear human
/// </summary>
void fire();