#pragma once

#include"menu.h"
#include <shellapi.h>



BOOL CALLBACK ABOUTBOX(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK: {
			EndDialog(handler, 0);
			return 0;
		}
		case REPOSITORIO: {
			ShellExecuteA(NULL, "open", "https://github.com/Alex-N64/Estdat.git", NULL, NULL, SW_SHOW);
		}

		default:
			return 0;
		}
	}

	case WM_CLOSE: {
		EndDialog(handler,0);
		return 0;
	}


	case WM_DESTROY: {
		
		return 0;
	}

	default:
		return 0;
	}
	return false;
}
