#include "Base.h";

extern HINSTANCE g_hInst;
HWND hBuseoList;			//�μ�����Ʈ�� �ڵ�
HWND hBCode;				//�μ��ڵ忡��Ʈ������ �ڵ�
HWND hBName;				//�μ��̸�����Ʈ������ �ڵ�
HWND hReligionList;			//��������Ʈ�� �ڵ�
HWND hRCode;				//�����ڵ忡��Ʈ������ �ڵ�
HWND hRName;				//�����̸�����Ʈ������ �ڵ�
HWND hPositionList;			//��������Ʈ�� �ڵ�
HWND hPCode;				//�����ڵ忡��Ʈ������ �ڵ�
HWND hPName;				//�����̸�����Ʈ������ �ڵ�
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����

enum { IDC_INSERT = 1, IDC_MODIFY, IDC_DEL, ID_NAME, ID_CODE, ID_BLIST, ID_RLIST, ID_PLIST };

LRESULT CALLBACK InitBuseoMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	BASE tempBase;		//�ӽ� ����ü

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hBuseoList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_BLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�μ��ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hBuseoList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�μ���");
		COL.iSubItem = 1;
		ListView_InsertColumn(hBuseoList, 1, &COL);
		//����Ʈ�信 �μ� ä���
		for (i = 0; i < totB; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = buseo[i].code;
			ListView_InsertItem(hBuseoList, &LI);
			ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
		}
		//�μ��ڵ� edit����
		hBCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//�μ��� edit����
		hBName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư

			//�μ��ڵ�� �μ��̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetWindowText(hBCode, tempBase.code, 3);
			GetWindowText(hBName, tempBase.name, 255);

			//���̰� 0�ΰ�� break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("���԰� ����"), MB_OK);
				break;
			}

			//�ߺ������� üũ
			for (i = 0; i < totB; i++) {
				if (lstrcmp(buseo[i].code, tempBase.code) == 0 || lstrcmp(buseo[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}

			//�ߺ����� �ʾҴٸ� �μ� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {

				buseo = (BASE*)realloc(buseo, (totB + 1) * sizeof(BASE));	//�μ� ������ ���Ҵ�
				buseo[totB] = tempBase;
				totB++;		//�μ�����++

				ListView_DeleteAllItems(hBuseoList);		//����Ʈ�� ���

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totB; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = buseo[i].code;
					ListView_InsertItem(hBuseoList, &LI);
					ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hBCode, TEXT(""));
			SetWindowText(hBName, TEXT(""));

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				//�μ��ڵ�� �μ��̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetWindowText(hBCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hBName, tempBase.name, lstrlen(tempBase.name));

				//���̰� 0�ΰ�� break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("������ ����"), MB_OK);
					break;
				}
				//�ߺ������� üũ
				for (i = 0; i < totB; i++) {
					if (i != ind && (lstrcmp(buseo[i].code, tempBase.code) == 0 || lstrcmp(buseo[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//�ߺ����̶�� �����Ұ�
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° buseo�� ���� �ٲ�
					buseo[ind] = tempBase;

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hBuseoList);

					for (i = 0; i < totB; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = buseo[i].code;
						ListView_InsertItem(hBuseoList, &LI);
						ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
					}
				}
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hBCode, TEXT(""));
			SetWindowText(hBName, TEXT(""));

			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hBuseoList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totB - 1; i++) {
					buseo[i] = buseo[i + 1];
				}

				lstrcpy(buseo[totB - 1].code, TEXT(""));
				lstrcpy(buseo[totB - 1].name, TEXT(""));
				totB--;
				buseo = (BASE*)realloc(buseo, totB * sizeof(BASE));
			}
			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
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

		//�μ�����Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
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
		TextOut(hdc, 300, 155, TEXT("�μ��ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�μ��̸�"), 4);
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
	BASE tempBase;		//�ӽ� ����ü

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hReligionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_RLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�����ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReligionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("������");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReligionList, 1, &COL);

		//����Ʈ�信 ���� ä���
		for (i = 0; i < totR; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = religion[i].code;
			ListView_InsertItem(hReligionList, &LI);
			ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
		}

		//�����ڵ� edit����
		hRCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//������ edit����
		hRName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư

			//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetWindowText(hRCode, tempBase.code, lstrlen(tempBase.code));
			GetWindowText(hRName, tempBase.name, lstrlen(tempBase.name));

			//���̰� 0�ΰ�� break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("���԰� ����"), MB_OK);
				break;
			}

			//�ߺ������� üũ
			for (i = 0; i < totR; i++) {
				if (lstrcmp(religion[i].code, tempBase.code) == 0 || lstrcmp(religion[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//�ߺ����� �ʾҴٸ� ���� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {
				religion = (BASE*)realloc(religion, (totR + 1) * sizeof(BASE));	//���� ������ ���Ҵ�
				religion[totR] = tempBase;
				totR++;		//��������++

				ListView_DeleteAllItems(hReligionList);		//����Ʈ�� ���

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totR; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = religion[i].code;
					ListView_InsertItem(hReligionList, &LI);
					ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hRCode, TEXT(""));
			SetWindowText(hRName, TEXT(""));

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetWindowText(hRCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hRName, tempBase.name, lstrlen(tempBase.name));

				//���̰� 0�ΰ�� break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("������ ����"), MB_OK);
					break;
				}

				//�ߺ������� üũ
				for (i = 0; i < totR; i++) {
					if (i != ind && (lstrcmp(religion[i].code, tempBase.code) == 0 || lstrcmp(religion[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//�ߺ����̶�� ���� �Ұ�
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° religion�� ���� �ٲ�
					religion[ind] = tempBase;

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hReligionList);

					for (i = 0; i < totR; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = religion[i].code;
						ListView_InsertItem(hReligionList, &LI);
						ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
					}
				}
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hRCode, TEXT(""));
			SetWindowText(hRName, TEXT(""));

			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hReligionList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totR - 1; i++) {
					religion[i] = religion[i + 1];
				}
				lstrcpy(religion[totR - 1].code, TEXT(""));
				lstrcpy(religion[totR - 1].name, TEXT(""));
				totR--;
				religion = (BASE*)realloc(religion, totR * sizeof(BASE));

			}
			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
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

		//��������Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
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
		TextOut(hdc, 300, 155, TEXT("�����ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�����̸�"), 4);
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
	BASE tempBase;		//�ӽ� ����ü

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hPositionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_PLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�����ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hPositionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("������");
		COL.iSubItem = 1;
		ListView_InsertColumn(hPositionList, 1, &COL);
		//����Ʈ�信 ���� ä���
		for (i = 0; i < totP; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = position[i].code;
			ListView_InsertItem(hPositionList, &LI);
			ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
		}
		//�����ڵ� edit����
		hPCode = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//������ edit����
		hPName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư

			//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetWindowText(hPCode, tempBase.code, lstrlen(tempBase.code));
			GetWindowText(hPName, tempBase.name, lstrlen(tempBase.name));

			//���̰� 0�ΰ�� break
			if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
				MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("���԰� ����"), MB_OK);
				break;
			}

			//�ߺ������� üũ
			for (i = 0; i < totP; i++) {
				if (lstrcmp(position[i].code, tempBase.code) == 0 || lstrcmp(position[i].name, tempBase.name) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//�ߺ����� �ʾҴٸ� �μ� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {
				position = (BASE*)realloc(position, (totP + 1) * sizeof(BASE));	//���� ������ ���Ҵ�
				position[totP] = tempBase;
				totP++;		//��������++

				ListView_DeleteAllItems(hPositionList);		//����Ʈ�� ���

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totP; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = position[i].code;
					ListView_InsertItem(hPositionList, &LI);
					ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);

			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hPCode, TEXT(""));
			SetWindowText(hPName, TEXT(""));

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {

				//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetWindowText(hPCode, tempBase.code, lstrlen(tempBase.code));
				GetWindowText(hPName, tempBase.name, lstrlen(tempBase.name));

				//���̰� 0�ΰ�� break
				if (lstrlen(tempBase.code) == 0 || lstrlen(tempBase.name) == 0) {
					MessageBox(hWnd, TEXT("���̰� 0�� �����δ� ������ �Ұ����մϴ�."), TEXT("������ ����"), MB_OK);
					break;
				}

				//�ߺ������� üũ
				for (i = 0; i < totP; i++) {
					if (i != ind && (lstrcmp(position[i].code, tempBase.code) == 0 || lstrcmp(position[i].name, tempBase.name) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° position�� ������ �ٲ�
					position[ind] = tempBase;

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hPositionList);		//����Ʈ�� ���

					for (i = 0; i < totP; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = position[i].code;
						ListView_InsertItem(hPositionList, &LI);
						ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
					}
				}
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
			SetWindowText(hPCode, TEXT(""));
			SetWindowText(hPName, TEXT(""));

			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hPositionList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totP - 1; i++) {
					position[i] = position[i + 1];
				}
				lstrcpy(position[totP - 1].code, TEXT(""));
				lstrcpy(position[totP - 1].name, TEXT(""));
				totP--;
				position = (BASE*)realloc(position, totP * sizeof(BASE));
			}

			//������ �ڵ�,�̸� ��Ʈ�� ��ĭ���� �ʱ�ȭ
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

		//��������Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
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
		TextOut(hdc, 300, 155, TEXT("�����ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�����̸�"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}