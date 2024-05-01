#pragma once

struct Vuelos
{
	wchar_t vueloOrigen[200];
	wchar_t vueloDestino[200];
	wchar_t vueloFechaEntrada[200];
	wchar_t vueloFechaSalida[200];
	wchar_t vueloHora[200];
	wchar_t vueloID[200];
	wchar_t vueloTipoAvion[200];
	wchar_t vueloAsientos[200];
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

		SendDlgItemMessage(handler, IDC_vueloOrigen, LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].vueloOrigen);
		SendDlgItemMessage(handler, IDC_vueloDestino, LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].vueloDestino);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);
		SendDlgItemMessage(handler, IDC_idVuelo, LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].vueloID);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);
		SendDlgItemMessage(handler, IDC_asientosDisponibles, LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].vueloAsientos);
		//SendDlgItemMessage(handler, , LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].);

	}

	delete[] vuelosArray;

	while (vuelosAux->vuelosSiguiente != vuelosInicio) {
		SendDlgItemMessage(handler, IDC_vuelos, LB_ADDSTRING, NULL, (LPARAM)vuelosAux->vueloID);
		vuelosAux = vuelosAux->vuelosSiguiente;
	}
	SendDlgItemMessage(handler, IDC_vuelos, LB_ADDSTRING, NULL, (LPARAM)vuelosAux->vueloID);

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
		case IDOK: {
			Vuelos* vuelosNuevo = NULL;
			if (vuelosActual == NULL) {
				vuelosNuevo = new Vuelos;
				SendMessage(GetDlgItem(handler, IDC_vueloOrigen), WM_GETTEXT, sizeof(vuelosNuevo->vueloOrigen) / sizeof(vuelosNuevo->vueloOrigen[0]), (LPARAM)vuelosNuevo->vueloOrigen);
				SendMessage(GetDlgItem(handler, IDC_vueloDestino), WM_GETTEXT, sizeof(vuelosNuevo->vueloDestino) / sizeof(vuelosNuevo->vueloDestino[0]), (LPARAM)vuelosNuevo->vueloDestino);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
				SendMessage(GetDlgItem(handler, IDC_idVuelo), WM_GETTEXT, sizeof(vuelosNuevo->vueloID) / sizeof(vuelosNuevo->vueloID[0]), (LPARAM)vuelosNuevo->vueloID);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);
				SendMessage(GetDlgItem(handler, IDC_asientosDisponibles), WM_GETTEXT, sizeof(vuelosNuevo->vueloAsientos) / sizeof(vuelosNuevo->vueloAsientos[0]), (LPARAM)vuelosNuevo->vueloAsientos);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);

				vuelosAgregar(vuelosNuevo);
				Vuelos_ActualizarLista(handler);

				vuelosActual* b = vuelosBuscar(0);
				int a = 0;
				a++;

				EndDialog(handler, 0);
			}

			else {
				vuelosNuevo = vuelosActual;
				SendMessage(GetDlgItem(handler, IDC_vueloOrigen), WM_GETTEXT, sizeof(vuelosNuevo->vueloOrigen) / sizeof(vuelosNuevo->vueloOrigen[0]), (LPARAM)vuelosNuevo->vueloOrigen);
				SendMessage(GetDlgItem(handler, IDC_vueloDestino), WM_GETTEXT, sizeof(vuelosNuevo->vueloDestino) / sizeof(vuelosNuevo->vueloDestino[0]), (LPARAM)vuelosNuevo->vueloDestino);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->NumeroConsultorio) / sizeof(vuelosNuevo->NumeroConsultorio[0]), (LPARAM)vuelosNuevo->NumeroConsultorio);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->TelefonoMedico) / sizeof(vuelosNuevo->TelefonoMedico[0]), (LPARAM)vuelosNuevo->TelefonoMedico);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->HoraInicio) / sizeof(vuelosNuevo->HoraInicio[0]), (LPARAM)vuelosNuevo->HoraInicio);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->HoraFinal) / sizeof(vuelosNuevo->HoraFinal[0]), (LPARAM)vuelosNuevo->HoraFinal);
				SendMessage(GetDlgItem(handler, IDC_idVuelo), WM_GETTEXT, sizeof(vuelosNuevo->vueloID) / sizeof(vuelosNuevo->vueloID[0]), (LPARAM)vuelosNuevo->vueloID);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->DiaSemana) / sizeof(vuelosNuevo->DiaSemana[0]), (LPARAM)vuelosNuevo->DiaSemana);
				SendMessage(GetDlgItem(handler, IDC_asientosDisponibles), WM_GETTEXT, sizeof(vuelosNuevo->vueloAsientos) / sizeof(vuelosNuevo->vueloAsientos[0]), (LPARAM)vuelosNuevo->vueloAsientos);
				//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->DiaSemana) / sizeof(vuelosNuevo->DiaSemana[0]), (LPARAM)vuelosNuevo->DiaSemana);

				EndDialog(handler, 0);
			}
			break;

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
