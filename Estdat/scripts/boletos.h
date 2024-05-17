#pragma once
#include"Estdat.h"

struct Boletos
{
	wchar_t nombresPasajeros[200];
	wchar_t apellidosPasajeros[200];
	int sexoPasajeros;
	wchar_t nacionalidadPasajeros[200];
	//	wchar_t fechaNacimientoPasajeros[200];

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
		if (wcscmp(arr[j].nombresPasajeros, pivot.nombresPasajeros) < 0) { //         <---------------
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

	if (l < n && wcscmp(arr[l].nombresPasajeros, arr[largest].nombresPasajeros) > 0)     //<-----------
		largest = l;

	if (r < n && wcscmp(arr[r].nombresPasajeros, arr[largest].nombresPasajeros) > 0)     //<-----------
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
	//SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_RESETCONTENT, NULL, NULL);  <-----
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

		//SendDlgItemMessage(handler, IDC_NOMBRE_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].nombresPasajeros);
		//SendDlgItemMessage(handler, IDC_APELLIDOS_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].apellidosPasajeros);
		//SendDlgItemMessage(handler, IDC_SEXO_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].sexoPasajeros);
		//SendDlgItemMessage(handler, IDC_NACIONALIDAD_PASAJEROS, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].nacionalidadPasajeros);
		//SendDlgItemMessage(handler, IDC_FechaNacimientoPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].FechaNacimientoPaciente);
		//SendDlgItemMessage(handler, IDC_EdadPaciente, LB_ADDSTRING, NULL, (LPARAM)pasajerosArray[i].EdadPaciente);

	}

	delete[] boletosArray;

	while (boletosAux->boletosSiguiente != boletosInicio) {
		//SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_ADDSTRING, NULL, (LPARAM)pasajerosAux->nombresPasajeros);
		boletosAux = boletosAux->boletosSiguiente;
	}
	//SendDlgItemMessage(handler, IDC_LIST_PASAJERO, LB_ADDSTRING, NULL, (LPARAM)pasajerosAux->nombresPasajeros);

}

void boletosLimpiar() {

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

BOOL CALLBACK MODIFICARBOLETOS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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

