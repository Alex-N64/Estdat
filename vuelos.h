#pragma once

struct Vuelos
{
	wchar_t NombrePaciente[200];
	wchar_t Genero[200];
	wchar_t TelefonoPaciente[200];
	wchar_t Referencia[400];
	wchar_t FechaNacimientoPaciente[200];
	wchar_t EdadPaciente[200];
	wchar_t Medico[200];

	Vuelos* Vuelos_siguiente;
	Vuelos* Vuelos_anterior;
};

Vuelos* Vuelos_inicio = NULL;
Vuelos* Vuelos_actual = NULL;

void swap(Vuelos* a, Vuelos* b) {
	Vuelos temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Vuelos* arr, int low, int high) {
	Vuelos pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (wcscmp(arr[j].NombrePaciente, pivot.NombrePaciente) < 0) {
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

	if (l < n && wcscmp(arr[l].NombrePaciente, arr[largest].NombrePaciente) > 0)
		largest = l;

	if (r < n && wcscmp(arr[r].NombrePaciente, arr[largest].NombrePaciente) > 0)
		largest = r;

	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

void Vuelos_agregar(Vuelos* Vuelos_nuevo) {
	if (Vuelos_inicio == NULL) {
		Vuelos_inicio = Vuelos_nuevo;
		Vuelos_nuevo->Vuelos_siguiente = Vuelos_nuevo;
		Vuelos_nuevo->Vuelos_anterior = Vuelos_nuevo;
	}
	else {
		Vuelos_inicio->Vuelos_anterior->Vuelos_siguiente = Vuelos_nuevo;
		Vuelos_nuevo->Vuelos_anterior = Vuelos_inicio->Vuelos_anterior;
		Vuelos_nuevo->Vuelos_siguiente = Vuelos_inicio;
		Vuelos_inicio->Vuelos_anterior = Vuelos_nuevo;
	}
}

void Vuelos_eliminar(Vuelos* Vuelos_aEliminar) {

	Vuelos* Vuelos_anterior = Vuelos_aEliminar->Vuelos_anterior;
	Vuelos* Vuelos_siguiente = Vuelos_aEliminar->Vuelos_siguiente;
	if (Vuelos_anterior == Vuelos_siguiente && Vuelos_aEliminar == Vuelos_anterior) {
		delete Vuelos_aEliminar;
		Vuelos_inicio = NULL;
		return;
	}
	if (Vuelos_anterior->Vuelos_siguiente == Vuelos_inicio) {
		Vuelos_inicio = Vuelos_inicio->Vuelos_siguiente;
	}
	Vuelos_anterior->Vuelos_siguiente = Vuelos_siguiente;
	Vuelos_siguiente->Vuelos_anterior = Vuelos_anterior;
	delete Vuelos_aEliminar;
}

void Vuelos_ActualizarLista(HWND handler) {
	//SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_RESETCONTENT, NULL, NULL);         <------- Descomentame
	if (Vuelos_inicio == NULL) return;

	Vuelos* Vuelos_aux = Vuelos_inicio;
	int totalVuelos = 0;

	while (Vuelos_aux->Vuelos_siguiente != Vuelos_inicio) {
		totalVuelos++;
		Vuelos_aux = Vuelos_aux->Vuelos_siguiente;
	}

	Vuelos* VuelosArray = new Vuelos[totalVuelos + 1];

	Vuelos_aux = Vuelos_inicio;
	for (int i = 0; i <= totalVuelos; i++) {
		VuelosArray[i] = *Vuelos_aux;
		Vuelos_aux = Vuelos_aux->Vuelos_siguiente;
	}

	quickSort(VuelosArray, 0, totalVuelos);

	for (int i = 0; i <= totalVuelos; i++) {
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

	delete[] VuelosArray;

	while (Vuelos_aux->Vuelos_siguiente != Vuelos_inicio) {
	//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame
		Vuelos_aux = Vuelos_aux->Vuelos_siguiente;
	}
//	SendDlgItemMessage(handler, IDC_LIST_PACIENTES, LB_ADDSTRING, NULL, (LPARAM)Vuelos_aux->NombrePaciente);         <------- Descomentame

}

void Vuelos_limpiar() {

	if (Vuelos_inicio != NULL) {
		Vuelos* Vuelos_aux = Vuelos_inicio;
		while (Vuelos_aux->Vuelos_siguiente != Vuelos_inicio) {
			Vuelos_aux = Vuelos_aux->Vuelos_siguiente;
			delete Vuelos_aux->Vuelos_anterior;
		}
		delete Vuelos_aux;
	}
	Vuelos_inicio = NULL;
	Vuelos_actual = NULL;

}

Vuelos* buscar(int i) {
	Vuelos* Vuelos_aux = Vuelos_inicio;
	for (int j = 0; j < i; j++) {
		Vuelos_aux = Vuelos_aux->Vuelos_siguiente;
	}
	return Vuelos_aux;
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
