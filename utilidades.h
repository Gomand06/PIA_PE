#ifndef utilidades_h
#define utilidades_h
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time() y strftime()
#include <unistd.h> // Para sleep()
#include <cstdio> //para remove y rename
//COLORES PARA LA TERMINAL
#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
using namespace std;
//struct para el historial
struct Evento {
    char id_zona[10];
    time_t timestamp; //para fecha y hora en numeros
    float temperatura;
    int status_ventilador; // 0=OFF, 1=ON
    char modo[20]; // "Auto" o "Manual"
};
//struct de usuarios
struct login{
    char user[10];
    char passwd[10];
};
//struct de zona
struct reg_zona{
    char id[10]= "";
    char nomZona[50];
    float umbral;
    int status_ventilador; //0=off y 1=on
};
extern login usuario;
extern reg_zona zona;

//funciones de Zonas
bool verificador_zonas(char ID[]);
void zonas();
void verZonas();
reg_zona seleccionarZona();

//funciones de Usuario
void newUser();
bool checkUser();

//funciones de Control de Temperatura
void verTemp();
void registrarEvento(const char* id, float temp, int status, const char* modo);
void ventilador();
void historial();
void monitoreo();
void menuTem();

//funciones de Fechas y Búsqueda
time_t construirFecha(int y, int m, int d, bool finDeDia);
bool pedirFecha(const char* etiqueta, time_t &out, bool finDeDia);
void buscarEventos();

//funciones de Consultas y Reportes
void reporteEstadistico();
void exportarCSV();
void menuConsultas();

//funciones de Configuración
void Configumbral();
void Restconfig();
void menuConfig();

//función del Menú Principal
int mainMenu();
#endif 