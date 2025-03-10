#include "Base.h";
/*
WM_CREATE에서 select문 한번날리고 그 이후는 구조체로 관리
삽입 수정 삭제는 DB반영
*/
extern HINSTANCE g_hInst;
HWND hWndBase;
HWND hBuseoList;			//부서리스트뷰 핸들
HWND hBCode;				//부서코드에디트윈도우 핸들
HWND hBName;				//부서이름에디트윈도우 핸들
HWND hReligionList;			//종교리스트뷰 핸들
HWND hRCode;				//종교코드에디트윈도우 핸들
HWND hRName;				//종교이름에디트윈도우 핸들
HWND hPositionList;			//직위리스트뷰 핸들
HWND hPCode;				//직위코드에디트윈도우 핸들
HWND hPName;				//직위이름에디트윈도우 핸들
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교

enum { IDC_INSERT = 1, IDC_MODIFY, IDC_DEL, ID_NAME, ID_CODE, ID_BLIST, ID_RLIST, ID_PLIST };

LRESULT CALLBACK InitBuseoMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	BASE tempBase;		//임시 구조체

	switch (iMessage) {
	case WM_CREATE:
		hWndBase = hWnd;

		//리스트뷰 생성
		hBuseoList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_BLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("부서코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hBuseoList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("부서명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hBuseoList, 1, &COL);
		ListView_SetExtendedListViewStyle(hBuseoList, LVS_EX_FULLROWSELECT);
		//리스트뷰에 부서 채우기
		for (i = 0; i < totB; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = buseo[i].code;
			ListView_InsertItem(hBuseoList, &LI);
			ListView_SetItemText(hBuseoList, i, 1, (LPSTR)buseo[i].name);
		}
		//부서코드 edit생성
		hBCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//부서명 edit생성
		hBName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼

			//부서코드와 부서이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetWindowText(hBCode, tempBase.code, 3);
			GetWindowText(hBName, tempBase.name, 255);

			//길이가 0인경우 break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("길이가 0인 값으로는 삽입이 불가능합니다."), TEXT("삽입값 에러"), MB_OK);
				break;
			}

			//중복값인지 체크
			for (i = 0; i < totB; i++) {
				if (lstrcmp(buseo[i].code, tempBase.code) == 0 || lstrcmp(buseo[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}

			//중복되지 않았다면 부서 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {

				buseo = (BASE*)realloc(buseo, (totB + 1) * sizeof(BASE));	//부서 포인터 재할당
				buseo[totB] = tempBase;
				totB++;		//부서갯수++

				//DB에 입력받은 tempBase 데이터 삽입
				DBConnect();
				BaseInsertSQL((LPSTR)"BUSEO", tempBase);
				DBDisconnect();

				//리스트뷰 비움
				ListView_DeleteAllItems(hBuseoList);

				//리스트뷰에 다시 있는값 채우기
				for (i = 0; i < totB; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = buseo[i].code;
					ListView_InsertItem(hBuseoList, &LI);
					ListView_SetItemText(hBuseoList, i, 1, (LPSTR)buseo[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);
			}

			//삽입후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hBCode, TEXT(""));
			SetWindowText(hBName, TEXT(""));

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//부서코드와 부서이름 edit컨트롤의 값을 tCode,tName에 임시 저장
				GetWindowText(hBCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hBName, tempBase.name, lstrlen(tempBase.name));

				//길이가 0인경우 break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("길이가 0인 값으로는 수정이 불가능합니다."), TEXT("수정값 에러"), MB_OK);
					break;
				}
				//중복값인지 체크
				for (i = 0; i < totB; i++) {
					if (i != ind && (lstrcmp(buseo[i].code, tempBase.code) == 0 || lstrcmp(buseo[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//중복값이라면 수정불가
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("해당 값이 존재합니다. 다른 값을 입력하세요."), TEXT("값 중복"), MB_OK);
					isDup = FALSE;
				}
				else {
					//DB에 쿼리 보내서 update문 실행
					DBConnect();
					BaseUpdateSQL((LPSTR)"BUSEO", buseo[ind].code, tempBase);
					DBDisconnect();

					//ind번째 buseo의 값을 바꿈
					buseo[ind] = tempBase;

					//리스트뷰 비우고 다시채움
					ListView_DeleteAllItems(hBuseoList);


					for (i = 0; i < totB; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = buseo[i].code;
						ListView_InsertItem(hBuseoList, &LI);
						ListView_SetItemText(hBuseoList, i, 1, (LPSTR)buseo[i].name);
					}
				}
			}

			//수정후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hBCode, TEXT(""));
			SetWindowText(hBName, TEXT(""));

			break;
		case IDC_DEL:		//삭제버튼
			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hBuseoList, ind);		//리스트뷰 아이템 지움

				//DB에서 해당 데이터 삭제
				DBConnect();
				BaseDeleteSQL((LPSTR)"BUSEO", buseo[ind].code);
				DBDisconnect();

				for (i = ind; i < totB - 1; i++) {
					buseo[i] = buseo[i + 1];
				}

				lstrcpy(buseo[totB - 1].code, TEXT(""));
				lstrcpy(buseo[totB - 1].name, TEXT(""));
				totB--;
				buseo = (BASE*)realloc(buseo, totB * sizeof(BASE));
			}
			//삭제후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hBCode, TEXT(""));
			SetWindowText(hBName, TEXT(""));
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//부서리스트뷰에서 선택된 항목 edit로 뿌리기
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetWindowText(hBCode, buseo[nlv->iItem].code);
				SetWindowText(hBName, buseo[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 300, 155, TEXT("코드"), 4);
		TextOut(hdc, 450, 155, TEXT("이름"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK InitReligionMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	BASE tempBase;		//임시 구조체

	switch (iMessage) {
	case WM_CREATE:
		//리스트뷰 생성
		hReligionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_RLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("종교코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReligionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("종교명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReligionList, 1, &COL);
		ListView_SetExtendedListViewStyle(hReligionList, LVS_EX_FULLROWSELECT);

		//리스트뷰에 종교 채우기
		for (i = 0; i < totR; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = religion[i].code;
			ListView_InsertItem(hReligionList, &LI);
			ListView_SetItemText(hReligionList, i, 1, (LPSTR)religion[i].name);
		}

		//종교코드 edit생성
		hRCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//종교명 edit생성
		hRName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼

			//종교코드와 종교이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetWindowText(hRCode, tempBase.code, lstrlen(tempBase.code));
			GetWindowText(hRName, tempBase.name, lstrlen(tempBase.name));

			//길이가 0인경우 break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("길이가 0인 값으로는 삽입이 불가능합니다."), TEXT("삽입값 에러"), MB_OK);
				break;
			}

			//중복값인지 체크
			for (i = 0; i < totR; i++) {
				if (lstrcmp(religion[i].code, tempBase.code) == 0 || lstrcmp(religion[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//중복되지 않았다면 종교 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {
				religion = (BASE*)realloc(religion, (totR + 1) * sizeof(BASE));	//종교 포인터 재할당
				religion[totR] = tempBase;
				totR++;		//종교갯수++

				ListView_DeleteAllItems(hReligionList);		//리스트뷰 비움

				//DB에 입력받은 tempBase 데이터 삽입
				DBConnect();
				BaseInsertSQL((LPSTR)"RELIGION", tempBase);
				DBDisconnect();

				//리스트뷰에 다시 있는값 채우기
				for (i = 0; i < totR; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = religion[i].code;
					ListView_InsertItem(hReligionList, &LI);
					ListView_SetItemText(hReligionList, i, 1, (LPSTR)religion[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);
			}

			//삽입후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hRCode, TEXT(""));
			SetWindowText(hRName, TEXT(""));

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//종교코드와 종교이름 edit컨트롤의 값을 tCode,tName에 임시 저장
				GetWindowText(hRCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hRName, tempBase.name, lstrlen(tempBase.name));

				//길이가 0인경우 break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("길이가 0인 값으로는 수정이 불가능합니다."), TEXT("수정값 에러"), MB_OK);
					break;
				}

				//중복값인지 체크
				for (i = 0; i < totR; i++) {
					if (i != ind && (lstrcmp(religion[i].code, tempBase.code) == 0 || lstrcmp(religion[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//중복값이라면 수정 불가
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("해당 값이 존재합니다. 다른 값을 입력하세요."), TEXT("값 중복"), MB_OK);
					isDup = FALSE;
				}
				else {
					//DB에 쿼리 보내서 update문 실행
					DBConnect();
					BaseUpdateSQL((LPSTR)"RELIGION", religion[ind].code, tempBase);
					DBDisconnect();

					//ind번째 religion의 값을 바꿈
					religion[ind] = tempBase;

					//리스트뷰 비우고 다시채움
					ListView_DeleteAllItems(hReligionList);

					for (i = 0; i < totR; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = religion[i].code;
						ListView_InsertItem(hReligionList, &LI);
						ListView_SetItemText(hReligionList, i, 1, (LPSTR)religion[i].name);
					}
				}
			}

			//수정후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hRCode, TEXT(""));
			SetWindowText(hRName, TEXT(""));

			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hReligionList, ind);		//리스트뷰 아이템 지움

				//DB에서 해당 데이터 삭제
				DBConnect();
				BaseDeleteSQL((LPSTR)"RELIGION", religion[ind].code);
				DBDisconnect();

				for (i = ind; i < totR - 1; i++) {
					religion[i] = religion[i + 1];
				}
				lstrcpy(religion[totR - 1].code, TEXT(""));
				lstrcpy(religion[totR - 1].name, TEXT(""));
				totR--;
				religion = (BASE*)realloc(religion, totR * sizeof(BASE));

			}
			//삭제후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hRCode, TEXT(""));
			SetWindowText(hRName, TEXT(""));
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//종교리스트뷰에서 선택된 항목 edit로 뿌리기
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetWindowText(hRCode, religion[nlv->iItem].code);
				SetWindowText(hRName, religion[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 300, 155, TEXT("코드"), 4);
		TextOut(hdc, 450, 155, TEXT("이름"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK InitPositionMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	BASE tempBase;		//임시 구조체

	switch (iMessage) {
	case WM_CREATE:
		//리스트뷰 생성
		hPositionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_PLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("직위코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hPositionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("직위명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hPositionList, 1, &COL);
		ListView_SetExtendedListViewStyle(hPositionList, LVS_EX_FULLROWSELECT);
		//리스트뷰에 종교 채우기
		for (i = 0; i < totP; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = position[i].code;
			ListView_InsertItem(hPositionList, &LI);
			ListView_SetItemText(hPositionList, i, 1, (LPSTR)position[i].name);
		}
		//직위코드 edit생성
		hPCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//직위명 edit생성
		hPName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼

			//직위코드와 직위이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetWindowText(hPCode, tempBase.code, lstrlen(tempBase.code));
			GetWindowText(hPName, tempBase.name, lstrlen(tempBase.name));

			//길이가 0인경우 break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("길이가 0인 값으로는 삽입이 불가능합니다."), TEXT("삽입값 에러"), MB_OK);
				break;
			}

			//중복값인지 체크
			for (i = 0; i < totP; i++) {
				if (lstrcmp(position[i].code, tempBase.code) == 0 || lstrcmp(position[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//중복되지 않았다면 부서 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {
				position = (BASE*)realloc(position, (totP + 1) * sizeof(BASE));	//직위 포인터 재할당
				position[totP] = tempBase;
				totP++;		//직위갯수++

				ListView_DeleteAllItems(hPositionList);		//리스트뷰 비움

				//DB에 입력받은 tempBase 데이터 삽입
				DBConnect();
				BaseInsertSQL((LPSTR)"POSITION", tempBase);
				DBDisconnect();

				//리스트뷰에 다시 있는값 채우기
				for (i = 0; i < totP; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = position[i].code;
					ListView_InsertItem(hPositionList, &LI);
					ListView_SetItemText(hPositionList, i, 1, (LPSTR)position[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);

			}

			//삽입후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hPCode, TEXT(""));
			SetWindowText(hPName, TEXT(""));

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {

				//직위코드와 직위이름 edit컨트롤의 값을 tCode,tName에 임시 저장
				GetWindowText(hPCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hPName, tempBase.name, lstrlen(tempBase.name));

				//길이가 0인경우 break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("길이가 0인 값으로는 수정이 불가능합니다."), TEXT("수정값 에러"), MB_OK);
					break;
				}

				//중복값인지 체크
				for (i = 0; i < totP; i++) {
					if (i != ind && (lstrcmp(position[i].code, tempBase.code) == 0 || lstrcmp(position[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("해당 값이 존재합니다. 다른 값을 입력하세요."), TEXT("값 중복"), MB_OK);
					isDup = FALSE;
				}
				else {
					//DB에 쿼리 보내서 update문 실행
					DBConnect();
					BaseUpdateSQL((LPSTR)"POSITION", position[ind].code, tempBase);
					DBDisconnect();

					//ind번째 position의 값들을 바꿈
					position[ind] = tempBase;

					//리스트뷰 비우고 다시채움
					ListView_DeleteAllItems(hPositionList);		//리스트뷰 비움

					for (i = 0; i < totP; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = position[i].code;
						ListView_InsertItem(hPositionList, &LI);
						ListView_SetItemText(hPositionList, i, 1, (LPSTR)position[i].name);
					}
				}
			}

			//수정후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hPCode, TEXT(""));
			SetWindowText(hPName, TEXT(""));

			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hPositionList, ind);		//리스트뷰 아이템 지움

				//DB에서 해당 데이터 삭제
				DBConnect();
				BaseDeleteSQL((LPSTR)"POSITION", position[ind].code);
				DBDisconnect();

				for (i = ind; i < totP - 1; i++) {
					position[i] = position[i + 1];
				}
				lstrcpy(position[totP - 1].code, TEXT(""));
				lstrcpy(position[totP - 1].name, TEXT(""));
				totP--;
				position = (BASE*)realloc(position, totP * sizeof(BASE));
			}

			//삭제후 코드,이름 컨트롤 빈칸으로 초기화
			SetWindowText(hPCode, TEXT(""));
			SetWindowText(hPName, TEXT(""));

			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//직위리스트뷰에서 선택된 항목 edit로 뿌리기
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetWindowText(hPCode, position[nlv->iItem].code);
				SetWindowText(hPName, position[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 300, 155, TEXT("코드"), 4);
		TextOut(hdc, 450, 155, TEXT("이름"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}