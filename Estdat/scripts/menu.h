#pragma once
#include "Estdat.h"
#include "misc.h"
#include "vuelos.h"
#include "pasajeros.h"
#include "boletos.h"
#include "manifiesto.h"

wchar_t direccion[255];

BOOL CALLBACK menu(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG: {
		
		/*
		OPENFILENAME openfilename;
		wchar_t Cargar[255];
		ZeroMemory(&openfilename, sizeof(openfilename));
		openfilename.lStructSize = sizeof(openfilename);
		openfilename.hwndOwner = handler;
		openfilename.lpstrFile = Cargar;
		openfilename.lpstrFilter = L"Cargar lista y envios en un archivo .bin\0 * .bin";
		openfilename.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		openfilename.lpstrFile[0] = NULL;
		openfilename.nMaxFile = sizeof(direccion);
		openfilename.nFilterIndex = 0;
		*/

		//if (GetOpenFileName(&openfilename) == TRUE) {
			vuelosLimpiar();
			//Vacuna_Limpiar();
			ifstream Leer;
			Leer.open(rutaListas, ios::in | ios::binary);
			if (Leer.is_open()) {
				while (true) {
					Vuelos* LeerArchivo = new Vuelos;
					Leer.read(reinterpret_cast<char*>(LeerArchivo), sizeof(Vuelos));
					if (Leer.eof()) {
						delete LeerArchivo;
						break;
					}
					vuelosAgregar(LeerArchivo);

					/*
					Vacuna* LeerArchivo2 = new Vacuna;
					Leer.read(reinterpret_cast<char*>(LeerArchivo2), sizeof(Vacuna));
					if (Leer.eof()) {
						delete LeerArchivo2;
						break;
					}
					Vacuna_Agregar(LeerArchivo2);
					*/
				}
			}
			Leer.close();
			//CarnetPersona_ActualizarLista(handler);
			//Vacuna_ActualizarLista(handler);
		//}
		
		
		vuelosActualizarLista(handler);
		pasajerosActualizarLista(handler);

		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		//Vuelos
		case ID_VUELOS_REGISTRARVUELO: {
			vuelosActual = NULL;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_REGISTRO), handler, (DLGPROC)REGISTRARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

		case ID_VUELOS_ELIMINARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_ELIMINAR), handler, (DLGPROC)ELIMINARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

		case ID_VUELOS_MODIFICARVUELO: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_MODIFICAR), handler, (DLGPROC)MODIFICARVUELO);
			vuelosActualizarLista(handler);
			return 0;
		}

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


		//Pasajero
		case ID_PASAJEROS_REGISTRARPASAJEROS: {
			pasajerosActual = NULL;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_REGISTRO), handler, (DLGPROC)REGISTRARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}
		case ID_PASAJEROS_ELIMINARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_ELIMINAR), handler, (DLGPROC)ELIMINARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}
		case ID_PASAJEROS_MODIFICARPASAJEROS: {
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_MODIFICAR), handler, (DLGPROC)MODIFICARPASAJEROS);
			pasajerosActualizarLista(handler);
			return 0;
		}

		case ID_LISTAS_PASAJEROS:
		{
			pasajerosActualizarLista(handler);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_LISTA), handler, (DLGPROC)LISTAPASAJEROS);
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

		case ID_LISTAS_BOLETOS:
		{

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

				/*
				OPENFILENAME openfilename;
				wchar_t Guardar[255];
				ZeroMemory(&openfilename, sizeof(openfilename));
				openfilename.lStructSize = sizeof(openfilename);
				openfilename.hwndOwner = handler;
				openfilename.lpstrFile = Guardar;
				openfilename.lpstrFilter = L"Guardar lista y envios en un archivo .bin\0 * .bin";
				openfilename.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
				openfilename.lpstrFile[0] = NULL;
				openfilename.nMaxFile = sizeof(direccion);
				openfilename.nFilterIndex = 0;
				*/

				//if (GetSaveFileName(&openfilename) == TRUE) {
					ofstream escribir;
					escribir.open(rutaListas, ios::out | ios::binary | ios::trunc);
					if (escribir.is_open()) {

						Vuelos* vuelosAux = vuelosInicio;
						while (vuelosAux->vuelosSiguiente != vuelosInicio) {
							escribir.write(reinterpret_cast<char*>(vuelosAux), sizeof(Vuelos));
							vuelosAux = vuelosAux->vuelosSiguiente;
						}

						/*
						Vacuna* Vacuna_aux = Vacuna_Inicio;
						while (Vacuna_aux->Vacuna_siguiente != Vacuna_Inicio) {
							escribir.write(reinterpret_cast<char*>(Vacuna_aux), sizeof(Vacuna));
							Vacuna_aux = Vacuna_aux->Vacuna_siguiente;
						}
						*/

						escribir.write(reinterpret_cast<char*>(vuelosAux), sizeof(Vuelos));
						//escribir.write(reinterpret_cast<char*>(Vacuna_aux), sizeof(Vacuna));
						escribir.close();
					}

				//}

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

