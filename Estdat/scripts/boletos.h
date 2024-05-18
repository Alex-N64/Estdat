#pragma once
#include"Estdat.h"

struct Boletos
{
	wchar_t nombreBoleto[200];
	wchar_t apellidoBoleto[200];
	wchar_t idBoleto[200];
	wchar_t avionBoleto[200];
	//wchar_t asientoBoleto
	int tipoBoleto;
	int claseBoleto;
	int pagoBoleto;

	Boletos* boletosSiguiente;
	Boletos* boletosAnterior;
};

Boletos* boletosInicio = NULL;
Boletos* boletosActual = NULL;



void swap(Boletos* a, Boletos* b) {
	Boletos temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Boletos* arr, int low, int high) {
	Boletos pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (wcscmp(arr[j].nombreBoleto, pivot.nombreBoleto) < 0) 
		{ 
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Boletos* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void heapify(Boletos* arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && wcscmp(arr[l].nombreBoleto, arr[largest].nombreBoleto) > 0)     
		largest = l;

	if (r < n && wcscmp(arr[r].nombreBoleto, arr[largest].nombreBoleto) > 0)     
		largest = r;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void boletosAgregar(Boletos* boletosNuevo) {
	if (boletosInicio == NULL) {
		boletosInicio = boletosNuevo;
		boletosNuevo->boletosSiguiente = boletosNuevo;
		boletosNuevo->boletosAnterior = boletosNuevo;
	}
	else {
		boletosInicio->boletosAnterior->boletosSiguiente = boletosNuevo;
		boletosNuevo->boletosAnterior = boletosInicio->boletosAnterior;
		boletosNuevo->boletosSiguiente = boletosInicio;
		boletosInicio->boletosAnterior = boletosNuevo;
	}
}

void boletosEliminar(Boletos* boletosAEliminar) {

	Boletos* boletosAnterior = boletosAEliminar->boletosAnterior;
	Boletos* boletosSiguiente = boletosAEliminar->boletosSiguiente;
	if (boletosAnterior == boletosSiguiente && boletosAEliminar == boletosAnterior) {
		delete boletosAEliminar;
		boletosInicio = NULL;
		return;
	}
	if (boletosAnterior->boletosSiguiente == boletosInicio) {
		boletosInicio = boletosInicio->boletosSiguiente;
	}
	boletosAnterior->boletosSiguiente = boletosSiguiente;
	boletosSiguiente->boletosAnterior = boletosAnterior;
	delete boletosAEliminar;
}

void boletosActualizarLista(HWND handler) {
	SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_RESETCONTENT, NULL, NULL);
	if (boletosInicio == NULL) return;

	Boletos* boletosAux = boletosInicio;
	int totalBoletos = 0;

	while (boletosAux->boletosSiguiente != boletosInicio) {
		totalBoletos++;
		boletosAux = boletosAux->boletosSiguiente;
	}

	Boletos* boletosArray = new Boletos[totalBoletos + 1];

	boletosAux = boletosInicio;
	for (int i = 0; i <= totalBoletos; i++) {
		boletosArray[i] = *boletosAux;
		boletosAux = boletosAux->boletosSiguiente;
	}

	quickSort(boletosArray, 0, totalBoletos);

	for (int i = 0; i <= totalBoletos; i++) {

		SendDlgItemMessage(handler, IDC_NOMBRE_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].nombreBoleto);
		SendDlgItemMessage(handler, IDC_APELLIDOS_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].apellidoBoleto);
		SendDlgItemMessage(handler, IDC_ID_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].idBoleto);
		SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].avionBoleto);
		
		SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].tipoBoleto);
		SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].claseBoleto);
		SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, LB_ADDSTRING, NULL, (LPARAM)boletosArray[i].pagoBoleto);

		//SendDlgItemMessage(handler, IDC_FechaNacimientoPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].FechaNacimientoPaciente);


		
	}

	delete[] boletosArray;

	while (boletosAux->boletosSiguiente != boletosInicio) {
		SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosAux->nombreBoleto);
		boletosAux = boletosAux->boletosSiguiente;
	}
	SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_ADDSTRING, NULL, (LPARAM)boletosAux->nombreBoleto);

}

void boletosLimpiar() {

	if (boletosInicio != NULL) {
		Boletos* boletosAux = boletosInicio;
		while (boletosAux->boletosSiguiente != boletosInicio) {
			boletosAux = boletosAux->boletosSiguiente;
			delete boletosAux->boletosAnterior;
		}
		delete boletosAux;
	}
	boletosInicio = NULL;
	boletosActual = NULL;

}

Boletos* boletosBuscar(int i) {
	Boletos* boletosAux = boletosInicio;
	for (int j = 0; j < i; j++) {
		boletosAux = boletosAux->boletosSiguiente;
	}
	return boletosAux;
}



BOOL CALLBACK COMPRARBOLETOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{	
		pasajerosActualizarLista(handler);
		vuelosActualizarLista(handler);

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
				Boletos* boletosNuevo = NULL;
				if (boletosActual == NULL) {
					boletosNuevo = new Boletos;

					SendMessage(GetDlgItem(handler, IDC_NOMBRE_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->nombreBoleto) / sizeof(boletosNuevo->nombreBoleto[0]), (LPARAM)boletosNuevo->nombreBoleto);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->apellidoBoleto) / sizeof(boletosNuevo->apellidoBoleto[0]), (LPARAM)boletosNuevo->apellidoBoleto);
					SendMessage(GetDlgItem(handler, IDC_ID_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->idBoleto) / sizeof(boletosNuevo->idBoleto[0]), (LPARAM)boletosNuevo->idBoleto);
					SendMessage(GetDlgItem(handler, IDC_TIPO_AVION_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->avionBoleto) / sizeof(boletosNuevo->avionBoleto[0]), (LPARAM)boletosNuevo->avionBoleto);
					
					boletosNuevo->tipoBoleto = SendDlgItemMessage(handler, IDC_TipoBoleto, CB_GETCURSEL, 0, 0);
					boletosNuevo->claseBoleto = SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_GETCURSEL, 0, 0);
					boletosNuevo->pagoBoleto = SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_GETCURSEL, 0, 0);


					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(pasajerosNuevo->apellidosPasajeros) / sizeof(pasajerosNuevo->apellidosPasajeros[0]), (LPARAM)pasajerosNuevo->apellidosPasajeros);
					//SendMessage(GetDlgItem(handler, IDC_SEXO_PASAJEROS), WM_GETTEXT, sizeof(pasajerosNuevo->sexoPasajeros) / sizeof(pasajerosNuevo->sexoPasajeros[0]), (LPARAM)pasajerosNuevo->sexoPasajeros);
					//pasajerosNuevo->sexoPasajeros = SendDlgItemMessage(handler, IDC_SEXO_LISTA, CB_GETCURSEL, 0, 0);

				
					if (boletosNuevo->tipoBoleto <= 0 || boletosNuevo->claseBoleto <= 0 || boletosNuevo->pagoBoleto <= 0)
					{
						MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONEXCLAMATION | MB_OK);
						return 0;
					}

					else
					{
						boletosAgregar(boletosNuevo);
						boletosActualizarLista(handler);

						Boletos* b = boletosBuscar(0);
						int a = 0;
						a++;
						
						EndDialog(handler, 0);
						return 0;
					}
				}

				else {
					boletosNuevo = boletosActual;
					SendMessage(GetDlgItem(handler, IDC_NOMBRE_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->nombreBoleto) / sizeof(boletosNuevo->nombreBoleto[0]), (LPARAM)boletosNuevo->nombreBoleto);
					SendMessage(GetDlgItem(handler, IDC_APELLIDOS_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->apellidoBoleto) / sizeof(boletosNuevo->apellidoBoleto[0]), (LPARAM)boletosNuevo->apellidoBoleto);
					SendMessage(GetDlgItem(handler, IDC_ID_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->idBoleto) / sizeof(boletosNuevo->idBoleto[0]), (LPARAM)boletosNuevo->idBoleto);
					SendMessage(GetDlgItem(handler, IDC_TIPO_AVION_BOLETOS), WM_GETTEXT, sizeof(boletosNuevo->avionBoleto) / sizeof(boletosNuevo->avionBoleto[0]), (LPARAM)boletosNuevo->avionBoleto);

					boletosNuevo->tipoBoleto = SendDlgItemMessage(handler, IDC_TipoBoleto, CB_GETCURSEL, 0, 0);
					boletosNuevo->claseBoleto = SendDlgItemMessage(handler, IDC_CLASE_BOLETO, CB_GETCURSEL, 0, 0);
					boletosNuevo->pagoBoleto = SendDlgItemMessage(handler, IDC_FORMA_PAGO, CB_GETCURSEL, 0, 0);



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

BOOL CALLBACK CANCELARBOLETOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		boletosActualizarLista(handler);
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
				boletosActual = boletosBuscar(seleccionado);
				boletosEliminar(boletosActual);
				boletosActualizarLista(handler);
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

BOOL CALLBACK MODIFICARBOLETOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		boletosActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_GETCURSEL, NULL, NULL);
			Boletos* aMostrar = boletosBuscar(seleccionado);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay boletos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			boletosActual = boletosBuscar(seleccionado);
			EndDialog(handler, 0);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_BOLETOS_REGISTRO), handler, (DLGPROC)COMPRARBOLETOS);
			boletosActualizarLista(handler);
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

BOOL CALLBACK LISTABOLETOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		boletosActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDC_LIST_BOLETOS:
		{
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				int seleccionado = SendDlgItemMessage(handler, IDC_LIST_BOLETOS, LB_GETCURSEL, NULL, NULL);
				Boletos* aMostrar = boletosBuscar(seleccionado);
				SendDlgItemMessage(handler, IDC_NOMBRE_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->nombreBoleto);
				SendDlgItemMessage(handler, IDC_APELLIDOS_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->apellidoBoleto);
				SendDlgItemMessage(handler, IDC_ID_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->idBoleto);
				SendDlgItemMessage(handler, IDC_TIPO_AVION_BOLETOS, WM_SETTEXT, NULL, (LPARAM)aMostrar->avionBoleto);

				
				if (aMostrar->tipoBoleto == 0)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Normal");
				}

				else if (aMostrar->tipoBoleto == 1)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Infantil");
				}

				else if (aMostrar->tipoBoleto == 2)
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Mayor de edad");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_TIPO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"");
				}
				
				//-----------------------------------
				
				if (aMostrar->claseBoleto == 0)
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Turista");
				}

				else if (aMostrar->claseBoleto == 1)
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Ejecutiva");
				}

				else
				{
					SendDlgItemMessage(handler, IDC_CLASE_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"");
				}

				//-----------------------------------

				if (aMostrar->pagoBoleto == 0)
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Efectivo");
				}

				else if (aMostrar->pagoBoleto == 1)
				{
					SendDlgItemMessage(handler, IDC_PAGO_BOLETO_EDITBOX, WM_SETTEXT, NULL, (LPARAM)L"Tarjeta de debito/credito");
				}

				else if (aMostrar->pagoBoleto == 2)
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


