#include<iostream>
#include<conio.h>
#include<windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;
typedef long long ll;
ll x, y, num, delay1, delay2;
int main() {
	cout << "ScreenMetrics:(" << GetSystemMetrics(SM_CXSCREEN) << "," << GetSystemMetrics(SM_CYSCREEN) << ")" << endl;
	cout << "Position: x y" << endl;
	cin >> x >> y;
	cout << "Number: n" << endl;
	cin >> num;
	cout << "Interval: t1, Hold: t2	[Min:1 ms]" << endl;
	cin >> delay1 >> delay2;
	if (x < 0 || y < 0 || x > GetSystemMetrics(SM_CXSCREEN) || y > GetSystemMetrics(SM_CYSCREEN) || delay1 < 1 || delay2 < 1) {
		cout << "ERROR!" << endl;
		while (1);
	}
	int cx = x * 65535 / GetSystemMetrics(SM_CXSCREEN);
	int cy = y * 65535 / GetSystemMetrics(SM_CYSCREEN);
	cout << "Time Spend: " << num*(delay1 + delay2) << " ms" << endl;
	while (KEY_DOWN(VK_RETURN));
	cout << "Press Enter to Continue! (Press Space to Exit!)" << endl;
	while (1) {
		if (KEY_DOWN(VK_RETURN)) {
			for (ll i = 1; i <= num; i++) {
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE, cx, cy, 0, 0 );
				Sleep(delay1);
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MOVE, cx, cy, 0, 0 );
				Sleep(delay2);
				if (KEY_DOWN(VK_SPACE))return 0;
			}
			return 0;
		}
		if (KEY_DOWN(VK_SPACE))return 0;
	}
	return 0;
}
