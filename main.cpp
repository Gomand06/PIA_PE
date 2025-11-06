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

//funciones para control de temperaturas
void verTemp(){
    
}

void ventilador(){

}
void historial(){

}

void monitoreo(){}



//menu para Control de Temperaturas
void menuTem(){
    int op=0;
    do{
        cout << "\nCONTROL DE TEMPERATURAS" << endl;
        cout << "1. Ver temperatura actual" << endl;
        cout << "2. Activar ventilador manualmente" << endl;
        cout << "3. Ver historial de eventos" << endl;
        cout << "4. Simular monitoreo en tiempo real" << endl;
        cout << "5. Volver al menu" << endl;
        cin >> op;
        switch (op) {
            case 1: {
                verTemp();
                break;
            }
            case 2: {
                ventilador();
            break;
            } 
            case 3:{
                historial();
            break;
            }
            case 4: {
                monitoreo();
            break;
            }
            case 5:{
                cout << "Volviendo al menu principal... " << endl;
            break;
            }
            default:
                cout << ROJO << "Opcion invalida" << RESET << endl;
                break;
        } 
    } while (op!=0);
}

//menu del programa principal YAP
int mainMenu(){
    int op;
    cout << "\n" << " MENU PRINCIPAL " << endl;
    cout << "1. Zonas" << endl;
    cout << "2. Control de Temperaturas" << endl;
    cout << "3. Consultas" << endl;
    cout << "4. Configuración" << endl;
    cout << "5. Salir" << endl;
    cin >> op;
    return op;

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
            
        }
    }while(op!=0);

}