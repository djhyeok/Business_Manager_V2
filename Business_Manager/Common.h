#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>

//��� ��������
typedef struct base {
	TCHAR code[3];		//�����ڵ�
	TCHAR name[255];	//�̸�
} BASE;

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

//�����������
typedef struct empInfo {
	TCHAR empBuseo[255];	//�ٹ��μ�
	TCHAR empPosCode[255];	//�����å
	SYSTEMTIME empStartYear;//�Ի�⵵
	TCHAR empNo[12];		//�����ȣ ex) 2024�� �Ի� �渮�� ���� 0001  -> 2024GR20001
	int empRetire;			//�ٹ�����(0:�ٹ�, 1:������û 2:����)
	PERSONALINFO pInfo;		//�����������
} EMP;

typedef struct retireInfo {
	TCHAR empNo[12];		//������ �����ȣ
	TCHAR empBuseo[255];	//���� �ٹ��μ�
	TCHAR empPoscode[255];	//���� ��� ��å
	TCHAR empName[255];		//�����ڸ�
	TCHAR empPhone[14];		//��󿬶�ó
	int retireReason;		//��������
}RETIRE;

typedef struct familyMember {
	TCHAR empNo[12];		//�����ȣ
	TCHAR name[255];		//�̸�
	TCHAR age[5];			//����
	TCHAR relation[255];	//����
	TCHAR job[255];			//����(ȸ���,������,�ڿ���,����,�л�)
} FAMILY;
#endif