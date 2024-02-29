#pragma once
#include "Estdat.h"
#include "misc.h"
#include "vuelos.h"
#include "pasajeros.h"
#include "boletos.h"



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
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_REGISTRO), handler, (DLGPROC)REGISTRARPASAJEROS);
			return 0;
		}
		case ID_PASAJEROS_ELIMINARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_ELIMINAR), handler, (DLGPROC)ELIMINARPASAJEROS);
			return 0;
		}
		case ID_PASAJEROS_MODIFICARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_MODIFICAR), handler, (DLGPROC)MODIFICARPASAJEROS);
			return 0;
		}
		//Boletos

		case ID_BOLETOS_COMPRARBOLETOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_REGISTRO), handler, (DLGPROC)COMPRARBOLETOS);
			return 0;
		}
		case ID_BOLETOS_CANCELARBOLETOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_ELIMINAR), handler, (DLGPROC)CANCELARBOLETOS);
			return 0;
		}
		case ID_BOLETOS_MODIFICARBOLETOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_MODIFICAR), handler, (DLGPROC)MODIFICARBOLETOS);
			return 0;
		}
		//Mas opciones
		case ID_MISC_PASEDEABORDAR: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASE_ABORDAR), handler, (DLGPROC)PASEABORDAR);
			return 0;
		}
		case ID_ADMIN_REGISTRARUSUARIOS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_USUARIO), handler, (DLGPROC)REGISTRARUSUARIOS);
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

