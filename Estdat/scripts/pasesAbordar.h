#pragma once
#include"Estdat.h"

struct Pases
{
	wchar_t nombrePases[200];
	wchar_t apellidoPases[200];
	wchar_t idPases[200];
	wchar_t avionPases[200];
	//wchar_t asientoBoleto
	int tipoPases;
	int clasePases;
	int pagoPases;

	Pases* pasesSiguiente;
	Pases* pasesAnterior;
};

Pases* pasesInicio = NULL;
Pases* pasesActual = NULL;



void swap(Pases* a, Pases* b) {
	Pases temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Pases* arr, int low, int high) {
	Pases pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (wcscmp(arr[j].nombrePases, pivot.nombrePases) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Pases* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void heapify(Pases* arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && wcscmp(arr[l].nombrePases, arr[largest].nombrePases) > 0)
		largest = l;

	if (r < n && wcscmp(arr[r].nombrePases, arr[largest].nombrePases) > 0)
		largest = r;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void pasesAgregar(Pases* pasesNuevo) {
	if (pasesInicio == NULL) {
		pasesInicio = pasesNuevo;
		pasesNuevo->pasesSiguiente = pasesNuevo;
		pasesNuevo->pasesAnterior = pasesNuevo;
	}
	else {
		pasesInicio->pasesAnterior->pasesSiguiente = pasesNuevo;
		pasesNuevo->pasesAnterior = pasesInicio->pasesAnterior;
		pasesNuevo->pasesSiguiente = pasesInicio;
		pasesInicio->pasesAnterior = pasesNuevo;
	}
}

void pasesEliminar(Pases* pasesAEliminar) {

	Pases* pasesAnterior = pasesAEliminar->pasesAnterior;
	Pases* pasesSiguiente = pasesAEliminar->pasesSiguiente;
	if (pasesAnterior == pasesSiguiente && pasesAEliminar == pasesAnterior) {
		delete pasesAEliminar;
		pasesInicio = NULL;
		return;
	}
	if (pasesAnterior->pasesSiguiente == pasesInicio) {
		pasesInicio = pasesInicio->pasesSiguiente;
	}
	pasesAnterior->pasesSiguiente = pasesSiguiente;
	pasesSiguiente->pasesAnterior = pasesAnterior;
	delete pasesAEliminar;
}

void pasesActualizarLista(HWND handler) {
	SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_RESETCONTENT, NULL, NULL);
	if (pasesInicio == NULL) return;

	Pases* pasesAux = pasesInicio;
	int totalPases = 0;

	while (pasesAux->pasesSiguiente != pasesInicio) {
		totalPases++;
		pasesAux = pasesAux->pasesSiguiente;
	}

	Pases* pasesArray = new Pases[totalPases + 1];

	pasesAux = pasesInicio;
	for (int i = 0; i <= totalPases; i++) {
		pasesArray[i] = *pasesAux;
		pasesAux = pasesAux->pasesSiguiente;
	}

	quickSort(pasesArray, 0, totalPases);

	for (int i = 0; i <= totalPases; i++) {

		SendDlgItemMessage(handler, IDC_NOMBRE_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].nombrePases);
		SendDlgItemMessage(handler, IDC_APELLIDOS_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].apellidoPases);
		SendDlgItemMessage(handler, IDC_ID_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].idPases);
		SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].avionPases);

		SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].tipoPases);
		SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].clasePases);
		SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)pasesArray[i].pagoPases);

		//SendDlgItemMessage(handler, IDC_FechaNacimientoPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].FechaNacimientoPaciente);



	}

	delete[] pasesArray;

	while (pasesAux->pasesSiguiente != pasesInicio) {
		SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesAux->nombrePases);
		pasesAux = pasesAux->pasesSiguiente;
	}
	SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)pasesAux->nombrePases);

}

void pasesLimpiar() {

	if (pasesInicio != NULL) {
		Pases* pasesAux = pasesInicio;
		while (pasesAux->pasesSiguiente != pasesInicio) {
			pasesAux = pasesAux->pasesSiguiente;
			delete pasesAux->pasesAnterior;
		}
		delete pasesAux;
	}
	pasesInicio = NULL;
	pasesActual = NULL;

}

Pases* pasesBuscar(int i) {
	Pases* pasesAux = pasesInicio;
	for (int j = 0; j < i; j++) {
		pasesAux = pasesAux->pasesSiguiente;
	}
	return pasesAux;
}



BOOL CALLBACK COMPRARPASES(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		//pasesActualizarLista(handler);
		//pasesActualizarLista(handler);

		vuelosActualizarLista(handler);
		pasajerosActualizarLista(handler);

		//SendDlgItemMessage(handler, , CB_ADDSTRING, NULL, (LPARAM)L"");

		SendDlgItemMessage(handler, IDC_TipoBoleto, CB_ADDSTRING, NULL, (LPARAM)L"Normal");
		SendDlgItemMessage(handler, IDC_TipoBoleto, CB_ADDSTRING, NULL, (LPARAM)L"Infantil");
		SendDlgItemMessage(handler, IDC_TipoBoleto, CB_ADDSTRING, NULL, (LPARAM)L"Mayor de edad");

		SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_ADDSTRING, NULL, (LPARAM)L"Turista");
		SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_ADDSTRING, NULL, (LPARAM)L"Ejecutiva");

		SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_ADDSTRING, NULL, (LPARAM)L"Efectivo");
		SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_ADDSTRING, NULL, (LPARAM)L"Tarjeta de debito/credito");
		SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_ADDSTRING, NULL, (LPARAM)L"Transferencia");

		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_LIST_PASAJERO:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_GETCURSEL, NULL, NULL);
				Pasajeros* aMostrarPasajeros = pasajerosBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_NOMBRE_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrarPasajeros->nombresPasajeros);
				SendDlgItemMessage(handler, IDC_APELLIDOS_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrarPasajeros->apellidosPasajeros);

				return 0;
			}
			return 0;
		}

		case IDC_vuelos:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_vuelos, LB_GETCURSEL, NULL, NULL);
				Vuelos* aMostrarVuelos = vuelosBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_ID_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrarVuelos->vueloID);
				//SendDlgItemMessage(handler, IDC_ASIENTOS_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrarVuelos->vueloAsientos);

				if (aMostrarVuelos->vueloTipoAvion == 0)
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"Airbus A380");
				}

				else if (aMostrarVuelos->vueloTipoAvion == 1)
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"Boeing 777");
				}
				else if (aMostrarVuelos->vueloTipoAvion == 2)
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"Boeing 787 Dreamliner");
				}
				else if (aMostrarVuelos->vueloTipoAvion == 3)
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"Airbus A350");
				}
				else if (aMostrarVuelos->vueloTipoAvion == 4)
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"Boeing 737");
				}
				else
				{
					SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)L"");
				}



				return 0;
			}
			return 0;
		}

		case IDOK:
		{
			wchar_t nombreVerificacion[256], apellidosVerificacion[256], idVerificacion[256], tipoVerificacion[256];

			SendMessage(GetDlgItem(handler, IDC_NOMBRE_BOLETOS), WM_GETTEXT, sizeof(nombreVerificacion) / sizeof(nombreVerificacion[0]), (LPARAM)nombreVerificacion);
			SendMessage(GetDlgItem(handler, IDC_APELLIDOS_BOLETOS), WM_GETTEXT, sizeof(apellidosVerificacion) / sizeof(apellidosVerificacion[0]), (LPARAM)apellidosVerificacion);
			SendMessage(GetDlgItem(handler, IDC_ID_BOLETOS), WM_GETTEXT, sizeof(idVerificacion) / sizeof(idVerificacion[0]), (LPARAM)idVerificacion);
			SendMessage(GetDlgItem(handler, IDC_TIPO_AVION_BOLETOS), WM_GETTEXT, sizeof(tipoVerificacion) / sizeof(tipoVerificacion[0]), (LPARAM)tipoVerificacion);

			wstring nombresWstring(nombreVerificacion);
			wstring apellidosWstring(apellidosVerificacion);
			wstring idWstring(idVerificacion);
			wstring tipoWstring(tipoVerificacion);

			string boletoNombre(nombresWstring.begin(), nombresWstring.end());
			string boletoApellidos(apellidosWstring.begin(), apellidosWstring.end());
			string boletoId(idWstring.begin(), idWstring.end());
			string boletoTipo(tipoWstring.begin(), tipoWstring.end());

			if (boletoNombre == "" || boletoApellidos == "" || boletoId == "" || boletoTipo == "") {
				MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONERROR);
				return 0;
			}

			else
			{
				Pases* pasesNuevo = NULL;
				if (pasesActual == NULL) {
					pasesNuevo = new Pases;

					SendMessage(GetDlgItem(handler, IDC_NOMBRE_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->nombrePases) / sizeof(pasesNuevo->nombrePases[0]), (LPARAM)pasesNuevo->nombrePases);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->apellidoPases) / sizeof(pasesNuevo->apellidoPases[0]), (LPARAM)pasesNuevo->apellidoPases);
					SendMessage(GetDlgItem(handler, IDC_ID_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->idPases) / sizeof(pasesNuevo->idPases[0]), (LPARAM)pasesNuevo->idPases);
					SendMessage(GetDlgItem(handler, IDC_TIPO_AVION_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->avionPases) / sizeof(pasesNuevo->avionPases[0]), (LPARAM)pasesNuevo->avionPases);

					pasesNuevo->tipoPases = SendDlgItemMessage(handler, IDC_TipoBoleto, CB_GETCURSEL, 0, 0);
					pasesNuevo->clasePases = SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_GETCURSEL, 0, 0);
					pasesNuevo->pagoPases = SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_GETCURSEL, 0, 0);


					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, IDC_SEXO_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->sexoPasajeros) / sizeof(pasajerosNuevo->sexoPasajeros[0]), (LPARAM)pasajerosNuevo->sexoPasajeros);
					//pasajerosNuevo->sexoPasajeros = SendDlgItemMessage(handler, IDC_SEXO_LISTA, CB_GETCURSEL, 0, 0);


					if (pasesNuevo->tipoPases <= 0 || pasesNuevo->clasePases <= 0 || pasesNuevo->pagoPases <= 0)
					{
						MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONEXCLAMATION | MB_OK);
						return 0;
					}

					else
					{
						pasesAgregar(pasesNuevo);
						pasesActualizarLista(handler);

						Pases* b = pasesBuscar(0);
						int a = 0;
						a++;

						EndDialog(handler, 0);
						return 0;
					}
				}

				else {
					pasesNuevo = pasesActual;
					SendMessage(GetDlgItem(handler, IDC_NOMBRE_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->nombrePases) / sizeof(pasesNuevo->nombrePases[0]), (LPARAM)pasesNuevo->nombrePases);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->apellidoPases) / sizeof(pasesNuevo->apellidoPases[0]), (LPARAM)pasesNuevo->apellidoPases);
					SendMessage(GetDlgItem(handler, IDC_ID_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->idPases) / sizeof(pasesNuevo->idPases[0]), (LPARAM)pasesNuevo->idPases);
					SendMessage(GetDlgItem(handler, IDC_TIPO_AVION_BOLETOS), WM_GETTEXT, sizeof(pasesNuevo->avionPases) / sizeof(pasesNuevo->avionPases[0]), (LPARAM)pasesNuevo->avionPases);

					pasesNuevo->tipoPases = SendDlgItemMessage(handler, IDC_TipoBoleto, CB_GETCURSEL, 0, 0);
					pasesNuevo->clasePases = SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_GETCURSEL, 0, 0);
					pasesNuevo->pagoPases = SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_GETCURSEL, 0, 0);



					//pasajerosNuevo->sexoPasajeros = SendDlgItemMessage(handler, IDC_SEXO_LISTA, CB_GETCURSEL, 0, 0);
					//SendMessage(GetDlgItem(handler, IDC_NACIONALIDAD_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->nacionalidadPasajeros) / sizeof(pasajerosNuevo->nacionalidadPasajeros[0]), (LPARAM)pasajerosNuevo->nacionalidadPasajeros);
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

BOOL CALLBACK CANCELARPASES(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasesActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_GETCURSEL, NULL, NULL);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay boletos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			if (MessageBox(handler, L"Esta seguro de querer eliminar el boleto seleccionado?", L"Eliminando boleto", MB_OKCANCEL) == IDOK)
			{
				pasesActual = pasesBuscar(seleccionado);
				pasesEliminar(pasesActual);
				pasesActualizarLista(handler);
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

BOOL CALLBACK MODIFICARPASES(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasesActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_GETCURSEL, NULL, NULL);
			Pases* aMostrar = pasesBuscar(seleccionado);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay boletos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			pasesActual = pasesBuscar(seleccionado);
			EndDialog(handler, 0);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_REGISTRO), handler, (DLGPROC)COMPRARBOLETOS);
			pasesActualizarLista(handler);
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

BOOL CALLBACK LISTAPASES(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		pasesActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_LIST_BOLETOS:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_GETCURSEL, NULL, NULL);
				Pases* aMostrar = pasesBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_NOMBRE_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->nombrePases);
				SendDlgItemMessage(handler, IDC_APELLIDOS_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->apellidoPases);
				SendDlgItemMessage(handler, IDC_ID_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->idPases);
				SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->avionPases);


				if (aMostrar->tipoPases == 0)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Normal");
				}

				else if (aMostrar->tipoPases == 1)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Infantil");
				}

				else if (aMostrar->tipoPases == 2)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Mayor de edad");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"");
				}

				//-----------------------------------

				if (aMostrar->clasePases == 0)
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Turista");
				}

				else if (aMostrar->clasePases == 1)
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Ejecutiva");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"");
				}

				//-----------------------------------

				if (aMostrar->pagoPases == 0)
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Efectivo");
				}

				else if (aMostrar->pagoPases == 1)
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Tarjeta de debito/credito");
				}

				else if (aMostrar->pagoPases == 2)
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Transferencia");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"");
				}

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



