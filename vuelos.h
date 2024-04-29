#pragma once

struct Vuelos
{
	wchar_t vueloOrigen[200];
	wchar_t vueloDestino[200];
	wchar_t vueloFechaSalida[200];
	wchar_t vueloFechaEntrada[200];
	wchar_t vueloHora[200];
	wchar_t vueloNumero[200];
	wchar_t vueloTipoAvion[200];
	wchar_t vueloCantidadAsientos[200];
	wchar_t vueloClase[200];

	Vuelos* vuelosSiguiente;
	Vuelos* vuelosAnterior;
};

Vuelos* vuelosInicio = NULL;
Vuelos* vuelosActual = NULL;

void swap(Vuelos* a, Vuelos* b) {
	Vuelos temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Vuelos* arr, int low, int high) {
	Vuelos pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (wcscmp(arr[j].vueloOrigen, pivot.vueloOrigen) < 0) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Vuelos* arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void heapify(Vuelos* arr, int n, int i) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && wcscmp(arr[l].vueloOrigen, arr[largest].vueloOrigen) > 0)
		largest = l;

	if (r < n && wcscmp(arr[r].vueloOrigen, arr[largest].vueloOrigen) > 0)
		largest = r;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void vuelosAgregar(Vuelos* vuelosNuevo) {
	if (vuelosInicio == NULL) {
		vuelosInicio = vuelosNuevo;
		vuelosNuevo->vuelosSiguiente = vuelosNuevo;
		vuelosNuevo->vuelosAnterior = vuelosNuevo;
	}
	else {
		vuelosInicio->vuelosAnterior->vuelosSiguiente = vuelosNuevo;
		vuelosNuevo->vuelosAnterior = vuelosInicio->vuelosAnterior;
		vuelosNuevo->vuelosSiguiente = vuelosInicio;
		vuelosInicio->vuelosAnterior = vuelosNuevo;
	}
}

void vuelosEliminar(Vuelos* vuelosAEliminar) {

	Vuelos* vuelosAnterior = vuelosAEliminar->vuelosAnterior;
	Vuelos* vuelosSiguiente = vuelosAEliminar->vuelosSiguiente;
	if (vuelosAnterior == vuelosSiguiente && vuelosAEliminar == vuelosAnterior) {
		delete vuelosAEliminar;
		vuelosInicio = NULL;
		return;
	}
	if (vuelosAnterior->vuelosSiguiente == vuelosInicio) {
		vuelosInicio = vuelosInicio->vuelosSiguiente;
	}
	vuelosAnterior->vuelosSiguiente = vuelosSiguiente;
	vuelosSiguiente->vuelosAnterior = vuelosAnterior;
	delete vuelosAEliminar;
}

void Vuelos_ActualizarLista(HWND handler) {
	//SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_RESETCONTENT, NULL, NULL);         <------- Descomentame
	if (vuelosInicio == NULL) return;

	Vuelos* vuelosAux = vuelosInicio;
	int totalVuelos = 0;

	while (vuelosAux->vuelosSiguiente != vuelosInicio) {
		totalVuelos++;
		vuelosAux = vuelosAux->vuelosSiguiente;
	}

	Vuelos* vuelosArray = new Vuelos[totalVuelos + 1];

	vuelosAux = vuelosInicio;
	for (int i = 0; i <= totalVuelos; i++) {
		vuelosArray[i] = *vuelosAux;
		vuelosAux = vuelosAux->vuelosSiguiente;
	}

	quickSort(vuelosArray, 0, totalVuelos);

	for (int i = 0; i <= totalVuelos; i++) {
		
		SendDlgItemMessage(handler, IDC_vueloOrigen, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].NombrePaciente);
		SendDlgItemMessage(handler, IDC_vueloDestino, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Genero);
		//SendDlgItemMessage(handler, IDC_fechaSalida, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].TelefonoPaciente);
		//SendDlgItemMessage(handler, IDC_fechaLlegada, LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Referencia);
		SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].FechaNacimientoPaciente);
		SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].EdadPaciente);
		SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Medico);
		SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Medico);
		SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)PacientesArray[i].Medico);

	}

	delete[] vuelosArray;

	while (vuelosAux->vuelosSiguiente != vuelosInicio) {
	//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame
		vuelosAux = vuelosAux->vuelosSiguiente;
	}
//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame

}

void vuelosLimpiar() {

	if (vuelosInicio != NULL) {
		Vuelos* vuelosAux = vuelosInicio;
		while (vuelosAux->vuelosSiguiente != vuelosInicio) {
			vuelosAux = vuelosAux->vuelosSiguiente;
			delete vuelosAux->vuelosAnterior;
		}
		delete vuelosAux;
	}
	vuelosInicio = NULL;
	vuelosActual = NULL;

}

Vuelos* vuelosBuscar(int i) {
	Vuelos* vuelosAux = vuelosInicio;
	for (int j = 0; j < i; j++) {
		vuelosAux = vuelosAux->vuelosSiguiente;
	}
	return vuelosAux;
}



BOOL CALLBACK REGISTRARVUELO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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

BOOL CALLBACK ELIMINARVUELO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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

BOOL CALLBACK MODIFICARVUELO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
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
