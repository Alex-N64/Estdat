#pragma once

#include "resource.h"

#include <Windows.h>
#include <iostream>
#include <CommCtrl.h>
#include <shellapi.h>
#include <string>
#include <fstream>

using namespace std;

//::::: ZONA DE OPCIONES :::::
bool loginStatus = false;
bool saveOnExit = true;

//::::::::::::::::::::::::::::

bool adminStatus;

string rutaUsuario = "Estdat/users/";
string rutaDatos = "Estdat/data/";

void usuariosReparar(HWND handler) {
	if (MessageBox(handler, L"Desea reparar los usuarios?", L"Reparar", MB_OKCANCEL) == IDOK)
	{
		ofstream file;
		file.open(rutaUsuario + "admin.txt");
		file << "admin" << endl << "admin" << endl;
		file.close();
		MessageBox(handler, L"El usuario admin a sido recreado", L"Reparar", MB_OK);
	}

	else
	{
		MessageBox(handler, L"false", L"false", MB_OK);
	}

}