#pragma once
#ifndef BASE_H
#define BASE_H

#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "Common.h"

LRESULT CALLBACK InitBuseoMDIProc(HWND, UINT, WPARAM, LPARAM);		//�μ� MDI ������ ���ν���
LRESULT CALLBACK InitReligionMDIProc(HWND, UINT, WPARAM, LPARAM);	//���� MDI ������ ���ν���
LRESULT CALLBACK InitPositionMDIProc(HWND, UINT, WPARAM, LPARAM);	//���� MDI ������ ���ν���




#endif