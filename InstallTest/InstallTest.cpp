// InstallTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR					tchPdbDir[MAX_PATH]		= {0};
	LPTSTR					lpPosition				= NULL;
	OS_VER_AND_PROC_TYPE	OsVerAndProcType		= OS_VER_AND_PROC_TYPE_UNKNOWN;
	TCHAR					tchPath[MAX_PATH]		= {0};

	CPrintfEx				PrintfEx;
	CService				Service;
	COperationSystemVersion	OperationSystemVersion;


	__try
	{
		if (GetModuleFileName(NULL, tchPdbDir, _countof(tchPdbDir)))
		{
			lpPosition = _tcsrchr(tchPdbDir, _T('\\'));
			if (lpPosition)
			{
				*(lpPosition) = _T('\0');

				if (!PrintfEx.Init(tchPdbDir, TRUE))
					printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");
			}
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续");
		_getch();

		OsVerAndProcType = OperationSystemVersion.GetOsVerAndProcType();
		switch (OsVerAndProcType)
		{
		case OS_VER_AND_PROC_TYPE_WINDOWS_XP_X86:
			{
				_tcscat_s(tchPath, _countof(tchPath), _T("C:\\Documents and Settings\\Administrator\\桌面\\test\\test.exe"));
				break;
			}
		case OS_VER_AND_PROC_TYPE_WINDOWS_7_X86:
			{
				_tcscat_s(tchPath, _countof(tchPath), _T("C:\\Users\\Test1\\Desktop\\test\\test.exe"));
				break;
			}
		case OS_VER_AND_PROC_TYPE_WINDOWS_7_X64:
			{
				if (PathFileExists(_T("G:\\GitHub\\Test\\Debug\\test.exe")))
					_tcscat_s(tchPath, _countof(tchPath), _T("G:\\GitHub\\Test\\Debug\\test.exe"));
				else
					_tcscat_s(tchPath, _countof(tchPath), _T("C:\\Users\\Administrator\\Desktop\\test\\test.exe"));

				break;
			}
		default:
			{
				printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "OsVerAndProcType error. %d", OsVerAndProcType);
				__leave;
			}
		}

		if (!Service.Install(
			_T("test"),
			_T("testDisplayName"),
			_T("testDescription"),
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			tchPath,
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
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		if (!PrintfEx.Unload())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Unload failed");
	}

	return 0;
}

