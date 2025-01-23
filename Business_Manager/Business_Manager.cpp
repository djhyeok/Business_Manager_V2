#include "Frame.h"
#include "Emp.h"
#include "Base.h"
#include "Common.h"
#include "RetireEmp.h"
#include "Family.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BusinessManager");
HWND g_hFrameWnd;	//���� ������ ������ �ڵ�
HWND g_hMDIClient;	//Ŭ���̾�Ʈ ������ �ڵ�
int totB = 0;		//�μ�����
int totP = 0;		//��������
int totR = 0;		//��������
int totEmp = 0;		//��ü�����
int totRetEmp = 0;	//�����Ϸ�����
int totFamily = 0;	//��ü���������
BASE* buseo;		//�μ�
BASE* position;		//����
BASE* religion;		//����
EMP* workEmp;		//���
RETIRE* retireEmp;	//�����Ϸ���
FAMILY* family;		//�������

//�λ���� ���α׷�

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

	//MDI Frame ������ ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	g_hFrameWnd = hWnd;

	//�μ� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitBuseoMDI");
	WndClass.lpfnWndProc = InitBuseoMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//���� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitRelMDI");
	WndClass.lpfnWndProc = InitReligionMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//���� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitPosMDI");
	WndClass.lpfnWndProc = InitPositionMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//����������� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitEMPMDI");
	WndClass.lpfnWndProc = InitEMPMDIProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//������� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitRetireEMPMDI");
	WndClass.lpfnWndProc = InitRetireEMPMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//��� �������� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitEMPFamilyMDI");
	WndClass.lpfnWndProc = InitEMPFamilyMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//���� MDI������ Ŭ���� ���
	WndClass.lpszClassName = TEXT("InitReportMDI");
	WndClass.lpfnWndProc = InitReportMDIPROC;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);	//������ �޸�
	RegisterClass(&WndClass);

	//MDI �޽��� ����
	while (GetMessage(&Message, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(g_hMDIClient, &Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

