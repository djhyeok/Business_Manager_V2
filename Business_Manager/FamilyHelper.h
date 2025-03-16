#pragma once
#ifndef FAMILYHELPER_H
#define FAMILYHELPER_H

#include "Common.h"
#include <CommCtrl.h>
#include <windows.h>
#include "DBHelper.h"

BOOL SelectEMP();
BOOL InsertFamily(FAMILY);
BOOL SelectFamily(LPSTR);
int GetFamilyIndex(LPSTR, LPSTR);
BOOL UpdateFamily(int, FAMILY);
BOOL DeleteFamily(int);

#endif