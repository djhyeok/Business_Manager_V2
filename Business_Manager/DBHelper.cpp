#include "DBHelper.h"

extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
/*
BOOL DBConnect(): DB����
*/
BOOL DBConnect() {
	//���� ������ ���� ������
	SQLRETURN Ret;
	//ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) {
		return FALSE;
	}
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		return FALSE;
	}

	//���� �ڵ��� �Ҵ��ϰ� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
		return FALSE;
	}

	//DB��������
	Ret = SQLConnect(hDbc, (SQLCHAR*)"odbcAPI", SQL_NTS, (SQLCHAR*)"c##odbcuser", SQL_NTS, (SQLCHAR*)"Dhdh159753", SQL_NTS);

	//����̹� ���� ���� ���� Ȯ��
	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO)) {
		return FALSE;
	}

	//���� ���� ��ȿ�� üũ
	//��� �ڵ��� �Ҵ��Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
	DBDisconnect(): DB���� ����
*/
void DBDisconnect() {
	//������
	if (hStmt) {
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	if (hDbc) {
		SQLDisconnect(hDbc);
	}
	if (hDbc) {
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	}
	if (hEnv) {
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}
}

/*
int CountRecord(LPSTR table) : table ���̺��� ���ڵ尹�� count(*)�� ����
*/
int CountRecord(LPSTR table) {
	TCHAR Q[512];
	int count;
	SQLLEN Icount;

	//count ����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &count, 0, &Icount);
	wsprintf(Q, "SELECT COUNT(*) FROM %s;", table);

	//count�� ����
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	//fetch �� closecursor
	SQLFetch(hStmt);
	SQLCloseCursor(hStmt);

	return count;
}