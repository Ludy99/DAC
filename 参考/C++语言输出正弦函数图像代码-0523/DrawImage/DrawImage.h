
// DrawImage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawImageApp: 
// �йش����ʵ�֣������ DrawImage.cpp
//

class CDrawImageApp : public CWinApp
{
public:
	CDrawImageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrawImageApp theApp;