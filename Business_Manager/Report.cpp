#include "Report.h"

extern HINSTANCE g_hInst;

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
	TCHAR option[3][50] = { TEXT("�����ȣ"),TEXT("�̸�"),TEXT("�Ի�⵵") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		//����Ʈ�� ����
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 120, 700, 500, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportEmpLV, LVS_EX_FULLROWSELECT);
		hReportFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 830, 120, 500, 600, hWnd, (HMENU)ID_REPORTFAMLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportFamilyLV, LVS_EX_FULLROWSELECT);
		hReportRetireLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 640, 700, 80, hWnd, (HMENU)ID_REPORTRETIRE, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hReportRetireLV, LVS_EX_FULLROWSELECT);

		//�������Ʈ�� ��� �߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("���");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("�����");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("�μ�");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("��å");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportEmpLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("����ó");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportEmpLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 6;
		ListView_InsertColumn(hReportEmpLV, 6, &COL);

		//�������� ����Ʈ�� ��� �߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportFamilyLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("�����");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportFamilyLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("�̸�");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportFamilyLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportFamilyLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportFamilyLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 75;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportFamilyLV, 5, &COL);

		//�������� ����Ʈ�� ��� �߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 160;
		COL.pszText = (LPSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportRetireLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 110;
		COL.pszText = (LPSTR)TEXT("�����");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportRetireLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("������úμ�");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportRetireLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPSTR)TEXT("��å");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportRetireLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 110;
		COL.pszText = (LPSTR)TEXT("����ó");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportRetireLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 90;
		COL.pszText = (LPSTR)TEXT("��������");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportRetireLV, 5, &COL);

		//�˻��ɼ� �޺��ڽ�
		hSearchOption = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			150, 65, 120, 250, hWnd, (HMENU)ID_SEARCHCOMBO, g_hInst, NULL);
		for (i = 0; i < 3; i++) {
			SendMessage(hSearchOption, CB_ADDSTRING, 0, (LPARAM)option[i]);
		}
		//�˻� ����Ʈ�ڽ�
		hSearch = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			275, 65, 245, 23, hWnd, (HMENU)ID_SEARCH, g_hInst, NULL);
		//�μ� �����޺��ڽ�
		hSelectBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			310, 5, 70, 250, hWnd, (HMENU)ID_SELECTBUSEO, g_hInst, NULL);
		//��å �����޺��ڽ�
		hSelectPos = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			445, 5, 70, 250, hWnd, (HMENU)ID_SELECTPOS, g_hInst, NULL);
		DBConnect();
		InitCombo((LPSTR)"BUSEO", hSelectBuseo);
		InitCombo((LPSTR)"POSITION", hSelectPos);
		DBDisconnect();
		//���� üũ�ڽ�
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 280, 35, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 335, 35, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 390, 35, 55, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 445, 35, 55, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);
		//������û üũ�ڽ�
		hRetireReqCheck = CreateWindow(TEXT("button"), TEXT("������û"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 505, 35, 100, 25, hWnd, (HMENU)ID_RETIREREQCHECK, g_hInst, NULL);
		//����˻� ��ư
		hSearchBtn = CreateWindow(TEXT("button"), TEXT("�˻�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			525, 63, 50, 25, hWnd, (HMENU)ID_SEARCHBTN, g_hInst, NULL);
		//���ΰ�ħ ��ư
		hRefreshBtn = CreateWindow(TEXT("button"), TEXT("���ΰ�ħ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
			//tempEmp �ʱ�ȭ �� ListView�� select�ؼ� �Ѹ�
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
		case ID_MALECHECK:	//�� üũ�ڽ� üũ,����
			if (SendMessage(hMaleCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hMaleCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hMaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_FEMALECHECK:	//�� üũ�ڽ� üũ,����
			if (SendMessage(hFemaleCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hMaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hFemaleCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_WORKCHECK:		//���� üũ�ڽ� üũ,����
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
		case ID_RETIRECHECK:	//���� üũ�ڽ� üũ,����
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
		case ID_RETIREREQCHECK:	//������û üũ�ڽ� üũ,����
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
			//�󼼰˻��ɼǿ��� �� ������
			i = SendMessage(hSelectBuseo, CB_GETCURSEL, 0, 0);
			if (i == -1) {
				lstrcpy(tempEmp.empBuseo, "");
			}
			else {
				SendMessage(hSelectBuseo, CB_GETLBTEXT, i, (LPARAM)tempEmp.empBuseo);
			}

			i = SendMessage(hSelectPos, CB_GETCURSEL, 0, 0);
			if (i == -1) {
				lstrcpy(tempEmp.empPosCode, "");
			}
			else {
				SendMessage(hSelectPos, CB_GETLBTEXT, i, (LPARAM)tempEmp.empPosCode);
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
			if (i == 0) {			//�����ȣ
				GetWindowText(hSearch, tempEmp.empNo, 12);
				lstrcpy(tempEmp.pInfo.pName[0], "");
				lstrcpy(str, "");
			}
			else if (i == 1) {		//�̸�
				GetWindowText(hSearch, tempEmp.pInfo.pName[0], 20);
				lstrcpy(tempEmp.empNo, "");
				lstrcpy(str, "");
			}
			else if (i == 2) {		//�Ի�⵵
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

		//�μ�����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		if (hdr->hwndFrom == hReportEmpLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//���������� Ȯ�� �� �������� ListView�� �Ѹ�
					ListView_GetItemText(hReportEmpLV, nlv->iItem, 6, str, 20);
					if (lstrcmp("����", str) == 0) {
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
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 275, 7, TEXT("�μ�"), lstrlen(TEXT("�μ�")));
		TextOut(hdc, 400, 9, TEXT("��å"), lstrlen(TEXT("��å")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}