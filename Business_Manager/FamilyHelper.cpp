#include "FamilyHelper.h"
//extern �ɾ �ٸ� ���Ͽ��� ����� �������� ������
extern HINSTANCE g_hInst;
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern HWND hEmpLV, hFamilyLV, hEmpName, hFamName, hFamAge, hFamRel, hFamJob, hFamInsert;
enum {
	ID_EMPLV, ID_FAMLV, ID_EMPNAME, ID_FAMNAME, ID_FAMAGE, ID_FAMREL, ID_FAMJOB,
	ID_FAMINSERT, ID_FAMMODIFY, ID_FAMDELETE, ID_COMPLETE
};

/*
BOOL SelectEMP(): ����Ʈ�信 ������� ä��
*/
BOOL SelectEMP() {
	LVITEM LI;
	int i;

	//���ε��� DB����ü ����
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);					//���
	SQLBindCol(hStmt, 2, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);			//�μ�
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);	//��å
	SQLBindCol(hStmt, 4, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);		//�̸�
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);		//�̸�

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, BUSEO, POSITION,NAME1,RETIRE from EMPVIEW", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select�� �����͸� hEMPList ����Ʈ�並 ����� ���� �Ѹ�
	i = 0;
	ListView_DeleteAllItems(hEmpLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 0) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hEmpLV, &LI);																//���
			ListView_SetItemText(hEmpLV, i, 1, (LPSTR)empDB.empBuseo);										//�μ�
			ListView_SetItemText(hEmpLV, i, 2, (LPSTR)empDB.empPosCode);									//��å
			ListView_SetItemText(hEmpLV, i, 3, (LPSTR)pInfoDB.pName[0]);									//�̸�
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL SelectFamily(): ����Ʈ�信 ������� ä��
*/
BOOL SelectFamily() {
	LVITEM LI;
	int i;

	//���ε��� DB����ü ����
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);					//���
	SQLBindCol(hStmt, 2, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);			//�μ�
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);	//��å
	SQLBindCol(hStmt, 4, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);		//�̸�
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);		//�̸�

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, BUSEO, POSITION,NAME1,RETIRE from EMPVIEW", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select�� �����͸� hEMPList ����Ʈ�並 ����� ���� �Ѹ�
	i = 0;
	ListView_DeleteAllItems(hEmpLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 0) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hEmpLV, &LI);																//���
			ListView_SetItemText(hEmpLV, i, 1, (LPSTR)empDB.empBuseo);										//�μ�
			ListView_SetItemText(hEmpLV, i, 2, (LPSTR)empDB.empPosCode);									//��å
			ListView_SetItemText(hEmpLV, i, 3, (LPSTR)pInfoDB.pName[0]);									//�̸�
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}