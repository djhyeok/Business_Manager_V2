#include "Emp.h"
/*
아직안함
WM_CREATE에서 select문 날려서 DB데이터 불러옴
삽입 수정 삭제 후 DB에서 다시 select해서 LV에 뿌림
*/
extern HINSTANCE g_hInst;
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern int totEmp;			//사원수
extern EMP* workEmp;		//사원
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpReligion;	//컨트롤 핸들
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDC_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_REFRESH
};

//사원관리 프로시져
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HFONT hFont, OldFont;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int index, cal, num;
	static EMP tempEmp;
	SYSTEMTIME st;
	TCHAR str[255];

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);
		InitControl(&hWnd);
		ListView_SetExtendedListViewStyle(hEMPList, LVS_EX_FULLROWSELECT);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:			//삽입 버튼
			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//입사일
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//생일
			}
			GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//이름
			GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//영문이름
			GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//한자이름
			if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pSex = TRUE;														//남자
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//여자
			}

			GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//주소
			GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//전자우편
			GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//연락처1
			GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//연락처2
			GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//신장
			GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//체중
			if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				tempEmp.pInfo.pFamily = TRUE;													//기혼
			}
			else {
				tempEmp.pInfo.pFamily = FALSE;													//미혼
			}
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);			//시력(좌)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);		//시력(우)
			DBConnect();
			num = CountRecord((LPSTR)"EMP");
			SendMessage(hEmpBuseo, CB_GETLBTEXT, SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.empBuseo);					//부서
			lstrcpy(tempEmp.empBuseo, Name2Code((LPSTR)"BUSEO", (LPSTR)tempEmp.empBuseo));
			SendMessage(hEmpReligion, CB_GETLBTEXT, SendMessage(hEmpReligion, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.pInfo.pReligion);	//종교
			lstrcpy(tempEmp.pInfo.pReligion, Name2Code((LPSTR)"RELIGION", (LPSTR)tempEmp.pInfo.pReligion));
			SendMessage(hEmpPoscode, CB_GETLBTEXT, SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0), (LPARAM)tempEmp.empPosCode);			//직책
			lstrcpy(tempEmp.empPosCode, Name2Code((LPSTR)"POSITION", (LPSTR)tempEmp.empPosCode));
			DBDisconnect();
			//근무여부 초기화
			tempEmp.empRetire = 0;
			//사원번호생성
			wsprintf(tempEmp.empNo, TEXT("%d"), tempEmp.empStartYear.wYear);
			lstrcat(tempEmp.empNo, tempEmp.empBuseo);
			if (tempEmp.pInfo.pSex == TRUE) {
				lstrcat(tempEmp.empNo, TEXT("1"));
			}
			else {
				lstrcat(tempEmp.empNo, TEXT("2"));
			}
			cal = num + 1;
			wsprintf(str, TEXT("%d"), cal / 1000);
			lstrcat(tempEmp.empNo, str);
			cal %= 1000;
			wsprintf(str, TEXT("%d"), cal / 100);
			lstrcat(tempEmp.empNo, str);
			cal %= 100;
			wsprintf(str, TEXT("%d"), cal / 10);
			lstrcat(tempEmp.empNo, str);
			cal %= 10;
			wsprintf(str, TEXT("%d"), cal);
			lstrcat(tempEmp.empNo, str);

			//모두 입력 및 선택시 재할당 후 값 추가
			GetWindowText(hEmpNo, str, 255);
			if (lstrlen(str) != 0) {
				MessageBox(hWnd, TEXT("기존 사원 선택으로는 삽입이 불가능합니다."), TEXT("삽입 오류"), MB_OK);
			}
			else if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {

				DBConnect();
				EMPInsertSQL(tempEmp);
				//리스트뷰 지우고 다시 사원정보 채우기
				ListView_DeleteAllItems(hEMPList);
				EMPSelectSQL();
				DBDisconnect();
			}
			else {
				MessageBox(hWnd, TEXT("길이가 0인 값은 추가할 수 없습니다."), TEXT("입력값 오류"), MB_OK);
			}
			//입력 컨트롤들 빈칸으로 초기화
			SetWindowText(hEmpNo, TEXT(""));
			SetWindowText(hEmpName1, TEXT(""));
			SetWindowText(hEmpName2, TEXT(""));
			SetWindowText(hEmpName3, TEXT(""));
			SetWindowText(hEmpAddress, TEXT(""));
			SetWindowText(hEmpEmail, TEXT(""));
			SetWindowText(hEmpPhone1, TEXT(""));
			SetWindowText(hEmpPhone2, TEXT(""));
			SetWindowText(hEmpHeight, TEXT(""));
			SetWindowText(hEmpWeight, TEXT(""));
			SetWindowText(hEmpLefteye, TEXT(""));
			SetWindowText(hEmpRighteye, TEXT(""));
			SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);

			break;
		case IDC_MODIFY:	//수정 버튼
			GetWindowText(hEmpNo, tempEmp.empNo, 12);
			if (lstrlen(tempEmp.empNo) == 0) {
				MessageBox(hWnd, TEXT("수정할 사원을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {

				if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.empStartYear = st;														//입사일
				}
				GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], 255);								//이름
				GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], 255);								//영문이름
				GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], 255);								//한자이름
				if (SendMessage(hEmpMale, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pSex = TRUE;														//남자
				}
				else {
					tempEmp.pInfo.pSex = FALSE;														//여자
				}
				if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
					tempEmp.pInfo.pBirth = st;														//생일
				}

				GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, 255);							//주소
				GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, 255);								//전자우편
				GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], 14);								//연락처1
				GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], 14);								//연락처2
				GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], 11);							//신장
				GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], 11);							//체중
				if (SendMessage(hEmpMarriage, BM_GETCHECK, 0, 0) == BST_CHECKED) {
					tempEmp.pInfo.pFamily = TRUE;													//기혼
				}
				else {
					tempEmp.pInfo.pFamily = FALSE;													//미혼
				}
				GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], 11);							//시력(좌)
				GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], 11);						//시력(우)

				DBConnect();
				SendMessage(hEmpBuseo, CB_GETLBTEXT, SendMessage(hEmpBuseo, CB_GETCURSEL, 0, 0), (LPARAM)str);			//부서
				lstrcpy(tempEmp.empBuseo, Name2Code((LPSTR)"BUSEO", str));

				SendMessage(hEmpReligion, CB_GETLBTEXT, SendMessage(hEmpReligion, CB_GETCURSEL, 0, 0), (LPARAM)str);	//종교
				lstrcpy(tempEmp.pInfo.pReligion, Name2Code((LPSTR)"RELIGION", str));

				SendMessage(hEmpPoscode, CB_GETLBTEXT, SendMessage(hEmpPoscode, CB_GETCURSEL, 0, 0), (LPARAM)str);		//직책
				lstrcpy(tempEmp.empPosCode, Name2Code((LPSTR)"POSITION", str));

				EMPUpdateSQL(tempEmp);
				EMPSelectSQL();
				DBDisconnect();

				//입력 컨트롤들 빈칸으로 초기화
				SetWindowText(hEmpNo, TEXT(""));
				SetWindowText(hEmpName1, TEXT(""));
				SetWindowText(hEmpName2, TEXT(""));
				SetWindowText(hEmpName3, TEXT(""));
				SetWindowText(hEmpAddress, TEXT(""));
				SetWindowText(hEmpEmail, TEXT(""));
				SetWindowText(hEmpPhone1, TEXT(""));
				SetWindowText(hEmpPhone2, TEXT(""));
				SetWindowText(hEmpHeight, TEXT(""));
				SetWindowText(hEmpWeight, TEXT(""));
				SetWindowText(hEmpLefteye, TEXT(""));
				SetWindowText(hEmpRighteye, TEXT(""));
				SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);

			}
			break;
		case IDC_REFRESH:			//새로고침 버튼
			ListView_DeleteAllItems(hEMPList);
			DBConnect();
			EMPSelectSQL();
			DBDisconnect();
			//입력 컨트롤들 빈칸으로 초기화
			SetWindowText(hEmpNo, TEXT(""));
			SetWindowText(hEmpName1, TEXT(""));
			SetWindowText(hEmpName2, TEXT(""));
			SetWindowText(hEmpName3, TEXT(""));
			SetWindowText(hEmpAddress, TEXT(""));
			SetWindowText(hEmpEmail, TEXT(""));
			SetWindowText(hEmpPhone1, TEXT(""));
			SetWindowText(hEmpPhone2, TEXT(""));
			SetWindowText(hEmpHeight, TEXT(""));
			SetWindowText(hEmpWeight, TEXT(""));
			SetWindowText(hEmpLefteye, TEXT(""));
			SetWindowText(hEmpRighteye, TEXT(""));
			SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
			SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);
			return 0;
		case IDC_RETIRE:		//퇴직처리 버튼
			index = ListView_GetNextItem(hEMPList, -1, LVNI_ALL | LVNI_SELECTED);
			if (index == -1) {
				MessageBox(hWnd, TEXT("퇴직처리할 사원을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				DBConnect();
				//선택된 사원의 근무상태를 퇴직요청으로 변경
				GetWindowText(hEmpNo, tempEmp.empNo, 12);
				EMPRetire(tempEmp.empNo);
				//리스트뷰 지우고 다시 사원정보 채우기
				ListView_DeleteAllItems(hEMPList);
				EMPSelectSQL();
				DBDisconnect();
				//입력 컨트롤들 빈칸으로 초기화
				SetWindowText(hEmpNo, TEXT(""));
				SetWindowText(hEmpName1, TEXT(""));
				SetWindowText(hEmpName2, TEXT(""));
				SetWindowText(hEmpName3, TEXT(""));
				SetWindowText(hEmpAddress, TEXT(""));
				SetWindowText(hEmpEmail, TEXT(""));
				SetWindowText(hEmpPhone1, TEXT(""));
				SetWindowText(hEmpPhone2, TEXT(""));
				SetWindowText(hEmpHeight, TEXT(""));
				SetWindowText(hEmpWeight, TEXT(""));
				SetWindowText(hEmpLefteye, TEXT(""));
				SetWindowText(hEmpRighteye, TEXT(""));
				SendMessage(hEmpBuseo, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpPoscode, CB_SETCURSEL, (WPARAM)-1, 0);
				SendMessage(hEmpReligion, CB_SETCURSEL, (WPARAM)-1, 0);
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LVITEM LI;
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
		if (hdr->hwndFrom == hEMPList) {
			switch (hdr->code) {
			case LVN_ITEMCHANGED:
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					//선택한 줄의 데이터들로 핸들 채우기
					LI.mask = LVIF_TEXT;
					LI.iSubItem = 0;
					LI.pszText = str;
					LI.cchTextMax = sizeof(str);
					SendMessage(hEMPList, LVM_GETITEMTEXT, (WPARAM)nlv->iItem, (LPARAM)&LI);

					DBConnect();
					ControlSelectSQL((LPSTR)str);
					//EMPSelectSQL();
					DBDisconnect();

				}
				return TRUE;
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 65, 13, TEXT("사원번호"), lstrlen(TEXT("사원번호")));
		TextOut(hdc, 65, 48, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 65, 83, TEXT("직책"), lstrlen(TEXT("직책")));
		TextOut(hdc, 65, 118, TEXT("입사일"), lstrlen(TEXT("입사일")));
		TextOut(hdc, 65, 153, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 65, 188, TEXT("영문이름"), lstrlen(TEXT("영문이름")));
		TextOut(hdc, 65, 223, TEXT("한문이름"), lstrlen(TEXT("한문이름")));
		TextOut(hdc, 65, 258, TEXT("성별"), lstrlen(TEXT("성별")));
		TextOut(hdc, 65, 293, TEXT("생년월일"), lstrlen(TEXT("생년월일")));
		TextOut(hdc, 65, 328, TEXT("주소"), lstrlen(TEXT("주소")));
		TextOut(hdc, 65, 363, TEXT("전자우편"), lstrlen(TEXT("전자우편")));
		TextOut(hdc, 65, 398, TEXT("연락처1"), lstrlen(TEXT("연락처1")));
		TextOut(hdc, 65, 433, TEXT("연락처2"), lstrlen(TEXT("연락처2")));
		TextOut(hdc, 65, 470, TEXT("신장"), lstrlen(TEXT("신장")));
		TextOut(hdc, 65, 505, TEXT("체중"), lstrlen(TEXT("체중")));
		TextOut(hdc, 65, 545, TEXT("결혼관계"), lstrlen(TEXT("결혼관계")));
		TextOut(hdc, 65, 585, TEXT("종교"), lstrlen(TEXT("종교")));
		TextOut(hdc, 65, 620, TEXT("시력(좌)"), lstrlen(TEXT("시력(좌)")));
		TextOut(hdc, 65, 655, TEXT("시력(우)"), lstrlen(TEXT("시력(우)")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
