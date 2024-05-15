#pragma once
#include "Estdat.h"

struct Pasajeros
{
	wchar_t nombresPasajeros[200];
	wchar_t apellidosPasajeros[200];
	wchar_t sexoPasajeros[200];
	wchar_t nacionalidadPasajeros[200];
//	wchar_t fechaNacimientoPasajeros[200];

	Pasajeros* pasajerosSiguiente;
	Pasajeros* pasajerosAnterior;
};

Pasajeros* pasajerosInicio = NULL;
Pasajeros* pasajerosActual = NULL;



void swap(Pasajeros* a, Pasajeros* b) {
	Pasajeros temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Pasajeros* arr, int low, int high) {
	Pasajeros pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (wcscmp(arr[j].nombresPasajeros, pivot.nombresPasajeros) < 0) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Pasajeros* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void heapify(Pasajeros* arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && wcscmp(arr[l].nombresPasajeros, arr[largest].nombresPasajeros) > 0)
		largest = l;

	if (r < n && wcscmp(arr[r].nombresPasajeros, arr[largest].nombresPasajeros) > 0)
		largest = r;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void pasajerosAgregar(Pasajeros* pasajerosNuevo) {
	if (pasajerosInicio == NULL) {
		pasajerosInicio = pasajerosNuevo;
		pasajerosNuevo->pasajerosSiguiente = pasajerosNuevo;
		pasajerosNuevo->pasajerosAnterior = pasajerosNuevo;
	}
	else {
		pasajerosInicio->pasajerosAnterior->pasajerosSiguiente = pasajerosNuevo;
		pasajerosNuevo->pasajerosAnterior = pasajerosInicio->pasajerosAnterior;
		pasajerosNuevo->pasajerosSiguiente = pasajerosInicio;
		pasajerosInicio->pasajerosAnterior = pasajerosNuevo;
	}
}

void pasajerosEliminar(Pasajeros* pasajerosAEliminar) {

	Pasajeros* pasajerosAnterior = pasajerosAEliminar->pasajerosAnterior;
	Pasajeros* pasajerosSiguiente = pasajerosAEliminar->pasajerosSiguiente;
	if (pasajerosAnterior == pasajerosSiguiente && pasajerosAEliminar == pasajerosAnterior) {
		delete pasajerosAEliminar;
		pasajerosInicio = NULL;
		return;
	}
	if (pasajerosAnterior->pasajerosSiguiente == pasajerosInicio) {
		pasajerosInicio = pasajerosInicio->pasajerosSiguiente;
	}
	pasajerosAnterior->pasajerosSiguiente = pasajerosSiguiente;
	pasajerosSiguiente->pasajerosAnterior = pasajerosAnterior;
	delete pasajerosAEliminar;
}

void pasajerosActualizarLista(HWND handler) {
	SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_RESETCONTENT, NULL, NULL);
	if (pasajerosInicio == NULL) return;

	Pasajeros* pasajerosAux = pasajerosInicio;
	int totalPasajeros = 0;

	while (pasajerosAux->pasajerosSiguiente != pasajerosInicio) {
		totalPasajeros++;
		pasajerosAux = pasajerosAux->pasajerosSiguiente;
	}

	Pasajeros* pasajerosArray = new Pasajeros[totalPasajeros + 1];

	pasajerosAux = pasajerosInicio;
	for (int i = 0; i <= totalPasajeros; i++) {
		pasajerosArray[i] = *pasajerosAux;
		pasajerosAux = pasajerosAux->pasajerosSiguiente;
	}

	quickSort(pasajerosArray, 0, totalPasajeros);

	for (int i = 0; i <= totalPasajeros; i++) {
		
		SendDlgItemMessage(handler, IDC_NOMBRE_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].nombresPasajeros);
		SendDlgItemMessage(handler, IDC_APELLIDOS_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].apellidosPasajeros);
		//SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].sexoPasajeros);
		SendDlgItemMessage(handler, IDC_NACIONALIDAD_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].nacionalidadPasajeros);
		//SendDlgItemMessage(handler, IDC_FechaNacimientoPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].FechaNacimientoPaciente);
		//SendDlgItemMessage(handler, IDC_EdadPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].EdadPaciente);

	}

	delete[] pasajerosArray;

	while (pasajerosAux->pasajerosSiguiente != pasajerosInicio) {
		SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_ADDSTRING, NULL, (LPARAM)pasajerosAux->nombresPasajeros);
		pasajerosAux = pasajerosAux->pasajerosSiguiente;
	}
		SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_ADDSTRING, NULL, (LPARAM)pasajerosAux->nombresPasajeros);
		
}

void pasajerosLimpiar() {

	if (pasajerosInicio != NULL) {
		Pasajeros* pasajerosAux = pasajerosInicio;
		while (pasajerosAux->pasajerosSiguiente != pasajerosInicio) {
			pasajerosAux = pasajerosAux->pasajerosSiguiente;
			delete pasajerosAux->pasajerosAnterior;
		}
		delete pasajerosAux;
	}
	pasajerosInicio = NULL;
	pasajerosActual = NULL;

}

Pasajeros* pasajerosBuscar(int i) {
	Pasajeros* pasajerosAux = pasajerosInicio;
	for (int j = 0; j < i; j++) {
		pasajerosAux = pasajerosAux->pasajerosSiguiente;
	}
	return pasajerosAux;
}



BOOL CALLBACK REGISTRARPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{

	case WM_INITDIALOG:
	{
		
		pasajerosActualizarLista(handler);

		if (pasajerosActual != NULL) {
			SendDlgItemMessage(handler, IDC_NOMBRE_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)pasajerosActual->nombresPasajeros);
			SendDlgItemMessage(handler, IDC_APELLIDOS_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)pasajerosActual->apellidosPasajeros);
			//SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->Dosis);
			SendDlgItemMessage(handler, IDC_NACIONALIDAD_PASAJEROS, WM_SETTEXT, NULL, (LPARAM)pasajerosActual->nacionalidadPasajeros);
			//SendDlgItemMessage(handler, IDC_Lote, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->Lote);
			

		}



		return 0;
		
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			wchar_t nombreVerificacion[256], apellidosVerificacion[256], nacionalidadVerificacion[256];

			SendMessage(GetDlgItem(handler, IDC_NOMBRE_PASAJEROS), WM_GETTEXT, sizeof(nombreVerificacion) / sizeof(nombreVerificacion[0]), (LPARAM)nombreVerificacion);
			SendMessage(GetDlgItem(handler, IDC_APELLIDOS_PASAJEROS), WM_GETTEXT, sizeof(apellidosVerificacion) / sizeof(apellidosVerificacion[0]), (LPARAM)apellidosVerificacion);
			SendMessage(GetDlgItem(handler, IDC_NACIONALIDAD_PASAJEROS), WM_GETTEXT, sizeof(nacionalidadVerificacion) / sizeof(nacionalidadVerificacion[0]), (LPARAM)nacionalidadVerificacion);

			wstring nombresWstring(nombreVerificacion);
			wstring apellidosWstring(apellidosVerificacion);
			wstring nacionalidadWstring(nacionalidadVerificacion);

			string pasajeroNombre(nombresWstring.begin(), nombresWstring.end());
			string pasajeroApellidos(apellidosWstring.begin(), apellidosWstring.end());
			string pasajeroNacionalidad(nacionalidadWstring.begin(), nacionalidadWstring.end());

			if (pasajeroNombre == "" || pasajeroApellidos == "" || pasajeroNacionalidad == "") {
				MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONERROR);
				return 0;
			}

			else
			{
				Pasajeros* pasajerosNuevo = NULL;
				if (pasajerosActual == NULL) {
					pasajerosNuevo = new Pasajeros;

					SendMessage(GetDlgItem(handler, IDC_NOMBRE_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->nombresPasajeros) / sizeof(pasajerosNuevo->nombresPasajeros[0]), (LPARAM)pasajerosNuevo->nombresPasajeros);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, IDC_SEXO_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->sexoPasajeros) / sizeof(pasajerosNuevo->sexoPasajeros[0]), (LPARAM)pasajerosNuevo->sexoPasajeros);
					SendMessage(GetDlgItem(handler, IDC_NACIONALIDAD_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->nacionalidadPasajeros) / sizeof(pasajerosNuevo->nacionalidadPasajeros[0]), (LPARAM)pasajerosNuevo->nacionalidadPasajeros);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
					
					pasajerosAgregar(pasajerosNuevo);
					pasajerosActualizarLista(handler);

					Pasajeros* b = pasajerosBuscar(0);
					int a = 0;
					a++;

					EndDialog(handler, 0);
				}

				else {
					pasajerosNuevo = pasajerosActual;
					SendMessage(GetDlgItem(handler, IDC_NOMBRE_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->nombresPasajeros) / sizeof(pasajerosNuevo->nombresPasajeros[0]), (LPARAM)pasajerosNuevo->nombresPasajeros);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, IDC_SEXO_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->sexoPasajeros) / sizeof(pasajerosNuevo->sexoPasajeros[0]), (LPARAM)pasajerosNuevo->sexoPasajeros);
					SendMessage(GetDlgItem(handler, IDC_NACIONALIDAD_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->nacionalidadPasajeros) / sizeof(pasajerosNuevo->nacionalidadPasajeros[0]), (LPARAM)pasajerosNuevo->nacionalidadPasajeros);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->HoraInicio) / sizeof(vuelosNuevo->HoraInicio[0]), (LPARAM)vuelosNuevo->HoraInicio);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->HoraFinal) / sizeof(vuelosNuevo->HoraFinal[0]), (LPARAM)vuelosNuevo->HoraFinal);
					
					EndDialog(handler, 0);
				}
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

BOOL CALLBACK ELIMINARPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasajerosActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_GETCURSEL, NULL, NULL);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay vuelos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			if (MessageBox(handler, L"Esta seguro de querer eliminar el vuelo seleccionado?", L"Eliminando vuelo", MB_OKCANCEL) == IDOK)
			{
				pasajerosActual = pasajerosBuscar(seleccionado);
				pasajerosEliminar(pasajerosActual);
				pasajerosActualizarLista(handler);
				return 0;
			}

			else
			{
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

BOOL CALLBACK MODIFICARPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasajerosActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
				int seleccionado = SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_GETCURSEL, NULL, NULL);
				Pasajeros* aMostrar = pasajerosBuscar(seleccionado);

				if (seleccionado == -1) {
					MessageBox(handler, L"No hay pasajeros registrados", L"Error", MB_OK | MB_ICONERROR);
					return 0;
				}

				pasajerosActual = pasajerosBuscar(seleccionado);
				EndDialog(handler, 0);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_PASAJEROS_REGISTRO), handler, (DLGPROC)REGISTRARPASAJEROS);
				pasajerosActualizarLista(handler);
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

BOOL CALLBACK LISTAPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasajerosActualizarLista(handler);
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



