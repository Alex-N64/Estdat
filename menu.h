#pragma once
#include "Estdat.h"
#include "misc.h"
#include "vuelos.h"
#include "pasajeros.h"
#include "boletos.h"
#include "manifiesto.h"



BOOL CALLBACK menu(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG: {
		Vuelos_ActualizarLista(handler);

		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		//Vuelos
		case ID_VUELOS_REGISTRARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_REGISTRO), handler, (DLGPROC)REGISTRARVUELO);
			Vuelos_ActualizarLista(handler);
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
		//Manifiesto
		case ID_VERMANIFIESTO_VERPORNUMERODEASIENTO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_NUMERO), handler, (DLGPROC)VERPORNUMERODEASIENTO);
			return 0;
		}
		case ID_VERMANIFIESTO_VERPORNOMBRE: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_NOMBRE), handler, (DLGPROC)VERPORNOMBRE);
			return 0;
		}
		case ID_VERMANIFIESTO_VERPORAPELLIDO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_MANIFIESTO_APELLIDO), handler, (DLGPROC)VERPORAPELLIDO);
			return 0;
		}
		//Lista de vuelos
		case IDC_vuelos:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_vuelos, LB_GETCURSEL, NULL, NULL);
				Vuelos* aMostrar = vuelosBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_EDIT_VUELOS_ORIGEN, WM_SETTEXT, NULL, (LPARAM)aMostrar->vueloOrigen);
				SendDlgItemMessage(handler, IDC_EDIT_VUELOS_DESTINO, WM_SETTEXT, NULL, (LPARAM)aMostrar->vueloDestino);
				//SendDlgItemMessage(handler, IDC_Dosis, WM_SETTEXT, NULL, (LPARAM)aMostrar->Dosis);
				//SendDlgItemMessage(handler, IDC_CentroVacuna, WM_SETTEXT, NULL, (LPARAM)aMostrar->CentroVacuna);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_SALIDA, WM_SETTEXT, NULL, (LPARAM)aMostrar->Lote);
				//SendDlgItemMessage(handler, IDC_EDIT_HORA_LLEGADA, WM_SETTEXT, NULL, (LPARAM)aMostrar->ApellidoPaterno);
				
				//SendDlgItemMessage(handler, IDC_ApellidoMaterno, WM_SETTEXT, NULL, (LPARAM)aMostrar->ApellidoMaterno);
				//SendDlgItemMessage(handler, IDC_Nombres, WM_SETTEXT, NULL, (LPARAM)aMostrar->Nombres);
				//SendDlgItemMessage(handler, IDC_RFC, WM_SETTEXT, NULL, (LPARAM)aMostrar->RFC);
				//SendDlgItemMessage(handler, IDC_Calle, WM_SETTEXT, NULL, (LPARAM)aMostrar->Calle);
				//SendDlgItemMessage(handler, IDC_Colonia, WM_SETTEXT, NULL, (LPARAM)aMostrar->Colonia);
				
				return 0;
			}
			return 0;
		}

		//Mas opciones
		case ID_MISC_PASEDEABORDAR: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASE_ABORDAR), handler, (DLGPROC)PASEABORDAR);
			return 0;
		}
		case ID_ADMIN_REGISTRARUSUARIOS: {
			if (!adminStatus) {
				MessageBox(handler, L"Se necesitan permisos de administrador para poder agregar nuevos usuarios", L"Admin", MB_ICONEXCLAMATION);
				return 0;
			}

			else {
				DialogBox(NULL, MAKEINTRESOURCE(IDD_USUARIO), handler, (DLGPROC)REGISTRARUSUARIOS);
				return 0;
			}
		}

		case ID_ADMIN_REINICIARIDSDEVUELOS: {
			if (!adminStatus) {
				MessageBox(handler, L"Se necesitan permisos de administrador para poder reiniciar los IDs de los vuelos", L"Admin", MB_ICONEXCLAMATION);
				return 0;
			}

			else {
				if (MessageBox(handler, L"Desea reiniciar los IDs de los vuelos?", L"Reparar", MB_OKCANCEL) == IDOK)
				{
					ofstream file;
					file.open(rutaDatos + "idVuelos.bin");
					file << "0" << endl;
					file.close();
					MessageBox(handler, L"Los IDs de los vuelos fueron reiniciados", L"Reparar", MB_OK);
					return 0;
				}

				else
				{
					return 0;
				}
				return 0;
			}

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

		if (MessageBox(handler, L"¿Desea salir de la aplicación? Los cambios realizados se guardarán.", L"Cerrando programa", MB_OKCANCEL) == IDOK)
		{
			if (!saveOnExit) {
				//MessageBox(handler, L"No", L"No", MB_OK);
				DestroyWindow(handler);
				return 0;

			}

			else {
				//MessageBox(handler, L"Guardar", L"Guardar", MB_OK);
				DestroyWindow(handler);
				return 0;
			}

			//DestroyWindow(handler);
			//return 0;
		}
		return 0;
	}

	case WM_DESTROY: {
		//PostQuitMessage(0);
		return 0;
	}

	default:
		return 0;
	}
	return false;
}

