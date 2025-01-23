#include "Report.h"

extern HINSTANCE g_hInst;
extern int totEmp;
extern EMP* workEmp;

HWND hReportEmpLV, hOptionCombo, hSearchEdit, hMaleCheck, hFemaleCheck, hWorkCheck, hRetireCheck, hMoveCheck;
enum { ID_REPORTEMPLV = 1, ID_OPTIONCOMBO, ID_SEARCHEDIT, ID_SEARCHBT, ID_MALECHECK, ID_FEMALECHECK, ID_WORKCHECK, ID_RETIRECHECK, ID_MOVECHECK };

LRESULT CALLBACK InitReportMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	TCHAR searchOption[4][255] = { TEXT("�̸�"),TEXT("��å"),TEXT("�μ�"),TEXT("���") };
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
		//����Ʈ�� ����
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 100, 140, 700, 500, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		//����Ʈ�� ��� �߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("���");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReportEmpLV, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�����");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReportEmpLV, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 120;
		COL.pszText = (LPWSTR)TEXT("�μ�");
		COL.iSubItem = 2;
		ListView_InsertColumn(hReportEmpLV, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("��å");
		COL.iSubItem = 3;
		ListView_InsertColumn(hReportEmpLV, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 180;
		COL.pszText = (LPWSTR)TEXT("����ó");
		COL.iSubItem = 4;
		ListView_InsertColumn(hReportEmpLV, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);
		for (i = 0; i < totEmp; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = workEmp[i].empNo;
			ListView_InsertItem(hReportEmpLV, &LI);											//���
			ListView_SetItemText(hReportEmpLV, i, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
			ListView_SetItemText(hReportEmpLV, i, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
			ListView_SetItemText(hReportEmpLV, i, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
			ListView_SetItemText(hReportEmpLV, i, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
			if (workEmp[i].pInfo.pSex == TRUE) {
				ListView_SetItemText(hReportEmpLV, i, 5, (LPWSTR)TEXT("��"));				//��
			}
			else {
				ListView_SetItemText(hReportEmpLV, i, 5, (LPWSTR)TEXT("��"));				//��
			}
		}

		//�˻��ɼ� �޺��ڽ�
		hOptionCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 130, 55, 150, 200, hWnd, (HMENU)ID_OPTIONCOMBO, g_hInst, NULL);
		for (i = 0; i < 4; i++) {
			SendMessage(hOptionCombo, CB_ADDSTRING, 0, (LPARAM)searchOption[i]);
		}
		//�˻� ����Ʈ
		hSearchEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 300, 55, 400, 25, hWnd, (HMENU)ID_SEARCHEDIT, g_hInst, NULL);
		//���� üũ�ڽ�
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 305, 90, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 360, 90, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 415, 90, 75, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 495, 90, 75, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);
		//�λ��̵� üũ�ڽ�
		hMoveCheck = CreateWindow(TEXT("button"), TEXT("�λ��̵�"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 575, 90, 90, 25, hWnd, (HMENU)ID_MOVECHECK, g_hInst, NULL);
		//�˻� ��ư
		CreateWindow(TEXT("button"), TEXT("�˻�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 710, 50, 70, 55, hWnd, (HMENU)ID_SEARCHBT, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
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
			}
			else {
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_RETIRECHECK:	//���� üũ�ڽ� üũ,����
			if (SendMessage(hRetireCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(hWorkCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(hRetireCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_MOVECHECK:		//�λ��̵� üũ�ڽ� üũ, ����
			if (SendMessage(hMoveCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(hMoveCheck, BM_SETCHECK, BST_CHECKED, 0);
			}
			else {
				SendMessage(hMoveCheck, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			break;
		case ID_SEARCHBT:		//�˻� ��ư
			ind = SendMessage(hOptionCombo, CB_GETCURSEL, 0, 0);
			//�˻� �ɼ� �޺��ڽ����� ������ �Ͼ���� ������ �޽����ڽ�
			if (ind == -1) {
				MessageBox(hWnd, TEXT("�˻� �ɼ��� �����ϼ���."), NULL, MB_OK);
			}
			else {				//���õǾ��ִ°��
				//�˻� edit�� �� str�� ����
				GetWindowText(hSearchEdit, str, 255);
				//����Ʈ�� ������ ��� �����
				ListView_DeleteAllItems(hReportEmpLV);
				for (i = 0; i < totEmp; i++) {
					//���ǿ� �´� �������
					if (lstrlen(str) == 0) {
						j = 1;
					}
					else if (ind == 0 && (lstrcmp(workEmp[i].pInfo.pName[0], str) == 0 || lstrcmp(workEmp[i].pInfo.pName[1], str) == 0
						|| lstrcmp(workEmp[i].pInfo.pName[2], str) == 0)) {				//�̸�
						j = 1;
					}
					else if (ind == 1 && lstrcmp(workEmp[i].empPosCode, str) == 0) {	//��å
						j = 1;
					}
					else if (ind == 2 && lstrcmp(workEmp[i].empBuseo, str) == 0) {		//�μ�
						j = 1;
					}
					else if (ind == 3 && lstrcmp(workEmp[i].empNo, str) == 0) {			//���
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
					//�˻� �ɼǿ� �´���
					if (j == 1) {
						if (workEmp[i].empNo[4] == workEmp[i].empPosCode[0] && workEmp[i].empNo[5] == workEmp[i].empPosCode[1]) {
							j = 0;
						}
						if (m) {		//�� üũ
							if (w) {	//���� üũ
								if (mv) {	//��,����,�λ��̵�
									if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2 && j == 0) {
										j = ListView_GetItemCount(hReportEmpLV);
										LI.mask = LVIF_TEXT;
										LI.iItem = j;
										LI.iSubItem = 0;
										LI.pszText = workEmp[i].empNo;
										ListView_InsertItem(hReportEmpLV, &LI);											//���
										ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
										ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
										ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
										ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
										if (workEmp[i].pInfo.pSex == TRUE) {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
										}
										else {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
										}
									}
								}
								else {		//��,����
									if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2) {
										j = ListView_GetItemCount(hReportEmpLV);
										LI.mask = LVIF_TEXT;
										LI.iItem = j;
										LI.iSubItem = 0;
										LI.pszText = workEmp[i].empNo;
										ListView_InsertItem(hReportEmpLV, &LI);											//���
										ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
										ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
										ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
										ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
										if (workEmp[i].pInfo.pSex == TRUE) {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
										}
										else {
											ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
										}
									}
								}
							}
							else {
								if (r) {	//���� üũ
									if (mv) {	//��,����,�λ��̵�
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire == 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
									else {		//��,����
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire == 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
								}
								else {		//����, ���� ��� üũX (��)
									if (mv) {	//��,����,�λ��̵�
										if (workEmp[i].pInfo.pSex == TRUE && workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											} 
										}
									}
									else {		//��,����
										if (workEmp[i].pInfo.pSex == TRUE) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
								}
							}
						}
						else {
							if (fm) {	//�� üũ
								if (w) {	//���� üũ
									if (mv) {	//��,����,�λ��̵�
										if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
									else {	//��,����
										if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
								}
								else {
									if (r) {	//���� üũ
										if (mv) {	//��,����,�λ��̵�
											if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire == 2 && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
										else {	//��,����
											if (workEmp[i].pInfo.pSex == FALSE && workEmp[i].empRetire != 2) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
									}
									else {		//����, ���� ��� üũX
										if (mv) {	//��,�λ��̵�	
											if (workEmp[i].pInfo.pSex == FALSE && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
										else {	//��	
											if (workEmp[i].pInfo.pSex == TRUE) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
									}
								}
							}
							else {		//��,�� ��� üũX
								if (w) {	//���� üũ
									if (mv) {	//����,�λ��̵�	
										if (workEmp[i].empRetire != 2 && j == 0) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
									else {	//����		
										if (workEmp[i].empRetire != 2) {
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
										}
									}
								}
								else {		//��,�� ��� üũx
									if (r) {	//���� üũ
										if (mv) {	//����,�λ��̵�	
											if (workEmp[i].empRetire == 2 && j == 0) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
										else {	//����	
											if (workEmp[i].empRetire == 2) {
												j = ListView_GetItemCount(hReportEmpLV);
												LI.mask = LVIF_TEXT;
												LI.iItem = j;
												LI.iSubItem = 0;
												LI.pszText = workEmp[i].empNo;
												ListView_InsertItem(hReportEmpLV, &LI);											//���
												ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
												ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
												ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
												ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
												if (workEmp[i].pInfo.pSex == TRUE) {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
												else {
													ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
												}
											}
										}
									}
									else {		//����, ���� ��� üũX
										if (mv) {	//�λ��̵�	
											if (j == 0) {
												if (j == 0) {
													j = ListView_GetItemCount(hReportEmpLV);
													LI.mask = LVIF_TEXT;
													LI.iItem = j;
													LI.iSubItem = 0;
													LI.pszText = workEmp[i].empNo;
													ListView_InsertItem(hReportEmpLV, &LI);											//���
													ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
													ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
													ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
													ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
													if (workEmp[i].pInfo.pSex == TRUE) {
														ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
													}
													else {
														ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
													}
												}
											}
										}
										else {	//��� üũx	
											j = ListView_GetItemCount(hReportEmpLV);
											LI.mask = LVIF_TEXT;
											LI.iItem = j;
											LI.iSubItem = 0;
											LI.pszText = workEmp[i].empNo;
											ListView_InsertItem(hReportEmpLV, &LI);											//���
											ListView_SetItemText(hReportEmpLV, j, 1, (LPWSTR)workEmp[i].pInfo.pName[0]);	//�̸�
											ListView_SetItemText(hReportEmpLV, j, 2, (LPWSTR)workEmp[i].empBuseo);			//�μ�
											ListView_SetItemText(hReportEmpLV, j, 3, (LPWSTR)workEmp[i].empPosCode);		//��å
											ListView_SetItemText(hReportEmpLV, j, 4, (LPWSTR)workEmp[i].pInfo.pPhone);		//����ó
											if (workEmp[i].pInfo.pSex == TRUE) {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
											}
											else {
												ListView_SetItemText(hReportEmpLV, j, 5, (LPWSTR)TEXT("��"));				//��
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