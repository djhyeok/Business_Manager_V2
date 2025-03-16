#include "FamilyHelper.h"
//extern �ɾ �ٸ� ���Ͽ��� ����� �������� ������
extern HINSTANCE g_hInst;
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern HWND hEmpLV, hFamilyLV, hEmpName, hFamName, hFamAge, hFamRel, hFamJob, hFamInsert;
HWND hwndnd;
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
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);							//��������

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
BOOL InsertFamily(FAMILY fam): fam ������ DB�� �߰�
*/
BOOL InsertFamily(FAMILY fam) {
	TCHAR Q[512];
	int cnt, max;
	cnt = CountRecord((LPSTR)"FAMILYMEMBER");
	if (cnt == 0) {
		max = 0;
	}
	else {
		SQLLEN Imax;
		SQLBindCol(hStmt, 1, SQL_C_ULONG, &max, 0, &Imax);				//�ε��� �ִ� ���ε�
		wsprintf(Q, "SELECT MAX(IDX) FROM FAMILYMEMBER", fam.empNo);
		if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
			return FALSE;
		}
		SQLFetch(hStmt);
		if (hStmt) {
			SQLCloseCursor(hStmt);
		}
	}
	wsprintf(Q, "INSERT INTO FAMILYMEMBER(IDX,EMPNO, NAME, AGE, RELATION, JOB) VALUES(%d,'%s','%s',%s,'%s','%s')"
		, max + 1, fam.empNo, fam.name, fam.age, fam.relation, fam.job);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL SelectFamily(LPSTR empno): ����Ʈ�信 ����� empno�� �������� ä��
*/
BOOL SelectFamily(LPSTR empno) {
	LVITEM LI;
	int i;
	TCHAR Q[512];

	//���ε��� DB����ü ����
	FAMILYDB famDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, famDB.name, sizeof(famDB.name), &famDB.Iname);				//�̸�
	SQLBindCol(hStmt, 2, SQL_C_CHAR, famDB.age, sizeof(famDB.age), &famDB.Iage);				//����
	SQLBindCol(hStmt, 3, SQL_C_CHAR, famDB.relation, sizeof(famDB.relation), &famDB.Irelation);	//����
	SQLBindCol(hStmt, 4, SQL_C_CHAR, famDB.job, sizeof(famDB.job), &famDB.Ijob);				//����

	wsprintf(Q, "SELECT NAME, AGE, RELATION, JOB from FAMILYMEMBER WHERE EMPNO = '%s'", empno);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select�� �����͸� hEMPList ����Ʈ�並 ����� ���� �Ѹ�
	i = 0;
	ListView_DeleteAllItems(hFamilyLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = famDB.name;
		ListView_InsertItem(hFamilyLV, &LI);										//�̸�
		ListView_SetItemText(hFamilyLV, i, 1, (LPSTR)famDB.age);					//����
		ListView_SetItemText(hFamilyLV, i, 2, (LPSTR)famDB.relation);				//��å
		ListView_SetItemText(hFamilyLV, i, 3, (LPSTR)famDB.job);					//�̸�
		i++;
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
int GetFamilyIndex(LPSTR empno,LPSTR name): empno ���������� �̸��� name�� ����� index ����
*/
int GetFamilyIndex(LPSTR empno, LPSTR name) {
	int ind;
	SQLLEN Iind;
	TCHAR Q[512];

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &ind, 0, &Iind);				//�ε���
	wsprintf(Q, "SELECT IDX FROM FAMILYMEMBER WHERE EMPNO = '%s' AND NAME = '%s'", empno, name);
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	return ind;
}

/*
BOOL UpdateFamily(int index, FAMILY fam); �ش� index�� ���������� �Ű������� ������ fam���� update
*/
BOOL UpdateFamily(int index, FAMILY fam) {
	TCHAR Q[512];

	//������ table��� value�� ���� �����
	wsprintf(Q, "UPDATE FAMILYMEMBER SET NAME = '%s', AGE = %s, RELATION = '%s', JOB = '%s' WHERE IDX = %d"
		, fam.name, fam.age, fam.relation, fam.job, index);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL DeleteFamily(int index): �ش� index�� ���������� ����
*/
BOOL DeleteFamily(int index) {
	TCHAR Q[512];

	wsprintf(Q, "DELETE FROM FAMILYMEMBER WHERE IDX = %d", index);
	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}