#include "RetireHelper.h"

extern HINSTANCE g_hInst;
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern HWND hRetEMPList, hRetEmpNo, hRetEmpBuseo, hRetEmpPoscode, hRetEmpName1, hRetEmpReason
, hRetReqEMPList, hRetReqEMPBuseo, hRetReqEmpPhone;	//��Ʈ�� �ڵ�
/*
BOOL SelectReqEMP(): ������û ����Ʈ�信 ������� ä��
*/
BOOL SelectReqEMP() {
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
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);							//��������

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, BUSEO, POSITION,NAME1,RETIRE from EMPVIEW", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select�� �����͸� hEMPList ����Ʈ�並 ����� ���� �Ѹ�
	i = 0;
	ListView_DeleteAllItems(hRetReqEMPList);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 1) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hRetReqEMPList, &LI);																//���
			ListView_SetItemText(hRetReqEMPList, i, 1, (LPSTR)empDB.empBuseo);										//�μ�
			ListView_SetItemText(hRetReqEMPList, i, 2, (LPSTR)empDB.empPosCode);									//��å
			ListView_SetItemText(hRetReqEMPList, i, 3, (LPSTR)pInfoDB.pName[0]);									//�̸�
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL SelectRetEMP(): ������ ����Ʈ�信 ������� ä��
*/
BOOL SelectRetEMP() {
	LVITEM LI;
	int i;

	//���ε��� DB����ü ����
	RETIREDB retDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, retDB.empNo, sizeof(retDB.empNo), &retDB.IempNo);						//���
	SQLBindCol(hStmt, 2, SQL_C_CHAR, retDB.empBuseo, sizeof(retDB.empBuseo), &retDB.IempBuseo);				//�μ�
	SQLBindCol(hStmt, 3, SQL_C_CHAR, retDB.empPoscode, sizeof(retDB.empPoscode), &retDB.IempPoscode);		//��å
	SQLBindCol(hStmt, 4, SQL_C_CHAR, retDB.empName, sizeof(retDB.empName), &retDB.IempName);				//�̸�
	SQLBindCol(hStmt, 5, SQL_C_CHAR, retDB.empPhone, sizeof(retDB.empPhone), &retDB.IempPhone);				//����ó
	SQLBindCol(hStmt, 6, SQL_C_CHAR, retDB.retireReason, sizeof(retDB.retireReason), &retDB.IretireReason);	//��������


	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, EMPBUSEO, EMPPOSCODE, EMPNAME,EMPPHONE,RETIREREASON from RETIREINFO", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select�� �����͸� hEMPList ����Ʈ�並 ����� ���� �Ѹ�
	i = 0;
	ListView_DeleteAllItems(hRetEMPList);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = retDB.empNo;
		ListView_InsertItem(hRetEMPList, &LI);																//���
		ListView_SetItemText(hRetEMPList, i, 1, (LPSTR)retDB.empBuseo);										//�μ�
		ListView_SetItemText(hRetEMPList, i, 2, (LPSTR)retDB.empPoscode);									//��å
		ListView_SetItemText(hRetEMPList, i, 3, (LPSTR)retDB.empName);										//�̸�
		ListView_SetItemText(hRetEMPList, i, 4, (LPSTR)retDB.retireReason);									//����
		ListView_SetItemText(hRetEMPList, i, 5, (LPSTR)retDB.empPhone);										//����ó
		i++;

	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL RetireEMP(LPSTR tempRet): EMP ���̺��� �ش� ��� ���������� 2�� �ٲٰ�tempRet���� RETIREINFO ���̺� �߰�
*/
BOOL RetireEMP(RETIRE tempRet) {
	TCHAR Q[512];
	//�ش� ����� ���� ������ EMP���̺��� 2�� UPDATE
	wsprintf(Q, "UPDATE EMP SET RETIRE = 2 WHERE EMPNO = '%s'", tempRet.empNo);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	
	//�ش� ����� ������ �Է¹��� ������ RETIREINFO ���̺� INSERT
	wsprintf(Q, "INSERT INTO RETIREINFO(EMPNO,EMPBUSEO,EMPPOSCODE,EMPNAME,EMPPHONE,RETIREREASON) VALUES ('%s','%s','%s','%s','%s','%s')"
		, tempRet.empNo, tempRet.empBuseo, tempRet.empPoscode, tempRet.empName, tempRet.empPhone, tempRet.retireReason);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	
	return TRUE;
}