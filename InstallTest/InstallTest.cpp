// InstallTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MOD_MAIN _T("��ģ��")

int _tmain(int argc, _TCHAR* argv[])
{
	OS_VERSION_USER_DEFINED	OsVerAndProcType		= OS_VERSION_UNKNOWN;

	CPrintfEx				PrintfEx;
	CService				Service;
	COperationSystemVersion	OperationSystemVersion;


	__try
	{
		if (!PrintfEx.Init())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��־ģ���ʼ����ϣ������������");
		_getch();

		if (!OperationSystemVersion.Init())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "OperationSystemVersion.Init failed");

		if (!Service.Install(
			_T("test"),
			_T("testDisplayName"),
			_T("testDescription"),
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			_T("G:\\GitHub\\Test\\Debug\\Test.exe"),
			NULL,
			NULL
			))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Service.Install failed");
			__leave;
		}
	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��������˳�");
		_getch();
	}

	return 0;
}

