#include "Emp.h"

extern HINSTANCE g_hInst;
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern int totEmp;			//�����
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����
extern EMP* workEmp;		//���

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//��Ʈ�� �ڵ�
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDC_RETIRE, IDC_INSERT, IDC_MODIFY
};

//������� ���ν���
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

		//����Ʈ�� ����
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1150, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�Ի���");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�̸�");
		COL.iSubItem = 4;
		ListView_InsertColumn(hEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("�����̸�");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("�����̸�");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�������");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�ּ�");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("���ڿ���");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("����ó1");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("����ó2");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("ü��");
		COL.iSubItem = 14;
		ListView_InsertColumn(hEMPList, 14, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��ȥ����");
		COL.iSubItem = 15;
		ListView_InsertColumn(hEMPList, 15, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 16;
		ListView_InsertColumn(hEMPList, 16, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 17;
		ListView_InsertColumn(hEMPList, 17, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 18;
		ListView_InsertColumn(hEMPList, 18, &COL);

		//����Ʈ�信 ������� ä���
		for (i = 0, j = 0; i < totEmp; i++) {
			if (workEmp[i].empRetire == 0) {
				LI.mask = LVIF_TEXT;
				LI.iItem = j;
				LI.iSubItem = 0;
				LI.pszText = workEmp[i].empNo;
				ListView_InsertItem(hEMPList, &LI);
				ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);	//�μ�
				ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);//��å
				wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
				ListView_SetItemText(hEMPList, j, 3, str);							//�Ի���
				ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);//�ѱ��̸�
				ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);//�����̸�
				ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);//�ѹ��̸�
				ListView_SetItemText(hEMPList, j, 7, (workEmp[i].pInfo.pSex == TRUE) ? (LPWSTR)TEXT("��") : (LPWSTR)TEXT("��"));
				wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
				ListView_SetItemText(hEMPList, j, 8, str);
				ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);
				ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);
				ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);
				ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);
				ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);
				ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);
				ListView_SetItemText(hEMPList, j, 15, (workEmp[i].pInfo.pFamily == TRUE) ? (LPWSTR)TEXT("��ȥ") : (LPWSTR)TEXT("��ȥ"));
				ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);
				ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);
				j++;
			}
		}

		//1.�����ȣ ��Ʈ�� ����
		hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 10, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//2.�μ� �޺��ڽ� ����
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 45, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		//3.��å �޺��ڽ� ����
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 80, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		for (i = 0; i < totP; i++) {
			SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)position[i].name);
		}
		//4.�Ի��� ��¥��Ʈ�� ����
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 115, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//5.�̸� ����Ʈ��Ʈ�� ����
		hEmpName1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 150, 150, 25, hWnd, (HMENU)ID_NAME1, g_hInst, NULL);
		hEmpName2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 185, 150, 25, hWnd, (HMENU)ID_NAME2, g_hInst, NULL);
		hEmpName3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 220, 150, 25, hWnd, (HMENU)ID_NAME3, g_hInst, NULL);
		//6.���� ������ư ����
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 255, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 255, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//7.������� ��¥��Ʈ�� ����
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 290, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//8.�ּ� ����Ʈ��Ʈ�� ����
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 325, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//9.�̸��� ����Ʈ��Ʈ�� ����
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 360, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//10.����ó1,2 ����Ʈ��Ʈ�� ����
		hEmpPhone1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 395, 150, 25, hWnd, (HMENU)ID_PHONE1, g_hInst, NULL);
		hEmpPhone2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_PHONE2, g_hInst, NULL);
		//12.���� ����Ʈ��Ʈ�� ����
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 465, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//13.ü�� ����Ʈ��Ʈ�� ����
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 500, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//14.��ȥ���� ������ư ����
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 535, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 535, 80, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//15.���� �޺��ڽ� ����
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 580, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		for (i = 0; i < totR; i++) {
			SendMessage(hEmpRelligion, CB_ADDSTRING, 0, (LPARAM)religion[i].name);
		}
		//16.�÷�(��,��) ����Ʈ��Ʈ�� ����
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 615, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 650, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);

		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 690, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 690, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������û ��ư����
		CreateWindow(TEXT("button"), TEXT("������û"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 690, 100, 25, hWnd, (HMENU)ID_RETIRE, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUSEO:						//�μ� �޺��ڽ��� �� �ӽ� ����ütempEmp�� ����
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpBuseo, CB_GETLBTEXT, i, (LPARAM)tempEmp.empBuseo);
				break;
			}
			break;
		case ID_RELLIGION:					//���� �޺��ڽ��� �� �ӽ� ����ütempEmp�� ����
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpRelligion, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpRelligion, CB_GETLBTEXT, i, (LPARAM)tempEmp.pInfo.pReligion);
				break;
			}
			break;
		case ID_POSCODE:					//��å �޺��ڽ��� �� �ӽ� ����ütempEmp�� ����
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0);
				SendMessage(hEmpPoscode, CB_GETLBTEXT, i, (LPARAM)tempEmp.empPosCode);
				break;
			}
			break;
		case IDC_INSERT:	//���� ��ư

			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//�Ի���
			}
			GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//�̸�
			GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//�����̸�
			GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//�����̸�
			if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pSex = TRUE;														//����
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//����
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//����
			}

			GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//�ּ�
			GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//���ڿ���
			GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//����ó1
			GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//����ó2
			GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//����
			GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//ü��
			if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pFamily = TRUE;													//��ȥ
			}
			else {
				tempEmp.pInfo.pFamily = FALSE;													//��ȥ
			}
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);			//�÷�(��)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);		//�÷�(��)
			//�ٹ����� �ʱ�ȭ
			tempEmp.empRetire = 0;
			//�����ȣ����
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

			//��� �Է� �� ���ý� ���Ҵ� �� �� �߰�
			if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {


				//��Ʈ�ѿ��� ���� �� �Է����� ���� �� �������� ����
				workEmp = (EMP*)realloc(workEmp, (totEmp + 1) * sizeof(EMP));
				workEmp[totEmp] = tempEmp;
				totEmp++;		//��������� 1����

				//����Ʈ�� ����� �ٽ� ������� ä���
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//�μ�
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//��å
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//�Ի���
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//�ѱ��̸�
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//�����̸�
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//�ѹ��̸�
						if (workEmp[i].pInfo.pSex == TRUE) {											//����
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//�������
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//�ּ�
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//���ڿ���
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//����ó1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//����ó2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//����
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//ü��
						if (workEmp[i].pInfo.pFamily == TRUE) {											//��ȥ����
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//����
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//�½÷�
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//��÷�
						j++;
					}
				}
			}
			else {
				MessageBox(hWnd, TEXT("���̰� 0�� ���� �߰��� �� �����ϴ�."), TEXT("�Է°� ����"), MB_OK);
			}

			//�Է� ��Ʈ�ѵ� ��ĭ���� �ʱ�ȭ
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
		case IDC_MODIFY:	//���� ��ư
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("������ ����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.empStartYear = st;														//�Ի���
				}
				GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//�̸�
				GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//�����̸�
				GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//�����̸�
				if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pSex = TRUE;														//����
				}
				else {
					tempEmp.pInfo.pSex = FALSE;														//����
				}
				if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.pInfo.pBirth = st;														//����
				}

				GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//�ּ�
				GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//���ڿ���
				GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//����ó1
				GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//����ó2
				GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//����
				GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//ü��
				if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pFamily = TRUE;													//��ȥ
				}
				else {
					tempEmp.pInfo.pFamily = FALSE;													//��ȥ
				}
				GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);			//�÷�(��)
				GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);		//�÷�(��)
				for (i = 0; i < totEmp; i++) {
					if (lstrcmp(workEmp[i].empNo, tempEmp.empNo) == 0) {
						workEmp[i] = tempEmp;
					}
				}
				workEmp[index] = tempEmp;

				//����Ʈ�� ����� �ٽ� ������� ä���
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//�μ�
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//��å
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//�Ի���
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//�ѱ��̸�
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//�����̸�
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//�ѹ��̸�
						if (workEmp[i].pInfo.pSex == TRUE) {											//����
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//�������
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//�ּ�
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//���ڿ���
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//����ó1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//����ó2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//����
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//ü��
						if (workEmp[i].pInfo.pFamily == TRUE) {											//��ȥ����
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//����
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//�½÷�
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//��÷�
						j++;

						//�Է� ��Ʈ�ѵ� ��ĭ���� �ʱ�ȭ
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
		case ID_RETIRE:		//����ó�� ��ư
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("����ó���� ����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				//���õ� ����� �ٹ����¸� ������û���� ����
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				for (i = 0; i < totEmp; i++) {
					if (lstrcmp(workEmp[i].empNo, tempEmp.empNo) == 0) {
						workEmp[i].empRetire = 1;
					}
				}
				//����Ʈ�� ����� �ٽ� ������� ä���
				ListView_DeleteAllItems(hEMPList);
				for (i = 0, j = 0; i < totEmp; i++) {
					if (workEmp[i].empRetire == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = j;
						LI.iSubItem = 0;
						LI.pszText = workEmp[i].empNo;
						ListView_InsertItem(hEMPList, &LI);
						ListView_SetItemText(hEMPList, j, 1, (LPWSTR)workEmp[i].empBuseo);				//�μ�
						ListView_SetItemText(hEMPList, j, 2, (LPWSTR)workEmp[i].empPosCode);			//��å
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].empStartYear.wYear, workEmp[i].empStartYear.wMonth, workEmp[i].empStartYear.wDay);
						ListView_SetItemText(hEMPList, j, 3, str);										//�Ի���
						ListView_SetItemText(hEMPList, j, 4, (LPWSTR)workEmp[i].pInfo.pName[0]);		//�ѱ��̸�
						ListView_SetItemText(hEMPList, j, 5, (LPWSTR)workEmp[i].pInfo.pName[1]);		//�����̸�
						ListView_SetItemText(hEMPList, j, 6, (LPWSTR)workEmp[i].pInfo.pName[2]);		//�ѹ��̸�
						if (workEmp[i].pInfo.pSex == TRUE) {											//����
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 7, (LPWSTR)TEXT("��"));
						}
						wsprintf(str, TEXT("%d.%d.%d"), workEmp[i].pInfo.pBirth.wYear, workEmp[i].pInfo.pBirth.wMonth, workEmp[i].pInfo.pBirth.wDay);
						ListView_SetItemText(hEMPList, j, 8, str);										//�������
						ListView_SetItemText(hEMPList, j, 9, (LPWSTR)workEmp[i].pInfo.pAddress);		//�ּ�
						ListView_SetItemText(hEMPList, j, 10, (LPWSTR)workEmp[i].pInfo.pEmail);			//���ڿ���
						ListView_SetItemText(hEMPList, j, 11, (LPWSTR)workEmp[i].pInfo.pPhone[0]);		//����ó1
						ListView_SetItemText(hEMPList, j, 12, (LPWSTR)workEmp[i].pInfo.pPhone[1]);		//����ó2
						ListView_SetItemText(hEMPList, j, 13, (LPWSTR)workEmp[i].pInfo.pPhysical[0]);	//����
						ListView_SetItemText(hEMPList, j, 14, (LPWSTR)workEmp[i].pInfo.pPhysical[1]);	//ü��
						if (workEmp[i].pInfo.pFamily == TRUE) {											//��ȥ����
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						else {
							ListView_SetItemText(hEMPList, j, 15, (LPWSTR)TEXT("��ȥ"));
						}
						ListView_SetItemText(hEMPList, j, 16, (LPWSTR)workEmp[i].pInfo.pReligion);		//����
						ListView_SetItemText(hEMPList, j, 17, (LPWSTR)workEmp[i].pInfo.pPhysical[2]);	//�½÷�
						ListView_SetItemText(hEMPList, j, 18, (LPWSTR)workEmp[i].pInfo.pPhysical[3]);	//��÷�
						j++;
					}
				}
				//�Է� ��Ʈ�ѵ� ��ĭ���� �ʱ�ȭ
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

		//����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		if (hdr->hwndFrom == hEMPList) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//�����ȣ,�μ�,��å,�Ի���,�̸�,�����̸�,�ѹ��̸�,����,�������,�ּ�,���ڿ���,����ó1,����ó2,����,ü��,��ȥ����,����,�÷�(��),�÷�(��)
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
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 65, 13, TEXT("�����ȣ"), lstrlen(TEXT("�����ȣ")));
		TextOut(hdc, 65, 48, TEXT("�μ�"), lstrlen(TEXT("�μ�")));
		TextOut(hdc, 65, 83, TEXT("��å"), lstrlen(TEXT("��å")));
		TextOut(hdc, 65, 118, TEXT("�Ի���"), lstrlen(TEXT("�Ի���")));
		TextOut(hdc, 65, 153, TEXT("�̸�"), lstrlen(TEXT("�̸�")));
		TextOut(hdc, 65, 188, TEXT("�����̸�"), lstrlen(TEXT("�����̸�")));
		TextOut(hdc, 65, 223, TEXT("�ѹ��̸�"), lstrlen(TEXT("�ѹ��̸�")));
		TextOut(hdc, 65, 258, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 293, TEXT("�������"), lstrlen(TEXT("�������")));
		TextOut(hdc, 65, 328, TEXT("�ּ�"), lstrlen(TEXT("�ּ�")));
		TextOut(hdc, 65, 363, TEXT("���ڿ���"), lstrlen(TEXT("���ڿ���")));
		TextOut(hdc, 65, 398, TEXT("����ó1"), lstrlen(TEXT("����ó1")));
		TextOut(hdc, 65, 433, TEXT("����ó2"), lstrlen(TEXT("����ó2")));
		TextOut(hdc, 65, 470, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 505, TEXT("ü��"), lstrlen(TEXT("ü��")));
		TextOut(hdc, 65, 545, TEXT("��ȥ����"), lstrlen(TEXT("��ȥ����")));
		TextOut(hdc, 65, 585, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 620, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		TextOut(hdc, 65, 655, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
