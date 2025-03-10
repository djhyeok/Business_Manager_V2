#pragma once
#ifndef BASEHELPER_H
#define BASEHELPER_H

#include "Common.h"
#include <windows.h>
#include "DBHelper.h"

BOOL BaseSelectSQL(LPSTR);
BOOL BaseDeleteSQL(LPSTR, LPSTR);
BOOL BaseUpdateSQL(LPSTR, LPSTR, BASE);
BOOL BaseInsertSQL(LPSTR, BASE);
LPSTR Name2Code(LPSTR, LPSTR);

#endif