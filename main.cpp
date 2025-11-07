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
//struct de zona
struct reg_zona{
    char id[10]= "";
    char nomZona[50];
    float umbral;
    int status_ventilador; //0=off y 1=on
}zona;
//Funcion para registro de zonas
void zonas(){
    reg_zona zona;
    cout<<VERDE<<"Registro de Zona nueva"<<RESET<<endl;
    cout<<"Ingrese el ID de la zona: ";
    cin>>zona.id;
    cin.ignore();//Ignora el \n que queda del cin
    cout<<"\nIngresa el nombre de la zona: ";
    cin.getline(zona.nomZona, 50);    
    cout<<"Ingrese el umbral al que se activará el ventilador: ";
    cin>>zona.umbral;
    zona.status_ventilador=0;

    ofstream file("zonas.dat", ios::binary | ios::app);
    if(!file){
        cout << ROJO << "ERROR: No se pudo abrir el archivo zonas.dat" << RESET << endl;
        return;
    }
    file.write((char*)&zona, sizeof(reg_zona));
    file.close();
    cout << VERDE << "Zona '" << zona.nomZona << "' registrada con exito" << RESET << endl;
}

void verZonas(){
    ifstream file("zonas.dat", ios::binary);
    if (!file){
        cout << ROJO << "ERROR: No se pudo abrir el archivo zonas.dat \nRegistre una zona primero " << RESET << endl;
        return;
    }
    reg_zona zona_temp;
    cout << "\n" << VERDE << "ZONAS REGISTRADAS" << RESET << endl;
    bool encontradas = false;
    while(file.read((char*) &zona_temp, sizeof(reg_zona))){
        encontradas= true;
        cout << "ID: " << AMARILLO << zona_temp.id << RESET << "\nNombre: " << zona_temp.nomZona << "\nUmbral" << zona_temp.umbral << " C" << endl;
    }
    if (!encontradas){
        cout << "No se encontraron zonas registradas" << endl;
    }
    file.close();
}
reg_zona seleccionarZona(){
    verZonas();
    ifstream file("zonas.dat", ios::binary);
    reg_zona zona_temp;
    reg_zona zona_encontrada;
    if (!file){
        return zona_encontrada;
    }
    char id_buscado[10];
    cout << "\n" << AMARILLO << "Ingrese el ID de la zona" << RESET << endl;
    cin >> id_buscado;
    while(file.read((char*)&zona_temp, sizeof(reg_zona))){
        if(strcmp(zona_temp.id, id_buscado)==0){
            zona_encontrada= zona_temp;
            break;
        }
    }
    file.close();
    if(strcmp(zona_encontrada.id, " ")==0){
        cout << ROJO << "ERROR: No se encontro ese ID de zona. " << RESET << endl;
        
    }
    return zona_encontrada;
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