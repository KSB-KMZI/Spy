#include "Screenshooter.h"

static const GUID png =
{ 0x557cf406, 0x1a04, 0x11d3,{ 0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e } };

void MakeShots(void)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HDC scrdc, memdc;
	HBITMAP membit;

	scrdc = GetDC(0);

	int Height, Width;
	Height = GetSystemMetrics(SM_CYSCREEN);
	Width = GetSystemMetrics(SM_CXSCREEN);

	memdc = CreateCompatibleDC(scrdc);
	membit = CreateCompatibleBitmap(scrdc, Width, Height);
	SelectObject(memdc, membit);

	BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)SelectObject(memdc, membit);
	Bitmap bitmap(hBitmap, NULL);
	bitmap.Save(L"Screen.png", &png);
	
	return;
}