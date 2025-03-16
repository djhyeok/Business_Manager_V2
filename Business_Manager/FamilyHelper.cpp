#include "FamilyHelper.h"
//extern 걸어서 다른 파일에서 선언된 전역변수 가져옴
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
BOOL SelectEMP(): 리스트뷰에 사원정보 채움
*/
BOOL SelectEMP() {
	LVITEM LI;
	int i;

	//바인딩할 DB구조체 선언
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);					//사번
	SQLBindCol(hStmt, 2, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);			//부서
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);	//직책
	SQLBindCol(hStmt, 4, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);		//이름
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);							//퇴직정보

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, BUSEO, POSITION,NAME1,RETIRE from EMPVIEW", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select된 데이터를 hEMPList 리스트뷰를 비운후 새로 뿌림
	i = 0;
	ListView_DeleteAllItems(hEmpLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 0) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hEmpLV, &LI);																//사번
			ListView_SetItemText(hEmpLV, i, 1, (LPSTR)empDB.empBuseo);										//부서
			ListView_SetItemText(hEmpLV, i, 2, (LPSTR)empDB.empPosCode);									//직책
			ListView_SetItemText(hEmpLV, i, 3, (LPSTR)pInfoDB.pName[0]);									//이름
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL InsertFamily(FAMILY fam): fam 정보를 DB에 추가
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
		SQLBindCol(hStmt, 1, SQL_C_ULONG, &max, 0, &Imax);				//인덱스 최댓값 바인딩
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
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL SelectFamily(LPSTR empno): 리스트뷰에 사번이 empno인 가족정보 채움
*/
BOOL SelectFamily(LPSTR empno) {
	LVITEM LI;
	int i;
	TCHAR Q[512];

	//바인딩할 DB구조체 선언
	FAMILYDB famDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, famDB.name, sizeof(famDB.name), &famDB.Iname);				//이름
	SQLBindCol(hStmt, 2, SQL_C_CHAR, famDB.age, sizeof(famDB.age), &famDB.Iage);				//나이
	SQLBindCol(hStmt, 3, SQL_C_CHAR, famDB.relation, sizeof(famDB.relation), &famDB.Irelation);	//관계
	SQLBindCol(hStmt, 4, SQL_C_CHAR, famDB.job, sizeof(famDB.job), &famDB.Ijob);				//직업

	wsprintf(Q, "SELECT NAME, AGE, RELATION, JOB from FAMILYMEMBER WHERE EMPNO = '%s'", empno);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select된 데이터를 hEMPList 리스트뷰를 비운후 새로 뿌림
	i = 0;
	ListView_DeleteAllItems(hFamilyLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = famDB.name;
		ListView_InsertItem(hFamilyLV, &LI);										//이름
		ListView_SetItemText(hFamilyLV, i, 1, (LPSTR)famDB.age);					//나이
		ListView_SetItemText(hFamilyLV, i, 2, (LPSTR)famDB.relation);				//직책
		ListView_SetItemText(hFamilyLV, i, 3, (LPSTR)famDB.job);					//이름
		i++;
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
int GetFamilyIndex(LPSTR empno,LPSTR name): empno 가족사항중 이름이 name인 사람의 index 리턴
*/
int GetFamilyIndex(LPSTR empno, LPSTR name) {
	int ind;
	SQLLEN Iind;
	TCHAR Q[512];

	SQLBindCol(hStmt, 1, SQL_C_ULONG, &ind, 0, &Iind);				//인덱스
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
BOOL UpdateFamily(int index, FAMILY fam); 해당 index의 가족정보를 매개변수로 가져온 fam으로 update
*/
BOOL UpdateFamily(int index, FAMILY fam) {
	TCHAR Q[512];

	//가져온 table명과 value로 쿼리 만들기
	wsprintf(Q, "UPDATE FAMILYMEMBER SET NAME = '%s', AGE = %s, RELATION = '%s', JOB = '%s' WHERE IDX = %d"
		, fam.name, fam.age, fam.relation, fam.job, index);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}

/*
BOOL DeleteFamily(int index): 해당 index의 가족정보를 삭제
*/
BOOL DeleteFamily(int index) {
	TCHAR Q[512];

	wsprintf(Q, "DELETE FROM FAMILYMEMBER WHERE IDX = %d", index);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	return TRUE;
}