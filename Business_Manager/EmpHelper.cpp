#include "EmpHelper.h"

//extern으로 다른 파일에서 선언된 전역변수 가져옴
extern HINSTANCE g_hInst;
extern SQLHENV hEnv;
extern SQLHDBC hDbc;
extern SQLHSTMT hStmt;
extern HWND hEMPList;		//사원관리MDI의 사원리스트뷰
extern HWND hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpReligion;	//컨트롤 핸들
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDC_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_REFRESH
};

/*
BOOL InitControl(HWND hWnd) : 컨트롤 생성 및 초기설정
*/
BOOL InitControl(HWND* hWnd) {
	LVCOLUMN COL;

	//리스트뷰 생성
	hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1150, 700, *hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
	//리스트뷰 헤더추가
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	COL.pszText = (LPSTR)TEXT("사원번호");
	COL.iSubItem = 0;
	ListView_InsertColumn(hEMPList, 0, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 50;
	COL.pszText = (LPSTR)TEXT("부서");
	COL.iSubItem = 1;
	ListView_InsertColumn(hEMPList, 1, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 60;
	COL.pszText = (LPSTR)TEXT("직책");
	COL.iSubItem = 2;
	ListView_InsertColumn(hEMPList, 2, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 80;
	COL.pszText = (LPSTR)TEXT("입사일");
	COL.iSubItem = 3;
	ListView_InsertColumn(hEMPList, 3, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 50;
	COL.pszText = (LPSTR)TEXT("이름");
	COL.iSubItem = 4;
	ListView_InsertColumn(hEMPList, 4, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 70;
	COL.pszText = (LPSTR)TEXT("영문이름");
	COL.iSubItem = 5;
	ListView_InsertColumn(hEMPList, 5, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 70;
	COL.pszText = (LPSTR)TEXT("한자이름");
	COL.iSubItem = 6;
	ListView_InsertColumn(hEMPList, 6, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 50;
	COL.pszText = (LPSTR)TEXT("성별");
	COL.iSubItem = 7;
	ListView_InsertColumn(hEMPList, 7, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 80;
	COL.pszText = (LPSTR)TEXT("생년월일");
	COL.iSubItem = 8;
	ListView_InsertColumn(hEMPList, 8, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("주소");
	COL.iSubItem = 9;
	ListView_InsertColumn(hEMPList, 9, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("이메일");
	COL.iSubItem = 10;
	ListView_InsertColumn(hEMPList, 10, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("연락처1");
	COL.iSubItem = 11;
	ListView_InsertColumn(hEMPList, 11, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = (LPSTR)TEXT("연락처2");
	COL.iSubItem = 12;
	ListView_InsertColumn(hEMPList, 12, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 40;
	COL.pszText = (LPSTR)TEXT("신장");
	COL.iSubItem = 13;
	ListView_InsertColumn(hEMPList, 13, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 40;
	COL.pszText = (LPSTR)TEXT("체중");
	COL.iSubItem = 14;
	ListView_InsertColumn(hEMPList, 14, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 60;
	COL.pszText = (LPSTR)TEXT("결혼관계");
	COL.iSubItem = 15;
	ListView_InsertColumn(hEMPList, 15, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 50;
	COL.pszText = (LPSTR)TEXT("종교");
	COL.iSubItem = 16;
	ListView_InsertColumn(hEMPList, 16, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 60;
	COL.pszText = (LPSTR)TEXT("시력(좌)");
	COL.iSubItem = 17;
	ListView_InsertColumn(hEMPList, 17, &COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 60;
	COL.pszText = (LPSTR)TEXT("시력(우)");
	COL.iSubItem = 18;
	ListView_InsertColumn(hEMPList, 18, &COL);

	DBConnect();
	EMPSelectSQL();
	//2.부서 콤보박스 생성
	BASEDB tempBase;

	hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 45, 153, 200, *hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
	SQLBindCol(hStmt, 1, SQL_C_CHAR, tempBase.name, sizeof(tempBase.name), &tempBase.IName);

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT name FROM BUSEO", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)tempBase.name);
	}
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	//3.직책 콤보박스 생성
	hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 80, 153, 200, *hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
	SQLBindCol(hStmt, 1, SQL_C_CHAR, tempBase.name, sizeof(tempBase.name), &tempBase.IName);

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT name FROM POSITION", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)tempBase.name);
	}
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	//15.종교 콤보박스 생성
	hEmpReligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 580, 153, 200, *hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
	SQLBindCol(hStmt, 1, SQL_C_CHAR, tempBase.name, sizeof(tempBase.name), &tempBase.IName);

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT name FROM RELIGION", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		SendMessage(hEmpReligion, CB_ADDSTRING, 0, (LPARAM)tempBase.name);
	}
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	DBDisconnect();


	//1.사원번호 컨트롤 생성
	hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 10, 150, 25, *hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);

	//4.입사일 날짜컨트롤 생성
	hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 115, 153, 25, *hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
	//5.이름 에디트컨트롤 생성
	hEmpName1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 150, 150, 25, *hWnd, (HMENU)ID_NAME1, g_hInst, NULL);
	hEmpName2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 185, 150, 25, *hWnd, (HMENU)ID_NAME2, g_hInst, NULL);
	hEmpName3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 220, 150, 25, *hWnd, (HMENU)ID_NAME3, g_hInst, NULL);
	//6.성별 라디오버튼 생성
	hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 255, 70, 25, *hWnd, (HMENU)ID_MALE, g_hInst, NULL);
	hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 255, 70, 25, *hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
	CheckRadioButton(*hWnd, ID_MALE, ID_FEMALE, ID_MALE);
	//7.생년월일 날짜컨트롤 생성
	hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 290, 153, 25, *hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
	//8.주소 에디트컨트롤 생성
	hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 325, 150, 25, *hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
	//9.이메일 에디트컨트롤 생성
	hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 360, 150, 25, *hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
	//10.연락처1,2 에디트컨트롤 생성
	hEmpPhone1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 395, 150, 25, *hWnd, (HMENU)ID_PHONE1, g_hInst, NULL);
	hEmpPhone2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, *hWnd, (HMENU)ID_PHONE2, g_hInst, NULL);
	//12.신장 에디트컨트롤 생성
	hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 465, 150, 25, *hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
	//13.체중 에디트컨트롤 생성
	hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 500, 150, 25, *hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
	//14.결혼관계 라디오버튼 생성
	hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 535, 70, 30, *hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
	hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 535, 80, 30, *hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
	CheckRadioButton(*hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
	//16.시력(좌,우) 에디트컨트롤 생성
	hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 615, 150, 25, *hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
	hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 650, 150, 25, *hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);

	//삽입버튼생성
	CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 690, 70, 25, *hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
	//수정버튼생성
	CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 690, 70, 25, *hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
	//퇴직요청 버튼생성
	CreateWindow(TEXT("button"), TEXT("퇴직요청"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 690, 100, 25, *hWnd, (HMENU)IDC_RETIRE, g_hInst, NULL);
	//새로고침버튼생성
	CreateWindow(TEXT("button"), TEXT("새로고침"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 720, 180, 25, *hWnd, (HMENU)IDC_REFRESH, g_hInst, NULL);

	return TRUE;
}
/*
BOOL EMPSelectSQL() : DB에서 EMPVIEW 조회한 후 hEMPList 리스트뷰에 값들 뿌림
*/
BOOL EMPSelectSQL() {
	LVITEM LI;
	int i;

	//바인딩할 DB구조체 선언
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//결과를 돌려받기 위해 바인딩
	//empDB를 EMPVIEW의 해당 column과 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, empDB.empStartYear, sizeof(empDB.empStartYear), &empDB.IempStartYear);
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);
	//pInfoDB를 EMPVIEW의 해당 column과 바인딩
	SQLBindCol(hStmt, 6, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);
	SQLBindCol(hStmt, 7, SQL_C_CHAR, pInfoDB.pName[1], sizeof(pInfoDB.pName[1]), &pInfoDB.IpName1);
	SQLBindCol(hStmt, 8, SQL_C_CHAR, pInfoDB.pName[2], sizeof(pInfoDB.pName[2]), &pInfoDB.IpName2);
	SQLBindCol(hStmt, 9, SQL_C_CHAR, pInfoDB.pAddress, sizeof(pInfoDB.pAddress), &pInfoDB.IpAddress);
	SQLBindCol(hStmt, 10, SQL_C_CHAR, pInfoDB.pEmail, sizeof(pInfoDB.pEmail), &pInfoDB.IpEmail);
	SQLBindCol(hStmt, 11, SQL_C_CHAR, pInfoDB.pPhone[0], sizeof(pInfoDB.pPhone[0]), &pInfoDB.IpPhone0);
	SQLBindCol(hStmt, 12, SQL_C_CHAR, pInfoDB.pPhone[1], sizeof(pInfoDB.pPhone[1]), &pInfoDB.IpPhone1);
	SQLBindCol(hStmt, 13, SQL_C_CHAR, pInfoDB.pBirth, sizeof(pInfoDB.pBirth), &pInfoDB.IpBirth);
	SQLBindCol(hStmt, 14, SQL_C_ULONG, &pInfoDB.pSex, 0, &pInfoDB.IpSex);
	SQLBindCol(hStmt, 15, SQL_C_CHAR, pInfoDB.pPhysical[0], sizeof(pInfoDB.pPhysical[0]), &pInfoDB.IpPhysical0);
	SQLBindCol(hStmt, 16, SQL_C_CHAR, pInfoDB.pPhysical[1], sizeof(pInfoDB.pPhysical[1]), &pInfoDB.IpPhysical1);
	SQLBindCol(hStmt, 17, SQL_C_CHAR, pInfoDB.pPhysical[2], sizeof(pInfoDB.pPhysical[2]), &pInfoDB.IpPhysical2);
	SQLBindCol(hStmt, 18, SQL_C_CHAR, pInfoDB.pPhysical[3], sizeof(pInfoDB.pPhysical[3]), &pInfoDB.IpPhysical3);
	SQLBindCol(hStmt, 19, SQL_C_ULONG, &pInfoDB.pFamily, 0, &pInfoDB.IpFamily);
	SQLBindCol(hStmt, 20, SQL_C_CHAR, pInfoDB.pReligion, sizeof(pInfoDB.pReligion), &pInfoDB.IpReligion);

	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)"SELECT EMPNO, BUSEO, POSITION,TO_CHAR(STARTYEAR,'YYYY-MM-DD'),RETIRE,NAME1,NAME2,NAME3,ADDRESS,EMAIL,PHONE1,PHONE2,TO_CHAR(BIRTH,'YYYY-MM-DD'),SEX,HEIGHT,WEIGHT,LEFTEYE,RIGHTEYE,MARRIAGE,RELIGION from EMPVIEW", SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}

	//select된 데이터를 hEMPList 리스트뷰를 비운후 새로 뿌림
	i = 0;
	ListView_DeleteAllItems(hEMPList);
	while (SQLFetch(hStmt) != SQL_NO_DATA) {
		if (empDB.empRetire == 0) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = empDB.empNo;
			ListView_InsertItem(hEMPList, &LI);
			ListView_SetItemText(hEMPList, i, 1, (LPSTR)empDB.empBuseo);										//부서
			ListView_SetItemText(hEMPList, i, 2, (LPSTR)empDB.empPosCode);										//직책
			ListView_SetItemText(hEMPList, i, 3, (LPSTR)empDB.empStartYear);									//입사일
			ListView_SetItemText(hEMPList, i, 4, (LPSTR)pInfoDB.pName[0]);										//한글이름
			ListView_SetItemText(hEMPList, i, 5, (LPSTR)pInfoDB.pName[1]);										//영문이름
			ListView_SetItemText(hEMPList, i, 6, (LPSTR)pInfoDB.pName[2]);										//한문이름
			ListView_SetItemText(hEMPList, i, 7, (pInfoDB.pSex == 1) ? (LPSTR)TEXT("남") : (LPSTR)TEXT("여"));	//성별
			ListView_SetItemText(hEMPList, i, 8, (LPSTR)pInfoDB.pBirth);										//생년월일
			ListView_SetItemText(hEMPList, i, 9, (LPSTR)pInfoDB.pAddress);										//주소
			ListView_SetItemText(hEMPList, i, 10, (LPSTR)pInfoDB.pEmail);										//이메일
			ListView_SetItemText(hEMPList, i, 11, (LPSTR)pInfoDB.pPhone[0]);									//연락처1
			ListView_SetItemText(hEMPList, i, 12, (LPSTR)pInfoDB.pPhone[1]);									//연락처2
			ListView_SetItemText(hEMPList, i, 13, (LPSTR)pInfoDB.pPhysical[0]);									//체중
			ListView_SetItemText(hEMPList, i, 14, (LPSTR)pInfoDB.pPhysical[1]);									//신장
			ListView_SetItemText(hEMPList, i, 15, (pInfoDB.pFamily == TRUE) ? (LPSTR)TEXT("기혼") : (LPSTR)TEXT("미혼"));	//결혼여부
			ListView_SetItemText(hEMPList, i, 16, (LPSTR)pInfoDB.pReligion);									//종교
			ListView_SetItemText(hEMPList, i, 17, (LPSTR)pInfoDB.pPhysical[2]);									//좌시력
			ListView_SetItemText(hEMPList, i, 18, (LPSTR)pInfoDB.pPhysical[3]);									//우시력
			i++;
		}
	}

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL ControlSelectSQL(LPSTR empno) : EMPVIEW뷰에서 사번이 empno인 사원 조회 후 컨트롤들에 값들 뿌림
*/
BOOL ControlSelectSQL(LPSTR empno) {
	TCHAR Q[500];

	//바인딩할 DB구조체 선언
	EMPDB empDB;
	PERSONALINFODB pInfoDB;

	//결과를 돌려받기 위해 바인딩
	//empDB를 EMPVIEW의 해당 column과 바인딩
	SQLBindCol(hStmt, 1, SQL_C_CHAR, empDB.empNo, sizeof(empDB.empNo), &empDB.IempNo);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, empDB.empBuseo, sizeof(empDB.empBuseo), &empDB.IempBuseo);
	SQLBindCol(hStmt, 3, SQL_C_CHAR, empDB.empPosCode, sizeof(empDB.empPosCode), &empDB.IempPosCode);
	SQLBindCol(hStmt, 4, SQL_C_CHAR, empDB.empStartYear, sizeof(empDB.empStartYear), &empDB.IempStartYear);
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &empDB.empRetire, 0, &empDB.IempRetire);
	//pInfoDB를 EMPVIEW의 해당 column과 바인딩
	SQLBindCol(hStmt, 6, SQL_C_CHAR, pInfoDB.pName[0], sizeof(pInfoDB.pName[0]), &pInfoDB.IpName0);
	SQLBindCol(hStmt, 7, SQL_C_CHAR, pInfoDB.pName[1], sizeof(pInfoDB.pName[1]), &pInfoDB.IpName1);
	SQLBindCol(hStmt, 8, SQL_C_CHAR, pInfoDB.pName[2], sizeof(pInfoDB.pName[2]), &pInfoDB.IpName2);
	SQLBindCol(hStmt, 9, SQL_C_CHAR, pInfoDB.pAddress, sizeof(pInfoDB.pAddress), &pInfoDB.IpAddress);
	SQLBindCol(hStmt, 10, SQL_C_CHAR, pInfoDB.pEmail, sizeof(pInfoDB.pEmail), &pInfoDB.IpEmail);
	SQLBindCol(hStmt, 11, SQL_C_CHAR, pInfoDB.pPhone[0], sizeof(pInfoDB.pPhone[0]), &pInfoDB.IpPhone0);
	SQLBindCol(hStmt, 12, SQL_C_CHAR, pInfoDB.pPhone[1], sizeof(pInfoDB.pPhone[1]), &pInfoDB.IpPhone1);
	SQLBindCol(hStmt, 13, SQL_C_CHAR, pInfoDB.pBirth, sizeof(pInfoDB.pBirth), &pInfoDB.IpBirth);
	SQLBindCol(hStmt, 14, SQL_C_ULONG, &pInfoDB.pSex, 0, &pInfoDB.IpSex);
	SQLBindCol(hStmt, 15, SQL_C_CHAR, pInfoDB.pPhysical[0], sizeof(pInfoDB.pPhysical[0]), &pInfoDB.IpPhysical0);
	SQLBindCol(hStmt, 16, SQL_C_CHAR, pInfoDB.pPhysical[1], sizeof(pInfoDB.pPhysical[1]), &pInfoDB.IpPhysical1);
	SQLBindCol(hStmt, 17, SQL_C_CHAR, pInfoDB.pPhysical[2], sizeof(pInfoDB.pPhysical[2]), &pInfoDB.IpPhysical2);
	SQLBindCol(hStmt, 18, SQL_C_CHAR, pInfoDB.pPhysical[3], sizeof(pInfoDB.pPhysical[3]), &pInfoDB.IpPhysical3);
	SQLBindCol(hStmt, 19, SQL_C_ULONG, &pInfoDB.pFamily, 0, &pInfoDB.IpFamily);
	SQLBindCol(hStmt, 20, SQL_C_CHAR, pInfoDB.pReligion, sizeof(pInfoDB.pReligion), &pInfoDB.IpReligion);

	lstrcpy(Q, "SELECT EMPNO, BUSEO, POSITION,TO_CHAR(STARTYEAR,'YYYY-MM-DD'),RETIRE,NAME1,NAME2,NAME3,ADDRESS,EMAIL,PHONE1,PHONE2,TO_CHAR(BIRTH,'YYYY-MM-DD'),SEX,HEIGHT,WEIGHT,LEFTEYE,RIGHTEYE,MARRIAGE,RELIGION from EMPVIEW WHERE EMPNO = '");
	lstrcat(Q, empno);
	lstrcat(Q, "'");
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	//fetch
	SQLFetch(hStmt);
	if (hStmt) {
		SQLCloseCursor(hStmt);
	}
	//선택한 줄의 데이터들로 핸들 채우기
	SetWindowText(hEmpNo, empDB.empNo);
	SetWindowText(hEmpName1, pInfoDB.pName[0]);
	SetWindowText(hEmpName2, pInfoDB.pName[1]);
	SetWindowText(hEmpName3, pInfoDB.pName[2]);
	SetWindowText(hEmpAddress, pInfoDB.pAddress);
	SetWindowText(hEmpEmail, pInfoDB.pEmail);
	SetWindowText(hEmpPhone1, pInfoDB.pPhone[0]);
	SetWindowText(hEmpPhone2, pInfoDB.pPhone[1]);
	SetWindowText(hEmpHeight, pInfoDB.pPhysical[0]);
	SetWindowText(hEmpWeight, pInfoDB.pPhysical[1]);
	SetWindowText(hEmpLefteye, pInfoDB.pPhysical[2]);
	SetWindowText(hEmpRighteye, pInfoDB.pPhysical[3]);

	if (pInfoDB.pSex == 1) {
		SendMessage(hEmpMale, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEmpFemale, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hEmpFemale, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEmpMale, BM_SETCHECK, BST_UNCHECKED, 0);
	}

	if (pInfoDB.pSex == TRUE) {
		SendMessage(hEmpMarriage, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEmpSingle, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hEmpSingle, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEmpMarriage, BM_SETCHECK, BST_UNCHECKED, 0);
	}

	SendMessage(hEmpBuseo, CB_SETCURSEL, SendMessage(hEmpBuseo, CB_FINDSTRINGEXACT, -1, (LPARAM)empDB.empBuseo), 0);
	SendMessage(hEmpPoscode, CB_SETCURSEL, SendMessage(hEmpPoscode, CB_FINDSTRINGEXACT, -1, (LPARAM)empDB.empPosCode), 0);
	SendMessage(hEmpReligion, CB_SETCURSEL, SendMessage(hEmpReligion, CB_FINDSTRINGEXACT, -1, (LPARAM)pInfoDB.pReligion), 0);

	TCHAR temp[50];
	SYSTEMTIME st;
	//입사일
	lstrcpy(temp, empDB.empStartYear);
	temp[4] = '\0';
	st.wYear = atoi(temp);
	temp[0] = empDB.empStartYear[5];
	temp[1] = empDB.empStartYear[6];
	temp[2] = '\0';
	st.wMonth = atoi(temp);
	temp[0] = empDB.empStartYear[8];
	temp[1] = empDB.empStartYear[9];
	temp[2] = '\0';
	st.wDay = atoi(temp);
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;
	SendMessage(hEmpIndate, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

	//생일
	lstrcpy(temp, pInfoDB.pBirth);
	temp[4] = '\0';
	st.wYear = atoi(temp);
	temp[0] = pInfoDB.pBirth[5];
	temp[1] = pInfoDB.pBirth[6];
	temp[2] = '\0';
	st.wMonth = atoi(temp);
	temp[0] = pInfoDB.pBirth[8];
	temp[1] = pInfoDB.pBirth[9];
	temp[2] = '\0';
	st.wDay = atoi(temp);
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;
	SendMessage(hEmpBirth, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

	if (hStmt) {
		SQLCloseCursor(hStmt);
	}

	return TRUE;
}

/*
BOOL EMPUpdateSQL(EMP updateData) : DB에서 사원번호가 updateData.empno인 사원정보 수정
*/
BOOL EMPUpdateSQL(EMP updateData) {
	TCHAR Q[512];

	//가져온 table명과 value로 쿼리 만들기
	wsprintf(Q, "UPDATE EMP SET BUSEO = '%s', POSITION = '%s', STARTYEAR = TO_DATE('%d-%d-%d','YYYY-MM-DD'), RETIRE = %d WHERE EMPNO ='%s'"
		, updateData.empBuseo, updateData.empPosCode, updateData.empStartYear.wYear, updateData.empStartYear.wMonth, updateData.empStartYear.wDay, updateData.empRetire, updateData.empNo);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	wsprintf(Q, "UPDATE PERSONALINFO SET NAME1 = '%s', NAME2 = '%s', NAME3 = '%s', ADDRESS = '%s',EMAIL = '%s',PHONE1 = '%s',PHONE2 = '%s',SEX = %d,HEIGHT = '%s',WEIGHT = '%s',LEFTEYE='%s',RIGHTEYE='%s',MARRIAGE =%d,RELIGION='%s',BIRTH=TO_DATE('%d-%d-%d','YYYY-MM-DD') WHERE EMPNO = '%s'"
		, updateData.pInfo.pName[0], updateData.pInfo.pName[1], updateData.pInfo.pName[2], updateData.pInfo.pAddress, updateData.pInfo.pEmail
		, updateData.pInfo.pPhone[0], updateData.pInfo.pPhone[1], updateData.pInfo.pSex, updateData.pInfo.pPhysical[0]
		, updateData.pInfo.pPhysical[1], updateData.pInfo.pPhysical[2], updateData.pInfo.pPhysical[3], updateData.pInfo.pFamily
		, updateData.pInfo.pReligion, updateData.pInfo.pBirth.wYear, updateData.pInfo.pBirth.wMonth, updateData.pInfo.pBirth.wDay, updateData.empNo);
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	return TRUE;
}

/*
BOOL EMPInsertSQL(EMP addData) : EMP 테이블에 addData 데이터 추가
*/
BOOL EMPInsertSQL(EMP addData) {
	TCHAR Q[512];
	wsprintf(Q, "INSERT INTO EMP(EMPNO,BUSEO,POSITION,STARTYEAR,RETIRE) VALUES ('%s','%s','%s',TO_DATE('%d-%d-%d','YYYY-MM-DD'),'%d')"
		, addData.empNo, addData.empBuseo, addData.empPosCode, addData.empStartYear.wYear, addData.empStartYear.wMonth, addData.empStartYear.wDay, addData.empRetire);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	wsprintf(Q, "INSERT INTO PERSONALINFO(EMPNO,NAME1,NAME2,NAME3,ADDRESS,EMAIL,PHONE1,PHONE2,SEX,HEIGHT,WEIGHT,LEFTEYE,RIGHTEYE,MARRIAGE,RELIGION,BIRTH) VALUES('%s','%s','%s','%s','%s','%s','%s','%s',%d,'%s','%s','%s','%s',%d,'%s',TO_DATE('%d-%d-%d','YYYY-MM-DD'))"
		, addData.empNo, addData.pInfo.pName[0], addData.pInfo.pName[1], addData.pInfo.pName[2], addData.pInfo.pAddress, addData.pInfo.pEmail, addData.pInfo.pPhone[0], addData.pInfo.pPhone[1], addData.pInfo.pSex
		, addData.pInfo.pPhysical[0], addData.pInfo.pPhysical[1], addData.pInfo.pPhysical[2], addData.pInfo.pPhysical[3], addData.pInfo.pFamily, addData.pInfo.pReligion, addData.pInfo.pBirth.wYear, addData.pInfo.pBirth.wMonth, addData.pInfo.pBirth.wDay);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	return TRUE;
}

/*
BOOL EMPRetire(LPSTR empno) :사번이 empno인 사원의 퇴직정보를 1로 바꿈
*/
BOOL EMPRetire(LPSTR empno) {
	TCHAR Q[512];
	wsprintf(Q, "UPDATE EMP SET RETIRE = 1 WHERE EMPNO = '%s'", empno);
	//SQL문을 실행한다.
	if (SQLExecDirect(hStmt, (SQLCHAR*)Q, SQL_NTS) != SQL_SUCCESS) {
		return FALSE;
	}
	return TRUE;
}