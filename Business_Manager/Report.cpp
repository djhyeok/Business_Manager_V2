#include "Report.h"

extern HINSTANCE g_hInst;
extern int totEmp;
extern EMP* workEmp;

HWND hReportEmpLV, hOptionCombo, hSearchEdit, hMaleCheck, hFemaleCheck, hWorkCheck, hRetireCheck, hMoveCheck;
enum { ID_REPORTEMPLV = 1, ID_OPTIONCOMBO, ID_SEARCHEDIT, ID_SEARCHBT, ID_MALECHECK, ID_FEMALECHECK, ID_WORKCHECK, ID_RETIRECHECK, ID_MOVECHECK };

LRESULT CALLBACK InitReportMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	TCHAR searchOption[4][255] = { TEXT("이름"),TEXT("직책"),TEXT("부서"),TEXT("사번") };
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	HBRUSH MyBrush, OldBrush;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int i, j, ind;
	BOOL m, fm, w, r, mv;
	TCHAR str[255];

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		//리스트뷰 생성
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 100, 140, 700, 500, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		//리스트뷰 헤더 추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("사번");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("사원명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPWSTR)TEXT("부서");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("직책");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportEmpLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 180;
		COL.pszText = (LPWSTR)TEXT("연락처");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportEmpLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("성별");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);
		for (i = 0; i < totEmp; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = workEmp[i].empNo;
			ListView_InsertItem(hReportEmpLV, &LI);											//사번
			ListView_SetItemText(hReportEmpLV, i, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
			ListView_SetItemText(hReportEmpLV, i, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
			ListView_SetItemText(hReportEmpLV, i, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
			ListView_SetItemText(hReportEmpLV, i, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
			if (workEmp[i].pInfo.pSex == TRUE) {
				ListView_SetItemText(hReportEmpLV, i, 5, (LPWSTR)TEXT("남"));				//남
			}
			else {
				ListView_SetItemText(hReportEmpLV, i, 5, (LPWSTR)TEXT("여"));				//여
			}
		}

		//검색옵션 콤보박스
		hOptionCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 130, 55, 150, 200, hWnd, (HMENU)ID_OPTIONCOMBO, g_hInst, NULL);
		for (i = 0; i < 4; i++) {
			SendMessage(hOptionCombo, CB_ADDSTRING, 0, (LPARAM)searchOption[i]);
		}
		//검색 에디트
		hSearchEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 300, 55, 400, 25, hWnd, (HMENU)ID_SEARCHEDIT, g_hInst, NULL);
		//남자 체크박스
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("남"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 305, 90, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//여자 체크박스
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("여"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 360, 90, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//재직 체크박스
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("재직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 415, 90, 75, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//퇴직 체크박스
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("퇴직"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 495, 90, 75, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);
		//인사이동 체크박스
		hMoveCheck = CreateWindow(TEXT("button"), TEXT("인사이동"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 575, 90, 90, 25, hWnd, (HMENU)ID_MOVECHECK, g_hInst, NULL);
		//검색 버튼
		CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 710, 50, 70, 55, hWnd, (HMENU)ID_SEARCHBT, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
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
			}
			else {
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_RETIRECHECK:	//퇴직 체크박스 체크,해제
			if (SendMessage(hRetireCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_MOVECHECK:		//인사이동 체크박스 체크, 해제
			if (SendMessage(hMoveCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hMoveCheck, BM_SETCHECK, BST_CHECKED, 0);
			}
			else {
				SendMessage(hMoveCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_SEARCHBT:		//검색 버튼
			ind = SendMessage(hOptionCombo, CB_GETCURSEL, 0, 0);
			//검색 옵션 콤보박스에서 선택이 일어나있지 않으면 메시지박스
			if (ind == -1) {
				MessageBox(hWnd, TEXT("검색 옵션을 선택하세요."), NULL, MB_OK);
			}
			else {				//선택되어있는경우
				//검색 edit의 값 str에 저장
				GetWindowText(hSearchEdit, str, 255);
				//리스트뷰 아이템 모두 지우기
				ListView_DeleteAllItems(hReportEmpLV);
				for (i = 0; i < totEmp; i++) {
					//조건에 맞는 사원인지
					if (lstrlen(str) == 0) {
						j = 1;
					}
					else if (ind == 0 && (lstrcmp(workEmp[i].pInfo.pName[0], str) == 0 || lstrcmp(workEmp[i].pInfo.pName[1], str) == 0
						|| lstrcmp(workEmp[i].pInfo.pName[2], str) == 0)) {				//이름
						j = 1;
					}
					else if (ind == 1 && lstrcmp(workEmp[i].empPosCode, str) == 0) {	//직책
						j = 1;
					}
					else if (ind == 2 && lstrcmp(workEmp[i].empBuseo, str) == 0) {		//부서
						j = 1;
					}
					else if (ind == 3 && lstrcmp(workEmp[i].empNo, str) == 0) {			//사번
						j = 1;
					}
					else {
						j = 0;
					}
					if (SendMessage(hMaleCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
						m = TRUE;
					}
					else {
						m = FALSE;
					}
					if (SendMessage(hFemaleCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
						fm = TRUE;
					}
					else {
						fm = FALSE;
					}
					if (SendMessage(hWorkCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
						w = TRUE;
					}
					else {
						w = FALSE;
					}
					if (SendMessage(hRetireCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
						r = TRUE;
					}
					else {
						r = FALSE;
					}
					if (SendMessage(hMoveCheck, BM_GETCHECK, 0, 0) == BST_CHECKED) {
						mv = TRUE;
					}
					else {
						mv = FALSE;
					}
					//검색 옵션에 맞는지
					if (j == 1) {
						if (workEmp[i].empNo[4] == workEmp[i].empPosCode[0] && workEmp[i].empNo[5] == workEmp[i].empPosCode[1]) {
							j = 0;
						}
						if (m) {		//남 체크
							if (w) {	//재직 체크
								if (mv) {	//남,재직,인사이동
									if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2 && j == 0) {
										j = ListView_GetItemCount(hReportEmpLV);
										LI.mask = LVIF_TEXT;
										LI.iItem = j;
										LI.iSubItem = 0;
										LI.pszText = workEmp[i].empNo;
										ListView_InsertItem(hReportEmpLV, &LI);											//사번
										ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
										ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
										ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
										ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
										if (workEmp[i].pInfo.pSex == TRUE) {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
										}
										else {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
										}
									}
								}
								else {		//남,재직
									if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2) {
										j = ListView_GetItemCount(hReportEmpLV);
										LI.mask = LVIF_TEXT;
										LI.iItem = j;
										LI.iSubItem = 0;
										LI.pszText = workEmp[i].empNo;
										ListView_InsertItem(hReportEmpLV, &LI);											//사번
										ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
										ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
										ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
										ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
										if (workEmp[i].pInfo.pSex == TRUE) {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
										}
										else {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
										}
									}
								}
							}
							else {
								if (r) {	//퇴직 체크
									if (mv) {	//남,퇴직,인사이동
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire == 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
									else {		//남,퇴직
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire == 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
								}
								else {		//재직, 퇴직 모두 체크X (남)
									if (mv) {	//남,재직,인사이동
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											} 
										}
									}
									else {		//남,재직
										if (workEmp[i].pInfo.pSex == TRUE) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
								}
							}
						}
						else {
							if (fm) {	//여 체크
								if (w) {	//재직 체크
									if (mv) {	//여,재직,인사이동
										if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
									else {	//여,재직
										if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
								}
								else {
									if (r) {	//퇴직 체크
										if (mv) {	//여,퇴직,인사이동
											if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire == 2 && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
										else {	//여,퇴직
											if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
									}
									else {		//재직, 퇴직 모두 체크X
										if (mv) {	//여,인사이동	
											if (workEmp[i].pInfo.pSex == FALSE && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
										else {	//여	
											if (workEmp[i].pInfo.pSex == TRUE) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
									}
								}
							}
							else {		//남,여 모두 체크X
								if (w) {	//재직 체크
									if (mv) {	//재직,인사이동	
										if (workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
									else {	//재직		
										if (workEmp[i].empRetire != 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
								}
								else {		//남,여 모두 체크x
									if (r) {	//퇴직 체크
										if (mv) {	//퇴직,인사이동	
											if (workEmp[i].empRetire == 2 && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
										else {	//퇴직	
											if (workEmp[i].empRetire == 2) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//사번
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
												}
											}
										}
									}
									else {		//재직, 퇴직 모두 체크X
										if (mv) {	//인사이동	
											if (j == 0) {
												if (j == 0) {
													j = ListView_GetItemCount(hReportEmpLV);
													LI.mask = LVIF_TEXT;
													LI.iItem = j;
													LI.iSubItem = 0;
													LI.pszText = workEmp[i].empNo;
													ListView_InsertItem(hReportEmpLV, &LI);											//사번
													ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
													ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
													ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
													ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
													if (workEmp[i].pInfo.pSex == TRUE) {
														ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
													}
													else {
														ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
													}
												}
											}
										}
										else {	//모두 체크x	
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//사번
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//이름
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//부서
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//직책
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//연락처
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("남"));				//남
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("여"));				//여
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MyBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, 100, 30, 800, 120);
		DeleteObject(SelectObject(hdc, OldBrush));

		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}