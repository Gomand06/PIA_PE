#ifndef utilidades_h
#define utilidades_h
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib> 
#include <ctime>   
#include <unistd.h> 
#include <cstdio> 
#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
using namespace std;
struct Evento {
    char id_zona[10];
    time_t timestamp; 
    float temperatura;
    int status_ventilador; 
    char modo[20]; 
};
struct login{
    char user[10];
    char passwd[10];
};
struct reg_zona{
    char id[10]= "";
    char nomZona[50];
    float umbral;
    int status_ventilador; 
};
extern login usuario;
extern reg_zona zona;
bool verificador_zonas(char ID[]);
void zonas();
void verZonas();
reg_zona seleccionarZona();
void newUser();
bool checkUser();
void verTemp();
void registrarEvento(const char* id, float temp, int status, const char* modo);
void ventilador();
void historial();
void monitoreo();
void menuTem();
time_t construirFecha(int y, int m, int d, bool finDeDia);
bool pedirFecha(const char* etiqueta, time_t &out, bool finDeDia);
void buscarEventos();
void reporteEstadistico();
void exportarCSV();
void menuConsultas();
void Configumbral();
void Restconfig();
void menuConfig();
int mainMenu();
#endif 