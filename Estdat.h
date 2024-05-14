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

int vueloIdActual;

