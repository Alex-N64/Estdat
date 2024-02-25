#pragma once
#include "Estdat.h"
#include "misc.h"
#include "vuelos.h"


BOOL CALLBACK menu(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		//Vuelos
		case ID_VUELOS_REGISTRARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_REGISTRO), handler, (DLGPROC)REGISTRARVUELO);
			return 0;
		}

		case ID_VUELOS_ELIMINARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_ELIMINAR), handler, (DLGPROC)ELIMINARVUELO);
			return 0;
		}

		case ID_VUELOS_MODIFICARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_MODIFICAR), handler, (DLGPROC)MODIFICARVUELO);
			return 0;
		}

		//Pasajero
		case ID_PASAJEROS_REGISTRARPASAJEROS: {

			return 0;
		}
		case ID_PASAJEROS_ELIMINARPASAJEROS: {

			return 0;
		}
		case ID_PASAJEROS_MODIFICARPASAJEROS: {

			return 0;
		}
		//Boletos

		case ID_BOLETOS_COMPRARBOLETOS: {

			return 0;
		}
		case ID_BOLETOS_CANCELARBOLETOS: {

			return 0;
		}
		case ID_BOLETOS_MODIFICARBOLETOS: {

			return 0;
		}
		//Mas opciones
		case ID_MISC_PASEDEABORDAR: {

			return 0;
		}
		case ID_ADMIN_REGISTRARUSUARIOS: {

			return 0;
		}
		case IDM_ABOUT: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_ABOUTBOX), handler, (DLGPROC)ABOUTBOX);
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

