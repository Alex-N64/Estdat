#pragma once
#include "Estdat.h"


struct Vuelos
{
	wchar_t vueloOrigen[200];
	wchar_t vueloDestino[200];
	wchar_t vueloID[200];
	
	int vueloTipoAvion;
	int vuelosAsientosTurista;
	int vuelosAsientosEjecutivo;
	int vuelosPrecioTurista;
	int vuelosPrecioEjecutivo;

	SYSTEMTIME vueloFechaSalida;
	SYSTEMTIME vueloFechaLlegada;
	SYSTEMTIME vueloHoraSalida;
	SYSTEMTIME vueloHoraLlegada;

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

wstring fechaSalidaString(SYSTEMTIME vueloFechaSalida) {
	//return to_wstring(fechaSalida.wYear) + L"/" + to_wstring(fechaSalida.wMonth) + L"/" + to_wstring(fechaSalida.wDay);
	return to_wstring(vueloFechaSalida.wDay) + L"/" + to_wstring(vueloFechaSalida.wMonth) + L"/" + to_wstring(vueloFechaSalida.wYear);
}

wstring fechaLlegadaString(SYSTEMTIME vueloFechaLlegada) {
	return to_wstring(vueloFechaLlegada.wDay) + L"/" + to_wstring(vueloFechaLlegada.wMonth) + L"/" + to_wstring(vueloFechaLlegada.wYear);
}

wstring horaSalidaString(SYSTEMTIME vueloHoraSalida) {
	return to_wstring(vueloHoraSalida.wHour) + L":" + to_wstring(vueloHoraSalida.wMinute);
}

wstring horaLlegadaString(SYSTEMTIME vueloHoraLlegada) {
	return to_wstring(vueloHoraLlegada.wHour) + L":" + to_wstring(vueloHoraLlegada.wMinute);
}




BOOL CALLBACK REGISTRARVUELO(HWND handler, UINT mensaje, WPARAM wParam, LPARAM lparam) {
	switch (mensaje)
	{
	case WM_INITDIALOG: {
		
		//SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Airbus A380");
		//SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 777");
		//SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 787 Dreamliner");
		//SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Airbus A350");
		//SendDlgItemMessage(handler, IDC_tipoAvion, CB_ADDSTRING, NULL, (LPARAM)L"Boeing 737");

		SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_ADDSTRING, NULL, (LPARAM)L"Airbus A380");
		SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_ADDSTRING, NULL, (LPARAM)L"Boeing 777");
		SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_ADDSTRING, NULL, (LPARAM)L"Boeing 787 Dreamliner");
		SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_ADDSTRING, NULL, (LPARAM)L"Airbus A350");
		SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_ADDSTRING, NULL, (LPARAM)L"Boeing 737");

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
			SendDlgItemMessage(handler, IDC_idVuelo, WM_SETTEXT, NULL, (LPARAM)vuelosActual->vueloID);

			vuelosActual->vueloTipoAvion = SendDlgItemMessage(handler, IDC_tipoAvion, CB_GETCURSEL, 0, 0);
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
					SendMessage(GetDlgItem(handler, IDC_idVuelo), WM_GETTEXT, sizeof(vuelosNuevo->vueloID) / sizeof(vuelosNuevo->vueloID[0]), (LPARAM)vuelosNuevo->vueloID);

					SendDlgItemMessage(handler, IDC_fechaSalida, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloFechaSalida));
					SendDlgItemMessage(handler, IDC_fechaLlegada, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloFechaLlegada));
					SendDlgItemMessage(handler, IDC_horaSalida, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloHoraSalida));
					SendDlgItemMessage(handler, IDC_horaLlegada, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloHoraLlegada));

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
					
					SendDlgItemMessage(handler, IDC_fechaSalida, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloFechaSalida));
					SendDlgItemMessage(handler, IDC_fechaLlegada, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloFechaLlegada));

					SendDlgItemMessage(handler, IDC_horaSalida, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloHoraSalida));
					SendDlgItemMessage(handler, IDC_horaLlegada, DTM_GETSYSTEMTIME, NULL, (LPARAM) & (vuelosNuevo->vueloHoraLlegada));


					SendMessage(GetDlgItem(handler, IDC_idVuelo), WM_GETTEXT, sizeof(vuelosNuevo->vueloID) / sizeof(vuelosNuevo->vueloID[0]), (LPARAM)vuelosNuevo->vueloID);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->DiaSemana) / sizeof(vuelosNuevo->DiaSemana[0]), (LPARAM)vuelosNuevo->DiaSemana);
					//SendMessage(GetDlgItem(handler, IDC_asientosDisponibles), WM_GETTEXT, sizeof(vuelosNuevo->vueloAsientos) / sizeof(vuelosNuevo->vueloAsientos[0]), (LPARAM)vuelosNuevo->vueloAsientos);
					//SendMessage(GetDlgItem(handler, ), WM_GETTEXT, sizeof(vuelosNuevo->DiaSemana) / sizeof(vuelosNuevo->DiaSemana[0]), (LPARAM)vuelosNuevo->DiaSemana);

					vuelosNuevo->vueloTipoAvion = SendDlgItemMessage(handler, IDC_tipoAvion, CB_GETCURSEL, 0, 0);

					EndDialog(handler, 0);
				}
				return 0;
			}
			return 0;
		}

		case IDC_LIST_TIPO_AVION:
		{
			int seleccionado = SendDlgItemMessage(handler, IDC_LIST_TIPO_AVION, LB_GETCURSEL, NULL, NULL);

			if (seleccionado == 0)
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"400");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"80");

				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"$700 USD");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"$3000 USD");
			}

			else if (seleccionado == 1)
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"300");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"50");
				
				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"$600 USD");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"$2500 USD");
			}

			else if (seleccionado == 2)
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"240");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"35");
				
				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"$800 USD");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"$2800 USD");
			}

			else if (seleccionado == 3)
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"300");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"40");
				
				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"$700 USD");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"$3000 USD");
			}

			else if (seleccionado == 4)
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"150");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"16");
				
				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"$200 USD");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"$800 USD");
			}

			else
			{
				SendDlgItemMessage(handler, IDC_ASIENTOS_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"");
				SendDlgItemMessage(handler, IDC_ASIENTOS_EJECUTIVAS, WM_SETTEXT, NULL, (LPARAM)L"");
				SendDlgItemMessage(handler, IDC_PRECIO_TURISTA, WM_SETTEXT, NULL, (LPARAM)L"");
				SendDlgItemMessage(handler, IDC_PRECIO_EJECUTIVO, WM_SETTEXT, NULL, (LPARAM)L"");

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
