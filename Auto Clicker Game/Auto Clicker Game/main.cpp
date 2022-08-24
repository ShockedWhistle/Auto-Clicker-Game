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

void ascend() {
	int x = 1114;
	int y = 246;
	SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
	waitKey(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);

	x = 490;
	y = 480;
	SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
	waitKey(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
}

void turnOnProgresssion(HWND hwnd) {
	int x = 1114;
	int y = 200;

	SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
	waitKey(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);

	Mat img = getMat(hwnd);
	Vec4f color = img.at<Vec4b>(y, x);

	if (color[0] == 0 && color[1] == 0 && color[3] == 255) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30); // Start
		waitKey(20);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	}
}

bool monsterDeath(Mat img, Vec4f previous) {
	//787, 582
	Vec4f rgba = img.at<Vec4b>(550, 787); // 550, 787  :  60, 60. 61, 255 
	// Death 51, 51, 51, 255
	//cout << rgba << "  :  " << death << endl;
	//if (previous[0] == 51) {
		//return false;
	//}
	if (rgba[0] == 51 && rgba[1] == 51 && rgba[2] == 51) {
		//std::cout << "Another One" << std::endl;
		return true;
		waitKey(1);
	}
	return false;
}

int clickMonsterFish(HWND hwnd, Mat img) {
	int curX = 580; // 580
	int curY = 180; // 130
	int wait = 80;
	int pixelStep = 20;
	Vec4f rgba = img.at<Vec4b>(550, 787);
	int bodyCount = 0;

	// left
	while (curY != 660) { // Left of abilities
		SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
		curY += pixelStep;
		waitKey(wait);
		img = getMat(hwnd);
		if (monsterDeath(img, rgba)) {
			bodyCount++;
		}
		rgba = img.at<Vec4b>(550, 787);
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
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
		}
		curY += pixelStep;
		while (curX > 660) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
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
		img = getMat(hwnd);
		if (monsterDeath(img, rgba)) {
			bodyCount++;
		}
		rgba = img.at<Vec4b>(550, 787);
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
		img = getMat(hwnd);
		if (monsterDeath(img, rgba)) {
			bodyCount++;
		}
		rgba = img.at<Vec4b>(550, 787);
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
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
		}
		curY += pixelStep;
		while (curX > 660) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
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
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
		}
		curY += pixelStep;
		while (curX > 940) {
			SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
			mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top, 0, 0);
			curX -= pixelStep;
			waitKey(wait);
			img = getMat(hwnd);
			if (monsterDeath(img, rgba)) {
				bodyCount++;
			}
			rgba = img.at<Vec4b>(550, 787);
		}
		curY += pixelStep;
	}
	return bodyCount;
}

int clickMonster(HWND hwnd, Mat img) {
	int curX = 1000;
	int curY = 400;
	int wait = 80;
	Vec4f rgba = img.at<Vec4b>(550, 787);
	int bodyCount = 0;

	// Top Left
	int timer = 0;
	while (timer < 100 && bodyCount < 4) {
		img = getMat(hwnd);
		if (monsterDeath(img, rgba)) {
			bodyCount++;
		}
		waitKey(wait);
		rgba = img.at<Vec4b>(550, 787);
		SetCursorPos(curX + gameRect.left, curY + gameRect.top); // Start
		mouse_event(MOUSEEVENTF_LEFTDOWN, curX + gameRect.left, curY + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, curX + gameRect.left, curY + gameRect.top + 30, 0, 0);
		img = getMat(hwnd);
		if (monsterDeath(img, rgba)) {
			bodyCount++;
		}
		rgba = img.at<Vec4b>(550, 787);
		timer++;
	}

	return bodyCount;
}

int upgradeHero(HWND hwnd, Mat img, int y) {
	img = getMat(hwnd);
	int x = 155;
	y -= 1;

	int wait = 4;
	int upgrade = 0;
	Vec4f av = { 49, 89, 100, 0 };
	waitKey(wait);
	Vec4f current = img.at<Vec4b>(y, x);

	std::cout << current << "\n";
	if (current != av) {
		for (int i = 0; i < 100; i++) {
			current = img.at<Vec4b>(y-i, x);
			if (current == av) {
				i = 100;
				break;
			}
		}
		if (current != av) {
			y += 100;
			for (int i = 0; i < 30; i++) {
				current = img.at<Vec4b>(y + i, x);
				if (current == av) {
					break;
				}
			}
		}
	}

	while (current == av) { // av[0] - 5 <= current[0] <= av[0] + 5 || av2[0] - 5 <= current[0] <= av2[0] + 5 || av3[0] - 5 <= current[0] <= av3[0] + 5 || current[0] <= av4[0] + 5 || av5[0] - 5 <= current[0] <= av5[0] + 5 || av6[0] - 5 <= current[0] <= av6[0] + 5
		upgrade++;
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		//SetCursorPos(x + 100 + gameRect.left, y + gameRect.top + 30);
		waitKey(wait);
		img = getMat(hwnd);
		current = img.at<Vec4b>(y, x);
	}
	std::cout << "Upgrade : " << upgrade << "\n";
	return upgrade;
}

void buyAbility(int y, int hero) {
	y += 36;
	int x = 190; // 36 apart 7 max
	int xJump = 36;
	int wait = 2;

	if (hero != 20) {
		for (int i = 0; i < 7; i++) {
			SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
			mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			waitKey(wait);
			x += xJump;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
			mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
			waitKey(wait);
			x += xJump;
		}
		x = 900;
		y = 110;
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	}
	return;
}

int findHero(HWND hwnd, Mat img, int hero) {
	int x = 548;
	int y = 240;
	int wait = 80;

	//Scrools up all the way
	waitKey(wait);
	waitKey(wait);
	SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
	waitKey(wait);

	x = 548;
	y = 188;

	for (int i = 0; i < 6; i++) {
		SetCursorPos(x + gameRect.left, y + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x + gameRect.left, y + gameRect.top + 30, 0, 0);
		waitKey(wait);
	}
	
	img = getMat(hwnd);

	Vec4f av = {49, 89, 100, 0};
	Vec4f un = { 24, 44, 49, 0 };


	x = 155; 
	y = 172;

	Vec4f current;

	int index = 0;
	int yJump = 100;

	if (hero <= 4) {
		while (y <= 592) {
			current = img.at<Vec4b>(y, x);
			if (current == av || current == un) {
				y++;
				current = img.at<Vec4b>(y, x);
				if (current == av || current == un) {
					if (current == av || current == un) {
						std::cout << "Found New " << y << " Index : " << index << "\n";
						index++;
						if (index == hero) {
							return y;
						}
						y += yJump;
					}
					else {
						y++;
					}
				}
				else {
					y += 2;
				}
			}
			else {
				y++;
			}
		}
		return -1;
	}
	int prev = 0;
	bool isNew = false;

	index = 4;

	while (index != hero) {
		img = getMat(hwnd);

		int temp = 0;
		int oldBot = 640;
		int bottom = 0;
		int second = 0;
		y = 172;
		while (y < 636) {
			current = img.at<Vec4b>(y, x);
			if (current == av || current == un) {
				y++;
				current = img.at<Vec4b>(y, x);
				if (current == av || current == un) {
					if (current == av || current == un) {
						temp++;
						second = bottom;
						bottom = y;
						//std::cout << "Found New " << y << " Index : " << index << "\n";
						y += yJump;
					}
					else {
						y++;
					}
				}
				else {
					y += 2;
				}
			}
			else {
				y++;
			}
		}

		if (isNew && bottom <= 590) {
			index++;
			isNew = false;
			std::cout << "Is New and bottom >= 590.\n";
			if (index == hero) {
				return bottom;
			}
		}
		else if (bottom <= 590 && prev == 4) {
			index++;
			isNew = false;
			std::cout << "Bottom and Old Bottom >= 590.\n";
			if (index == hero) {
				return bottom;
			}
		}
		else if (isNew && bottom > 590) {
			index++;
			isNew = false;
			std::cout << "Is New and bottom >= 590.\n";
			if (index == hero) {
				return second;
			}
		}
		else if (index == 20 && oldBot < bottom < 590) {
			index++;
			isNew = false;
			std::cout << "Given up.\n";
			if (index == hero) {
				return bottom;
			}
		}
		else if (index == 12) {
			index++;
			isNew = false;
			std::cout << "Given up.\n";
			if (index == hero) {
				return bottom;
			}
		}
		
		if (temp <= 4 && bottom <= 476) {
			std::cout << "Bottom is above 590\n";
			return 0;
		}

		if (bottom > 590) {
			std::cout << "Bottom is above 590\n";
			isNew = true;
		}

		prev = temp;
		oldBot = bottom;
		if (GetKeyState('B') & 0x8000) {
			return 0;
		}

		SetCursorPos(548 + gameRect.left, 622 + gameRect.top + 30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 548 + gameRect.left, 622 + gameRect.top + 30, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 548 + gameRect.left, 622 + gameRect.top + 30, 0, 0);
		waitKey(wait);
		waitKey(wait);
		waitKey(wait);
		waitKey(wait);
		//std::cout << index << " : Scrool\n\n\n";
	}

	return -1;
}

bool checkBoss(HWND hwnd, Mat img) {
	// Check if boss fight;
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
	int killsNeeded = 10;
	int heroUpgrade = 9;
	int upgrades = 0;
	int heroY = 0;
	int timer = 0;
	int fail = 0;
	Mat temp = getMat(hwnd);

	std::cout << "Find Hero : " << heroUpgrade << "\n";
	Mat img = getMat(hwnd);

	int x = 1114;
	int y = 200;
	Vec4f color = img.at<Vec4b>(y, x);
	turnOnProgresssion(hwnd);
	// Main Loop
	bool isOn;
	isOn = true;
	bool isProgressing = true;
	while (isOn) {
		heroUpgrade++;
		heroY = findHero(hwnd, img, heroUpgrade);
		if (heroY <= 0) {
			std::cout << "Levels : " << upgrades << "\n";
			if (heroUpgrade >= 20 && upgrades < 100) {
				ascend();
				heroUpgrade = 0;
				bodyCount = 0;
				timer = 0;
				upgrades = 0;
				isProgressing = false;
			}
			heroUpgrade = 1;
			heroY = findHero(hwnd, img, heroUpgrade);
		}
		img = getMat(hwnd);
		buyAbility(heroY, heroUpgrade);

		upgrades += upgradeHero(hwnd, img, heroY);
		buyAbility(heroY, heroUpgrade);
		bodyCount += clickMonster(hwnd, img);


		checkAbility(img);

		// Level stuff
		color = img.at<Vec4b>(y, x);
		if (color[0] == 0 && color[1] == 0 && color[3] == 255) {
			bodyCount = 0;
			isProgressing = false;
		}
		if (!isProgressing && bodyCount >= 10) {
			bodyCount = 0;
			turnOnProgresssion(hwnd);
		}

		/*
		if (bodyCount >= killsNeeded && !isProgressing) {
			nextLevel();
			bodyCount = 0;
			if (checkBoss(hwnd, img)) {
				bodyCount += clickMonster(hwnd, img);
				bodyCount += clickMonster(hwnd, img);
				if (bodyCount >= 1) {
					nextLevel();
					bodyCount = 0;
				}
				else {
					prevLevel();
					bodyCount = -20;
					killsNeeded += 10;
				}
			}
		}
		*/

		// Stop Button
		for (int i = 0; i < 50; i++) {
			if (GetKeyState('B') & 0x8000) {
				isOn = false;
			}
			else {
				waitKey(2);
			}
		}

		// Timer
		if (timer == 999) {
			timer = 1;
		}
		else {
			timer++;
		}
	}


	std::cout << "Done\n";

	return 1;
}