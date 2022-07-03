#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>

using namespace cv;

RECT gameRect;
// Border : 30px For Mouse Positions Only
// Next Level : 916, 42
// Prev Level : 786, 42

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
		std::cout << "Another One" << std::endl;
		return 1;
	}
	return 0;
}

int upgradeHero(Mat img, int y) {

	return 0;

	int x = 90;
	y += 60;
	std::cout << y << std::endl;
	//Vec4f level = img.at<Vec4b>(y, x);
	int wait = 80;
	int upgrade = 0;

	std::cout << "Level : " << x << ", " << y << std::endl;

	SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
	/*
	while (level[0] == 255 && level[1] == 184 && level[2] == 81) {
		upgrade++;
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		waitKey(wait);
		level = img.at<Vec4b>(y, x);
	}
	*/
	return upgrade;
}

int findHero(HWND hwnd, Mat img, int hero) {
	// X : 155 down 48
// Up : 548, 188 Down : 548, 626

	int x = 548;
	int y = 188;
	int wait = 80;

	//Scrools up all the way
	
	for (int i = 0; i < 100; i++) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		waitKey(wait);
	}
	
	// Sets pixel color values
	Vec4f u[5], a[5], gu[5], ga[5];

	u[0] = 109, 154, 163, 255;
	u[1] = 56, 87, 93, 255;
	u[2] = 50, 78, 84, 255;
	u[3] = 24, 44, 49, 255;
	u[4] = 29, 50, 56, 255;

	a[0] = 110, 162, 172, 255;
	a[1] = 58, 101, 110, 255;
	a[2] = 69, 113, 124, 255;
	a[3] = 49, 89, 100, 255;
	a[4] = 60, 102, 113, 255;

	gu[0] = 53, 145, 169, 255;
	gu[1] = 28, 82, 96, 255;
	gu[2] = 34, 76, 86, 255;
	gu[3] = 24, 44, 49, 255;
	gu[4] = 29, 50, 56, 255;

	ga[0] = 54, 153, 178, 255;
	ga[1] = 30, 96, 113, 255;
	ga[2] = 53, 111, 126, 255;
	ga[3] = 49, 89, 100, 255;
	ga[4] = 60, 102, 113, 255;

	x = 155; 
	y = 172;

	Vec4f current;

	Vec4b boxs[4];

	int ids[4];

	int index = 0;

	while (y <= 592 && index < 4) {

		current = img.at<Vec4b>(y, x);

		if (current[0] == u[0] &&[0] && current[0] == u[0][0] && current[0] == u[0][0] && current[0] == u[0][0) {
			std::cout << "Find\n";
			y++;
			current = img.at<Vec4b>(y, x);
			for (int i = 1; i < 48; i++) {
				if (current == u[3]) {
					y++;
				}
				else if (i == 1 && current == u[1]) {
					y++;
				}
				else if (i == 2 && current == u[2]){
					y++;
				}
				else if (i == 3 && current == u[4]) {
					y++;
				}
				else {
					break;
				}
				current = img.at<Vec4b>(y, x);
			}
			// Found a Unavalible Level Up

			std::cout << "Found a Unavalible Level Up\n";

			boxs[index] = current;
			ids[index] = 0;
			index++;
		}

		else  if(current == a[0]) {
			std::cout << "Find\n";
			y++;
			current = img.at<Vec4b>(y, x);
			for (int i = 1; i < 48; i++) {
				if (current == a[3]) {
					y++;
				}
				else if (i == 1 && current == a[1]) {
					y++;
				}
				else if (i == 2 && current == a[2]) {
					y++;
				}
				else if (i == 3 && current == a[4]) {
					y++;
				}
				else {
					break;
				}
				current = img.at<Vec4b>(y, x);
			}
			// Found a Avalible Level Up

			std::cout << "Found a Avalible Level Up\n";

			boxs[index] = current;
			ids[index] = 1;
			index++;
		}

		else  if (current == gu[0]) {
			std::cout << "Find\n";
			y++;
			current = img.at<Vec4b>(y, x);
			for (int i = 1; i < 48; i++) {
				if (current == gu[3]) {
					y++;
				}
				else if (i == 1 && current == gu[1]) {
					y++;
				}
				else if (i == 2 && current == gu[2]) {
					y++;
				}
				else if (i == 3 && current == gu[4]) {
					y++;
				}
				else {
					break;
				}
				current = img.at<Vec4b>(y, x);
			}
			// Found a Gold Unavalible Level Up

			std::cout << "Found a Gold Unavalible Level Up\n";

			boxs[index] = current;
			ids[index] = 2;
			index++;
		}

		else  if (current == ga[0]) {
			std::cout << "Find\n";
			y++;
			current = img.at<Vec4b>(y, x);
			for (int i = 1; i < 48; i++) {
				if (current == ga[3]) {
					y++;
				}
				else if (i == 1 && current == ga[1]) {
					y++;
				}
				else if (i == 2 && current == ga[2]) {
					y++;
				}
				else if (i == 3 && current == ga[4]) {
					y++;
				}
				else {
					break;
				}
				current = img.at<Vec4b>(y, x);
			}
			// Found a Gold Avalible Level Up

			std::cout << "Found a Gold Avalible Level Up\n";

			boxs[index] = current;
			ids[index] = 3;
			index++;
		}
		
		else {
		std::cout << "Nope\n";
		y++;
		}

	}

	std::cout << "Index of Heros : " << index << std::endl;

	return upgradeHero(img, -1);
}

bool bossFight() {
	clickMonster();
	return false;
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
	if (rgba[0] == 0 && rgba[1] == 0 && rgba[2] == 0) {
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
	if (rgba[0] == 0 && rgba[1] == 0 && rgba[2] == 0) {
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

int main() {
	LPCWSTR windowTitle = L"Clicker Heroes";

	HWND hwnd = FindWindow(NULL, windowTitle);
	SetForegroundWindow(hwnd);

	while (!hwnd) {
		system("cls");
		std::cout << "Start" << std::endl;
		Sleep(100);
	}

	GetWindowRect(hwnd, &gameRect);

	int bodyCount = 0;
	int heroUpgrade = 5;
	int timer = 0;
	Mat temp = getMat(hwnd);

	findHero(hwnd, temp, heroUpgrade);
	return 1;

	while (true) {
		Mat img = getMat(hwnd);

		checkAbility(img);

		Vec4f previous = img.at<Vec4b>(550, 787);
		bodyCount += monsterDeath(img, previous);

		//findHero(hwnd, img, heroUpgrade);

		if (timer % 100 == 0) {
			clickMonster();
		}

		if (timer % 1000 == 0 && timer != 0) {
			findFish();
			timer = 0;
		}

		Vec4f boss = img.at<Vec4b>(174, 824);
		if (boss[0] == 151 && boss[1] == 118 && boss[2] == 98) {
			//if (bossFight()) {
				//nextLevel();
			//}
			//else {
				//prevLevel();
				//bodyCount = -200;
			//}
		}

		//if (bodyCount >= 20) {
			//nextLevel();
			//bodyCount = 0;
		//}

		timer++;
		waitKey(100);

		// Stop Button
		if (GetKeyState('B') & 0x8000) {
			return 0;
		}
	}
	return 0;
}