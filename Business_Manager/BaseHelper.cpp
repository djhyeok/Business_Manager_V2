#include "BaseHelper.h"

extern int totB;
extern int totP;
extern int totR;
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;

/*
selectSQL(QSTATE state) : DB에서 select문을 수행
*/
BOOL BaseSelectSQL(LPSTR table) {
	TCHAR Q[512];
	int i;

	//바인딩할 DB구조체 선언
	BASEDB baseDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, baseDB.code, sizeof(baseDB.code), &baseDB.ICode);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, baseDB.name, sizeof(baseDB.name), &baseDB.IName);

	//SQL문을 실행한다.
	wsprintf(Q, "SELECT CODE, NAME from %s", table);
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//데이터 읽어와서 buseo구조체에 담음
	if (strcmp(table, "BUSEO") == 0) {
		if (totB > 0) {
			if (buseo) {
				//count만큼 realloc
				buseo = (BASE*)realloc(buseo, totB * sizeof(BASE));
			}
			else {
				buseo = (BASE*)malloc(totB * sizeof(BASE));
			}

			//select된 데이터를 buseo구조체에 담음
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
				//count만큼 realloc
				religion = (BASE*)realloc(religion, totR * sizeof(BASE));
			}
			else {
				religion = (BASE*)malloc(totR * sizeof(BASE));
			}

			//select된 데이터를 religion구조체에 담음
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
				//count만큼 realloc
				position = (BASE*)realloc(position, totP * sizeof(BASE));
			}
			else {
				position = (BASE*)malloc(totP * sizeof(BASE));
			}

			//select된 데이터를 position구조체에 담음
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
BOOL BaseDeleteSQL(LPSTR table, LPSTR value) : table 테이블의 code==value인 레코드 삭제
*/
BOOL BaseDeleteSQL(LPSTR table, LPSTR value) {
	TCHAR Q[512];
	//가져온 table명과 value로 쿼리 만들기
	lstrcpy(Q, "DELETE FROM ");
	lstrcat(Q, table);
	lstrcat(Q, " WHERE CODE = '");
	lstrcat(Q, value);
	lstrcat(Q, "'");
	//wsprintf(Q, "DELETE FROM %s WHERE CODE = '%s'", table, value);

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL BaseUpdateSQL(LPSTR table, LPSTR origin, BASE updateData) : table 테이블에 code==origin인 데이터를 updateData로 치환
*/
BOOL BaseUpdateSQL(LPSTR table, LPSTR origin, BASE updateData) {
	TCHAR Q[512];
	//가져온 table명과 value로 쿼리 만들기
	lstrcpy(Q, "UPDATE ");
	lstrcat(Q, table);
	lstrcat(Q, " SET CODE = '");
	lstrcat(Q, updateData.code);
	lstrcat(Q, "', NAME = '");
	lstrcat(Q, updateData.name);
	lstrcat(Q, "' WHERE CODE = '");
	lstrcat(Q, origin);
	lstrcat(Q, "'");

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL BaseInsertSQL(LPSTR table, BASE inData) : table 테이블에 inData 데이터 삽입
*/
BOOL BaseInsertSQL(LPSTR table, BASE inData) {
	TCHAR Q[512];
	//가져온 table명과 inData로 쿼리 만들기
	lstrcpy(Q, "INSERT INTO ");
	lstrcat(Q, table);
	lstrcat(Q, "(CODE,NAME) values('");
	lstrcat(Q, inData.code);
	lstrcat(Q, "','");
	lstrcat(Q, inData.name);
	lstrcat(Q, "')");

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
LPSTR Name2Code(LPSTR table , LPSTR name) : 해당 테이블의 name을 code로 전환
*/
LPSTR Name2Code(LPSTR table, LPSTR name) {
	TCHAR Q[512];

	//바인딩할 DB구조체 선언
	BASEDB baseDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, baseDB.code, sizeof(baseDB.code), &baseDB.ICode);

	//SQL문을 실행한다.
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