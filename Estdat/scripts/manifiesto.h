#pragma once
#include "pasajeros.h"



BOOL CALLBACK VERPORNUMERODEASIENTO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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

BOOL CALLBACK VERPORNOMBRE(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_LIST_PASAJERO:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_GETCURSEL, NULL, NULL);
				Pasajeros* aMostrar = pasajerosBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_NOMBRE_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)aMostrar->nombresPasajeros);
				SendDlgItemMessage(handler, IDC_APELLIDOS_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)aMostrar->apellidosPasajeros);

				//SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)aMostrar->sexoPasajeros);

				if (aMostrar->sexoPasajeros == 0)
				{
					SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)L"Hombre");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)L"Mujer");
				}



				SendDlgItemMessage(handler, IDC_NACIONALIDAD_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)aMostrar->nacionalidadPasajeros);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_SALIDA, WM_SETTEXT, NULL, (LPARAM)aMostrar->Lote);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_LLEGADA, WM_SETTEXT, NULL, (LPARAM)aMostrar->ApellidoPaterno);


				return 0;
			}
			return 0;
		}
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

BOOL CALLBACK VERPORAPELLIDO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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