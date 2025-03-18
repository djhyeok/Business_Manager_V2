#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdlib.h>

//��� ��������
typedef struct base {
	TCHAR code[3];		//�����ڵ�
	TCHAR name[255];	//�̸�
} BASE;
typedef struct baseDB {
	TCHAR code[10];
	SQLLEN ICode;
	TCHAR name[255];
	SQLLEN IName;
} BASEDB;

//���νŻ�����
typedef struct personalInfo {
	TCHAR pName[3][255];	//�̸�(�ѱ�,����,����)
	TCHAR pAddress[255];	//�ּ�
	TCHAR pEmail[255];		//email
	TCHAR pPhone[2][14];	//����ó1,2
	SYSTEMTIME pBirth;		//�������
	BOOL pSex;				//����(TRUE:����, FALSE:����)
	TCHAR pPhysical[4][11];	//����, ü��, �½÷�, ��÷�
	BOOL pFamily;			//��ȥ����(TRUE:��ȥ, FALSE:��ȥ)
	TCHAR pReligion[255];	//����
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

//�����������
typedef struct empInfo {
	TCHAR empNo[12];		//�����ȣ ex) 2024�� �Ի� �渮�� ���� 0001  -> 2024GR20001
	TCHAR empBuseo[255];	//�ٹ��μ�
	TCHAR empPosCode[255];	//��å
	SYSTEMTIME empStartYear;//�Ի�⵵
	int empRetire;			//�ٹ�����(0:�ٹ�, 1:������û 2:����)
	PERSONALINFO pInfo;		//�����������
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
	TCHAR empNo[12];		//������ �����ȣ
	TCHAR empBuseo[255];	//���� �ٹ��μ�
	TCHAR empPoscode[255];	//���� ��� ��å
	TCHAR empName[255];		//�����ڸ�
	TCHAR empPhone[14];		//��󿬶�ó
	TCHAR retireReason[20];		//��������
} RETIRE;
typedef struct retireInfoDB {
	TCHAR empNo[12];
	SQLLEN IempNo;
	TCHAR empBuseo[255];
	SQLLEN IempBuseo;
	TCHAR empPoscode[3];
	SQLLEN IempPoscode;
	TCHAR empName[255];
	SQLLEN IempName;
	TCHAR empPhone[14];
	SQLLEN IempPhone;
	TCHAR retireReason[20];
	SQLLEN IretireReason;
} RETIREDB;

typedef struct familyMember {
	TCHAR empNo[12];		//�����ȣ
	TCHAR name[255];		//�̸�
	TCHAR age[5];			//����
	TCHAR relation[255];	//����
	TCHAR job[255];			//����(ȸ���,������,�ڿ���,����,�л�)
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