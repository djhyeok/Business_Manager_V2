#include "Family.h"

extern HINSTANCE g_hInst;
extern int totEmp;			//�����
extern EMP* workEmp;		//���
extern FAMILY* family;		//�������
extern int totFamily;		//��ü���������

HWND hEmpLV, hFamilyLV, hEmpName, hFamName, hFamAge, hFamRel, hFamJob, hFamInsert;
enum {
	ID_EMPLV, ID_FAMLV, ID_EMPNAME, ID_FAMNAME, ID_FAMAGE, ID_FAMREL, ID_FAMJOB,
	ID_FAMINSERT, ID_FAMMODIFY, ID_FAMDELETE, ID_COMPLETE
};
/*
	�������׵��
	-��� �����ε�
	��,��,����,���� �� �Ѹ� �־���ϴ� �� ����ó��
*/
LRESULT CALLBACK InitEMPFamilyMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	INITCOMMONCONTROLSEX icex;
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[256];
	HFONT hFont, OldFont;
	static FAMILY tempFam;
	int i, j;
	TCHAR famRelation[8][255] = { TEXT("����"),TEXT("����"),TEXT("��"),TEXT("��"),TEXT("�����"),TEXT("�ڳ�"),TEXT("����"),TEXT("������") };
	TCHAR famJob[6][255] = { TEXT("ȸ���"),TEXT("�ڿ���"),TEXT("�л�"),TEXT("�ֺ�"),TEXT("����"),TEXT("��Ÿ") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//���, �������� ����Ʈ�� ����
		hEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			100, 60, 340, 500, hWnd, (HMENU)ID_EMPLV, g_hInst, NULL);
		hFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			700, 60, 470, 500, hWnd, (HMENU)ID_FAMLV, g_hInst, NULL);

		//��� ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�̸�");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEmpLV, 3, &COL);

		//�������� ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hFamilyLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�̸�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hFamilyLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 2;
		ListView_InsertColumn(hFamilyLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 3;
		ListView_InsertColumn(hFamilyLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 4;
		ListView_InsertColumn(hFamilyLV, 4, &COL);

		//����� static ��Ʈ��
		hEmpName = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			700, 29, 60, 22, hWnd, (HMENU)ID_EMPNAME, g_hInst, NULL);
		//����������� �����Է� ��Ʈ��
		hFamName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			540, 78, 100, 25, hWnd, (HMENU)ID_FAMNAME, g_hInst, NULL);
		hFamRel = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			540, 118, 100, 175, hWnd, (HMENU)ID_FAMREL, g_hInst, NULL);
		for (i = 0; i < 8; i++) {
			SendMessage(hFamRel, CB_ADDSTRING, 0, (LPARAM)famRelation[i]);
		}
		hFamAge = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			540, 158, 100, 25, hWnd, (HMENU)ID_FAMAGE, g_hInst, NULL);
		hFamJob = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			540, 198, 100, 125, hWnd, (HMENU)ID_FAMJOB, g_hInst, NULL);
		for (i = 0; i < 6; i++) {
			SendMessage(hFamJob, CB_ADDSTRING, 0, (LPARAM)famJob[i]);
		}

		//�ξ簡���߰� ��ư
		CreateWindow(TEXT("button"), TEXT("�߰�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			490, 235, 50, 25, hWnd, (HMENU)ID_FAMINSERT, g_hInst, NULL);
		//�ξ簡������ ��ư
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			545, 235, 50, 25, hWnd, (HMENU)ID_FAMMODIFY, g_hInst, NULL);
		//�ξ簡������ ��ư
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			600, 235, 50, 25, hWnd, (HMENU)ID_FAMDELETE, g_hInst, NULL);
		//�ξ簡������ ��ư
		CreateWindow(TEXT("button"), TEXT("�Ϸ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			1180, 530, 70, 30, hWnd, (HMENU)ID_COMPLETE, g_hInst, NULL);

		//����Ʈ�信 ������� ä���
		//�����ȣ,��å,�μ�,�̸�
		for (i = 0, j = 0; i < totEmp; i++) {
			if (workEmp[i].empRetire != 2) {
				LI.mask = LVIF_TEXT;
				LI.iItem = j;
				LI.iSubItem = 0;
				LI.pszText = workEmp[i].empNo;
				ListView_InsertItem(hEmpLV, &LI);
				ListView_SetItemText(hEmpLV, j, 1, (LPWSTR)workEmp[i].empBuseo);		//�μ�
				ListView_SetItemText(hEmpLV, j, 2, (LPWSTR)workEmp[i].empPosCode);		//��å
				ListView_SetItemText(hEmpLV, j, 3, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�ѱ��̸�
				j++;
			}
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FAMJOB:			//�������� �޺��ڽ�
			//���� �޺��ڽ��� �� �ӽ� ����ütempFam�� ����
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hFamJob, CB_GETCURSEL, 0, 0);
				SendMessage(hFamJob, CB_GETLBTEXT, i, (LPARAM)tempFam.job);
				break;
			}
			break;
		case ID_FAMREL:			//�������� �޺��ڽ�
			//���� �޺��ڽ��� �� �ӽ� ����ütempFam�� ����
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				i = SendMessage(hFamRel, CB_GETCURSEL, 0, 0);
				SendMessage(hFamRel, CB_GETLBTEXT, i, (LPARAM)tempFam.relation);
				break;
			}
			break;
		case ID_FAMINSERT:		//�߰���ư
			i = ListView_GetNextItem(hEmpLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("�߰��� ����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				//GetWindowText(hFamJob, tempFam.job, 255);
				//GetWindowText(hFamRel, tempFam.relation, 255);

				for (i = 0; i < ListView_GetItemCount(hFamilyLV); i++) {
					ListView_GetItemText(hFamilyLV, i, 3, str, 255);
					if ((lstrcmp(tempFam.relation, famRelation[0]) == 0 || lstrcmp(tempFam.relation, famRelation[1]) == 0 ||
						lstrcmp(tempFam.relation, famRelation[2]) == 2 || lstrcmp(tempFam.relation, famRelation[3]) == 3 ||
						lstrcmp(tempFam.relation, famRelation[4]) == 4) && lstrcmp(tempFam.relation, str) == 0) {
						MessageBox(hWnd, TEXT("���輳������"), NULL, MB_OK);
						SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
						lstrcpy(tempFam.relation, TEXT(""));
						break;
					}
				}
				if (lstrlen(tempFam.relation)) {
					LI.mask = LVIF_TEXT;
					LI.iItem = ListView_GetItemCount(hFamilyLV);
					LI.iSubItem = 0;
					LI.pszText = tempFam.empNo;
					ListView_InsertItem(hFamilyLV, &LI);
					ListView_SetItemText(hFamilyLV, ListView_GetItemCount(hFamilyLV) - 1, 1, (LPWSTR)tempFam.name);
					ListView_SetItemText(hFamilyLV, ListView_GetItemCount(hFamilyLV) - 1, 2, (LPWSTR)tempFam.age);
					ListView_SetItemText(hFamilyLV, ListView_GetItemCount(hFamilyLV) - 1, 3, (LPWSTR)tempFam.relation);
					ListView_SetItemText(hFamilyLV, ListView_GetItemCount(hFamilyLV) - 1, 4, (LPWSTR)tempFam.job);
				}
			}
			SetWindowText(hFamName, TEXT(""));
			SetWindowText(hFamAge, TEXT(""));
			SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
			break;
		case ID_FAMMODIFY:		//������ư
			i = ListView_GetNextItem(hFamilyLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("���� �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				GetWindowText(hFamJob, tempFam.job, 255);
				GetWindowText(hFamRel, tempFam.relation, 255);
				/*
				�������׿��� �����Ҷ� ��ġ�� �����ִ��� Ȯ���� ����
				*/
				if ((lstrcmp(tempFam.relation, famRelation[0]) == 0 || lstrcmp(tempFam.relation, famRelation[1]) == 0 ||
					lstrcmp(tempFam.relation, famRelation[2]) == 2 || lstrcmp(tempFam.relation, famRelation[3]) == 3 ||
					lstrcmp(tempFam.relation, famRelation[4]) == 4)) {
					for (j = 0; j < ListView_GetItemCount(hFamilyLV); j++) {
						ListView_GetItemText(hFamilyLV, j, 3, str, 255);
						if (i != j && lstrcmp(str, tempFam.relation) == 0) {
							MessageBox(hWnd, TEXT("���輳������"), NULL, MB_OK);
							break;
						}
					}
					if (j != ListView_GetItemCount(hFamilyLV)) {
						break;
					}
				}
				
				ListView_SetItemText(hFamilyLV, i, 1, (LPWSTR)tempFam.name);
				ListView_SetItemText(hFamilyLV, i, 2, (LPWSTR)tempFam.age);
				ListView_SetItemText(hFamilyLV, i, 3, (LPWSTR)tempFam.relation);
				ListView_SetItemText(hFamilyLV, i, 4, (LPWSTR)tempFam.job);
			}
			break;
		case ID_FAMDELETE:		//������ư
			i = ListView_GetNextItem(hFamilyLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("���� �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hFamilyLV, i);
			}
			break;
		case ID_COMPLETE:		//�Ϸ��ư
			i = ListView_GetNextItem(hEmpLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_GetItemText(hFamilyLV, i, 0, tempFam.empNo, 255);
				//�ش� �����ȣ�� ���� �������� �Ǽ� count
				for (i = 0, j = 0; i < totFamily; i++) {
					if (lstrcmp(family[i].empNo, tempFam.empNo) == 0) {
						j++;
					}
				}
				//�ش� �������׵� �ϰ� ������ ���
				for (i = 0; i < totFamily - j - 1; i++) {
					if (lstrcmp(family[i].empNo, tempFam.empNo) == 0) {
						family[i] = family[i + j];
					}
				}
				//�� ������ ���� �� ���Ҵ�
				totFamily -= j;
				family = (FAMILY*)realloc(family, sizeof(FAMILY) * totFamily);

				for (i = 0; i < ListView_GetItemCount(hFamilyLV); i++) {
					//�ӽñ���ü�� ���� ����
					ListView_GetItemText(hFamilyLV, i, 1, tempFam.name, 255);
					ListView_GetItemText(hFamilyLV, i, 2, tempFam.age, 5);
					ListView_GetItemText(hFamilyLV, i, 3, tempFam.relation, 255);
					ListView_GetItemText(hFamilyLV, i, 4, tempFam.job, 255);

					family = (FAMILY*)realloc(family, (totFamily + 1) * sizeof(FAMILY));
					family[totFamily] = tempFam;
					totFamily++;
				}
				ListView_DeleteAllItems(hFamilyLV);
				//��Ʈ�� �ʱ�ȭ
				SetWindowText(hEmpName, TEXT(""));
				SetWindowText(hFamName, TEXT(""));
				SetWindowText(hFamAge, TEXT(""));
				SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);

				//�ӽð��� ����ü �ʱ�ȭ
				lstrcpy(tempFam.empNo, TEXT(""));
				lstrcpy(tempFam.age, TEXT(""));
				lstrcpy(tempFam.job, TEXT(""));
				lstrcpy(tempFam.name, TEXT(""));
				lstrcpy(tempFam.relation, TEXT(""));
				break;
			}
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//�μ�����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		if (hdr->hwndFrom == hEmpLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					ListView_GetItemText(hEmpLV, nlv->iItem, 3, str, 12);
					ListView_GetItemText(hEmpLV, nlv->iItem, 0, tempFam.empNo, 255);
					SetWindowText(hEmpName, str);
					ListView_DeleteAllItems(hFamilyLV);
					//�������׸���Ʈ�信 ����������� �Ѹ���
					for (i = 0, j = 0; i < totFamily; i++) {
						if (lstrcmp(tempFam.empNo, family[i].empNo) == 0) {
							LI.mask = LVIF_TEXT;
							LI.iItem = j;
							LI.iSubItem = 0;
							LI.pszText = family[i].empNo;
							ListView_InsertItem(hFamilyLV, &LI);								//���
							ListView_SetItemText(hFamilyLV, j, 1, (LPWSTR)family[i].name);		//�̸�
							ListView_SetItemText(hFamilyLV, j, 2, (LPWSTR)family[i].age);		//����
							ListView_SetItemText(hFamilyLV, j, 3, (LPWSTR)family[i].relation);	//����
							ListView_SetItemText(hFamilyLV, j, 4, (LPWSTR)family[i].job);		//����
							j++;
						}
					}

				}
				return TRUE;
			}
		}
		else if (hdr->hwndFrom == hFamilyLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					ListView_GetItemText(hFamilyLV, nlv->iItem, 1, str, 255);
					SetWindowText(hFamName, str);
					ListView_GetItemText(hFamilyLV, nlv->iItem, 2, str, 5);
					SetWindowText(hFamAge, str);
					ListView_GetItemText(hFamilyLV, nlv->iItem, 3, str, 255);
					for (i = 0; i < 8; i++) {
						if (lstrcmp(str, (LPCWSTR)famRelation[i]) == 0) {
							SendMessage(hFamRel, CB_SETCURSEL, i, 0);
							break;
						}
					}
					ListView_GetItemText(hFamilyLV, nlv->iItem, 4, str, 255);
					for (i = 0; i < 6; i++) {
						if (lstrcmp(str, (LPCWSTR)famJob[i]) == 0) {
							SendMessage(hFamJob, CB_SETCURSEL, i, 0);
							break;
						}
					}
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
		TextOut(hdc, 120, 30, TEXT("���"), lstrlen(TEXT("���")));
		TextOut(hdc, 760, 30, TEXT("�� ����"), lstrlen(TEXT("�� ����")));
		TextOut(hdc, 490, 80, TEXT("�̸�"), lstrlen(TEXT("�̸�")));
		TextOut(hdc, 490, 120, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 490, 160, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 490, 200, TEXT("����"), lstrlen(TEXT("����")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
