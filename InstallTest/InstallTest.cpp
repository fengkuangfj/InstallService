// InstallTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;
	CService		Service;


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

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续\n");
		_getch();

		Service.Install(
			_T("test"),
			SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			_T("G:\\GitHub\\Test\\Debug\\test.exe"),
			/*_T("C:\\Users\\Administrator\\Desktop\\test\\test.exe"),*/
			NULL,
			NULL
			);
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

