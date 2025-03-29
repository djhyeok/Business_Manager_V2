#include "Emp.h"
/*
��������
WM_CREATE���� select�� ������ DB������ �ҷ���
���� ���� ���� �� DB���� �ٽ� select�ؼ� LV�� �Ѹ�
*/
extern HINSTANCE g_hInst;
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpReligion;	//��Ʈ�� �ڵ�
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDC_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_REFRESH
};

//������� ���ν���
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HFONT hFont, OldFont;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int index, cal, num;
	static EMP tempEmp;
	SYSTEMTIME st;
	TCHAR str[255];

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		InitControl(&hWnd);
		ListView_SetExtendedListViewStyle(hEMPList, LVS_EX_FULLROWSELECT);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:			//���� ��ư
			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//�Ի���
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//����
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
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);							//�÷�(��)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);						//�÷�(��)
			DBConnect();
			num = CountRecord((LPSTR)"EMP");
			SendMessage(hEmpBuseo, CB_GETLBTEXT, SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.empBuseo);					//�μ�
			lstrcpy(tempEmp.empBuseo, Name2Code((LPSTR)"BUSEO", (LPSTR)tempEmp.empBuseo));
			SendMessage(hEmpReligion, CB_GETLBTEXT, SendMessage(hEmpReligion, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.pInfo.pReligion);	//����
			lstrcpy(tempEmp.pInfo.pReligion, Name2Code((LPSTR)"RELIGION", (LPSTR)tempEmp.pInfo.pReligion));
			SendMessage(hEmpPoscode, CB_GETLBTEXT, SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.empPosCode);			//��å
			lstrcpy(tempEmp.empPosCode, Name2Code((LPSTR)"POSITION", (LPSTR)tempEmp.empPosCode));
			DBDisconnect();
			//�ٹ����� �ʱ�ȭ
			tempEmp.empRetire = 0;
			//�����ȣ����
			wsprintf(tempEmp.empNo, TEXT("%d"), tempEmp.empStartYear.wYear);
			lstrcat(tempEmp.empNo, tempEmp.empBuseo);
			if (tempEmp.pInfo.pSex == TRUE) {
				lstrcat(tempEmp.empNo, TEXT("1"));
			}
			else {
				lstrcat(tempEmp.empNo, TEXT("2"));
			}
			cal = num + 1;
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
			GetWindowText(hEmpNo, str, 255);
			if (lstrlen(str) != 0) {
				MessageBox(hWnd, TEXT("���� ��� �������δ� ������ �Ұ����մϴ�."), TEXT("���� ����"), MB_OK);
			}
			else if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {

				DBConnect();
				EMPInsertSQL(tempEmp);
				//����Ʈ�� ����� �ٽ� ������� ä���
				ListView_DeleteAllItems(hEMPList);
				EMPSelectSQL();
				DBDisconnect();
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
			SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);

			break;
		case IDC_MODIFY:	//���� ��ư
			GetWindowText(hEmpNo, tempEmp.empNo, 12);
			if (lstrlen(tempEmp.empNo) == 0) {
				MessageBox(hWnd, TEXT("������ ����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {

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
				GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);							//�÷�(��)
				GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);						//�÷�(��)

				DBConnect();
				SendMessage(hEmpBuseo, CB_GETLBTEXT, SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0), (LPARAM)str);			//�μ�
				lstrcpy(tempEmp.empBuseo, Name2Code((LPSTR)"BUSEO", str));

				SendMessage(hEmpReligion, CB_GETLBTEXT, SendMessage(hEmpReligion, CB_GETCURSEL, 0, 0), (LPARAM)str);	//����
				lstrcpy(tempEmp.pInfo.pReligion, Name2Code((LPSTR)"RELIGION", str));

				SendMessage(hEmpPoscode, CB_GETLBTEXT, SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0), (LPARAM)str);		//��å
				lstrcpy(tempEmp.empPosCode, Name2Code((LPSTR)"POSITION", str));

				EMPUpdateSQL(tempEmp);
				EMPSelectSQL();
				DBDisconnect();

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
				SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);

			}
			break;
		case IDC_REFRESH:			//���ΰ�ħ ��ư
			ListView_DeleteAllItems(hEMPList);
			DBConnect();
			EMPSelectSQL();
			DBDisconnect();
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
			SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);
			return 0;
		case IDC_RETIRE:		//����ó�� ��ư
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("����ó���� ����� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				DBConnect();
				//���õ� ����� �ٹ����¸� ������û���� ����
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				EMPRetire(tempEmp.empNo);
				//����Ʈ�� ����� �ٽ� ������� ä���
				ListView_DeleteAllItems(hEMPList);
				EMPSelectSQL();
				DBDisconnect();
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
				SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LVITEM LI;
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		if (hdr->hwndFrom == hEMPList) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//������ ���� �����͵�� �ڵ� ä���
					LI.mask = LVIF_TEXT;
					LI.iSubItem = 0;
					LI.pszText = str;
					LI.cchTextMax = sizeof(str);
					SendMessage(hEMPList, LVM_GETITEMTEXT, (WPARAM)nlv->iItem, (LPARAM)&LI);

					DBConnect();
					ControlSelectSQL((LPSTR)str);
					//EMPSelectSQL();
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
