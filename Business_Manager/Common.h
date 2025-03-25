#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdlib.h>

//기업 기초정보
typedef struct base {
	TCHAR code[3];		//구분코드
	TCHAR name[255];	//이름
} BASE;
typedef struct baseDB {
	TCHAR code[10];
	SQLLEN ICode;
	TCHAR name[255];
	SQLLEN IName;
} BASEDB;

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
typedef struct personalInfoDB {
	TCHAR pName[3][255];
	SQLLEN IpName0;
	SQLLEN IpName1;
	SQLLEN IpName2;
	TCHAR pAddress[255];
	SQLLEN IpAddress;
	TCHAR pEmail[255];
	SQLLEN IpEmail;
	TCHAR pPhone[2][20];
	SQLLEN IpPhone0;
	SQLLEN IpPhone1;
	TCHAR pBirth[255];
	SQLLEN IpBirth;
	int pSex;
	SQLLEN IpSex;
	TCHAR pPhysical[4][11];
	SQLLEN IpPhysical0;
	SQLLEN IpPhysical1;
	SQLLEN IpPhysical2;
	SQLLEN IpPhysical3;
	int pFamily;
	SQLLEN IpFamily;
	TCHAR pReligion[255];
	SQLLEN IpReligion;
} PERSONALINFODB;

//사원기초정보
typedef struct empInfo {
	TCHAR empNo[12];		//사원번호 ex) 2024년 입사 경리부 여성 0001  -> 2024GR20001
	TCHAR empBuseo[255];	//근무부서
	TCHAR empPosCode[255];	//직책
	SYSTEMTIME empStartYear;//입사년도
	int empRetire;			//근무여부(0:근무, 1:퇴직요청 2:퇴직)
	PERSONALINFO pInfo;		//사원개인정보
} EMP;
typedef struct empInfoDB {
	TCHAR empBuseo[255];
	SQLLEN IempBuseo;
	TCHAR empPosCode[255];
	SQLLEN IempPosCode;
	TCHAR empStartYear[20];
	SQLLEN IempStartYear;
	TCHAR empNo[12];
	SQLLEN IempNo;
	int empRetire;
	SQLLEN IempRetire;
} EMPDB;

typedef struct retireInfo {
	TCHAR empNo[12];		//퇴직자 사원번호
	TCHAR empBuseo[255];	//최종 근무부서
	TCHAR empPoscode[255];	//퇴직 당시 직책
	TCHAR empName[255];		//퇴직자명
	TCHAR empPhone[14];		//비상연락처
	TCHAR retireReason[20];		//퇴직사유
} RETIRE;
typedef struct retireInfoDB {
	TCHAR empNo[12];
	SQLLEN IempNo;
	TCHAR empBuseo[255];
	SQLLEN IempBuseo;
	TCHAR empPoscode[20];
	SQLLEN IempPoscode;
	TCHAR empName[255];
	SQLLEN IempName;
	TCHAR empPhone[14];
	SQLLEN IempPhone;
	TCHAR retireReason[20];
	SQLLEN IretireReason;
} RETIREDB;

typedef struct familyMember {
	TCHAR empNo[12];		//사원번호
	TCHAR name[255];		//이름
	TCHAR age[5];			//나이
	TCHAR relation[255];	//관계
	TCHAR job[255];			//직업(회사원,공무원,자영업,무직,학생)
} FAMILY;
typedef struct familiyMemberDB {
	TCHAR empNo[12];
	SQLLEN IempNo;
	TCHAR name[255];
	SQLLEN Iname;
	TCHAR age[5];
	SQLLEN Iage;
	TCHAR relation[255];
	SQLLEN Irelation;
	TCHAR job[255];
	SQLLEN Ijob;
} FAMILYDB;

#endif