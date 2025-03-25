#pragma once
#ifndef REPORT_H
#define REPORT_H

#include "windows.h"
#include <CommCtrl.h>
#include "resource.h"
#include "Common.h"
#include "DBHelper.h"
#include "ReportHelper.h"
#include "BaseHelper.h"

LRESULT CALLBACK InitReportMDIPROC(HWND, UINT, WPARAM, LPARAM);		//보고서 MDI 윈도우 프로시져

#endif