#include "DBHelper.h"

extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern EMP* workEmp;		//사원
extern RETIRE* retireEmp;	//퇴직완료사원
extern FAMILY* family;		//사원가족
/*
BOOL DBConnect(): DB연결 함수
*/
BOOL DBConnect() {
	//연결 설정을 위한 변수들
	SQLRETURN Ret;
	//환경 핸들을 할당하고 버전 속성을 설정한다.
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) {
		return FALSE;
	}
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS) {
		return FALSE;
	}

	//연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
		return FALSE;
	}

	//DB계정정보
	Ret = SQLConnect(hDbc, (SQLCHAR*)"odbcAPI", SQL_NTS, (SQLCHAR*)"c##odbcuser", SQL_NTS, (SQLCHAR*)"Dhdh159753", SQL_NTS);

	//드라이버 연결 가능 여부 확인
	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO)) {
		return FALSE;
	}

	//계정 정보 유효성 체크
	//명령 핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
	DBDisconnect(): DB연결 해제
*/
void DBDisconnect() {
	//뒷정리
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
int CountRecord(LPSTR table) : table 테이블의 레코드갯수 count(*)후 리턴
*/
int CountRecord(LPSTR table) {
	TCHAR Q[512];
	int count;
	SQLLEN Icount;

	//count 결과를 돌려받기 위한 바인딩
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &count, 0, &Icount);
	wsprintf(Q, "SELECT COUNT(*) FROM %s;", table);

	//count문 실행
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	//fetch 후 closecursor
	SQLFetch(hStmt);
	SQLCloseCursor(hStmt);

	return count;
}