#include <locale>
#include <codecvt>

#include "Estdat.h"
#include "menu.h"
#include "misc.h"


//MessageBox(handler, L"", L"", MB_OK);


BOOL CALLBACK iniciarSeccion(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	string usuarioRead, contrasenaRead;
	wchar_t usuarioWchart[256], contrasenaWchart[256];
	BOOL usuarioCheck = IsDlgButtonChecked(handler, IDC_CHECK_RECORDAR);
	HWND pegarUsuario = GetDlgItem(handler, IDC_USUARIO);
	HWND pegarConstrasenas = GetDlgItem(handler, IDC_CONTRASENA);
	HWND casillaRecordar = GetDlgItem(handler, IDC_CHECK_RECORDAR);

	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		ifstream read(rutaRecordarUsuario);
		getline(read, usuarioRead);
		getline(read, contrasenaRead);

		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring usuarioWstring = converter.from_bytes(usuarioRead);
		std::wstring contrasenaWstring = converter.from_bytes(contrasenaRead);
		
		if (usuarioRead == "" && contrasenaRead == "") 
		{
			
			return 0;
		}

		else  		
		{
			SetWindowText(pegarUsuario, usuarioWstring.c_str());
			SetWindowText(pegarConstrasenas, contrasenaWstring.c_str());
			
			SendMessage(casillaRecordar, BM_SETCHECK, BST_CHECKED, 0);
			
			return 0;
		}

		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		
		case ID_iniciarSesion: {
			
				SendMessage(GetDlgItem(handler, IDC_USUARIO), WM_GETTEXT, sizeof(usuarioWchart) / sizeof(usuarioWchart[0]), (LPARAM)usuarioWchart);
				SendMessage(GetDlgItem(handler, IDC_CONTRASENA), WM_GETTEXT, sizeof(contrasenaWchart) / sizeof(contrasenaWchart[0]), (LPARAM)contrasenaWchart);

				wstring usuarioWstring(usuarioWchart);
				wstring contrasenaWstring(contrasenaWchart);

				string usuario(usuarioWstring.begin(), usuarioWstring.end());
				string contrasena(contrasenaWstring.begin(), contrasenaWstring.end());

				ifstream read(rutaUsuario + usuario + ".txt");
				getline(read, usuarioRead);
				getline(read, contrasenaRead);

				if (usuarioRead == usuario && contrasenaRead == contrasena) {
					if (usuarioRead == "" && contrasenaRead == "") {
						MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONERROR);
						return 0;
					}

					else if (usuarioRead == "admin" && contrasenaRead == "admin") {
						adminStatus = true;
						EndDialog(handler, 0);
						MessageBox(handler, L"Permisos de administrador activados", L"Admin", MB_ICONINFORMATION);
						//DialogBox(NULL, MAKEINTRESOURCE(IDD_Menu), NULL, (DLGPROC)menu);
						//return 0;
					}

					else {
						adminStatus = false;
						EndDialog(handler, 0);
						//DialogBox(NULL, MAKEINTRESOURCE(IDD_Menu), NULL, (DLGPROC)menu);
						//return 0;
					}

					if (usuarioCheck)
					{
						ofstream file;
						file.open(rutaRecordarUsuario);
						file << usuario << endl;
						file << contrasena << endl;
						file.close();
					}
					else
					{
						ofstream file;
						file.open(rutaRecordarUsuario);
						file << "" << endl;
						file << "" << endl;
						file.close();
					}
					
					DialogBox(NULL, MAKEINTRESOURCE(IDD_Menu), NULL, (DLGPROC)menu);
					return 0;

				}

				else {
					MessageBox(handler, L"Usuario o contraseña incorrectos", L"Error", MB_ICONERROR);
					return 0;
				}
			return 0;
			
		}

		case ID_REPARAR_USUARIO: {
			usuariosReparar(handler);
			return 0;
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