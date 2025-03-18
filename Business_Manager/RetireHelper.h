#pragma once

#ifndef RETIREHELPER_H
#define RETIREHELPER_H

#include "Common.h"
#include <CommCtrl.h>
#include <windows.h>
#include "DBHelper.h"
#include "BaseHelper.h"

BOOL SelectReqEMP();
BOOL SelectRetEMP();
BOOL RetireEMP(RETIRE);

#endif