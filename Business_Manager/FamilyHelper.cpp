#include "FamilyHelper.h"
//extern 걸어서 다른 파일에서 선언된 전역변수 가져옴
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
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);		//이름

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
BOOL SelectFamily(): 리스트뷰에 사원정보 채움
*/
BOOL SelectFamily() {
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
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);		//이름

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