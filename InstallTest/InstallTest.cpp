// InstallTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MOD_MAIN _T("��ģ��")

int _tmain(int argc, _TCHAR* argv[])
{
	OS_VERSION_USER_DEFINED	OsVerAndProcType = OS_VERSION_UNKNOWN;


	__try
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��־ģ���ʼ����ϣ������������");
		_getch();

		if (!CService::GetInstance()->Install(
			_T("test"),
			_T("testDisplayName"),
			_T("testDescription"),
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			_T("G:\\GitHub\\Test\\Debug\\Test.exe"),
			NULL,
			NULL,
			TRUE
			))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Service.Install failed");
			__leave;
		}
	}
	__finally
	{
		CService::ReleaseInstance();

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��������˳�");
		CPrintfEx::ReleaseInstance();
		_getch();
	}

	return 0;
}

