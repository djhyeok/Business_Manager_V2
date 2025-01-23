#include "Frame.h"
#include "Emp.h"
#include "Base.h"
#include "Common.h"
#include "RetireEmp.h"
#include "Family.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BusinessManager");
HWND g_hFrameWnd;	//메인 프레임 윈도우 핸들
HWND g_hMDIClient;	//클라이언트 윈도우 핸들
int totB = 0;		//부서갯수
int totP = 0;		//직위갯수
int totR = 0;		//종교갯수
int totEmp = 0;		//전체사원수
int totRetEmp = 0;	//퇴직완료사원수
int totFamily = 0;	//전체사원가족수
BASE* buseo;		//부서
BASE* position;		//직위
BASE* religion;		//종교
EMP* workEmp;		//사원
RETIRE* retireEmp;	//퇴직완료사원
FAMILY* family;		//사원가족

//인사관리 프로그램

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(243, 243, 243));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = MDIWndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	//MDI Frame 윈도우 만듬
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	g_hFrameWnd = hWnd;

	//부서 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitBuseoMDI");
	WndClass.lpfnWndProc = InitBuseoMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//종교 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitRelMDI");
	WndClass.lpfnWndProc = InitReligionMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//직위 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitPosMDI");
	WndClass.lpfnWndProc = InitPositionMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//사원기초정보 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitEMPMDI");
	WndClass.lpfnWndProc = InitEMPMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//퇴직사원 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitRetireEMPMDI");
	WndClass.lpfnWndProc = InitRetireEMPMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//사원 가족사항 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitEMPFamilyMDI");
	WndClass.lpfnWndProc = InitEMPFamilyMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//보고서 MDI윈도우 클래스 등록
	WndClass.lpszClassName = TEXT("InitReportMDI");
	WndClass.lpfnWndProc = InitReportMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//여분의 메모리
	RegisterClass(&WndClass);

	//MDI 메시지 루프
	while (GetMessage(&Message, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(g_hMDIClient, &Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

