#include "Report.h"

extern HINSTANCE g_hInst;
extern int totEmp;
extern EMP* workEmp;

HWND hReportEmpLV, hReportFamilyLV, hSearchOption, hSearch, hSearchBtn, hSelectBuseo, hSelectPos
, hMaleCheck, hFemaleCheck, hWorkCheck, hRetireCheck;

enum {
	ID_REPORTEMPLV = 1, ID_REPORTFAMLV, ID_SEARCHCOMBO, ID_SEARCH, ID_SEARCHBTN, ID_SELECTBUSEO, ID_SELECTPOS
	, ID_MALECHECK, ID_FEMALECHECK, ID_WORKCHECK, ID_RETIRECHECK
};


LRESULT CALLBACK InitReportMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HFONT hFont, OldFont;
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	HBRUSH MyBrush, OldBrush;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	TCHAR str[255];
	int i;
	TCHAR option[][50] = { TEXT("사원번호"),TEXT("이름"),TEXT("부서"),TEXT("직책"),TEXT("입사년도") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		//리스트뷰 생성
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 120, 700, 600, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		hReportFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 830, 120, 500, 600, hWnd, (HMENU)ID_REPORTFAMLV, g_hInst, NULL);

		//사원리스트뷰 헤더 추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("사번");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("사원명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("부서");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("직책");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportEmpLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("연락처");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportEmpLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("성별");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("퇴직");
		COL.iSubItem = 6;
		ListView_InsertColumn(hReportEmpLV, 6, &COL);

		//가족사항 리스트뷰 헤더 추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportFamilyLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("사원명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportFamilyLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("이름");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportFamilyLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("나이");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportFamilyLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("관계");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportFamilyLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("직업");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportFamilyLV, 5, &COL);

		//검색옵션 콤보박스
		hSearchOption = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			150, 65, 120, 250, hWnd, (HMENU)ID_SEARCHCOMBO, g_hInst, NULL);
		for (i = 0; i < 5; i++) {
			SendMessage(hSearchOption, CB_ADDSTRING, 0, (LPARAM)option[i]);
		}
		//검색 에디트박스
		hSearch = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			275, 65, 245, 23, hWnd, (HMENU)ID_SEARCH, g_hInst, NULL);
		//부서 선택콤보박스
		hSelectBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			310, 5, 70, 250, hWnd, (HMENU)ID_SELECTBUSEO, g_hInst, NULL);
		//직책 선택콤보박스
		hSelectPos = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			445, 5, 70, 250, hWnd, (HMENU)ID_SELECTPOS, g_hInst, NULL);
		//남자 체크박스
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("남"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 280, 35, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//여자 체크박스
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("여"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 335, 35, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//재직 체크박스
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("재직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 390, 35, 75, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//퇴직 체크박스
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("퇴직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 465, 35, 75, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);

		//사번검색 버튼
		hSearchBtn = CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			525, 63, 50, 25, hWnd, (HMENU)ID_SEARCHBTN, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 275, 7, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 400, 9, TEXT("직책"), lstrlen(TEXT("직책")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}