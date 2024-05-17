#pragma once
#include "Estdat.h"


struct Vuelos
{
	wchar_t vueloOrigen[200];
	wchar_t vueloDestino[200];
	wchar_t vueloFechaEntrada[200];
	wchar_t vueloFechaSalida[200];
	wchar_t vueloHoraSalida[200];
	wchar_t vueloHoraLlegada[200];
	wchar_t vueloID[200];
	//wchar_t vueloTipoAvion[200];
	int vueloTipoAvion;
	wchar_t vueloAsientos[200];

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

void vuelosActualizarLista(HWND handler) {
	SendDlgItemMessage(handler, IDC_vuelos, LB_RESETCONTENT, NULL, NULL);
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
		//SendDlgItemMessage(handler, IDC_asientosDisponibles, LB_ADDSTRING, NULL, (LPARAM)vuelosArray[i].vueloAsientos);
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
	case WM_INITDIALOG: {
		
		SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Airbus A380");
		SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 777");
		SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 787 Dreamliner");
		SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Airbus A350");
		SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 737");

		string leerVariable;
		HWND idTraducion = GetDlgItem(handler, IDC_idVuelo);

		ifstream read(rutaIdVuelo);
		getline(read, leerVariable);
		vueloIdActual = stoi(leerVariable);


		std::wstring text = std::to_wstring(vueloIdActual);
		SetWindowText(idTraducion, text.c_str());

		vuelosActualizarLista(handler);

		if (vuelosActual != NULL) {
			SendDlgItemMessage(handler, IDC_vueloOrigen, WM_SETTEXT, NULL, (LPARAM)vuelosActual->vueloOrigen);
			SendDlgItemMessage(handler, IDC_vueloDestino, WM_SETTEXT, NULL, (LPARAM)vuelosActual->vueloDestino);
			//SendDlgItemMessage(handler, IDC_Dosis, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->Dosis);
			//SendDlgItemMessage(handler, IDC_CentroVacuna, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->CentroVacuna);
			//SendDlgItemMessage(handler, IDC_Lote, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->Lote);
			//SendDlgItemMessage(handler, IDC_ApellidoPaterno, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->ApellidoPaterno);
			SendDlgItemMessage(handler, IDC_idVuelo, WM_SETTEXT, NULL, (LPARAM)vuelosActual->vueloID);
			//SendDlgItemMessage(handler, IDC_Nombres, WM_SETTEXT, NULL, (LPARAM)CarnetPersona_actual->Nombres);
			//SendDlgItemMessage(handler, IDC_asientosDisponibles, WM_SETTEXT, NULL, (LPARAM)vuelosActual->vueloAsientos);
			//vuelosActual->vueloClase = SendDlgItemMessage(handler, IDC_claseAvion, CB_GETCURSEL, 0, 0);

			//SendDlgItemMessage(handler, IDC_FechaNacimiento, DTM_SETSYSTEMTIME, NULL, (LPARAM) & (CarnetPersona_actual->FechaNacimiento));
			//SendDlgItemMessage(handler, IDC_FechaNacimiento, DTM_SETSYSTEMTIME, NULL, (LPARAM) & (CarnetPersona_actual->FechaNacimiento));

		}
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK: {
			wchar_t vueloOrigenVerificacion[256], vueloDestinoVerificacion[256];

			SendMessage(GetDlgItem(handler, IDC_vueloOrigen), WM_GETTEXT, sizeof(vueloOrigenVerificacion) / sizeof(vueloOrigenVerificacion[0]), (LPARAM)vueloOrigenVerificacion);
			SendMessage(GetDlgItem(handler, IDC_vueloDestino), WM_GETTEXT, sizeof(vueloDestinoVerificacion) / sizeof(vueloDestinoVerificacion[0]), (LPARAM)vueloDestinoVerificacion);

			wstring vueloOrigenWstring(vueloOrigenVerificacion);
			wstring vueloDestinoWstring(vueloDestinoVerificacion);

			string vueloOrigen(vueloOrigenWstring.begin(), vueloOrigenWstring.end());
			string vueloDestino(vueloDestinoWstring.begin(), vueloDestinoWstring.end());
			
			if (vueloOrigen == "" || vueloDestino == "") {
				MessageBox(handler, L"No ingreso los datos solicitados", L"Error", MB_ICONERROR);
				return 0;
			}

			else
			{
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
					//SendMessage(GetDlgItem(handler, IDC_asientosDisponibles), WM_GETTEXT, sizeof(vuelosNuevo->vueloAsientos) / sizeof(vuelosNuevo->vueloAsientos[0]), (LPARAM)vuelosNuevo->vueloAsientos);
					vuelosNuevo->vueloTipoAvion = SendDlgItemMessage(handler, IDC_tipoAvion, CB_GETCURSEL, 0, 0);

					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->) / sizeof(vuelosNuevo->[0]), (LPARAM)vuelosNuevo->);

					vuelosAgregar(vuelosNuevo);
					vuelosActualizarLista(handler);

					vueloIdActual++;

					ofstream file;
					file.open(rutaIdVuelo);
					file << vueloIdActual << endl;
					file.close();

					Vuelos* b = vuelosBuscar(0);
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
					//SendMessage(GetDlgItem(handler, IDC_asientosDisponibles), WM_GETTEXT, sizeof(vuelosNuevo->vueloAsientos) / sizeof(vuelosNuevo->vueloAsientos[0]), (LPARAM)vuelosNuevo->vueloAsientos);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->DiaSemana) / sizeof(vuelosNuevo->DiaSemana[0]), (LPARAM)vuelosNuevo->DiaSemana);

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

BOOL CALLBACK ELIMINARVUELO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG: {
		vuelosActualizarLista(handler);
		return 0;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_vuelos, LB_GETCURSEL, NULL, NULL);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay vuelos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			if (MessageBox(handler, L"Esta seguro de querer eliminar el vuelo seleccionado?", L"Eliminando vuelo", MB_OKCANCEL) == IDOK)
			{
				vuelosActual = vuelosBuscar(seleccionado);
				vuelosEliminar(vuelosActual);
				vuelosActualizarLista(handler);
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
		return 0;
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
	case WM_INITDIALOG:
	{
		vuelosActualizarLista(handler);
		return 0;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			//if (HIWORD(wParam) == LBN_SELCHANGE) {	}

			int seleccionado = SendDlgItemMessage(handler, IDC_vuelos, LB_GETCURSEL, NULL, NULL);
			Vuelos* aMostrar = vuelosBuscar(seleccionado);

			if (seleccionado == -1) {
				MessageBox(handler, L"No hay vuelos registrados", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			vuelosActual = vuelosBuscar(seleccionado);
			EndDialog(handler, 0);
			DialogBox(NULL, MAKEINTRESOURCE(IDD_VUELO_REGISTRO), handler, (DLGPROC)REGISTRARVUELO);
			vuelosActualizarLista(handler);
			return 0;

			//return 0;
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
