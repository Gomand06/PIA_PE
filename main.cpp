#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
//COLORES PARA LA TERMINAL
#define RESET   "\033[0m"
#define ROJO    "\033[31m"
#define VERDE   "\033[32m"
#define AMARILLO "\033[33m"
using namespace std;
//struct de usuarios
struct login{
    char user[10];
    char passwd[10];
}usuario;
//struct de zona
struct reg_zona{
    char id[10]= "";
    string nomZona= "";
    float umbral = 0;
    int status_ventilador = 1;
}zona;
//Funcion para registro de zonas
void zonas(){
    cout<<VERDE<<"Zona nueva"<<RESET<<endl;
    cout<<"Ingrese el ID de la zona: ";
    cin>>zona.id;
    cin.ignore();//Ignora el \n que queda del cin
    cout<<"\nIngresa el nombre de la zona: ";
    getline(cin,zona.nomZona);
    cout<<"Ingrese el umbral al que se activará el ventilador: ";
    cin>>zona.umbral;
}
//funcion para crear usuarios
void newUser(){
    cout<<VERDE<<"NUEVO USUARIO"<<RESET<<endl;
    cout<<"Usuario [10]: "<<endl;
    cin>>usuario.user;
    cout<<"Contraseña [10]: "<<endl;
    cin>>usuario.passwd;
    fstream file("usuarios.dat",ios::binary | ios::app);
    file.write((char*)&usuario, sizeof(usuario));
    file.close();
    cout<<VERDE<<"Usuario creado con exito"<<RESET<<endl;
}
//funcion para checar el usuario
bool checkUser(){
    char userTemp[10],passwdTemp[10];
    cout<<AMARILLO<<"INICIO DE SESIÓN"<<RESET<<endl;
    cout<<"Usuario: ";
    cin>>userTemp;
    cout<<"Contraseña: ";
    cin>>passwdTemp;
    ifstream file("usuarios.dat",ios::binary);
    bool exito=false;
    while(file.read((char*)&usuario, sizeof(usuario))){
        if(strcmp(usuario.user,userTemp)==0 && strcmp(usuario.passwd,passwdTemp)==0){
            exito=true;
            cout<<VERDE<<"Exito al iniciar sesión"<<RESET<<endl;
        }else{
            cout<<ROJO<<"Usuario y contraseña incorrectos."<<RESET<<endl;
        }
    }
    return exito;
}
//menu del programa principal
int mainMenu(){
            /*
            1. Zonas
                a. Registro de Zona
            2. Control de Temperaturas
                a. Ver temperatura actual
                b. Activar ventilador manualmente
                c. Ver historial de eventos
                d. Simular monitoreo en tiempo real
            3. Consultas
                a. Buscar eventos por rango de temperatura o fecha
                b. Generar reporte estadístico 
                c. Exportar historial a archivo csv
            4. Configuración
                a. Configurar umbral de temperatura por zona
                b. Restaurar configuración por defecto por zona
            5. Salir
            */
}
int main(){
    int op=0;
    bool exito=false;
    cout<<AMARILLO<<"SISTEMA DE CONTROL DE TEMPERATURA"<<endl<<RESET;
    do{
        cout<<"MENÚ"<<endl<<"1. Iniciar Sesión\n2. Crear Usuario\n0. Salir";
        cin>>op;
        switch(op){
            case 1:
            {
                exito=checkUser();
                break;
            }
            case 2:
            {
                newUser();
                break;
            }
            case 0:
            {
                cout<<ROJO<<"Saliendo del sistema...\nGracias por usar nuestro programa"<<RESET;
                break;
            }
            default:
            {
                cout<<ROJO<<"Operado incorrecto. Ingrese de nuevo."<<RESET<<endl;
            }
        }
    }while(op!=0 && exito==false);
    cout<<VERDE<<"BIENVENIDO AL SISTEMA DE CONTROL DE TEMPERATURA"<<endl<<RESET;
    do{
        op=mainMenu();
        switch(op){
            /*
            1. Zonas
                a. Registro de Zona
            2. Control de Temperaturas
                a. Ver temperatura actual
                b. Activar ventilador manualmente
                c. Ver historial de eventos
                d. Simular monitoreo en tiempo real
            3. Consultas
                a. Buscar eventos por rango de temperatura o fecha
                b. Generar reporte estadístico 
                c. Exportar historial a archivo csv
            4. Configuración
                a. Configurar umbral de temperatura por zona
                b. Restaurar configuración por defecto por zona
            5. Salir
            */
        }
    }while(op!=0);

}