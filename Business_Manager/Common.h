#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>

//기업 기초정보
typedef struct base {
	TCHAR code[3];		//구분코드
	TCHAR name[255];	//이름
} BASE;

//개인신상정보
typedef struct personalInfo {
	TCHAR pName[3][255];	//이름(한글,한자,영문)
	TCHAR pAddress[255];	//주소
	TCHAR pEmail[255];		//email
	TCHAR pPhone[2][14];	//연락처1,2
	SYSTEMTIME pBirth;		//생년월일
	BOOL pSex;				//성별(TRUE:남자, FALSE:여자)
	TCHAR pPhysical[4][11];	//신장, 체중, 좌시력, 우시력
	BOOL pFamily;			//기혼여부(TRUE:기혼, FALSE:미혼)
	TCHAR pReligion[255];	//종교
} PERSONALINFO;

//사원기초정보
typedef struct empInfo {
	TCHAR empBuseo[255];	//근무부서
	TCHAR empPosCode[255];	//사원직책
	SYSTEMTIME empStartYear;//입사년도
	TCHAR empNo[12];		//사원번호 ex) 2024년 입사 경리부 여성 0001  -> 2024GR20001
	int empRetire;			//근무여부(0:근무, 1:퇴직요청 2:퇴직)
	PERSONALINFO pInfo;		//사원개인정보
} EMP;

typedef struct retireInfo {
	TCHAR empNo[12];		//퇴직자 사원번호
	TCHAR empBuseo[255];	//최종 근무부서
	TCHAR empPoscode[255];	//퇴직 당시 직책
	TCHAR empName[255];		//퇴직자명
	TCHAR empPhone[14];		//비상연락처
	int retireReason;		//퇴직사유
}RETIRE;

typedef struct familyMember {
	TCHAR empNo[12];		//사원번호
	TCHAR name[255];		//이름
	TCHAR age[5];			//나이
	TCHAR relation[255];	//관계
	TCHAR job[255];			//직업(회사원,공무원,자영업,무직,학생)
} FAMILY;
#endif