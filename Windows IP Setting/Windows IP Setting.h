
// Windows IP Setting.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWindowsIPSettingApp:
// See Windows IP Setting.cpp for the implementation of this class
//

class CWindowsIPSettingApp : public CWinApp
{
public:
	CWindowsIPSettingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWindowsIPSettingApp theApp;