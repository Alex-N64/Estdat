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

void exportarVuelo(HWND handler)
{
	wchar_t vueloOrigenWchart[256], vueloDestinoWchart[256], fechaSalidaWchart[256], 
			fechaLlegadaWchart[256], horaSalidaWchart[256], horaLlegadaWchart[256], tipoAvionWchart[256];

	SendMessage(GetDlgItem(handler, IDC_EDIT_VUELOS_ORIGEN), WM_GETTEXT, sizeof(vueloOrigenWchart) / sizeof(vueloOrigenWchart[0]), (LPARAM)vueloOrigenWchart);
	SendMessage(GetDlgItem(handler, IDC_EDIT_VUELOS_DESTINO), WM_GETTEXT, sizeof(vueloDestinoWchart) / sizeof(vueloDestinoWchart[0]), (LPARAM)vueloDestinoWchart);
	SendMessage(GetDlgItem(handler, IDC_FECHA_SALIDA), WM_GETTEXT, sizeof(fechaSalidaWchart) / sizeof(fechaSalidaWchart[0]), (LPARAM)fechaSalidaWchart);
	SendMessage(GetDlgItem(handler, IDC_FECHA_LLEGADA), WM_GETTEXT, sizeof(fechaLlegadaWchart) / sizeof(fechaLlegadaWchart[0]), (LPARAM)fechaLlegadaWchart);
	SendMessage(GetDlgItem(handler, IDC_EDIT_HORA_SALIDA), WM_GETTEXT, sizeof(horaSalidaWchart) / sizeof(horaSalidaWchart[0]), (LPARAM)horaSalidaWchart);
	SendMessage(GetDlgItem(handler, IDC_EDIT_HORA_LLEGADA), WM_GETTEXT, sizeof(horaLlegadaWchart) / sizeof(horaLlegadaWchart[0]), (LPARAM)horaLlegadaWchart);
	SendMessage(GetDlgItem(handler, IDC_tipoAvion_EditBox), WM_GETTEXT, sizeof(tipoAvionWchart) / sizeof(tipoAvionWchart[0]), (LPARAM)tipoAvionWchart);

	wstring vueloOrigenWstring(vueloOrigenWchart);
	wstring vueloDestinoWstring(vueloDestinoWchart);
	wstring fechaSalidaWstring(fechaSalidaWchart);
	wstring fechaLlegadaWstring(fechaLlegadaWchart);
	wstring horaSalidaWstring(horaSalidaWchart);
	wstring horaLlegadaWstring(horaLlegadaWchart);
	wstring tipoAvionWstring(tipoAvionWchart);


	string vueloOrigen(vueloOrigenWstring.begin(), vueloOrigenWstring.end());
	string vueloDestino(vueloDestinoWstring.begin(), vueloDestinoWstring.end());
	string fechaSalida(fechaSalidaWstring.begin(), fechaSalidaWstring.end());
	string fechaLlegada(fechaLlegadaWstring.begin(), fechaLlegadaWstring.end());
	string horaSalida(horaSalidaWstring.begin(), horaSalidaWstring.end());
	string horaLlegada(horaLlegadaWstring.begin(), horaLlegadaWstring.end());
	string tipoAvion(tipoAvionWstring.begin(), tipoAvionWstring.end());

	if (vueloOrigen == ""|| vueloDestino == ""|| tipoAvion == "")
	{
		MessageBox(handler, L"No has seleccionado un vuelo", L"Error", MB_ICONERROR | MB_OK);

	}

	else
	{
		ofstream file;
		file.open(rutaReporteVuelos + vueloOrigen +" a " + vueloDestino + ".txt");
		file << vueloOrigen << endl;
		file << vueloDestino << endl;
		file << fechaSalida << endl;
		file << fechaLlegada << endl;
		file << horaSalida << endl;
		file << horaLlegada << endl;
		file << tipoAvion << endl;
		file.close();

		MessageBox(handler, L"El vuelo ha sido exportado con exitom, se ha gurdado en la siguiente ruta: Estdat/exports/ReporteVuelo", L"Exportar", MB_ICONINFORMATION);
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
