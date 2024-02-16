#pragma once
#include "Estdat.h"

BOOL CALLBACK menu(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{


		default:
			return 0;
		}
	}

	case WM_CLOSE: {

		if (MessageBox(handler, L"�Desea salir de la aplicaci�n?. Los cambios ser�n guardados.", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(handler);
		}
		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}

	default:
		return 0;
	}
	return false;
}