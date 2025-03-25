#include "ReportHelper.h"

extern HINSTANCE g_hInst;
extern SQLHSTMT hStmt;
extern HWND hReportEmpLV, hReportRetireLV, hReportFamilyLV;

/*
BOOL InitCombo(LPSTR table,HWND combo) : combo핸들에 table의 정보를 채움
*/
BOOL InitCombo(LPSTR table, HWND combo) {
	TCHAR Q[512];
	BASEDB tempBase;
	SQLBindCol(hStmt, 1, SQL_C_CHAR, tempBase.name, sizeof(tempBase.name), &tempBase.IName);
	wsprintf(Q, "SELECT name FROM %s", table);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)tempBase.name);
	}
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	return TRUE;
}

/*
BOOL SelectReport(LPSTR str,EMP tEmp): select할 정보를 매개변수로 가져와서 select문 실행
*/
BOOL SelectReport(LPSTR str, EMP tEmp) {
	int i, cnt = 0;
	LVITEM LI;
	TCHAR Q[512], temp[512];
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);					//사번
	SQLBindCol(hStmt, 2, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);		//이름
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);			//부서
	SQLBindCol(hStmt, 4, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);	//직책
	SQLBindCol(hStmt, 5, SQL_C_CHAR, pInfoDB.pPhone[0], sizeof(pInfoDB.pPhone[0]), &pInfoDB.IpPhone0);	//연락처
	SQLBindCol(hStmt, 6, SQL_C_ULONG, &pInfoDB.pSex, 0, &pInfoDB.IpSex);								//성별
	SQLBindCol(hStmt, 7, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);							//퇴직정보

	lstrcpy(Q, TEXT("SELECT EMPNO,NAME1,BUSEO,POSITION,PHONE1,SEX,RETIRE FROM EMPVIEW"));
	if (lstrlen(str) != 0) {
		wsprintf(temp, " WHERE SUBSTR(EMPNO,1,4) = '%s'", str);
		lstrcat(Q, temp);
		cnt++;
	}
	if (lstrlen(tEmp.empNo) != 0) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "EMPNO = '%s'", tEmp.empNo);
		lstrcat(Q, temp);
	}
	if (lstrlen(tEmp.empBuseo) != 0) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "BUSEO = '%s'", tEmp.empBuseo);
		lstrcat(Q, temp);
	}
	if (lstrlen(tEmp.empPosCode) != 0) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "POSITION = '%s'", tEmp.empPosCode);
		lstrcat(Q, temp);
	}
	if (tEmp.pInfo.pSex != -1) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "SEX = %d ", tEmp.pInfo.pSex);
		lstrcat(Q, temp);
	}
	if (tEmp.empRetire != -1) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "RETIRE = %d", tEmp.empRetire);
		lstrcat(Q, temp);
	}
	if (lstrlen(tEmp.pInfo.pName[0]) != 0) {
		if (cnt == 0) {
			lstrcat(Q, " WHERE ");
			cnt++;
		}
		else {
			lstrcat(Q, " AND ");
		}
		wsprintf(temp, "NAME LIKE '%%s%'", tEmp.pInfo.pName[0]);
		lstrcat(Q, temp);
	}
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	i = 0;
	ListView_DeleteAllItems(hReportEmpLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = empDB.empNo;
		ListView_InsertItem(hReportEmpLV, &LI);																//사번
		ListView_SetItemText(hReportEmpLV, i, 1, (LPSTR)pInfoDB.pName[0]);									//이름
		ListView_SetItemText(hReportEmpLV, i, 2, (LPSTR)empDB.empBuseo);									//부서
		ListView_SetItemText(hReportEmpLV, i, 3, (LPSTR)empDB.empPosCode);									//직책
		ListView_SetItemText(hReportEmpLV, i, 4, (LPSTR)pInfoDB.pPhone[0]);									//연락처
		if (pInfoDB.pSex == 1) {																			//성별
			ListView_SetItemText(hReportEmpLV, i, 5, (LPSTR)"남");											//남
		}
		else {
			ListView_SetItemText(hReportEmpLV, i, 5, (LPSTR)"여");											//여
		}
		if (empDB.empRetire == 0) {
			ListView_SetItemText(hReportEmpLV, i, 6, (LPSTR)"재직");										//재직
		}
		else if (empDB.empRetire == 1) {
			ListView_SetItemText(hReportEmpLV, i, 6, (LPSTR)"퇴직요청");									//퇴직요청
		}
		else {
			ListView_SetItemText(hReportEmpLV, i, 6, (LPSTR)"퇴직");										//퇴직
		}
		i++;
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL SelectRetire(LPSTR empno): RETIREINFO DB에서 empno에 해당하는 레코드 뿌림
*/
BOOL SelectRetire(LPSTR empno) {
	LVITEM LI;
	TCHAR Q[512];
	RETIREDB retireDB;
	int i;

	SQLBindCol(hStmt, 1, SQL_C_CHAR, retireDB.empNo, sizeof(retireDB.empNo), &retireDB.IempNo);								//사번
	SQLBindCol(hStmt, 2, SQL_C_CHAR, retireDB.empName, sizeof(retireDB.empName), &retireDB.IempName);						//이름
	SQLBindCol(hStmt, 3, SQL_C_CHAR, retireDB.empBuseo, sizeof(retireDB.empBuseo), &retireDB.IempBuseo);					//부서
	SQLBindCol(hStmt, 4, SQL_C_CHAR, retireDB.empPoscode, sizeof(retireDB.empPoscode), &retireDB.IempPoscode);				//직책
	SQLBindCol(hStmt, 5, SQL_C_CHAR, retireDB.empPhone, sizeof(retireDB.empPhone), &retireDB.IempPhone);					//연락처
	SQLBindCol(hStmt, 6, SQL_C_CHAR, retireDB.retireReason, sizeof(retireDB.retireReason), &retireDB.IretireReason);		//퇴직사유

	wsprintf(Q, TEXT("SELECT EMPNO, EMPNAME, EMPBUSEO, EMPPOSCODE, EMPPHONE, RETIREREASON FROM RETIREINFO WHERE EMPNO = '%s'"), empno);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	SQLBindCol(hStmt, 1, SQL_C_CHAR, retireDB.empBuseo, sizeof(retireDB.empBuseo), &retireDB.IempBuseo);				//부서명

	wsprintf(Q, TEXT("SELECT NAME FROM BUSEO WHERE CODE = '%s'"), retireDB.empBuseo);
	//SQL문 실행
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	SQLBindCol(hStmt, 1, SQL_C_CHAR, retireDB.empPoscode, sizeof(retireDB.empPoscode), &retireDB.IempPoscode);			//직책명

	wsprintf(Q, TEXT("SELECT NAME FROM POSITION WHERE CODE = '%s'"), retireDB.empPoscode);
	//SQL문 실행
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	ListView_DeleteAllItems(hReportRetireLV);
	LI.mask = LVIF_TEXT;
	LI.iItem = 0;
	LI.iSubItem = 0;
	LI.pszText = retireDB.empNo;
	ListView_InsertItem(hReportRetireLV, &LI);													//사번
	ListView_SetItemText(hReportRetireLV, 0, 1, (LPSTR)retireDB.empName);						//이름
	ListView_SetItemText(hReportRetireLV, 0, 2, (LPSTR)retireDB.empBuseo);						//부서
	ListView_SetItemText(hReportRetireLV, 0, 3, (LPSTR)retireDB.empPoscode);					//직책
	ListView_SetItemText(hReportRetireLV, 0, 4, (LPSTR)retireDB.empPhone);						//연락처
	ListView_SetItemText(hReportRetireLV, 0, 5, (LPSTR)retireDB.retireReason);					//퇴직사유

	return TRUE;
}

/*
BOOL SelectFamily(LPSTR empno): FAMILYMEMBER DB에서 empno에 해당하는 레코드 뿌림
*/
BOOL SelectFamily(LPSTR empno, LPSTR empName) {
	LVITEM LI;
	int i;
	TCHAR Q[512];

	//바인딩할 DB구조체 선언
	FAMILYDB famDB;

	//결과를 돌려받기 위해 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, famDB.name, sizeof(famDB.name), &famDB.Iname);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, famDB.age, sizeof(famDB.age), &famDB.Iage);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, famDB.relation, sizeof(famDB.relation), &famDB.Irelation);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, famDB.job, sizeof(famDB.job), &famDB.Ijob);

	wsprintf(Q, "SELECT NAME, AGE, RELATION, JOB from FAMILYMEMBER WHERE EMPNO = '%s'", empno);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select된 데이터를 hEMPList 리스트뷰를 비운후 새로 뿌림
	i = 0;
	ListView_DeleteAllItems(hReportFamilyLV);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		LI.mask = LVIF_TEXT;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = empno;
		ListView_InsertItem(hReportFamilyLV, &LI);													//사원번호
		ListView_SetItemText(hReportFamilyLV, i, 1, empName);										//사원명
		ListView_SetItemText(hReportFamilyLV, i, 2, (LPSTR)famDB.name);								//이름
		ListView_SetItemText(hReportFamilyLV, i, 3, (LPSTR)famDB.age);								//나이
		ListView_SetItemText(hReportFamilyLV, i, 4, (LPSTR)famDB.relation);							//관계
		ListView_SetItemText(hReportFamilyLV, i, 5, (LPSTR)famDB.job);								//직업
		i++;
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}