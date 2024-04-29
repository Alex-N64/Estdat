#pragma once

struct Pasajeros
{
	wchar_t nombresPasajeros[200];
	wchar_t apellidosPasajeros[200];
	wchar_t generoPasajeros[200];
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
	//SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_RESETCONTENT, NULL, NULL);         <------- Descomentame
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
		/*
		SendDlgItemMessage(handler, IDC_NombrePaciente, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].NombrePaciente);
		SendDlgItemMessage(handler, IDC_Genero, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Genero);
		SendDlgItemMessage(handler, IDC_TelefonoPaciente, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].TelefonoPaciente);
		SendDlgItemMessage(handler, IDC_Referencia, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Referencia);
		SendDlgItemMessage(handler, IDC_FechaNacimientoPaciente, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].FechaNacimientoPaciente);
		SendDlgItemMessage(handler, IDC_EdadPaciente, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].EdadPaciente);
		SendDlgItemMessage(handler, IDC_Medico, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Medico);
		*/


	}

	delete[] pasajerosArray;

	while (pasajerosAux->pasajerosSiguiente != pasajerosInicio) {
		//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame
		pasajerosAux = pasajerosAux->pasajerosSiguiente;
	}
	//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame

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

BOOL CALLBACK ELIMINARPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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

BOOL CALLBACK MODIFICARPASAJEROS(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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




