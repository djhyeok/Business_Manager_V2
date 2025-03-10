#pragma once
#ifndef DBHelper_H
#define DBHelper_H

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include "Common.h"

BOOL DBConnect();
void DBDisconnect();
int CountRecord(LPSTR);

#endif