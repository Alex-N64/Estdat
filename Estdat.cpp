#include "Estdat.h"

//MessageBox(handler, L"", L"", MB_OK);

//BOOL CALLBACK iniciarSeccion(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam);


BOOL CALLBACK iniciarSeccion(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{


		default:
			break;
		}
	}

	case WM_CLOSE: {

		if (MessageBox(handler, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
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
		break;
	}
	return false;
}


int WINAPI WinMain(HINSTANCE instancia, HINSTANCE legado, LPSTR comando, int modo) {
	DialogBox(instancia, MAKEINTRESOURCE(IDD_INICIO), NULL, (DLGPROC)iniciarSeccion);
	return 0;
}