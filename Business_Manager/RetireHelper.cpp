#include "RetireHelper.h"

extern HINSTANCE g_hInst;
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern HWND hRetEMPList, hRetEmpNo, hRetEmpBuseo, hRetEmpPoscode, hRetEmpName1, hRetEmpReason
, hRetReqEMPList, hRetReqEMPBuseo, hRetReqEmpPhone;	//컨트롤 핸들
/*
BOOL SelectReqEMP(): 퇴직요청 리스트뷰에 사원정보 채움
*/
BOOL SelectReqEMP() {
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
	ListView_DeleteAllItems(hRetReqEMPList);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 1) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hRetReqEMPList, &LI);																//사번
			ListView_SetItemText(hRetReqEMPList, i, 1, (LPSTR)empDB.empBuseo);										//부서
			ListView_SetItemText(hRetReqEMPList, i, 2, (LPSTR)empDB.empPosCode);									//직책
			ListView_SetItemText(hRetReqEMPList, i, 3, (LPSTR)pInfoDB.pName[0]);									//이름
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL SelectRetEMP(): 퇴직자 리스트뷰에 사원정보 채움
*/
BOOL SelectRetEMP() {
	LVITEM LI;
	int i;

	//바인딩할 DB구조체 선언
	RETIREDB retDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, retDB.empNo, sizeof(retDB.empNo), &retDB.IempNo);						//사번
	SQLBindCol(hStmt, 2, SQL_C_CHAR, retDB.empBuseo, sizeof(retDB.empBuseo), &retDB.IempBuseo);				//부서
	SQLBindCol(hStmt, 3, SQL_C_CHAR, retDB.empPoscode, sizeof(retDB.empPoscode), &retDB.IempPoscode);		//직책
	SQLBindCol(hStmt, 4, SQL_C_CHAR, retDB.empName, sizeof(retDB.empName), &retDB.IempName);				//이름
	SQLBindCol(hStmt, 5, SQL_C_CHAR, retDB.empPhone, sizeof(retDB.empPhone), &retDB.IempPhone);				//연락처
	SQLBindCol(hStmt, 6, SQL_C_CHAR, retDB.retireReason, sizeof(retDB.retireReason), &retDB.IretireReason);	//퇴직사유


	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, EMPBUSEO, EMPPOSCODE, EMPNAME,EMPPHONE,RETIREREASON from RETIREINFO", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select된 데이터를 hEMPList 리스트뷰를 비운후 새로 뿌림
	i = 0;
	ListView_DeleteAllItems(hRetEMPList);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = retDB.empNo;
		ListView_InsertItem(hRetEMPList, &LI);																//사번
		ListView_SetItemText(hRetEMPList, i, 1, (LPSTR)retDB.empBuseo);										//부서
		ListView_SetItemText(hRetEMPList, i, 2, (LPSTR)retDB.empPoscode);									//직책
		ListView_SetItemText(hRetEMPList, i, 3, (LPSTR)retDB.empName);										//이름
		ListView_SetItemText(hRetEMPList, i, 4, (LPSTR)retDB.retireReason);									//사유
		ListView_SetItemText(hRetEMPList, i, 5, (LPSTR)retDB.empPhone);										//연락처
		i++;

	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL RetireEMP(LPSTR tempRet): EMP 테이블에서 해당 사원 퇴직정보를 2로 바꾸고tempRet정보 RETIREINFO 테이블에 추가
*/
BOOL RetireEMP(RETIRE tempRet) {
	TCHAR Q[512];
	//해당 사원의 퇴직 정보를 EMP테이블에서 2로 UPDATE
	wsprintf(Q, "UPDATE EMP SET RETIRE = 2 WHERE EMPNO = '%s'", tempRet.empNo);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	
	//해당 사원의 퇴직시 입력받은 정보를 RETIREINFO 테이블에 INSERT
	wsprintf(Q, "INSERT INTO RETIREINFO(EMPNO,EMPBUSEO,EMPPOSCODE,EMPNAME,EMPPHONE,RETIREREASON) VALUES ('%s','%s','%s','%s','%s','%s')"
		, tempRet.empNo, tempRet.empBuseo, tempRet.empPoscode, tempRet.empName, tempRet.empPhone, tempRet.retireReason);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	
	return TRUE;
}