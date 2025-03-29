#include "RetireEmp.h"

extern HINSTANCE g_hInst;
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern int totEmp;			//�����
extern int totRetEmp;		//���������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����

HWND hRetEMPList, hRetEmpNo, hRetEmpBuseo, hRetEmpPoscode, hRetEmpName1, hRetEmpReason
, hRetReqEMPList, hRetReqEMPBuseo, hRetReqEmpPhone;	//��Ʈ�� �ڵ�

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
	TCHAR retReason[6][255] = { TEXT("��������"),TEXT("������"),TEXT("�ǰ����"),TEXT("����"),TEXT("�������"),TEXT("��Ÿ") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//����Ʈ�� ����
		hRetReqEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 100, 60, 340, 500, hWnd, (HMENU)ID_RETREQEMPLIST, g_hInst, NULL);
		hRetEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 600, 60, 600, 500, hWnd, (HMENU)ID_RETEMPLIST, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hRetReqEMPList, LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyle(hRetEMPList, LVS_EX_FULLROWSELECT);

		//������û ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hRetReqEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hRetReqEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hRetReqEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("�̸�");
		COL.iSubItem = 3;
		ListView_InsertColumn(hRetReqEMPList, 3, &COL);

		//������ ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hRetEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hRetEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hRetEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("�̸�");
		COL.iSubItem = 3;
		ListView_InsertColumn(hRetEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("��������");
		COL.iSubItem = 4;
		ListView_InsertColumn(hRetEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("����ó");
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
		CreateWindow(TEXT("button"), TEXT("����ó��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 530, 705, 70, 25, hWnd, (HMENU)IDC_RETBUTTON, g_hInst, NULL);

		//����Ʈ�信 ������� ä���
		//�����ȣ,��å,�μ�,�̸�
		DBConnect();
		SelectReqEMP();
		DBDisconnect();
		//�����ϷḮ��Ʈ��
		DBConnect();
		SelectRetEMP();
		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RETBUTTON:		//����ó����ư
			GetWindowText(hRetEmpNo, str, 200);
			if (lstrlen(str)) {
				//������� �μ�,����ó,�������� ���� tempRet �ӽ� ����ü�� ���
				
				SendMessage(hRetReqEMPBuseo, CB_GETLBTEXT, SendMessage(hRetReqEMPBuseo, CB_GETCURSEL, 0, 0), (LPARAM)tempRet.empBuseo);
				GetWindowText(hRetReqEmpPhone, tempRet.empPhone, 14);
				SendMessage(hRetEmpReason, CB_GETLBTEXT, SendMessage(hRetEmpReason, CB_GETCURSEL, 0, 0), (LPARAM)tempRet.retireReason);
				//�μ�,����ó,������ �Է��ߴٸ� ����ó��
				if (lstrlen(tempRet.empBuseo) && lstrlen(tempRet.empPhone) && lstrlen(tempRet.retireReason)) {
					//tempRet�� �� ����
					GetWindowText(hRetEmpNo, tempRet.empNo, 12);			//�����ȣ
					GetWindowText(hRetEmpName1, tempRet.empName, 255);		//�̸�
					GetWindowText(hRetEmpPoscode, tempRet.empPoscode, 255);	//��å
					//DB�� EMP���̺��� �ش� ������� ���������� 2�� �����ϰ� RETIREINFO ���̺� ������ ���� INSERT
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
					MessageBox(hWnd, TEXT("�����Է¿����Դϴ�."), NULL, MB_OK);
				}
			}
			else {
				MessageBox(hWnd, TEXT("���� ������û�ڸ� �����ϼ���."), NULL, MB_OK);
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//�μ�����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
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
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 120, 30, TEXT("������û"), lstrlen(TEXT("������û")));
		TextOut(hdc, 620, 30, TEXT("������"), lstrlen(TEXT("������")));
		TextOut(hdc, 50, 590, TEXT("�����ȣ"), lstrlen(TEXT("�����ȣ")));
		TextOut(hdc, 50, 630, TEXT("�μ�"), lstrlen(TEXT("�μ�")));
		TextOut(hdc, 50, 670, TEXT("��å"), lstrlen(TEXT("��å")));
		TextOut(hdc, 50, 710, TEXT("�̸�"), lstrlen(TEXT("�̸�")));
		TextOut(hdc, 300, 590, TEXT("������� �μ�"), lstrlen(TEXT("������� �μ�")));
		TextOut(hdc, 300, 630, TEXT("������� ��ȣ"), lstrlen(TEXT("������� ��ȣ")));
		TextOut(hdc, 300, 670, TEXT("��������"), lstrlen(TEXT("��������")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}