#include "Emp.h"

extern HINSTANCE g_hInst;
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern int totEmp;			//사원수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교
extern EMP* workEmp;		//사원

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//컨트롤 핸들
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDC_RETIRE, IDC_INSERT, IDC_MODIFY
};

//사원관리 프로시져
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HFONT hFont, OldFont;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int i, j, index, cal;
	static EMP tempEmp;
	SYSTEMTIME st;
	TCHAR str[255];

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//리스트뷰 생성
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1150, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
		//리스트뷰 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("부서");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("직책");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("입사일");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("이름");
		COL.iSubItem = 4;
		ListView_InsertColumn(hEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("영문이름");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("한자이름");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("성별");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("생년월일");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("주소");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("전자우편");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("연락처1");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("연락처2");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("신장");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("체중");
		COL.iSubItem = 14;
		ListView_InsertColumn(hEMPList, 14, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("결혼관계");
		COL.iSubItem = 15;
		ListView_InsertColumn(hEMPList, 15, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("종교");
		COL.iSubItem = 16;
		ListView_InsertColumn(hEMPList, 16, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(좌)");
		COL.iSubItem = 17;
		ListView_InsertColumn(hEMPList, 17, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(우)");
		COL.iSubItem = 18;
		ListView_InsertColumn(hEMPList, 18, &COL);

		//리스트뷰에 사원정보 채우기
		for (i = 0, j = 0; i < totEmp; i++) {
			if (workEmp[i].empRetire == 0) {
				LI.mask = LVIF_TEXT;
				LI.iItem = j;
				LI.iSubItem = 0;
				LI.pszText = workEmp[i].empNo;
				ListView_InsertItem(hEMPList, &LI);
				ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);	//부서
				ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);//직책
				wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
				ListView_SetItemText(hEMPList, j, 3, str);							//입사일
				ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);//한글이름
				ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);//영문이름
				ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);//한문이름
				ListView_SetItemText(hEMPList, j, 7, (workEmp[i].pInfo.pSex == TRUE) ? (LPWSTR)TEXT("남") : (LPWSTR)TEXT("여"));
				wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
				ListView_SetItemText(hEMPList, j, 8, str);
				ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);
				ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);
				ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);
				ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);
				ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);
				ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);
				ListView_SetItemText(hEMPList, j, 15, (workEmp[i].pInfo.pFamily == TRUE) ? (LPWSTR)TEXT("기혼") : (LPWSTR)TEXT("미혼"));
				ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);
				ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);
				j++;
			}
		}

		//1.사원번호 컨트롤 생성
		hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 10, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//2.부서 콤보박스 생성
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 45, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		//3.직책 콤보박스 생성
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 80, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		for (i = 0; i < totP; i++) {
			SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)position[i].name);
		}
		//4.입사일 날짜컨트롤 생성
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 115, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//5.이름 에디트컨트롤 생성
		hEmpName1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 150, 150, 25, hWnd, (HMENU)ID_NAME1, g_hInst, NULL);
		hEmpName2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 185, 150, 25, hWnd, (HMENU)ID_NAME2, g_hInst, NULL);
		hEmpName3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 220, 150, 25, hWnd, (HMENU)ID_NAME3, g_hInst, NULL);
		//6.성별 라디오버튼 생성
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 255, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 255, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//7.생년월일 날짜컨트롤 생성
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 290, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//8.주소 에디트컨트롤 생성
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 325, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//9.이메일 에디트컨트롤 생성
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 360, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//10.연락처1,2 에디트컨트롤 생성
		hEmpPhone1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 395, 150, 25, hWnd, (HMENU)ID_PHONE1, g_hInst, NULL);
		hEmpPhone2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_PHONE2, g_hInst, NULL);
		//12.신장 에디트컨트롤 생성
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 465, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//13.체중 에디트컨트롤 생성
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 500, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//14.결혼관계 라디오버튼 생성
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 535, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 535, 80, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//15.종교 콤보박스 생성
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 580, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		for (i = 0; i < totR; i++) {
			SendMessage(hEmpRelligion, CB_ADDSTRING, 0, (LPARAM)religion[i].name);
		}
		//16.시력(좌,우) 에디트컨트롤 생성
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 615, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 650, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);

		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 690, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 690, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//퇴직요청 버튼생성
		CreateWindow(TEXT("button"), TEXT("퇴직요청"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 690, 100, 25, hWnd, (HMENU)ID_RETIRE, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUSEO:						//부서 콤보박스의 값 임시 구조체tempEmp에 담음
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpBuseo, CB_GETLBTEXT, i, (LPARAM)tempEmp.empBuseo);
				break;
			}
			break;
		case ID_RELLIGION:					//종교 콤보박스의 값 임시 구조체tempEmp에 담음
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpRelligion, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpRelligion, CB_GETLBTEXT, i, (LPARAM)tempEmp.pInfo.pReligion);
				break;
			}
			break;
		case ID_POSCODE:					//직책 콤보박스의 값 임시 구조체tempEmp에 담음
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpPoscode, CB_GETLBTEXT, i, (LPARAM)tempEmp.empPosCode);
				break;
			}
			break;
		case IDC_INSERT:	//삽입 버튼

			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//입사일
			}
			GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//이름
			GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//영문이름
			GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//한자이름
			if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pSex = TRUE;														//남자
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//여자
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//생일
			}

			GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//주소
			GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//전자우편
			GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//연락처1
			GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//연락처2
			GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//신장
			GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//체중
			if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pFamily = TRUE;													//기혼
			}
			else {
				tempEmp.pInfo.pFamily = FALSE;													//미혼
			}
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);			//시력(좌)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);		//시력(우)
			//근무여부 초기화
			tempEmp.empRetire = 0;
			//사원번호생성
			wsprintf(tempEmp.empNo, TEXT("%d"), tempEmp.empStartYear.wYear);
			for (i = 0; i < totB; i++) {
				if (lstrcmp(tempEmp.empBuseo, buseo[i].name) == 0) {
					lstrcat(tempEmp.empNo, buseo[i].code);
				}
			}
			if (tempEmp.pInfo.pSex == TRUE) {
				lstrcat(tempEmp.empNo, TEXT("1"));
			}
			else {
				lstrcat(tempEmp.empNo, TEXT("2"));
			}
			cal = totEmp + 1;
			wsprintf(str, TEXT("%d"), cal / 1000);
			lstrcat(tempEmp.empNo, str);
			cal %= 1000;
			wsprintf(str, TEXT("%d"), cal / 100);
			lstrcat(tempEmp.empNo, str);
			cal %= 100;
			wsprintf(str, TEXT("%d"), cal / 10);
			lstrcat(tempEmp.empNo, str);
			cal %= 10;
			wsprintf(str, TEXT("%d"), cal);
			lstrcat(tempEmp.empNo, str);

			//모두 입력 및 선택시 재할당 후 값 추가
			if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {


				//컨트롤에서 선택 및 입력하지 않을 시 삽입하지 않음
				workEmp = (EMP*)realloc(workEmp, (totEmp + 1) * sizeof(EMP));
				workEmp[totEmp] = tempEmp;
				totEmp++;		//재직사원수 1증가

				//리스트뷰 지우고 다시 사원정보 채우기
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//부서
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//직책
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//입사일
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//한글이름
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//영문이름
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//한문이름
						if (workEmp[i].pInfo.pSex == TRUE) {											//성별
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("남"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("여"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//생년월일
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//주소
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//전자우편
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//연락처1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//연락처2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//신장
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//체중
						if (workEmp[i].pInfo.pFamily == TRUE) {											//결혼관계
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("기혼"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("미혼"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//종교
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//좌시력
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//우시력
						j++;
					}
				}
			}
			else {
				MessageBox(hWnd, TEXT("길이가 0인 값은 추가할 수 없습니다."), TEXT("입력값 오류"), MB_OK);
			}

			//입력 컨트롤들 빈칸으로 초기화
			SetWindowText(hEmpNo, TEXT(""));
			SetWindowText(hEmpName1, TEXT(""));
			SetWindowText(hEmpName2, TEXT(""));
			SetWindowText(hEmpName3, TEXT(""));
			SetWindowText(hEmpAddress, TEXT(""));
			SetWindowText(hEmpEmail, TEXT(""));
			SetWindowText(hEmpPhone1, TEXT(""));
			SetWindowText(hEmpPhone2, TEXT(""));
			SetWindowText(hEmpHeight, TEXT(""));
			SetWindowText(hEmpWeight, TEXT(""));
			SetWindowText(hEmpLefteye, TEXT(""));
			SetWindowText(hEmpRighteye, TEXT(""));
			SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpRelligion, CB_SETCURSEL, (WPARAM)-1, 0);

			break;
		case IDC_MODIFY:	//수정 버튼
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("수정할 사원을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.empStartYear = st;														//입사일
				}
				GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//이름
				GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//영문이름
				GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//한자이름
				if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pSex = TRUE;														//남자
				}
				else {
					tempEmp.pInfo.pSex = FALSE;														//여자
				}
				if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.pInfo.pBirth = st;														//생일
				}

				GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//주소
				GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//전자우편
				GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//연락처1
				GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//연락처2
				GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//신장
				GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//체중
				if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pFamily = TRUE;													//기혼
				}
				else {
					tempEmp.pInfo.pFamily = FALSE;													//미혼
				}
				GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);			//시력(좌)
				GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);		//시력(우)
				for (i = 0; i < totEmp; i++) {
					if (lstrcmp(workEmp[i].empNo, tempEmp.empNo) == 0) {
						workEmp[i] = tempEmp;
					}
				}
				workEmp[index] = tempEmp;

				//리스트뷰 지우고 다시 사원정보 채우기
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//부서
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//직책
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//입사일
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//한글이름
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//영문이름
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//한문이름
						if (workEmp[i].pInfo.pSex == TRUE) {											//성별
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("남"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("여"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//생년월일
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//주소
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//전자우편
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//연락처1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//연락처2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//신장
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//체중
						if (workEmp[i].pInfo.pFamily == TRUE) {											//결혼관계
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("기혼"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("미혼"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//종교
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//좌시력
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//우시력
						j++;

						//입력 컨트롤들 빈칸으로 초기화
						SetWindowText(hEmpNo, TEXT(""));
						SetWindowText(hEmpName1, TEXT(""));
						SetWindowText(hEmpName2, TEXT(""));
						SetWindowText(hEmpName3, TEXT(""));
						SetWindowText(hEmpAddress, TEXT(""));
						SetWindowText(hEmpEmail, TEXT(""));
						SetWindowText(hEmpPhone1, TEXT(""));
						SetWindowText(hEmpPhone2, TEXT(""));
						SetWindowText(hEmpHeight, TEXT(""));
						SetWindowText(hEmpWeight, TEXT(""));
						SetWindowText(hEmpLefteye, TEXT(""));
						SetWindowText(hEmpRighteye, TEXT(""));
						SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
						SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
						SendMessage(hEmpRelligion, CB_SETCURSEL, (WPARAM)-1, 0);
					}
				}
			}
			break;
		case ID_RETIRE:		//퇴직처리 버튼
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("퇴직처리할 사원을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//선택된 사원의 근무상태를 퇴직요청으로 변경
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				for (i = 0; i < totEmp; i++) {
					if (lstrcmp(workEmp[i].empNo, tempEmp.empNo) == 0) {
						workEmp[i].empRetire = 1;
					}
				}
				//리스트뷰 지우고 다시 사원정보 채우기
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//부서
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//직책
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//입사일
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//한글이름
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//영문이름
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//한문이름
						if (workEmp[i].pInfo.pSex == TRUE) {											//성별
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("남"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("여"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//생년월일
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//주소
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//전자우편
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//연락처1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//연락처2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//신장
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//체중
						if (workEmp[i].pInfo.pFamily == TRUE) {											//결혼관계
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("기혼"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("미혼"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//종교
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//좌시력
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//우시력
						j++;
					}
				}
				//입력 컨트롤들 빈칸으로 초기화
				SetWindowText(hEmpNo, TEXT(""));
				SetWindowText(hEmpName1, TEXT(""));
				SetWindowText(hEmpName2, TEXT(""));
				SetWindowText(hEmpName3, TEXT(""));
				SetWindowText(hEmpAddress, TEXT(""));
				SetWindowText(hEmpEmail, TEXT(""));
				SetWindowText(hEmpPhone1, TEXT(""));
				SetWindowText(hEmpPhone2, TEXT(""));
				SetWindowText(hEmpHeight, TEXT(""));
				SetWindowText(hEmpWeight, TEXT(""));
				SetWindowText(hEmpLefteye, TEXT(""));
				SetWindowText(hEmpRighteye, TEXT(""));
				SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpRelligion, CB_SETCURSEL, (WPARAM)-1, 0);
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
		if (hdr->hwndFrom == hEMPList) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//사원번호,부서,직책,입사일,이름,영문이름,한문이름,성별,생년월일,주소,전자우편,연락처1,연락처2,신장,체중,결혼관계,종교,시력(좌),시력(우)
					SetWindowText(hEmpNo, workEmp[nlv->iItem].empNo);
					SetWindowText(hEmpName1, workEmp[nlv->iItem].pInfo.pName[0]);
					SetWindowText(hEmpName2, workEmp[nlv->iItem].pInfo.pName[1]);
					SetWindowText(hEmpName3, workEmp[nlv->iItem].pInfo.pName[2]);
					SetWindowText(hEmpAddress, workEmp[nlv->iItem].pInfo.pAddress);
					SetWindowText(hEmpEmail, workEmp[nlv->iItem].pInfo.pEmail);
					SetWindowText(hEmpPhone1, workEmp[nlv->iItem].pInfo.pPhone[0]);
					SetWindowText(hEmpPhone2, workEmp[nlv->iItem].pInfo.pPhone[1]);
					SetWindowText(hEmpHeight, workEmp[nlv->iItem].pInfo.pPhysical[0]);
					SetWindowText(hEmpWeight, workEmp[nlv->iItem].pInfo.pPhysical[1]);
					SetWindowText(hEmpLefteye, workEmp[nlv->iItem].pInfo.pPhysical[2]);
					SetWindowText(hEmpRighteye, workEmp[nlv->iItem].pInfo.pPhysical[3]);

					if (workEmp[nlv->iItem].pInfo.pSex == TRUE) {
						SendMessage(hEmpMale, BM_SETCHECK, BST_CHECKED, 0);
						SendMessage(hEmpFemale, BM_SETCHECK, BST_UNCHECKED, 0);
					}
					else {
						SendMessage(hEmpFemale, BM_SETCHECK, BST_CHECKED, 0);
						SendMessage(hEmpMale, BM_SETCHECK, BST_UNCHECKED, 0);
					}

					if (workEmp[nlv->iItem].pInfo.pFamily == TRUE) {
						SendMessage(hEmpMarriage, BM_SETCHECK, BST_CHECKED, 0);
						SendMessage(hEmpSingle, BM_SETCHECK, BST_UNCHECKED, 0);
					}
					else {
						SendMessage(hEmpSingle, BM_SETCHECK, BST_CHECKED, 0);
						SendMessage(hEmpMarriage, BM_SETCHECK, BST_UNCHECKED, 0);
					}

					for (i = 0; i < totB; i++) {
						if (lstrcmp(workEmp[nlv->iItem].empBuseo, (LPCWSTR)buseo[i].name) == 0) {
							SendMessage(hEmpBuseo, CB_SETCURSEL, i, 0);
							lstrcpy(tempEmp.empBuseo, buseo[i].name);
							break;
						}
					}

					for (i = 0; i < totP; i++) {
						if (lstrcmp(workEmp[nlv->iItem].empPosCode, (LPCWSTR)position[i].name) == 0) {
							SendMessage(hEmpPoscode, CB_SETCURSEL, i, 0);
							lstrcpy(tempEmp.empPosCode, position[i].name);
							break;
						}
					}

					for (i = 0; i < totR; i++) {
						if (lstrcmp(workEmp[nlv->iItem].pInfo.pReligion, (LPCWSTR)religion[i].name) == 0) {
							SendMessage(hEmpRelligion, CB_SETCURSEL, i, 0);
							lstrcpy(tempEmp.pInfo.pReligion, religion[i].name);
							break;
						}
					}

					st = workEmp[nlv->iItem].empStartYear;
					SendMessage(hEmpIndate, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

					st = workEmp[nlv->iItem].pInfo.pBirth;
					SendMessage(hEmpBirth, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);
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
		TextOut(hdc, 65, 13, TEXT("사원번호"), lstrlen(TEXT("사원번호")));
		TextOut(hdc, 65, 48, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 65, 83, TEXT("직책"), lstrlen(TEXT("직책")));
		TextOut(hdc, 65, 118, TEXT("입사일"), lstrlen(TEXT("입사일")));
		TextOut(hdc, 65, 153, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 65, 188, TEXT("영문이름"), lstrlen(TEXT("영문이름")));
		TextOut(hdc, 65, 223, TEXT("한문이름"), lstrlen(TEXT("한문이름")));
		TextOut(hdc, 65, 258, TEXT("성별"), lstrlen(TEXT("성별")));
		TextOut(hdc, 65, 293, TEXT("생년월일"), lstrlen(TEXT("생년월일")));
		TextOut(hdc, 65, 328, TEXT("주소"), lstrlen(TEXT("주소")));
		TextOut(hdc, 65, 363, TEXT("전자우편"), lstrlen(TEXT("전자우편")));
		TextOut(hdc, 65, 398, TEXT("연락처1"), lstrlen(TEXT("연락처1")));
		TextOut(hdc, 65, 433, TEXT("연락처2"), lstrlen(TEXT("연락처2")));
		TextOut(hdc, 65, 470, TEXT("신장"), lstrlen(TEXT("신장")));
		TextOut(hdc, 65, 505, TEXT("체중"), lstrlen(TEXT("체중")));
		TextOut(hdc, 65, 545, TEXT("결혼관계"), lstrlen(TEXT("결혼관계")));
		TextOut(hdc, 65, 585, TEXT("종교"), lstrlen(TEXT("종교")));
		TextOut(hdc, 65, 620, TEXT("시력(좌)"), lstrlen(TEXT("시력(좌)")));
		TextOut(hdc, 65, 655, TEXT("시력(우)"), lstrlen(TEXT("시력(우)")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
