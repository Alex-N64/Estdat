#pragma once

#include <shellapi.h>
#include"menu.h"
#include"Estdat.h"

void usuariosReparar(HWND handler) {
	if (MessageBox(handler, L"Desea reparar los usuarios?", L"Reparar", MB_OKCANCEL) == IDOK)
	{
		ofstream file;
		file.open(rutaUsuario + "admin.txt");
		file << "admin" << endl << "admin" << endl;
		file.close();
		MessageBox(handler, L"El usuario admin a sido recreado", L"Reparar", MB_OK);
	}

	else
	{
		MessageBox(handler, L"false", L"false", MB_OK);
	}

}

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

BOOL CALLBACK REGISTRARUSUARIOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{

		case IDCANCEL: {
			EndDialog(handler, 0);
			return 0;
		}

		case IDOK: {
			wchar_t usuarioWchart[256], correoWchart[256], contrasenaWchart[256],nombreWchart[256], generoWchart[256];

			SendMessage(GetDlgItem(handler, IDC_USUARIO), WM_GETTEXT, sizeof(usuarioWchart) / sizeof(usuarioWchart[0]), (LPARAM)usuarioWchart);
			SendMessage(GetDlgItem(handler, IDC_CORREO), WM_GETTEXT, sizeof(correoWchart) / sizeof(correoWchart[0]), (LPARAM)correoWchart);
			SendMessage(GetDlgItem(handler, IDC_CONTRASENA), WM_GETTEXT, sizeof(contrasenaWchart) / sizeof(contrasenaWchart[0]), (LPARAM)contrasenaWchart);
			SendMessage(GetDlgItem(handler, IDC_NOMBRE), WM_GETTEXT, sizeof(nombreWchart) / sizeof(nombreWchart[0]), (LPARAM)nombreWchart);
			SendMessage(GetDlgItem(handler, IDC_GENERO), WM_GETTEXT, sizeof(generoWchart) / sizeof(generoWchart[0]), (LPARAM)generoWchart);

			wstring usuarioWstring(usuarioWchart);
			wstring correoWstring(correoWchart);
			wstring contrasenaWstring(contrasenaWchart);
			wstring nombreWstring(nombreWchart);
			wstring generoWstring(generoWchart);

			string usuario(usuarioWstring.begin(), usuarioWstring.end());
			string correo(correoWstring.begin(), correoWstring.end());
			string contrasena(contrasenaWstring.begin(), contrasenaWstring.end());
			string nombre(nombreWstring.begin(), nombreWstring.end());
			string genero(generoWstring.begin(), generoWstring.end());

			ofstream file;
			file.open(rutaUsuario + usuario + ".txt");
			file << usuario << endl;
			file << correo << endl;
			file << contrasena << endl;
			file << nombre << endl;
			file << genero << endl;
			file.close();

			MessageBox(handler, usuarioWchart, L"Usuario registrado correctamente", MB_ICONINFORMATION);
			
			return 0;
		}

		default:
			return 0;
		}
	}

	case WM_CLOSE: {
		EndDialog(handler, 0);
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

BOOL CALLBACK PASEABORDAR(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{

		case IDCANCEL: {
			EndDialog(handler, 0);
			return 0;
		}

		default:
			return 0;
		}
	}

	case WM_CLOSE: {
		EndDialog(handler, 0);
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
