#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

RECT gameRect;
// Border : 30px For Mouse Positions Only
// Next Level : 916, 42
// Prev Level : 786, 42

void clickMonster() {
	int curX = 580; // 580
	int curY = 180; // 130
	int wait = 80;
	int pixelStep = 20;

	// left
	while (curY != 660) { // Left of abilities
		SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
		curY += pixelStep;
		waitKey(wait);
	}

	curX = 660; // 580
	curY = 180; // 130
	
	// Main
	while (curY < 570) {
		while (curX < 1050) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX += pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
		while (curX > 660) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
	}

	curX = 1060; // 580
	curY = 180; // 130

	// Top Left
	while (curY != 360) {
		SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
		curY += pixelStep;
		waitKey(wait);
	}
	
	curX = 1060; // 580
	curY = 420; // 130
	// Bottom Left
	while (curY != 600) {
		SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
		curY += pixelStep;
		waitKey(wait);
	}
	
	curX = 660; // 580
	curY = 570; // 130
	
	// Bottom
	while (curY < 640) {
		while (curX < 780) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX += pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
		while (curX > 660) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
	}

	curX = 940; // 580
	curY = 570; // 130

	// Bottom
	while (curY < 660) {
		while (curX < 1030) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX += pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
		while (curX > 940) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
		}
		curY += pixelStep;
	}
}

int monsterDeath(Mat img, Vec4f previous) {
	//787, 582
	Vec4f rgba = img.at<Vec4b>(550, 787); // 550, 787  :  60, 60. 61, 255 
	// Death 51, 51, 51, 255
	//cout << rgba << "  :  " << death << endl;
	if (previous[0] == 51) {
		return 0;
	}
	if (rgba[0] == 51 && rgba[1] == 51 && rgba[2] == 51) {
		cout << "Another One" << endl;
		return 1;
	}
	return 0;
}

bool bossFight() {
	clickMonster();
	return false;
}

void nextLevel() {
	SetCursorPos(916 + gameRect.left, 42 + gameRect.top + 30); // Start
	waitKey(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 916 + gameRect.left, 42 + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 916 + gameRect.left, 42 + gameRect.top + 30, 0, 0);
}

void prevLevel() {
	SetCursorPos(786 + gameRect.left, 42 + gameRect.top + 30); // Start
	waitKey(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 786 + gameRect.left, 42 + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 786 + gameRect.left, 42 + gameRect.top + 30, 0, 0);
}

void checkAbility(Mat img) {
	int x = 607;
	int y = 168;
	Vec4f rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 219 && rgba[1] == 255 && rgba[2] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 220;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 100 && rgba[1] == 100 && rgba[2] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 272;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 165 && rgba[1] == 172 && rgba[2] == 173) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 324;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 219 && rgba[1] == 255 && rgba[2] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 375;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 0 && rgba[1] == 191 && rgba[2] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 426;
	rgba = img.at<Vec4b>(y, x);
	cout << "6 : " << rgba << endl;
	if (rgba[0] == 90 && rgba[1] == 226 && rgba[2] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 479;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 190 && rgba[1] == 180 && rgba[2] == 252) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 531;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 229 && rgba[1] == 234 && rgba[2] == 165) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}

	y = 583;
	rgba = img.at<Vec4b>(y, x);
	if (rgba[0] == 60 && rgba[1] == 60 && rgba[2] == 242) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top, 0, 0);
	}



}

void findFish() {
	int x = 112;
	int y = 100;
	int pixelStep = 20;
	int wait = 40;

	SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
	waitKey(5);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);

	// Menue
	y = 130;
	while (y < 640) { 
		x = 10;
		while (x < 562) {
			SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			x += pixelStep;
			waitKey(wait);
		}
		y += pixelStep;
	}

	// Money
	y = 0;
	while (y < 80) {
		x = 10;
		while (x < 640) {
			SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			x += pixelStep;
			waitKey(wait);
		}
		y += pixelStep;
	}

	x = 44;
	y = 100;

	SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
	waitKey(5);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
}

Mat getMat(HWND hwnd) {
	HDC deviceContext = GetDC(hwnd);
	HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	int height = windowRect.bottom;
	int width = windowRect.right;

	HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

	SelectObject(memoryDeviceContext, bitmap);

	// Copy data into bitmap
	BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);

	// Spesify format by using bitmapinfoheader
	BITMAPINFOHEADER bi;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0; // No compression
	bi.biXPelsPerMeter = 1;
	bi.biYPelsPerMeter = 2;
	bi.biClrUsed = 3;
	bi.biClrImportant = 4;

	Mat mat = Mat(height, width, CV_8UC4); // 8 bit unsigned ints 4 channels -> RGBA

	// Transform data and store into mat.data
	GetDIBits(memoryDeviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	// Clean up
	DeleteObject(bitmap);
	DeleteDC(memoryDeviceContext);
	ReleaseDC(hwnd, deviceContext);

	return mat;
}

int main() {
	LPCWSTR windowTitle = L"Clicker Heroes";

	HWND hwnd = FindWindow(NULL, windowTitle);
	SetForegroundWindow(hwnd);

	while (!hwnd) {
		system("cls");
		cout << "Start" << endl;
		Sleep(100);
	}

	GetWindowRect(hwnd, &gameRect);

	int bodyCount = 0;
	int timer = 0;
	while (true) {
		Mat img = getMat(hwnd);

		checkAbility(img);

		Vec4f previous = img.at<Vec4b>(550, 787);
		bodyCount += monsterDeath(img, previous);

		if (timer % 100 == 0) {
			clickMonster();
		}

		if (timer % 500 == 0 && timer != 0) {
			findFish();
			timer = 0;
		}

		Vec4f boss = img.at<Vec4b>(174, 824);
		if (boss[0] == 151 && boss[1] == 118 && boss[2] == 98) {
			if (bossFight()) {
				nextLevel();
			}
			else {
				prevLevel();
				bodyCount = -200;
			}
		}

		if (bodyCount >= 20) {
			nextLevel();
			bodyCount = 0;
		}

		timer++;
		waitKey(100);

		// Stop Button
		if (GetKeyState('B') & 0x8000) {
			return 0;
		}
	}
	return 0;
}