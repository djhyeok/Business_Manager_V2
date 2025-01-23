#pragma once
#ifndef BASE_H
#define BASE_H

#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "Common.h"

LRESULT CALLBACK InitBuseoMDIProc(HWND, UINT, WPARAM, LPARAM);		//부서 MDI 윈도우 프로시져
LRESULT CALLBACK InitReligionMDIProc(HWND, UINT, WPARAM, LPARAM);	//종교 MDI 윈도우 프로시져
LRESULT CALLBACK InitPositionMDIProc(HWND, UINT, WPARAM, LPARAM);	//직위 MDI 윈도우 프로시져




#endif