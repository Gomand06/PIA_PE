// Christopher Gómez Andrade 2225437 | Mónica Guadalupe Torres Lazaro 2118346 | Santiago Elías Chaparro 2225342
#include "utilidades.h"
int main(){
    int op=0;
    bool exito=false;
    cout<<AMARILLO<<"SISTEMA DE CONTROL DE TEMPERATURA"<<endl<<RESET;
    do{
        cout<<"MENU"<<endl<<"1. Iniciar Sesion\n2. Crear Usuario\n0. Salir\n";
        cin>>op;
        switch(op){
            case 1:{
                exito=checkUser();
                break;
            }
            case 2:{
                newUser();
                break;
            }
            case 0:{
                cout<<ROJO<<"Saliendo del sistema...\nGracias por usar nuestro programa"<<RESET;
                return 0;
                break;
            }
            default:{
                cout<<ROJO<<"Operado incorrecto. Ingrese de nuevo."<<RESET<<endl;
            }
        }
    }while(op!=0 && exito==false);
    srand(time(NULL));
    cout<<VERDE<<"BIENVENIDO AL SISTEMA DE CONTROL DE TEMPERATURA"<<endl<<RESET;
    do{
        op=mainMenu();
        switch(op){
            case 1:{
                zonas();
                break;
            }
            case 2:{
                menuTem();
                break;
            }
            case 3:{
                menuConsultas();
                break;
            }
            case 4:{
                menuConfig();
                break;
            }
            case 5:{
                cout<<ROJO<<"Cerrando sesión...\n"<<RESET;
                return 0;
                break;
            }
        }
    }while(op!=0);
}