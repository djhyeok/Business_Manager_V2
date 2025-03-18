#include "Family.h"

extern HINSTANCE g_hInst;
HWND hEmpLV, hFamilyLV, hEmpName, hFamName, hFamAge, hFamRel, hFamJob, hFamInsert, hFamEmpno, hEmpno, hFindBtn;
enum {
	ID_EMPLV, ID_FAMLV, ID_EMPNAME, ID_FAMNAME, ID_FAMAGE, ID_FAMREL, ID_FAMJOB,
	ID_FAMINSERT, ID_FAMMODIFY, ID_FAMDELETE, ID_REFRESH, ID_FAMEMPNO, ID_FINDEMPNO, ID_FIND
};

LRESULT CALLBACK InitEMPFamilyMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	INITCOMMONCONTROLSEX icex;
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[256];
	HFONT hFont, OldFont;
	static FAMILY tempFam;
	int i, j;
	TCHAR famRelation[8][255] = { TEXT("조부"),TEXT("조모"),TEXT("부"),TEXT("모"),TEXT("배우자"),TEXT("자녀"),TEXT("형제"),TEXT("동거인") };
	TCHAR famJob[6][255] = { TEXT("회사원"),TEXT("자영업"),TEXT("학생"),TEXT("주부"),TEXT("무직"),TEXT("기타") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//사원, 가족사항 리스트뷰 생성
		hEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			100, 60, 340, 500, hWnd, (HMENU)ID_EMPLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hEmpLV, LVS_EX_FULLROWSELECT);
		hFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			700, 60, 320, 500, hWnd, (HMENU)ID_FAMLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hFamilyLV, LVS_EX_FULLROWSELECT);

		//사원 리스트뷰에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("부서");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("직책");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("이름");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEmpLV, 3, &COL);

		//가족사항 리스트뷰에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("이름");
		COL.iSubItem = 0;
		ListView_InsertColumn(hFamilyLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("나이");
		COL.iSubItem = 1;
		ListView_InsertColumn(hFamilyLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("관계");
		COL.iSubItem = 2;
		ListView_InsertColumn(hFamilyLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("직업");
		COL.iSubItem = 3;
		ListView_InsertColumn(hFamilyLV, 3, &COL);

		//사번검색 edit 컨트롤
		hEmpno = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			135, 570, 150, 25, hWnd, (HMENU)ID_FINDEMPNO, g_hInst, NULL);
		//사번검색 버튼
		hFindBtn = CreateWindow(TEXT("button"), TEXT("사번검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			300, 570, 100, 25, hWnd, (HMENU)ID_FIND, g_hInst, NULL);
		//사원명 static 컨트롤
		hEmpName = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			700, 29, 60, 22, hWnd, (HMENU)ID_EMPNAME, g_hInst, NULL);
		hFamEmpno = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			900, 29, 120, 22, hWnd, (HMENU)ID_FAMEMPNO, g_hInst, NULL);
		//사원가족사항 정보입력 컨트롤
		hFamName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			540, 78, 100, 25, hWnd, (HMENU)ID_FAMNAME, g_hInst, NULL);
		hFamAge = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			540, 118, 100, 25, hWnd, (HMENU)ID_FAMAGE, g_hInst, NULL);
		hFamRel = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			540, 158, 100, 175, hWnd, (HMENU)ID_FAMREL, g_hInst, NULL);
		for (i = 0; i < 8; i++) {
			SendMessage(hFamRel, CB_ADDSTRING, 0, (LPARAM)famRelation[i]);
		}
		hFamJob = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			540, 198, 100, 125, hWnd, (HMENU)ID_FAMJOB, g_hInst, NULL);
		for (i = 0; i < 6; i++) {
			SendMessage(hFamJob, CB_ADDSTRING, 0, (LPARAM)famJob[i]);
		}

		//부양가족추가 버튼
		CreateWindow(TEXT("button"), TEXT("추가"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			490, 235, 50, 25, hWnd, (HMENU)ID_FAMINSERT, g_hInst, NULL);
		//부양가족수정 버튼
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			545, 235, 50, 25, hWnd, (HMENU)ID_FAMMODIFY, g_hInst, NULL);
		//부양가족삭제 버튼
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			600, 235, 50, 25, hWnd, (HMENU)ID_FAMDELETE, g_hInst, NULL);
		//부양가족정보 다시입력 버튼
		CreateWindow(TEXT("button"), TEXT("다시입력"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			490, 265, 160, 25, hWnd, (HMENU)ID_REFRESH, g_hInst, NULL);

		//리스트뷰에 사원정보 채우기
		//사원번호,직책,부서,이름
		DBConnect();
		SelectEMP();
		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FIND:			//사번검색버튼
			int idx;
			LVFINDINFO fi;
			//검색할 사번 str에 담음
			GetWindowText(hEmpno, str, 255);
			//str을 hEmpLV에서 찾음
			fi.flags = LVFI_STRING;
			fi.psz = str;
			fi.vkDirection = VK_DOWN;
			idx = ListView_FindItem(hEmpLV, -1, &fi);
			if (idx == -1) {
				MessageBox(hWnd, "해당 사번의 사원이 존재하지 않습니다.", NULL, MB_OK);
			}
			else {
				ListView_SetItemState(hEmpLV, -1, 0, LVIS_FOCUSED | LVIS_SELECTED);
				ListView_SetItemState(hEmpLV, idx, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				ListView_EnsureVisible(hEmpLV, idx, FALSE);
			}
			break;
		case ID_FAMINSERT:		//추가버튼
			GetWindowText(hFamEmpno, tempFam.empNo, 12);
			if (lstrlen(tempFam.empNo) == 0) {
				MessageBox(hWnd, TEXT("사원 선택 후 가족사항을 추가하세요"), TEXT("삽입 오류"), MB_OK);
			}
			else {
				//컨트롤에 입력받은 값 가져와서 insert 수행
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				SendMessage(hFamRel, CB_GETLBTEXT, SendMessage(hFamRel, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.relation);
				SendMessage(hFamJob, CB_GETLBTEXT, SendMessage(hFamJob, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.job);
				if (lstrlen(tempFam.name) == 0 || lstrlen(tempFam.age) == 0 || lstrlen(tempFam.relation) == 0 || lstrlen(tempFam.job) == 0) {
					MessageBox(hWnd, TEXT("삽입정보오류"), NULL, MB_OK);
				}
				else {
					for (i = 0; i < ListView_GetItemCount(hFamilyLV); i++) {
						ListView_GetItemText(hFamilyLV, i, 0, str, 255);
						if (lstrcmp(tempFam.name, str) == 0) {
							MessageBox(hWnd, TEXT("이름이 동일한 가족은 추가할 수 없습니다."), NULL, MB_OK);
							SetWindowText(hFamName, TEXT(""));
							lstrcpy(tempFam.name, TEXT(""));
							break;
						}
					}
					for (i = 0; i < ListView_GetItemCount(hFamilyLV); i++) {
						ListView_GetItemText(hFamilyLV, i, 2, str, 255);
						if ((lstrcmp(tempFam.relation, famRelation[0]) == 0 || lstrcmp(tempFam.relation, famRelation[1]) == 0 ||
							lstrcmp(tempFam.relation, famRelation[2]) == 0 || lstrcmp(tempFam.relation, famRelation[3]) == 0 ||
							lstrcmp(tempFam.relation, famRelation[4]) == 0) && lstrcmp(tempFam.relation, str) == 0) {
							MessageBox(hWnd, TEXT("관계설정오류"), NULL, MB_OK);
							SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
							lstrcpy(tempFam.relation, TEXT(""));
							break;
						}
					}
					if (lstrlen(tempFam.relation) && lstrlen(tempFam.name)) {
						DBConnect();
						InsertFamily(tempFam);
						SelectFamily(tempFam.empNo);
						DBDisconnect();
					}
				}
			}
			//입력 컨트롤 초기화
			SetWindowText(hFamName, TEXT(""));
			SetWindowText(hFamAge, TEXT(""));
			SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
			break;
		case ID_FAMMODIFY:		//수정버튼
			i = ListView_GetNextItem(hFamilyLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("수정 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//컨트롤의 값들 임시구조체 tempFam에 담음
				GetWindowText(hFamEmpno, tempFam.empNo, 20);
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				SendMessage(hFamRel, CB_GETLBTEXT, SendMessage(hFamRel, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.relation);
				SendMessage(hFamJob, CB_GETLBTEXT, SendMessage(hFamJob, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.job);
				//가족사항에서 수정할때 관계유효성 확인후 수정

				if ((lstrcmp(tempFam.relation, famRelation[0]) == 0 || lstrcmp(tempFam.relation, famRelation[1]) == 0 ||
					lstrcmp(tempFam.relation, famRelation[2]) == 0 || lstrcmp(tempFam.relation, famRelation[3]) == 0 ||
					lstrcmp(tempFam.relation, famRelation[4]) == 0)) {
					for (j = 0; j < ListView_GetItemCount(hFamilyLV); j++) {
						ListView_GetItemText(hFamilyLV, j, 2, str, 255);
						if (i != j && lstrcmp(str, tempFam.relation) == 0) {
							MessageBox(hWnd, TEXT("관계설정오류"), NULL, MB_OK);
							lstrcpy(tempFam.relation, "");
							break;
						}
					}
				}
				//모든 입력값이 유효하다면 해당 index의 가족정보 update
				if (lstrlen(tempFam.relation) != 0) {
					ListView_GetItemText(hFamilyLV, i, 0, str, 50);

					DBConnect();
					UpdateFamily(GetFamilyIndex(tempFam.empNo, str), tempFam);
					SelectFamily(tempFam.empNo);
					DBDisconnect();
					//입력 컨트롤 빈칸으로 초기화
					SetWindowText(hFamName, TEXT(""));
					SetWindowText(hFamAge, TEXT(""));
					SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
					SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
				}
			}
			break;
		case ID_FAMDELETE:		//삭제버튼
			i = ListView_GetNextItem(hFamilyLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("삭제 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//사원번호와 이름을 컨트롤에서 가져와서 지울 가족정보 특정
				GetWindowText(hFamEmpno, tempFam.empNo, 20);
				GetWindowText(hFamName, tempFam.name, 255);
				ListView_GetItemText(hFamilyLV, i, 0, str, 50);
				DBConnect();
				DeleteFamily(GetFamilyIndex(tempFam.empNo, str));
				SelectFamily(tempFam.empNo);
				DBDisconnect();
				//입력 컨트롤 빈칸으로 초기화
				SetWindowText(hFamName, TEXT(""));
				SetWindowText(hFamAge, TEXT(""));
				SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
			}
			break;
		case ID_REFRESH:		//다시입력버튼
			//입력 컨트롤 빈칸으로 초기화
			SetWindowText(hFamName, TEXT(""));
			SetWindowText(hFamAge, TEXT(""));
			SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//부서리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
		if (hdr->hwndFrom == hEmpLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					ListView_GetItemText(hEmpLV, nlv->iItem, 3, str, 12);
					ListView_GetItemText(hEmpLV, nlv->iItem, 0, tempFam.empNo, 255);

					//static컨트롤에 이름,사번뿌려서 보여주기
					SetWindowText(hEmpName, str);
					SetWindowText(hFamEmpno, tempFam.empNo);

					//가족사항리스트뷰에 사원가족정보 뿌리기
					DBConnect();
					SelectFamily((LPSTR)tempFam.empNo);
					DBDisconnect();

					//입력 컨트롤 초기화
					SetWindowText(hFamName, TEXT(""));
					SetWindowText(hFamAge, TEXT(""));
					SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
					SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);

					//임시가족 구조체 초기화
					lstrcpy(tempFam.empNo, TEXT(""));
					lstrcpy(tempFam.age, TEXT(""));
					lstrcpy(tempFam.job, TEXT(""));
					lstrcpy(tempFam.name, TEXT(""));
					lstrcpy(tempFam.relation, TEXT(""));
				}
				return TRUE;
			}
		}
		else if (hdr->hwndFrom == hFamilyLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//LV에서 선택한 내용을 입력 컨트롤에 뿌리기
					ListView_GetItemText(hFamilyLV, nlv->iItem, 0, str, 255);
					SetWindowText(hFamName, str);
					ListView_GetItemText(hFamilyLV, nlv->iItem, 1, str, 5);
					SetWindowText(hFamAge, str);
					ListView_GetItemText(hFamilyLV, nlv->iItem, 2, str, 255);
					SendMessage(hFamRel, CB_SETCURSEL, SendMessage(hFamRel, CB_FINDSTRINGEXACT, -1, (LPARAM)str), 0);
					ListView_GetItemText(hFamilyLV, nlv->iItem, 3, str, 255);
					SendMessage(hFamJob, CB_SETCURSEL, SendMessage(hFamJob, CB_FINDSTRINGEXACT, -1, (LPARAM)str), 0);
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
		TextOut(hdc, 120, 30, TEXT("사원"), lstrlen(TEXT("사원")));
		TextOut(hdc, 760, 30, TEXT("님 가족"), lstrlen(TEXT("님 가족")));
		TextOut(hdc, 870, 30, TEXT("사번"), lstrlen(TEXT("사번")));
		TextOut(hdc, 490, 80, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 490, 120, TEXT("나이"), lstrlen(TEXT("나이")));
		TextOut(hdc, 490, 160, TEXT("관계"), lstrlen(TEXT("관계")));
		TextOut(hdc, 490, 200, TEXT("직업"), lstrlen(TEXT("직업")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
