#include "Frame.h"

#define IDM_WINDOWCHILD 8000

extern HINSTANCE g_hInst;
extern HWND g_hMDIClient;	//클라이언트 윈도우 핸들
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교

LRESULT CALLBACK MDIWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	CLIENTCREATESTRUCT ccs;
	MDICREATESTRUCT mcs;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControls();
		//MDI Client 윈도우 만듬
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = IDM_WINDOWCHILD;
		g_hMDIClient = CreateWindow(TEXT("MDIClient"), NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)NULL, g_hInst, (LPSTR)&ccs);
		ShowWindow(g_hMDIClient, SW_SHOW);

		//DB에서 totB,totR,totP,buseo,religion,position 에 데이터 받아옴(select)
		DBConnect();

		totB = CountRecord((LPSTR)"BUSEO");
		BaseSelectSQL((LPSTR)"BUSEO");
		totR = CountRecord((LPSTR)"RELIGION");
		BaseSelectSQL((LPSTR)"RELIGION");
		totP = CountRecord((LPSTR)"POSITION");
		BaseSelectSQL((LPSTR)"POSITION");

		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			//새 MDI 윈도우 만듬
		case IDM_BUSEO:		//기초정보관리(메뉴바)->부서
			mcs.szClass = TEXT("InitBuseoMDI");
			mcs.szTitle = TEXT("부서");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_POSITION:	//기초정보관리(메뉴바)->직위
			mcs.szClass = TEXT("InitPosMDI");
			mcs.szTitle = TEXT("직위");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_RELIGION:	//기초정보관리(메뉴바)->종교
			mcs.szClass = TEXT("InitRelMDI");
			mcs.szTitle = TEXT("종교");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case ID_EMP:
			mcs.szClass = TEXT("InitEMPMDI");
			mcs.szTitle = TEXT("사원");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case ID_RETIRE:
			mcs.szClass = TEXT("InitRetireEMPMDI");
			mcs.szTitle = TEXT("퇴직자");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case ID_FAMILY:
			mcs.szClass = TEXT("InitEMPFamilyMDI");
			mcs.szTitle = TEXT("가족사항");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case ID_REPORT:
			mcs.szClass = TEXT("InitReportMDI");
			mcs.szTitle = TEXT("보고서");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		//할당된 부서,직위,종교,사원,퇴직사원 free
		free(buseo);
		free(position);
		free(religion);

		return 0;
	}
	return(DefFrameProc(hWnd, g_hMDIClient, iMessage, wParam, lParam));
}
