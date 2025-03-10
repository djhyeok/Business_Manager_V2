#include "BaseHelper.h"

extern int totB;
extern int totP;
extern int totR;
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;

/*
selectSQL(QSTATE state) : DB���� select���� ����
*/
BOOL BaseSelectSQL(LPSTR table) {
	TCHAR Q[512];
	int i;

	//���ε��� DB����ü ����
	BASEDB baseDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, baseDB.code, sizeof(baseDB.code), &baseDB.ICode);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, baseDB.name, sizeof(baseDB.name), &baseDB.IName);

	//SQL���� �����Ѵ�.
	wsprintf(Q, "SELECT CODE, NAME from %s", table);
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//������ �о�ͼ� buseo����ü�� ����
	if (strcmp(table, "BUSEO") == 0) {
		if (totB > 0) {
			if (buseo) {
				//count��ŭ realloc
				buseo = (BASE*)realloc(buseo, totB * sizeof(BASE));
			}
			else {
				buseo = (BASE*)malloc(totB * sizeof(BASE));
			}

			//select�� �����͸� buseo����ü�� ����
			i = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				lstrcpy(buseo[i].code, (LPCSTR)baseDB.code);
				lstrcpy(buseo[i].name, (LPCSTR)baseDB.name);
				i++;
			}
		}
	}
	else if (strcmp(table, "RELIGION") == 0) {
		if (totR > 0) {
			if (religion) {
				//count��ŭ realloc
				religion = (BASE*)realloc(religion, totR * sizeof(BASE));
			}
			else {
				religion = (BASE*)malloc(totR * sizeof(BASE));
			}

			//select�� �����͸� religion����ü�� ����
			i = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				lstrcpy(religion[i].code, (LPCSTR)baseDB.code);
				lstrcpy(religion[i].name, (LPCSTR)baseDB.name);
				i++;
			}
		}
	}
	else if (strcmp(table, "POSITION") == 0) {
		if (totP > 0) {
			if (position) {
				//count��ŭ realloc
				position = (BASE*)realloc(position, totP * sizeof(BASE));
			}
			else {
				position = (BASE*)malloc(totP * sizeof(BASE));
			}

			//select�� �����͸� position����ü�� ����
			i = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				lstrcpy(position[i].code, (LPCSTR)baseDB.code);
				lstrcpy(position[i].name, (LPCSTR)baseDB.name);
				i++;
			}
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL BaseDeleteSQL(LPSTR table, LPSTR value) : table ���̺��� code==value�� ���ڵ� ����
*/
BOOL BaseDeleteSQL(LPSTR table, LPSTR value) {
	TCHAR Q[512];
	//������ table��� value�� ���� �����
	lstrcpy(Q, "DELETE FROM ");
	lstrcat(Q, table);
	lstrcat(Q, " WHERE CODE = '");
	lstrcat(Q, value);
	lstrcat(Q, "'");
	//wsprintf(Q, "DELETE FROM %s WHERE CODE = '%s'", table, value);

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL BaseUpdateSQL(LPSTR table, LPSTR origin, BASE updateData) : table ���̺� code==origin�� �����͸� updateData�� ġȯ
*/
BOOL BaseUpdateSQL(LPSTR table, LPSTR origin, BASE updateData) {
	TCHAR Q[512];
	//������ table��� value�� ���� �����
	lstrcpy(Q, "UPDATE ");
	lstrcat(Q, table);
	lstrcat(Q, " SET CODE = '");
	lstrcat(Q, updateData.code);
	lstrcat(Q, "', NAME = '");
	lstrcat(Q, updateData.name);
	lstrcat(Q, "' WHERE CODE = '");
	lstrcat(Q, origin);
	lstrcat(Q, "'");

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL BaseInsertSQL(LPSTR table, BASE inData) : table ���̺� inData ������ ����
*/
BOOL BaseInsertSQL(LPSTR table, BASE inData) {
	TCHAR Q[512];
	//������ table��� inData�� ���� �����
	lstrcpy(Q, "INSERT INTO ");
	lstrcat(Q, table);
	lstrcat(Q, "(CODE,NAME) values('");
	lstrcat(Q, inData.code);
	lstrcat(Q, "','");
	lstrcat(Q, inData.name);
	lstrcat(Q, "')");

	//SQL���� �����Ѵ�.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
LPSTR Name2Code(LPSTR table , LPSTR name) : �ش� ���̺��� name�� code�� ��ȯ
*/
LPSTR Name2Code(LPSTR table, LPSTR name) {
	TCHAR Q[512];

	//���ε��� DB����ü ����
	BASEDB baseDB;

	//����� �����ޱ� ���� ���ε�
	SQLBindCol(hStmt, 1, SQL_C_CHAR, baseDB.code, sizeof(baseDB.code), &baseDB.ICode);

	//SQL���� �����Ѵ�.
	wsprintf(Q, "SELECT CODE from %s WHERE NAME = '%s'", table, name);
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return NULL;
	}

	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return baseDB.code;
}