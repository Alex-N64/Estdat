#include "Estdat.h"
#include "menu.h"

//MessageBox(handler, L"", L"", MB_OK);

BOOL CALLBACK iniciarSeccion(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case ID_iniciarSesion: {
			EndDialog(handler, 0);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_Menu), NULL, (DLGPROC)menu);
		}


		default:
			return 0;
		}
	}

	case WM_CLOSE: {

		if (MessageBox(handler, L"¿Desea salir de la aplicación? Se guardarán los cambios realizados.", L"My application", MB_OKCANCEL) == IDOK)
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


int WINAPI WinMain(HINSTANCE instancia, HINSTANCE legado, LPSTR comando, int modo) {
	DialogBox(instancia, MAKEINTRESOURCE(IDD_INICIO), NULL, (DLGPROC)iniciarSeccion);
	return 0;
}