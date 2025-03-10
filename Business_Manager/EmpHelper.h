#pragma once
#ifndef EMPHELPER_H
#define EMPHELPER_H

#include "Common.h"
#include <CommCtrl.h>
#include <windows.h>
#include "DBHelper.h"

BOOL InitControl(HWND*);
BOOL EMPSelectSQL();
BOOL ControlSelectSQL(LPSTR);
BOOL EMPUpdateSQL(EMP);
BOOL EMPInsertSQL(EMP);
BOOL EMPRetire(LPSTR);

#endif