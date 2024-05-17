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
bool loginStatus = true;
bool saveOnExit = true;

//::::::::::::::::::::::::::::

bool adminStatus;

string rutaUsuario = "Estdat/users/";
string rutaDatos = "Estdat/data/";
string rutaIdVuelo = "Estdat/data/idVuelos.bin";
string rutaRecordarUsuario = "Estdat/data/recordarUsuario.bin";
string rutaBoletosConteo = "Estdat/data/boletos/rutaBoletosConteo.bin";

string rutaListaVuelos = "Estdat/data/ListaVuelos.bin";
string rutaListaPasajeros = "Estdat/data/ListaPasajeros.bin";
string rutaListaBoletos = "Estdat/data/ListaBoletos.bin";

//wchar_t rutaListas[] = L"Estdat/data/Listas.bin";
//wchar_t rutaListasCargar[MAX_PATH] = L"Estdat/data/Listas.bin";


int vueloIdActual;

