// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__941A820E_B177_48CB_8711_D37DE8967598__INCLUDED_)
#define AFX_STDAFX_H__941A820E_B177_48CB_8711_D37DE8967598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Windows.h>

#ifndef AFXAPI
#define AFXAPI __stdcall
#endif

// TODO: reference additional headers your program requires here
class CWinApp;
class CWinThread;

CWinApp* AFXAPI AfxGetApp();
CWinThread* AFXAPI AfxGetThread();

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__941A820E_B177_48CB_8711_D37DE8967598__INCLUDED_)
