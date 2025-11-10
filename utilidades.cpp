#include "utilidades.h"
login usuario;
reg_zona zona;
bool verificador_zonas(char ID[]){
    reg_zona z;
    ifstream file("zonas.dat",ios::binary);
    if(!file){
        ofstream crear("zonas.dat",ios::binary);
        cout<<ROJO<<"No se pudo abrir el archivo, intenta de nuevo: "<<RESET<<endl;
        crear.close();
        return false;
    }
    while (file.read((char*)(&z), sizeof(reg_zona))){
        if(strcmp(z.id,ID)==0){
            file.close();
            cout<<ROJO<<"Este id ya fue usado previamente, ingrese un id nuevo: "<<RESET<<endl;
            return false;
        }
    }
    file.close();
    return true;
}
void zonas(){
    bool res=false;
    reg_zona zona{};
    do{
        cout<<VERDE<<"Registro de Zona nueva"<<RESET<<endl;
        cout<<"Ingrese el ID de la zona: ";
        cin>>zona.id;
        res=verificador_zonas(zona.id);
    }while(!res);    
    cin.ignore();
    cout<<"\nIngresa el nombre de la zona: ";
    cin.getline(zona.nomZona, 50);    
    cout<<"Ingrese el umbral al que se activara el ventilador: ";
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
void newUser(){
    cout<<VERDE<<"NUEVO USUARIO"<<RESET<<endl;
    cout<<"Usuario [10]: "<<endl;
    cin>>usuario.user;
    cout<<"Contrasena [10]: "<<endl;
    cin>>usuario.passwd;
    fstream file("usuarios.dat",ios::binary | ios::app);
    file.write((char*)&usuario, sizeof(usuario));
    file.close();
    cout<<VERDE<<"Usuario creado con exito"<<RESET<<endl;
}
bool checkUser(){
    char userTemp[10],passwdTemp[10];
    cout<<AMARILLO<<"INICIO DE SESION"<<RESET<<endl;
    cout<<"Usuario: ";
    cin>>userTemp;
    cout<<"Contrasena: ";
    cin>>passwdTemp;
    ifstream file("usuarios.dat",ios::binary);
    bool exito=false;
    while(file.read((char*)&usuario, sizeof(usuario))){
        if(strcmp(usuario.user,userTemp)==0 && strcmp(usuario.passwd,passwdTemp)==0){
            exito=true;
            cout<<VERDE<<"Exito al iniciar sesion\n"<<RESET<<endl;
            break;
        } 
    }
    if(!exito){
            cout<<ROJO<<"Usuario y contrasena incorrectos."<<RESET<<endl;
        }
    return exito;
}
void verTemp(){
    ifstream file("zonas.dat", ios::binary);
    if (!file){
        cout << ROJO << "ERROR: No se pudo abrir el archivo zonas.dat. \nRegistre una zona primero " << RESET << endl;
        return;
    }
    reg_zona zona_temp;
    cout << "\n" << VERDE << "MONITOR DE TEMPERATURA ACTUAL" << RESET << endl;
    bool encontradas = false;
    while(file.read((char*) &zona_temp, sizeof(reg_zona))){
        encontradas = true;
        float temp_actual = 20.0 + (rand() % 150) / 10.0; 
        cout << "------------------------------------" << endl;
        cout << "Zona: " << AMARILLO << zona_temp.nomZona << RESET << " (ID: " << zona_temp.id << ")" << endl;
        cout << "Temperatura actual: " << temp_actual << " °C" << endl;
        if(temp_actual > zona_temp.umbral) {
            cout << "Estado del ventilador: " << VERDE << "ACTIVADO (automatico)" << RESET << endl;
        } else {
            cout << "Estado del ventilador: " << ROJO << "OFF (automatico)" << RESET << endl;
        }
    }
    if (!encontradas){
        cout << "No se encontraron zonas registradas" << endl;
    }
    file.close();
}
void registrarEvento(const char* id, float temp, int status, const char* modo) {
    ofstream file("eventos.dat", ios::binary | ios::app);
    if (!file) {
        cout << ROJO << "ERROR: No se pudo abrir el archivo de eventos." << RESET << endl;
        return;
    }
    Evento ev;
    strcpy(ev.id_zona, id);
    ev.timestamp = time(NULL);
    ev.temperatura = temp;
    ev.status_ventilador = status;
    strcpy(ev.modo, modo);

    file.write((char*)&ev, sizeof(Evento));
    file.close();
}
time_t construirFecha(int y, int m, int d, bool finDeDia){
    tm t{};
    t.tm_year = y-1900;
    t.tm_mon  = m - 1;
    t.tm_mday = d;
    t.tm_hour = finDeDia ? 23 : 0;
    t.tm_min  = finDeDia ? 59 : 0;
    t.tm_sec  = finDeDia ? 59 : 0;
    return mktime(&t);
}
bool pedirFecha(const char* etiqueta, time_t &out, bool finDeDia){
    int y,m,d;
    cout << etiqueta << " (AAAA MM DD): ";
    if(!(cin >> y >> m >> d)){
        cout << ROJO << "Entrada invalida." << RESET << endl;
        cin.clear(); cin.ignore(10000, '\n');
        return false;
    }
    out = construirFecha(y,m,d,finDeDia);
    return true;
}
void buscarEventos(){
    cout << "\n" << VERDE << "CONSULTA: BUSCAR EVENTOS" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if (zona_sel.id[0] == '\0') {
        cout << ROJO << "Operacion cancelada. No se selecciono una zona valida." << RESET << endl;
        return;
    }
    cout << "\nSeleccione tipo de filtro:\n";
    cout << "1. Por Rango de Temperatura\n";
    cout << "2. Por Rango de Fechas\n";
    cout << "0. Cancelar\n";
    int op; 
    cin >> op;
    ifstream f("eventos.dat", ios::binary);
    if(!f){
        cout << ROJO << "ERROR: No se pudo abrir eventos.dat." << RESET << endl;
        return;
    }
    bool encontrados = false;
    Evento e;
    char time_buffer[100];
    switch(op){
        case 0:
            cout << "Operacion cancelada." << endl;
            f.close();
            return;
        case 1: {
            float tmin, tmax;
            cout << "Temperatura minima: "; cin >> tmin;
            cout << "Temperatura maxima: "; cin >> tmax;
            cout << "\n" << AMARILLO << "Resultados (filtro por temperatura)" << RESET << endl;
            while(f.read((char*)&e, sizeof(Evento))){
                if(strcmp(e.id_zona, zona_sel.id)==0){
                    if(e.temperatura >= 0.0f && e.temperatura >= tmin && e.temperatura <= tmax){
                        tm* ptm = localtime(&e.timestamp);
                        strftime(time_buffer, 100, "[%H:%M:%S]", ptm);
                        cout << AMARILLO << time_buffer << RESET
                             << " Temperatura: " << e.temperatura << " °C"
                             << "  Ventilador: " << (e.status_ventilador==1? VERDE "ON" : ROJO "OFF") << RESET
                             << " (" << e.modo << ")" << endl;
                        encontrados = true;
                    }
                }
            }
            break;
        }
        case 2: {
            time_t desde, hasta;
            if(!pedirFecha("Desde", desde, false)) { f.close(); return; }
            if(!pedirFecha("Hasta", hasta, true))  { f.close(); return; }
            if(difftime(hasta, desde) < 0){
                cout << ROJO << "Rango de fechas invalido." << RESET << endl;
                f.close(); 
                return;
            }
            cout << "\n" << AMARILLO << "Resultados (filtro por fecha)" << RESET << endl;
            while(f.read((char*)&e, sizeof(Evento))){
                if(strcmp(e.id_zona, zona_sel.id)==0){
                    if(e.timestamp >= desde && e.timestamp <= hasta){
                        tm* ptm = localtime(&e.timestamp);
                        strftime(time_buffer, 100, "[%H:%M:%S]", ptm);
                        cout << AMARILLO << time_buffer << RESET;
                        if(strcmp(e.modo,"Auto")==0 && e.temperatura>=0.0f){
                            cout << " Temperatura: " << e.temperatura << " °C";
                        }
                        cout << "  Ventilador: " << (e.status_ventilador==1? VERDE "ON" : ROJO "OFF") << RESET
                             << " (" << e.modo << ")" << endl;
                        encontrados = true;
                    }
                }
            }
            break;
        }
        default:
            cout << ROJO << "Opcion invalida." << RESET << endl;
            break;
    }
    if(!encontrados && op != 0){
        cout << "No se encontraron eventos que cumplan el criterio." << endl;
    }
    f.close();
}
void reporteEstadistico(){
    cout << "\n"<<VERDE<<"CONSULTA: REPORTE ESTADISTICO"<<RESET<<endl;
    ifstream fz("zonas.dat", ios::binary);
    if(!fz){
        cout<<ROJO<<"ERROR: No se pudo abrir zonas.dat"<<RESET<<endl;
        return;
    }
        reg_zona z;
    bool hayZonas = false;
    bool initMax=false, initMin=false;
    float globalMax = 0, globalMin = 0, globalProm = 0;
    char idMax[10]="", idMin[10]="", idProm[10]="";
    while(fz.read((char*)&z, sizeof(reg_zona))){
        hayZonas = true;

        ifstream fe("eventos.dat", ios::binary);
        if(!fe){
            cout << ROJO << "ERROR: No se pudo abrir eventos.dat." << RESET << endl;
            fz.close();
            return;
        }
        float maxT = -1e9f, minT =  1e9f, sumT = 0.0f;
        long  cnt  = 0;
        Evento e;
        while(fe.read((char*)&e, sizeof(Evento))){
            if(strcmp(e.id_zona, z.id)==0){
                if(strcmp(e.modo,"Auto")==0 && e.temperatura >= 0.0f){
                    if(e.temperatura > maxT) maxT = e.temperatura;
                    if(e.temperatura < minT) minT = e.temperatura;
                    sumT += e.temperatura;
                    cnt++;
                }
            }
        }
        fe.close();
        cout << "\nZona: " << AMARILLO << z.nomZona << RESET << " (ID: " << z.id << ")\n";
        if(cnt==0){
            cout << ROJO << "Sin datos automaticos para estadisticas." << RESET << endl;
        } else {
            float prom = sumT / (float)cnt;
            cout << "Temperatura Maxima: " << maxT << " °C\n";
            cout << "Temperatura Minima: " << minT << " °C\n";
            cout << "Promedio: " << prom << " °C\n";
            if(!initMax || maxT > globalMax){ globalMax = maxT; strcpy(idMax, z.id); initMax = true; }
            if(!initMin || minT < globalMin){ globalMin = minT; strcpy(idMin, z.id); initMin = true; }
            if(prom > globalProm){ globalProm = prom; strcpy(idProm, z.id); }
        }
    }
    fz.close();
    if(!hayZonas){
        cout << ROJO << "No hay zonas registradas." << RESET << endl;
        return;
    }
    cout << "\n" << VERDE << "RESUMEN GLOBAL" << RESET << endl;
    if(!(initMax && initMin)){
        cout << ROJO << "No hay suficientes datos para consolidado." << RESET << endl;
    } else {
        cout << "Zona con Temperatura Maxima: " << AMARILLO << idMax << RESET << " (" << globalMax << " °C)\n";
        cout << "Zona con Temperatura Minima: " << AMARILLO << idMin << RESET << " (" << globalMin << " °C)\n";
        cout << "Zona con Mejor Promedio: "    << AMARILLO << idProm << RESET << " (" << globalProm << " °C)\n";
    }
}
void exportarCSV(){
    cout << "\n" << VERDE << "CONSULTA: EXPORTAR HISTORIAL A CSV" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if (zona_sel.id[0] == '\0') {
        cout << ROJO << "Operacion cancelada. No se selecciono una zona valida." << RESET << endl;
        return;
    }
    ifstream fe("eventos.dat", ios::binary);
    if(!fe){
        cout << ROJO << "ERROR: No se pudo abrir eventos.dat." << RESET << endl;
        return;
    }
    char nombreCSV[64];
    snprintf(nombreCSV, sizeof(nombreCSV), "historial_%s.csv", zona_sel.id);

    ofstream out(nombreCSV);
    if(!out){
        cout << ROJO << "ERROR: No se pudo crear el archivo CSV." << RESET << endl;
        fe.close(); return;
    }

    out << "id_zona,fecha,hora,temperatura,estado,modo\n";
    Evento e;
    char fecha[16], hora[16];
    bool alguno=false;

    while(fe.read((char*)&e, sizeof(Evento))){
        if(strcmp(e.id_zona, zona_sel.id)==0){
            tm* ptm = localtime(&e.timestamp);
            strftime(fecha, sizeof(fecha), "%Y-%m-%d", ptm);
            strftime(hora,  sizeof(hora),  "%H:%M:%S", ptm);
            out << e.id_zona << "," 
                << fecha << "," << hora << ",";
            if(e.temperatura >= 0.0f) out << e.temperatura;
            else                      out << ""; 
            out << "," << (e.status_ventilador==1 ? "ON" : "OFF") << "," << e.modo << "\n";
            alguno = true;
        }
    }
    fe.close(); out.close();

    if(alguno){
        cout << VERDE << "Exportacion exitosa: " << nombreCSV << RESET << endl;
    } else {
        cout << ROJO << "No hay eventos para la zona seleccionada. CSV vacio no generado." << RESET << endl;
        remove(nombreCSV);
    }
}
void menuConsultas(){
    int op=0;
    do{
        cout << "\n" << AMARILLO << "CONSULTAS" << RESET << endl;
        cout << "1. Buscar eventos (rango temperatura/fecha)" << endl;
        cout << "2. Generar reporte estadistico" << endl;
        cout << "3. Exportar historial a CSV" << endl;
        cout << "4. Volver al menu" << endl;
        cin >> op;

        switch(op){
            case 1: buscarEventos();       break;
            case 2: reporteEstadistico();  break;
            case 3: exportarCSV();         break;
            case 4: cout << "Volviendo..." << endl; break;
            default: cout << ROJO << "Opcion invalida" << RESET << endl; break;
        }
    } while(op!=4);
}
void ventilador(){
    cout << "\n" << VERDE << "ACTIVAR VENTILADOR MANUALMENTE" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if (zona_sel.id[0] == '\0') {
         cout << ROJO << "Operacion cancelada. No se selecciono una zona valida." << RESET << endl;
        return;
    }
    cout << "Selecciono la zona: " << AMARILLO << zona_sel.nomZona << RESET << endl;
    cout << "Estado actual: " << (zona_sel.status_ventilador == 1 ? "ENCENDIDO" : "APAGADO") << endl;
    cout << "Seleccione accion:" << endl;
    cout << "1. Encender ventilador" << endl;
    cout << "2. Apagar ventilador" << endl;
    cout << "0. Cancelar" << endl;
    int op;
    cin >> op;
    int nuevo_estado = -1;
    switch(op){
        case 1:
            nuevo_estado = 1; 
            cout << "-> " << VERDE << "Ventilador encendido manualmente." << RESET << endl;
            break;
        case 2:
            nuevo_estado = 0; 
            cout << "-> " << ROJO << "Ventilador apagado manualmente." << RESET << endl;
            break;
        case 0:
            cout << "Operacion cancelada." << endl;
            return;
        default:
            cout << ROJO << "Opcion invalida." << RESET << endl;
            return;
    }
    fstream file("zonas.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << ROJO << "ERROR: No se pudo abrir 'zonas.dat' para actualizar." << RESET << endl;
        return;
    }
    reg_zona zona_temp;
    while(file.read((char*) &zona_temp, sizeof(reg_zona))){
        if(strcmp(zona_temp.id, zona_sel.id) == 0){
            zona_temp.status_ventilador = nuevo_estado;
            long pos = (long)file.tellg() - sizeof(reg_zona);
            file.seekp(pos);
            file.write((char*)&zona_temp, sizeof(reg_zona));
            cout << VERDE << "Estado de la zona actualizado." << RESET << endl;
            break;
        }
    }
    file.close();
    registrarEvento(zona_sel.id, -1.0, nuevo_estado, "Manual");
}
void historial(){
    cout << "\n" << VERDE << "HISTORIAL DE EVENTOS" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if (zona_sel.id[0] == '\0') {
        cout << ROJO << "Operacion cancelada. No se selecciono una zona valida." << RESET << endl;
        return;
    }
    cout << "Mostrando historial para: " << AMARILLO << zona_sel.nomZona << RESET << endl;
    ifstream file("eventos.dat", ios::binary);
    if (!file){
        cout << ROJO << "ERROR: No se pudo abrir el archivo eventos.dat." << RESET << endl;
        cout << "Aún no se ha registrado ningún evento." << endl;
        return;
    }
    Evento ev;
    bool encontradas = false;
    char time_buffer[100];
    while(file.read((char*)&ev, sizeof(Evento))){
        if(strcmp(ev.id_zona, zona_sel.id) == 0){
            encontradas = true;
            tm* ptm = localtime(&ev.timestamp);
            strftime(time_buffer, 100, "[%H:%M:%S]", ptm);
            cout << AMARILLO << time_buffer << RESET;
            if (strcmp(ev.modo, "Auto") == 0) {
                 cout << " Temperatura: " << ev.temperatura << " °C";
            }
            cout << " Ventilador: " << (ev.status_ventilador == 1 ? VERDE "ON" : ROJO "OFF") << RESET;
            cout << " (" << ev.modo << ")" << endl;
        }
    }
    if (!encontradas){
        cout << "No se encontraron eventos para esta zona." << endl;
    }
    file.close();
}
void monitoreo(){
    cout << "\n" << VERDE << "SIMULAR MONITOREO EN TIEMPO REAL" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if (zona_sel.id[0] == '\0') {
        cout << ROJO << "Operacion cancelada. No se selecciono una zona valida." << RESET << endl;
        return;
    }
    int ciclos, segundos;
    cout << "Ingrese el número de ciclos (lecturas) a simular: ";
    cin >> ciclos;
    cout << "Ingrese los segundos de espera entre ciclos: ";
    cin >> segundos;
    if (ciclos <= 0 || segundos <= 0) {
        cout << ROJO << "Valores invalidos. Deben ser números positivos." << RESET << endl;
        return;
    }
    cout << "\n" << AMARILLO << "Iniciando simulacion para " << zona_sel.nomZona << "..." << RESET << endl;
    cout << "Umbral de la zona: " << zona_sel.umbral << " °C" << endl;

    for (int i = 0; i < ciclos; i++) {
        float temp_actual = 20.0 + (rand() % 150) / 10.0;
        int nuevo_estado = (temp_actual > zona_sel.umbral) ? 1 : 0;
        time_t t_actual = time(NULL);
        char time_buffer[100];
        tm* ptm = localtime(&t_actual);
        strftime(time_buffer, 100, "[%H:%M:%S]", ptm);
        cout << AMARILLO << time_buffer << RESET 
             << " Temperatura: " << temp_actual << " °C"
             << "\tVentilador: " << (nuevo_estado == 1 ? VERDE "ON" : ROJO "OFF") << RESET << endl;
        registrarEvento(zona_sel.id, temp_actual, nuevo_estado, "Auto");
        sleep(segundos);
    }
    cout << VERDE << "Simulacion finalizada." << RESET << endl;
}
void menuTem(){
    int op=0;
    do{
        cout << "\n" << AMARILLO << "CONTROL DE TEMPERATURAS" << RESET << endl;
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
    } while (op!=5);
}
void Configumbral(){
    cout << "\n" << VERDE << "CONFIGURAR UMBRAL DE TEMPERATURA POR ZONA" << RESET << endl;
    reg_zona zona_sel = seleccionarZona();
    if(zona_sel.id[0]== '\0'){
        cout << ROJO << "No se selecciono una zona valida." << RESET << endl;
        return;
    }
    cout << "Zona Seleccionada: " << AMARILLO << zona_sel.nomZona << RESET << endl;
    cout << "Umbral actual: " << zona_sel.umbral << " C" << endl;
    float newumbral;
    cout << "Ingrese nuevo umbral: ";
    cin >> newumbral;
    if(newumbral<=0){
        cout << ROJO << "INVALIDO. El umbral debe ser positivo." << RESET << endl;
        return;
    }
    fstream file("zonas.dat", ios::in | ios::out | ios::binary);
    if (!file){
        cout << ROJO << "ERROR: No se pudo abrir 'zonas.dat' para actualizar." << RESET << endl;
        return; 
    }
    reg_zona zona_temp;
    bool actualizado=false;
    while(file.read((char*) &zona_temp, sizeof(reg_zona))){
        if(strcmp(zona_temp.id, zona_sel.id)==0){
            zona_temp.umbral=newumbral;
            long posicion = (long)file.tellg()-sizeof(reg_zona);
            file.seekp(posicion);
            file.write((char*) &zona_temp, sizeof(reg_zona));
            actualizado=true;
            break;
        }
    }
    file.close();
    if(actualizado){
        cout << VERDE << "Umbral actualizado correctamente. " << RESET << endl;
    } else {
        cout << ROJO << "ERROR. No se pudo actualizar el registro." << RESET << endl;
    }
}
void Restconfig(){
    cout << "\n" << AMARILLO <<"RESTAURAR CONFIGURACION POR DEFECTO POR ZONA" << RESET << endl;
    const float umbralxdefecto= 30.0;
    reg_zona zona_sel=seleccionarZona();
    if(zona_sel.id[0]== '\0'){
        cout << ROJO << "No se selecciono una zona valida." << RESET << endl;
        return;
    }
    char confirm;
    cout << AMARILLO << "¿Desea restaurar el umbral y limpiar historial para '" << zona_sel.nomZona << "'? (S/N): " << RESET;
    cin >> confirm;

    if (confirm != 'S' && confirm != 's') {
        cout << "Operacion cancelada." << endl;
        return;
    }
    bool umbral_ok=false;
    fstream file_zona("zonas.dat", ios::in | ios::out | ios::binary);
    if (file_zona){
        reg_zona zona_temp;
        while(file_zona.read((char*) &zona_temp, sizeof(reg_zona))){
            if(strcmp(zona_temp.id, zona_sel.id)== 0){
                zona_temp.umbral=umbralxdefecto;
                long posicion=(long)file_zona.tellg()-sizeof(reg_zona);
                file_zona.seekp(posicion);
                file_zona.write((char*) &zona_temp, sizeof(reg_zona));
                umbral_ok=true;
                break;
            }
        }
        file_zona.close();
    }
    if(!umbral_ok){
        cout << ROJO << "ERROR. No se pudo actualizar el umbral en 'zonas.dat'." << RESET << endl;
    }
    ifstream fe_in("eventos.dat", ios::binary);
    ofstream fe_out("eventos.tmp", ios::binary | ios::trunc);
    if(!fe_in || !fe_out){
        cout << ROJO << "ERROR. No se pudieron abrir los archivos de eventos para limpirarlos" << RESET << endl;
        if (fe_in) fe_in.close();
        if (fe_out) fe_out.close();
        return;
    }
    Evento e;
    bool historial_ok=true;
    while(fe_in.read((char*)&e, sizeof(Evento))){
        if(strcmp(e.id_zona, zona_sel.id)!=0){
            fe_out.write((char*)&e, sizeof(Evento));
        }
    }
    fe_in.close();
    fe_out.close();
    if (remove("eventos.dat")!=0){
        cout << ROJO << "ERROR: No se pudo eliminar 'eventos.dat'. " << RESET << endl;
        historial_ok=false;
    } else if (rename("eventos.tmp", "eventos.dat") != 0){
        cout << ROJO << "ERROR: No se pudo renombrar 'eventos.tmp'." << RESET << endl;
        historial_ok=false;
    }
    if(umbral_ok && historial_ok){
        cout << VERDE << "->Configuracion restaurada. Umbral: " << umbralxdefecto << " C. Historial borrado. " << RESET << endl;
    } else {
        cout << ROJO << "La operacion finalizo con errores. " << RESET << endl;
    }
}
void menuConfig(){
    int op;
    do{
    cout <<  "\n" << AMARILLO << "Configuracion" << RESET << endl;
    cout << "1. Configurar umbral de temperatura por zona " << endl;
    cout << "2. Restaurar configuracion por defecto por zona " << endl;
    cout << "3. Volver al menu " << endl;
    cin >> op;
        switch (op){
            case 1: Configumbral();
                break;
            case 2: Restconfig();
                break;
            case 3:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << ROJO << "Opcion invalida" << RESET << endl;
                break;

        }
    }while (op!=3);
}
int mainMenu(){
    int op;
    cout << "\n" << AMARILLO << " MENU PRINCIPAL " << RESET << endl;
    cout << "1. Zonas" << endl;
    cout << "2. Control de Temperaturas" << endl;
    cout << "3. Consultas" << endl;
    cout << "4. Configuracion" << endl;
    cout << "5. Salir" << endl;
    cin >> op;
    return op;
}
