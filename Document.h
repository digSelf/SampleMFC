// Document.h: interface for the CDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENT_H__05CE317D_B8D7_45B5_A8C4_9AC01B8A9411__INCLUDED_)
#define AFX_DOCUMENT_H__05CE317D_B8D7_45B5_A8C4_9AC01B8A9411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdTarget.h"

class CDocument : public CCmdTarget  
{
public:
	CDocument();
	virtual ~CDocument();

};

#endif // !defined(AFX_DOCUMENT_H__05CE317D_B8D7_45B5_A8C4_9AC01B8A9411__INCLUDED_)
