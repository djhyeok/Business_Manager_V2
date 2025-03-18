#include "Report.h"

extern HINSTANCE g_hInst;
extern int totEmp;
extern EMP* workEmp;

HWND hReportEmpLV, hReportFamilyLV, hSearchOption, hSearch, hSearchBtn, hSelectBuseo, hSelectPos
, hMaleCheck, hFemaleCheck, hWorkCheck, hRetireCheck;

enum {
	ID_REPORTEMPLV = 1, ID_REPORTFAMLV, ID_SEARCHCOMBO, ID_SEARCH, ID_SEARCHBTN, ID_SELECTBUSEO, ID_SELECTPOS
	, ID_MALECHECK, ID_FEMALECHECK, ID_WORKCHECK, ID_RETIRECHECK
};


LRESULT CALLBACK InitReportMDIPROC(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HFONT hFont, OldFont;
	LVCOLUMN COL;
	LVITEM LI;
	HDC hdc;
	HBRUSH MyBrush, OldBrush;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	TCHAR str[255];
	int i;
	TCHAR option[][50] = { TEXT("�����ȣ"),TEXT("�̸�"),TEXT("�μ�"),TEXT("��å"),TEXT("�Ի�⵵") };

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		//����Ʈ�� ����
		hReportEmpLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 80, 120, 700, 600, hWnd, (HMENU)ID_REPORTEMPLV, g_hInst, NULL);
		hReportFamilyLV = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 830, 120, 500, 600, hWnd, (HMENU)ID_REPORTFAMLV, g_hInst, NULL);

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
		COL.cx = 60;
		COL.pszText = (LPSTR)TEXT("����");
		COL.iSubItem = 5;
		ListView_InsertColumn(hReportEmpLV, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
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

		//�˻��ɼ� �޺��ڽ�
		hSearchOption = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
			150, 65, 120, 250, hWnd, (HMENU)ID_SEARCHCOMBO, g_hInst, NULL);
		for (i = 0; i < 5; i++) {
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
		//���� üũ�ڽ�
		hMaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 280, 35, 50, 25, hWnd, (HMENU)ID_MALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hFemaleCheck = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 335, 35, 50, 25, hWnd, (HMENU)ID_FEMALECHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hWorkCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 390, 35, 75, 25, hWnd, (HMENU)ID_WORKCHECK, g_hInst, NULL);
		//���� üũ�ڽ�
		hRetireCheck = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 465, 35, 75, 25, hWnd, (HMENU)ID_RETIRECHECK, g_hInst, NULL);

		//����˻� ��ư
		hSearchBtn = CreateWindow(TEXT("button"), TEXT("�˻�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			525, 63, 50, 25, hWnd, (HMENU)ID_SEARCHBTN, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		return 0;
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