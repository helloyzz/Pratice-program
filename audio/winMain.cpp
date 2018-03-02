
#include "./Capture/audio.h"

#define MYWINX 400
#define MYWINY 150
#define MYWINWIDTH 400
#define MYWINHEIGHT 500

#define MYTOLEFT 20
#define MYTOTOPONE 30
#define MYTOTOPCHANGE 60 

#define BUTTONWIDTH 80
#define BUTTONHEIGHT 30

#define HWNDCOUNT 6

typedef enum {
	BEGIINPLAY, PAUSEPLAY, FINISHPLAY, BEGINRECORD, PAUSERECORD, FINISHRECORD
}wBottonType;

static WCHAR* wcAppName = TEXT("RecordAudio");
static WCHAR* wcCapturePath = TEXT("AudioCapture\\CAP");
static WCHAR* wcCaptureFileType = TEXT(".wav");
static WCHAR* wcRenderPath = TEXT("E:\\AudioCapture\\Example.mp3");

static HWND hwndArray[HWNDCOUNT];
static wavCapture clzCapture;
static audioRender clzRender;
static enumDevice clzEnumDevice;
static HRESULT capHr;
static HRESULT renHr;

void initAudioCapture(const enumDevice& clzEnumDevice) {
	fileManage fm;
	enumDevice ed;
	WCHAR* filePath = NULL;
	WCHAR* deviceName = NULL;

	deviceName = clzEnumDevice.getInDevEnd();
	filePath = fm.getUsePath(wcCapturePath, wcCaptureFileType);
	capHr = clzCapture.initCapture(filePath, deviceName);
}
void initAudioRender(const enumDevice& clzEnumDevice) {
	fileManage fm;
	enumDevice ed;
	WCHAR* deviceName = NULL;

	deviceName = clzEnumDevice.getOutDevStart();
	renHr = clzRender.initRender(wcRenderPath, deviceName);
}
void initContainer() {
	clzEnumDevice.initDevContainer();
	initAudioCapture(clzEnumDevice);
	initAudioRender(clzEnumDevice);
}

void initConsole(void)
{
    AllocConsole();
    freopen("CONIN$", "r+t", stdin);
    freopen("CONOUT$", "w+t", stdout);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	WCHAR* wcButtonText = NULL;
	switch(msg) {
		case WM_CREATE:
			initCom();
			initContainer();
			for(int i=0; i<HWNDCOUNT; i++) {
				switch(i) {
					case 0:
						wcButtonText = TEXT("��ʼ¼��");
						break;
					case 1:
						wcButtonText = TEXT("��ͣ¼��");
						break;
					case 2:
						wcButtonText = TEXT("����¼��");
						break;
					case 3:
						wcButtonText = TEXT("��ʼ����");
						break;
					case 4:
						wcButtonText = TEXT("��ͣ����");
						break;
					case 5:
						wcButtonText = TEXT("��������");
						break;
				}
				hwndArray[i] = CreateWindow(TEXT("button"), wcButtonText, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
				MYTOLEFT, MYTOTOPONE+i*MYTOTOPCHANGE, BUTTONWIDTH, BUTTONHEIGHT, hwnd, (HMENU)i, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
			}
			break;
		case WM_DESTROY:
			releaseCom();
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			if(wParam==0 && !capHr) {
				clzCapture.startCapture();
				capHr = 1;
			} else if(wParam==1 && capHr) {
				clzCapture.pauseCapture();
				capHr = 0;
			}  else if(wParam==2) {
				clzCapture.stopCapture();
				initAudioCapture(clzEnumDevice);
			} else if(wParam==3 && !renHr) {
				clzRender.startRender();
				renHr = 1;
			} else if(wParam==4 && renHr) {
				clzRender.pauseRender();
				renHr = 0;
			} else if(wParam==5) {
				clzRender.stopRender();
				initAudioRender(clzEnumDevice);
			}
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

ATOM initWindowClass(HINSTANCE histance) {
	WNDCLASS wndc;
	wndc.style = CS_HREDRAW | CS_VREDRAW;
	wndc.hInstance = histance;
	wndc.cbClsExtra = 0;
	wndc.cbWndExtra = 0;
	wndc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndc.lpfnWndProc = WndProc;
	wndc.lpszMenuName = NULL;
	wndc.lpszClassName = wcAppName;
	wndc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	return RegisterClass(&wndc);
}
BOOL createWindow(HINSTANCE hinstance, int nCmdShow) {
	HWND hwnd;
	BOOL res = FALSE;
	hwnd = CreateWindow(wcAppName, TEXT("HELLO"), WS_OVERLAPPEDWINDOW, 
		MYWINX, MYWINY, MYWINWIDTH, MYWINHEIGHT, NULL, NULL, hinstance, NULL);
	if(hwnd) {
		res = TRUE;
		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);
	}
	return res;
}
/*

*/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int res = 0;
	BOOL gotMessage = 0;
	MSG msg;
	if(!initWindowClass(hinstance)) {
		res = 1;
	}
	if(!createWindow(hinstance, nCmdShow)) {
		res = 1;
	}
	if(!res) {
		while((gotMessage = GetMessage(&msg, NULL, 0, 0)) && gotMessage!=-1) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
} 

