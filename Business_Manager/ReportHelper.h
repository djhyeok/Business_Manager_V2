#pragma once
#ifndef REPORTHELPER_H
#define REPORTHELPER_H

#include "Common.h"
#include <CommCtrl.h>
#include <windows.h>

BOOL InitCombo(LPSTR, HWND);
BOOL SelectReport(LPSTR, EMP);
BOOL SelectRetire(LPSTR);
BOOL SelectFamily(LPSTR, LPSTR);

#endif