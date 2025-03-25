#include "Report.h"

extern HINSTANCE g_hInst;
extern int totEmp;
extern EMP* workEmp;

HWND hReportEmpLV, hReportFamilyLV, hReportRetireLV, hSearchOption, hSearch, hSearchBtn, hSelectBuseo, hSelectPos
, hMaleCheck, hFemaleCheck, hWorkCheck, hRetireCheck, hRetireReqCheck, hRefreshBtn;

enum {
	ID_REPORTEMPLV = 1, ID_REPORTFAMLV, ID_REPORTRETIRE, ID_SEARCHCOMBO, ID_SEARCH, ID_SEARCHBTN, ID_SELECTBUSEO, ID_SELECTPOS
	, ID_MALECHECK, ID_FEMALECHECK, ID_WORKCHECK, ID_RETIRECHECK, ID_RETIREREQCHECK, ID_REFRESH
};


LRESULT CALLBACK InitReportMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HFONT hFont, OldFont;
	LVCOLUMN COL;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	TCHAR str[255], str2[255];
	EMP tempEmp;
	int i;
	TCHAR option[3][50] = { TEXT("사원번호"),TEXT("이름"),TEXT("입사년도") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		//리스트뷰 생성
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 120, 700, 500, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportEmpLV, LVS_EX_FULLROWSELECT);
		hReportFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 830, 120, 500, 600, hWnd, (HMENU)ID_REPORTFAMLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportFamilyLV, LVS_EX_FULLROWSELECT);
		hReportRetireLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 640, 700, 80, hWnd, (HMENU)ID_REPORTRETIRE, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportRetireLV, LVS_EX_FULLROWSELECT);

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
		COL.cx = 40;
		COL.pszText = (LPSTR)TEXT("성별");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
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

		//퇴직정보 리스트뷰 헤더 추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 160;
		COL.pszText = (LPSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportRetireLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 110;
		COL.pszText = (LPSTR)TEXT("사원명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportRetireLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("퇴직당시부서");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportRetireLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("직책");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportRetireLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 110;
		COL.pszText = (LPSTR)TEXT("연락처");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportRetireLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 90;
		COL.pszText = (LPSTR)TEXT("퇴직사유");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportRetireLV, 5, &COL);

		//검색옵션 콤보박스
		hSearchOption = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			150, 65, 120, 250, hWnd, (HMENU)ID_SEARCHCOMBO, g_hInst, NULL);
		for (i = 0; i < 3; i++) {
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
		DBConnect();
		InitCombo((LPSTR)"BUSEO", hSelectBuseo);
		InitCombo((LPSTR)"POSITION", hSelectPos);
		DBDisconnect();
		//남자 체크박스
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("남"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 280, 35, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//여자 체크박스
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("여"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 335, 35, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//재직 체크박스
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("재직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 390, 35, 55, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//퇴직 체크박스
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("퇴직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 445, 35, 55, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);
		//퇴직요청 체크박스
		hRetireReqCheck = CreateWindow(TEXT("button"), TEXT("퇴직요청"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 505, 35, 100, 25, hWnd, (HMENU)ID_RETIREREQCHECK, g_hInst, NULL);
		//사번검색 버튼
		hSearchBtn = CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			525, 63, 50, 25, hWnd, (HMENU)ID_SEARCHBTN, g_hInst, NULL);
		//새로고침 버튼
		hRefreshBtn = CreateWindow(TEXT("button"), TEXT("새로고침"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			585, 63, 70, 25, hWnd, (HMENU)ID_REFRESH, g_hInst, NULL);
		lstrcpy(tempEmp.empNo, "");
		lstrcpy(tempEmp.empBuseo, "");
		lstrcpy(tempEmp.empPosCode, "");
		tempEmp.empRetire = -1;
		tempEmp.pInfo.pSex = -1;
		lstrcpy(tempEmp.pInfo.pName[0], "");
		DBConnect();
		SelectReport((LPSTR)"", tempEmp);
		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_REFRESH:

			SetWindowText(hSearch, TEXT(""));
			SendMessage(hMaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hFemaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hRetireReqCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hSearchOption, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hSelectBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hSelectPos, CB_SETCURSEL, (WPARAM)-1, 0);
			//tempEmp 초기화 후 ListView에 select해서 뿌림
			lstrcpy(tempEmp.empNo, "");
			lstrcpy(tempEmp.empBuseo, "");
			lstrcpy(tempEmp.empPosCode, "");
			tempEmp.empRetire = -1;
			tempEmp.pInfo.pSex = -1;
			lstrcpy(tempEmp.pInfo.pName[0], "");
			ListView_DeleteAllItems(hReportEmpLV);
			ListView_DeleteAllItems(hReportRetireLV);
			ListView_DeleteAllItems(hReportFamilyLV);
			DBConnect();
			SelectReport((LPSTR)"", tempEmp);
			DBDisconnect();
			break;
		case ID_MALECHECK:	//남 체크박스 체크,해제
			if (SendMessage(hMaleCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hMaleCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hMaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_FEMALECHECK:	//여 체크박스 체크,해제
			if (SendMessage(hFemaleCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hMaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_WORKCHECK:		//재직 체크박스 체크,해제
			if (SendMessage(hWorkCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hWorkCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hRetireReqCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hRetireReqCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_RETIRECHECK:	//퇴직 체크박스 체크,해제
			if (SendMessage(hRetireCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hRetireReqCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hRetireReqCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_RETIREREQCHECK:	//퇴직요청 체크박스 체크,해제
			if (SendMessage(hRetireReqCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hRetireReqCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_SEARCHBTN:
			//상세검색옵션에서 값 가져옴
			i = SendMessage(hSelectBuseo, CB_GETCURSEL, 0, 0);
			if (i == -1) {
				lstrcpy(tempEmp.empBuseo, "");
			}
			else {
				DBConnect();
				SendMessage(hSelectBuseo, CB_GETLBTEXT, i, (LPARAM)tempEmp.empBuseo);
				DBDisconnect();
			}

			i = SendMessage(hSelectPos, CB_GETCURSEL, 0, 0);
			if (i == -1) {
				lstrcpy(tempEmp.empPosCode, "");
			}
			else {
				DBConnect();
				SendMessage(hSelectPos, CB_GETLBTEXT, i, (LPARAM)tempEmp.empPosCode);
				DBDisconnect();
			}

			if (SendMessage(hMaleCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pSex = 1;
			}
			else if (SendMessage(hFemaleCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pSex = 0;
			}
			else {
				tempEmp.pInfo.pSex = -1;
			}

			if (SendMessage(hRetireCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.empRetire = 2;
			}
			else if (SendMessage(hWorkCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.empRetire = 0;
			}
			else if (SendMessage(hRetireReqCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.empRetire = 1;
			}
			else {
				tempEmp.empRetire = -1;
			}

			i = SendMessage(hSearchOption, CB_GETCURSEL, 0, 0);
			if (i == 0) {			//사원번호
				GetWindowText(hSearch, tempEmp.empNo, 12);
				lstrcpy(tempEmp.pInfo.pName[0], "");
				lstrcpy(str, "");
			}
			else if (i == 1) {		//이름
				GetWindowText(hSearch, tempEmp.pInfo.pName[0], 20);
				lstrcpy(tempEmp.empNo, "");
				lstrcpy(str, "");
			}
			else if (i == 2) {		//입사년도
				lstrcpy(tempEmp.empNo, "");
				lstrcpy(tempEmp.pInfo.pName[0], "");
				GetWindowText(hSearch, str, 20);
			}
			else {
				lstrcpy(tempEmp.empNo, "");
				lstrcpy(tempEmp.pInfo.pName[0], "");
				lstrcpy(str, "");
			}
			DBConnect();
			SelectReport(str, tempEmp);
			DBDisconnect();

			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//부서리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
		if (hdr->hwndFrom == hReportEmpLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//퇴직자인지 확인 후 퇴직정보 ListView에 뿌림
					ListView_GetItemText(hReportEmpLV, nlv->iItem, 6, str, 20);
					if (lstrcmp("퇴직", str) == 0) {
						ListView_GetItemText(hReportEmpLV, nlv->iItem, 0, str, 20);
						DBConnect();
						SelectRetire(str);
						DBDisconnect();
					}
					else {
						ListView_DeleteAllItems(hReportRetireLV);
					}
					ListView_GetItemText(hReportEmpLV, nlv->iItem, 0, str, 20);
					ListView_GetItemText(hReportEmpLV, nlv->iItem, 1, str2, 20);
					DBConnect();
					SelectFamily(str, str2);
					DBDisconnect();
				}
				return TRUE;
			}
		}
		break;
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