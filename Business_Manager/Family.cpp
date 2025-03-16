#include "Family.h"

extern HINSTANCE g_hInst;
extern int totEmp;			//�����
extern EMP* workEmp;		//���
extern FAMILY* family;		//�������
extern int totFamily;		//��ü���������
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
	TCHAR famRelation[8][255] = { TEXT("����"),TEXT("����"),TEXT("��"),TEXT("��"),TEXT("�����"),TEXT("�ڳ�"),TEXT("����"),TEXT("������") };
	TCHAR famJob[6][255] = { TEXT("ȸ���"),TEXT("�ڿ���"),TEXT("�л�"),TEXT("�ֺ�"),TEXT("����"),TEXT("��Ÿ") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//���, �������� ����Ʈ�� ����
		hEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			100, 60, 340, 500, hWnd, (HMENU)ID_EMPLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hEmpLV, LVS_EX_FULLROWSELECT);
		hFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
			700, 60, 320, 500, hWnd, (HMENU)ID_FAMLV, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(hFamilyLV, LVS_EX_FULLROWSELECT);

		//��� ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("�̸�");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEmpLV, 3, &COL);

		//�������� ����Ʈ�信 ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPSTR)TEXT("�̸�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hFamilyLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 1;
		ListView_InsertColumn(hFamilyLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 2;
		ListView_InsertColumn(hFamilyLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 130;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 3;
		ListView_InsertColumn(hFamilyLV, 3, &COL);

		//����˻� edit ��Ʈ��
		hEmpno = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			135, 570, 150, 25, hWnd, (HMENU)ID_FINDEMPNO, g_hInst, NULL);
		//����˻� ��ư
		hFindBtn = CreateWindow(TEXT("button"), TEXT("����˻�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			300, 570, 100, 25, hWnd, (HMENU)ID_FIND, g_hInst, NULL);
		//����� static ��Ʈ��
		hEmpName = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			700, 29, 60, 22, hWnd, (HMENU)ID_EMPNAME, g_hInst, NULL);
		hFamEmpno = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			900, 29, 120, 22, hWnd, (HMENU)ID_FAMEMPNO, g_hInst, NULL);
		//����������� �����Է� ��Ʈ��
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

		//�ξ簡���߰� ��ư
		CreateWindow(TEXT("button"), TEXT("�߰�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			490, 235, 50, 25, hWnd, (HMENU)ID_FAMINSERT, g_hInst, NULL);
		//�ξ簡������ ��ư
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			545, 235, 50, 25, hWnd, (HMENU)ID_FAMMODIFY, g_hInst, NULL);
		//�ξ簡������ ��ư
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			600, 235, 50, 25, hWnd, (HMENU)ID_FAMDELETE, g_hInst, NULL);
		//�ξ簡������ �ٽ��Է� ��ư
		CreateWindow(TEXT("button"), TEXT("�ٽ��Է�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			490, 265, 160, 25, hWnd, (HMENU)ID_REFRESH, g_hInst, NULL);

		//����Ʈ�信 ������� ä���
		//�����ȣ,��å,�μ�,�̸�
		DBConnect();
		SelectEMP();
		DBDisconnect();
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_FIND:
			int idx;
			LVFINDINFO fi;
			//�˻��� ��� str�� ����
			GetWindowText(hEmpno, str, 255);
			//str�� hEmpLV���� ã��
			fi.flags = LVFI_STRING;
			fi.psz = str;
			fi.vkDirection = VK_DOWN;
			idx = ListView_FindItem(hEmpLV, -1, &fi);
			if (idx == -1) {
				MessageBox(hWnd, "�ش� ����� ����� �������� �ʽ��ϴ�.", NULL, MB_OK);
			}
			else {
				ListView_SetItemState(hEmpLV, -1, 0, LVIS_FOCUSED | LVIS_SELECTED);
				ListView_SetItemState(hEmpLV, idx, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				ListView_EnsureVisible(hEmpLV, idx, FALSE);
			}
			break;
		case ID_FAMINSERT:		//�߰���ư
			GetWindowText(hFamEmpno, tempFam.empNo, 12);
			if (lstrlen(tempFam.empNo) == 0) {
				MessageBox(hWnd, TEXT("��� ���� �� ���������� �߰��ϼ���"), TEXT("���� ����"), MB_OK);
			}
			else {
				//��Ʈ�ѿ� �Է¹��� �� �����ͼ� insert ����
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				SendMessage(hFamRel, CB_GETLBTEXT, SendMessage(hFamRel, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.relation);
				SendMessage(hFamJob, CB_GETLBTEXT, SendMessage(hFamJob, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.job);
				if (lstrlen(tempFam.name) == 0 || lstrlen(tempFam.age) == 0 || lstrlen(tempFam.relation) == 0 || lstrlen(tempFam.job) == 0) {
					MessageBox(hWnd, TEXT("������������"), NULL, MB_OK);
				}
				else {
					for (i = 0; i < ListView_GetItemCount(hFamilyLV); i++) {
						ListView_GetItemText(hFamilyLV, i, 0, str, 255);
						if (lstrcmp(tempFam.name, str) == 0) {
							MessageBox(hWnd, TEXT("�̸��� ������ ������ �߰��� �� �����ϴ�."), NULL, MB_OK);
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
							MessageBox(hWnd, TEXT("���輳������"), NULL, MB_OK);
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
			//�Է� ��Ʈ�� �ʱ�ȭ
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
				//��Ʈ���� ���� �ӽñ���ü tempFam�� ����
				GetWindowText(hFamEmpno, tempFam.empNo, 20);
				GetWindowText(hFamName, tempFam.name, 255);
				GetWindowText(hFamAge, tempFam.age, 5);
				SendMessage(hFamRel, CB_GETLBTEXT, SendMessage(hFamRel, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.relation);
				SendMessage(hFamJob, CB_GETLBTEXT, SendMessage(hFamJob, CB_GETCURSEL, 0, 0), (LPARAM)tempFam.job);
				//�������׿��� �����Ҷ� ������ȿ�� Ȯ���� ����

				if ((lstrcmp(tempFam.relation, famRelation[0]) == 0 || lstrcmp(tempFam.relation, famRelation[1]) == 0 ||
					lstrcmp(tempFam.relation, famRelation[2]) == 0 || lstrcmp(tempFam.relation, famRelation[3]) == 0 ||
					lstrcmp(tempFam.relation, famRelation[4]) == 0)) {
					for (j = 0; j < ListView_GetItemCount(hFamilyLV); j++) {
						ListView_GetItemText(hFamilyLV, j, 2, str, 255);
						if (i != j && lstrcmp(str, tempFam.relation) == 0) {
							MessageBox(hWnd, TEXT("���輳������"), NULL, MB_OK);
							lstrcpy(tempFam.relation, "");
							break;
						}
					}
				}
				//��� �Է°��� ��ȿ�ϴٸ� �ش� index�� �������� update
				if (lstrlen(tempFam.relation) != 0) {
					ListView_GetItemText(hFamilyLV, i, 0, str, 50);

					DBConnect();
					UpdateFamily(GetFamilyIndex(tempFam.empNo, str), tempFam);
					SelectFamily(tempFam.empNo);
					DBDisconnect();
					//�Է� ��Ʈ�� ��ĭ���� �ʱ�ȭ
					SetWindowText(hFamName, TEXT(""));
					SetWindowText(hFamAge, TEXT(""));
					SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
					SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
				}
			}
			break;
		case ID_FAMDELETE:		//������ư
			i = ListView_GetNextItem(hFamilyLV, -1, LVNI_ALL | LVNI_SELECTED);
			if (i == -1) {
				MessageBox(hWnd, TEXT("���� �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				//�����ȣ�� �̸��� ��Ʈ�ѿ��� �����ͼ� ���� �������� Ư��
				GetWindowText(hFamEmpno, tempFam.empNo, 20);
				GetWindowText(hFamName, tempFam.name, 255);
				ListView_GetItemText(hFamilyLV, i, 0, str, 50);
				DBConnect();
				DeleteFamily(GetFamilyIndex(tempFam.empNo, str));
				SelectFamily(tempFam.empNo);
				DBDisconnect();
				//�Է� ��Ʈ�� ��ĭ���� �ʱ�ȭ
				SetWindowText(hFamName, TEXT(""));
				SetWindowText(hFamAge, TEXT(""));
				SendMessage(hFamJob, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hFamRel, CB_SETCURSEL, (WPARAM)-1, 0);
			}
			break;
		case ID_REFRESH:		//�ٽ��Է¹�ư
			//�Է� ��Ʈ�� ��ĭ���� �ʱ�ȭ
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

		//�μ�����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		if (hdr->hwndFrom == hEmpLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					ListView_GetItemText(hEmpLV, nlv->iItem, 3, str, 12);
					ListView_GetItemText(hEmpLV, nlv->iItem, 0, tempFam.empNo, 255);

					//static��Ʈ�ѿ� �̸�,����ѷ��� �����ֱ�
					SetWindowText(hEmpName, str);
					SetWindowText(hFamEmpno, tempFam.empNo);

					//�������׸���Ʈ�信 ����������� �Ѹ���
					DBConnect();
					SelectFamily((LPSTR)tempFam.empNo);
					DBDisconnect();

					//�Է� ��Ʈ�� �ʱ�ȭ
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
				}
				return TRUE;
			}
		}
		else if (hdr->hwndFrom == hFamilyLV) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//LV���� ������ ������ �Է� ��Ʈ�ѿ� �Ѹ���
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
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 120, 30, TEXT("���"), lstrlen(TEXT("���")));
		TextOut(hdc, 760, 30, TEXT("�� ����"), lstrlen(TEXT("�� ����")));
		TextOut(hdc, 870, 30, TEXT("���"), lstrlen(TEXT("���")));
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
