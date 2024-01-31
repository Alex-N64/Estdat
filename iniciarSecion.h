#pragma once

BOOL CALLBACK iniciarSeccion(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case iniciarSesion: {
			EndDialog(handler, 0);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MENU), NULL, (DLGPROC)iniciarSeccion);
			return 0;
		}

		case crearUsuario: {

			return 0;
		}

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
