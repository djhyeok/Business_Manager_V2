#include "RetireEmp.h"

extern HINSTANCE g_hInst;
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern int totEmp;			//사원수
extern int totRetEmp;		//퇴직사원수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교

HWND hRetEMPList, hRetEmpNo, hRetEmpBuseo, hRetEmpPoscode, hRetEmpName1, hRetEmpReason
, hRetReqEMPList, hRetReqEMPBuseo, hRetReqEmpPhone;	//컨트롤 핸들

enum {
	ID_RETREQEMPLIST = 1, ID_RETREQBUSEO, ID_RETREQPHONE,
	ID_RETEMPLIST, ID_RETEMPNO, ID_RETBUSEO, ID_RETPOSCODE, ID_RETNAME1, ID_RETREASON, IDC_RETBUTTON
};

LRESULT CALLBACK InitRetireEMPMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HFONT hFont, OldFont;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int i, j;
	static RETIRE tempRet;
	TCHAR str[256];
	TCHAR retReason[6][255] = { TEXT("정년퇴직"),TEXT("명예퇴직"),TEXT("권고사직"),TEXT("이직"),TEXT("희망퇴직"),TEXT("기타") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//리스트뷰 생성
		hRetReqEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 100, 60, 340, 500, hWnd, (HMENU)ID_RETREQEMPLIST, g_hInst, NULL);
		hRetEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 600, 60, 600, 500, hWnd, (HMENU)ID_RETEMPLIST, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hRetReqEMPList, LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyle(hRetEMPList, LVS_EX_FULLROWSELECT);

		//퇴직요청 리스트뷰에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hRetReqEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("부서");
		COL.iSubItem = 1;
		ListView_InsertColumn(hRetReqEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("직책");
		COL.iSubItem = 2;
		ListView_InsertColumn(hRetReqEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("이름");
		COL.iSubItem = 3;
		ListView_InsertColumn(hRetReqEMPList, 3, &COL);

		//퇴직자 리스트뷰에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hRetEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("부서");
		COL.iSubItem = 1;
		ListView_InsertColumn(hRetEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("직책");
		COL.iSubItem = 2;
		ListView_InsertColumn(hRetEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("이름");
		COL.iSubItem = 3;
		ListView_InsertColumn(hRetEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("퇴직사유");
		COL.iSubItem = 4;
		ListView_InsertColumn(hRetEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("연락처");
		COL.iSubItem = 5;
		ListView_InsertColumn(hRetEMPList, 5, &COL);

		hRetEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 115, 588, 150, 25, hWnd, (HMENU)ID_RETEMPNO, g_hInst, NULL);
		hRetEmpBuseo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 115, 628, 150, 25, hWnd, (HMENU)ID_RETBUSEO, g_hInst, NULL);
		hRetEmpPoscode = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 115, 668, 150, 25, hWnd, (HMENU)ID_RETPOSCODE, g_hInst, NULL);
		hRetEmpName1 = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 115, 708, 150, 25, hWnd, (HMENU)ID_RETNAME1, g_hInst, NULL);
		hRetReqEMPBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 395, 588, 200, 125, hWnd, (HMENU)ID_RETREQBUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hRetReqEMPBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		hRetReqEmpPhone = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 395, 628, 200, 25, hWnd, (HMENU)ID_RETREQPHONE, g_hInst, NULL);
		hRetEmpReason = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 395, 668, 200, 125, hWnd, (HMENU)ID_RETREASON, g_hInst, NULL);
		for (i = 0; i < 6; i++) {
			SendMessage(hRetEmpReason, CB_ADDSTRING, 0, (LPARAM)retReason[i]);
		}
		CreateWindow(TEXT("button"), TEXT("퇴직처리"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 530, 705, 70, 25, hWnd, (HMENU)IDC_RETBUTTON, g_hInst, NULL);

		//리스트뷰에 사원정보 채우기
		//사원번호,직책,부서,이름
		DBConnect();
		SelectReqEMP();
		DBDisconnect();
		//퇴직완료리스트뷰
		DBConnect();
		SelectRetEMP();
		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RETBUTTON:		//퇴직처리버튼
			GetWindowText(hRetEmpNo, str, 200);
			if (lstrlen(str)) {
				//퇴직당시 부서,연락처,퇴직사유 정보 tempRet 임시 구조체에 담기
				
				SendMessage(hRetReqEMPBuseo, CB_GETLBTEXT, SendMessage(hRetReqEMPBuseo, CB_GETCURSEL, 0, 0), (LPARAM)tempRet.empBuseo);
				GetWindowText(hRetReqEmpPhone, tempRet.empPhone, 14);
				SendMessage(hRetEmpReason, CB_GETLBTEXT, SendMessage(hRetEmpReason, CB_GETCURSEL, 0, 0), (LPARAM)tempRet.retireReason);
				//부서,연락처,사유를 입력했다면 퇴직처리
				if (lstrlen(tempRet.empBuseo) && lstrlen(tempRet.empPhone) && lstrlen(tempRet.retireReason)) {
					//tempRet로 값 복사
					GetWindowText(hRetEmpNo, tempRet.empNo, 12);			//사원번호
					GetWindowText(hRetEmpName1, tempRet.empName, 255);		//이름
					GetWindowText(hRetEmpPoscode, tempRet.empPoscode, 255);	//직책
					//DB에 EMP테이블에서 해당 사원정보 퇴직정보를 2로 변경하고 RETIREINFO 테이블에 퇴직자 정보 INSERT
					DBConnect();
					lstrcpy(tempRet.empBuseo, Name2Code((LPSTR)"BUSEO", tempRet.empBuseo));
					lstrcpy(tempRet.empPoscode, Name2Code((LPSTR)"POSITION", tempRet.empPoscode));
					RetireEMP(tempRet);
					SelectReqEMP();
					SelectRetEMP();
					DBDisconnect();

					SetWindowText(hRetEmpNo, TEXT(""));
					SetWindowText(hRetEmpBuseo, TEXT(""));
					SetWindowText(hRetEmpPoscode, TEXT(""));
					SetWindowText(hRetEmpName1, TEXT(""));
					SetWindowText(hRetReqEmpPhone, TEXT(""));
					SendMessage(hRetReqEMPBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
					SendMessage(hRetEmpReason, CB_SETCURSEL, (WPARAM)-1, 0);

				}
				else {
					MessageBox(hWnd, TEXT("정보입력오류입니다."), NULL, MB_OK);
				}
			}
			else {
				MessageBox(hWnd, TEXT("먼저 퇴직요청자를 선택하세요."), NULL, MB_OK);
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//부서리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
		if (hdr->hwndFrom == hRetReqEMPList) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					ListView_GetItemText(hRetReqEMPList, nlv->iItem, 0, tempRet.empNo, 12);
					ListView_GetItemText(hRetReqEMPList, nlv->iItem, 1, tempRet.empBuseo, 255);
					ListView_GetItemText(hRetReqEMPList, nlv->iItem, 2, tempRet.empPoscode, 255);
					ListView_GetItemText(hRetReqEMPList, nlv->iItem, 3, tempRet.empName, 255);
					SetWindowText(hRetEmpNo, tempRet.empNo);
					SetWindowText(hRetEmpBuseo, tempRet.empBuseo);
					SetWindowText(hRetEmpPoscode, tempRet.empPoscode);
					SetWindowText(hRetEmpName1, tempRet.empName);
				}
				return TRUE;
			}
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 120, 30, TEXT("퇴직요청"), lstrlen(TEXT("퇴직요청")));
		TextOut(hdc, 620, 30, TEXT("퇴직자"), lstrlen(TEXT("퇴직자")));
		TextOut(hdc, 50, 590, TEXT("사원번호"), lstrlen(TEXT("사원번호")));
		TextOut(hdc, 50, 630, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 50, 670, TEXT("직책"), lstrlen(TEXT("직책")));
		TextOut(hdc, 50, 710, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 300, 590, TEXT("퇴직당시 부서"), lstrlen(TEXT("퇴직당시 부서")));
		TextOut(hdc, 300, 630, TEXT("퇴직당시 번호"), lstrlen(TEXT("퇴직당시 번호")));
		TextOut(hdc, 300, 670, TEXT("퇴직사유"), lstrlen(TEXT("퇴직사유")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}