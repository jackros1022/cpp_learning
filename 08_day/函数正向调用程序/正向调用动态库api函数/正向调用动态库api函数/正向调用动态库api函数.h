
// ������ö�̬��api����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C������ö�̬��api����App:
// �йش����ʵ�֣������ ������ö�̬��api����.cpp
//

class C������ö�̬��api����App : public CWinApp
{
public:
	C������ö�̬��api����App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C������ö�̬��api����App theApp;