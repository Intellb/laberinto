#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include<conio.h>
#include<windows.h>
using namespace std;
using namespace std::chrono;
//VARIABLES GLOBALES
struct Celda{                   //Estructura basica para la generacion del laberinto
    bool visitado=false;    
    bool paredes[4]={true,true,true,true}; //Arriba, derecha, abajo,izquierda
};
Celda celdas[15][15];           //Matriz de struct para la generacion 
char laberinto[31][31];         //Matriz de caracteres para impresion de laberinto
vector<int> recuri, recurj;     //Stacks de posiciones, para backtrack
string nombres[3];              //Vector de nombres correspondientes a puntajes maximos
int max_punt[3];                //Vector de puntajes maximos
//DECLARACION FUNCIONES
void globalreset(int n);        //Devuelve las variables globales a su estado inicial
//Usuario
void jugar();                   //Ejecuta y controla el juego laberinto
void mover_jugador(int &i, int &j, int n, bool &gameover);  //Controla y muestra la posicion del jugador
void puntmaximo(int puntos);    //Inserta el puntaje obtenido de la secion si este se califica dentro de puntaje maximo
//Laberinto
void crearlaberinto(int n);     //Controla la generacion del laberinto bajo el algoritmo de backtraking
bool VecinoVisitados(int i, int j, int n);  //Identifica si una celda tiene vecinos sin visitar
void mover(int &i, int &j, int n);  //Mueve aleatoriamente la posicion a una celda no visitada
//Imprimir Informacion
int menu();                 //Opciones, retorna una opcion valida
void instrucciones();       //Instrucciones para jugar
void max_puntajes();        //Top 3 puntajes de maxpuntajes.txt
void creditos();            //Autores del programa
//Manipulacion de archivos
void leerpuntajes();        //Lee documento y extrae informacion de puntajes maximos
void guardar();             //Guarda puntajes y nombres en un documento
//Manipulacion de terminal
void cursor_coor(int i, int j); //Posiciona el cursor de la termninal en un lugar de la pantalla
    //Tomadas de la documentacion de Windows
void Mostrarcursor(bool bandera);   //Remueve el crusor de la termial
void DimVentana(int Width, int Height);      //Dimensiona la ventana de la terminal
//FUNCION PRINCIPAL
int main(){
    bool go=true;
    int opcion;
    leerpuntajes();
    while(go){
        DimVentana(50,25);
        opcion=menu();
        switch(opcion){
            case 1:
                jugar();
                break;
            case 2:
                max_puntajes();
                break;
            case 3:
                creditos();
                break;
            case 4:
                go=false;
                cout<<"Gracias por jugar";
                break;
            default:
                break;
        }
    }
    return 0;
}
//FUNCIONES
void leerpuntajes(){ 
    string line;
    int i=0, index;
    ifstream puntajes("max_puntajes.txt");
    while (getline (puntajes, line)){
        index=line.find(",");
        nombres[i]=line.substr(index+1,line.size()-index); 
        max_punt[i]=stoi(line.substr(0,index));
        i++;
    }   
    puntajes.close();
}
int menu(){
    int opcion;
    int valido=true;
    system ("CLS");
    cursor_coor(4, 22);cout<<"Menu";
    cursor_coor(6, 5);cout<<"1: Jugar";
    cursor_coor(8, 5);cout<<"2: Puntajes Maximos";
    cursor_coor(10, 5);cout<<"3: Creditos";
    cursor_coor(12, 5);cout<<"4: Salir";
    cursor_coor(14, 5);cout<<"Opcion: ";
    cin>>opcion;
    while(valido){ // Valida inputs de tipo diferente a entero
        while(cin.fail()){
            cin.clear(); 
            cin.ignore(256,'\n');
            cursor_coor(14, 5);cout<<"\e[2K"<<"Ingrese un valor entero\n"; // \e[2K  escape code para borrar linea
            cout<<"\e[2K"<<"    Opcion: ";cin >> opcion;
        }
        if(opcion<0 or opcion>4){
            cursor_coor(14, 5);cout<<"\e[2K"<<"Ingrese una opcion valida\n";
            cout<<"\e[2K"<<"    Opcion: ";cin >> opcion;
        }else{
            valido=false;
        }
    }
    return opcion;
}
void jugar(){
    bool gameover=false;
    int nivel=1, mapsize=10, puntaje=0;
    instrucciones();
    Mostrarcursor(false);
    while (!gameover and nivel<=5){
        int pji=1,pjj=1;
        system("CLS");
        DimVentana(2*(mapsize*2+1),mapsize*2+2);
        if(nivel==5){
            cursor_coor((2*mapsize+1)/2-1,5);cout<<"Ultimo nivel\n";
        }
        cursor_coor((2*mapsize+1)/2,5);cout<<"Nivel: "<<nivel<<"\n\n"; 
        system("Pause");
        crearlaberinto(mapsize);
        cursor_coor((2*mapsize+1)*2,0);cout<<"Puntaje: "<<puntaje;
        auto Tiempo0=steady_clock::now();
        mover_jugador(pji,pjj,mapsize,gameover);
        if(!gameover){
            auto TiempoF=steady_clock::now();
            globalreset(mapsize);
            duration<double> deltaT=TiempoF-Tiempo0;
            puntaje=puntaje+nivel*100-deltaT.count();
            nivel++;
            mapsize++;
        }
    }
    Mostrarcursor(true);
    globalreset(mapsize);
    system("CLS");
    cursor_coor((2*mapsize+1)/2,5);cout<<"Fin de juego\n";
    puntmaximo(puntaje);
    system("Pause");
}
void max_puntajes(){
    system ("CLS");
    cursor_coor(2,17);cout<<"Puntajes Maximos\n";
    cursor_coor(4,3);cout<<"Nombre ";
    cursor_coor(4,34);cout<<"Puntaje "<<endl;
    for(int i=0; i<3; i++){
        cursor_coor(6+i*2,4);cout<<nombres[i]; 
        cursor_coor(6+i*2,35);cout<<max_punt[i];
    }   
    cursor_coor(12,0);system("PAUSE");
}
void creditos(){
    system ("CLS");
    cursor_coor(2,12);cout<<"Fundamentos de programacion";
    cursor_coor(4,13);cout<<"Proyecto Final: Laberinto";
    cursor_coor(6,5);cout<<"Grupo #3:";
    cursor_coor(8,5);cout<<"Burbano Nicolas";
    cursor_coor(10,5);cout<<"Salome Garzon";
    cursor_coor(12,5);cout<<"Feria Danna";
    cursor_coor(14,5);cout<<"Galo Lopez\n\n";
    system("PAUSE");
}
void instrucciones(){
    system ("CLS");
    DimVentana(45,15);
    cout<<"Instrucciones para jugar"<<endl;
    cout<<"Cruza los 5 niveles lo mas rapido posible"<<endl;
    cout<<"Cada nivel aumenta el multiplicador de puntos"<<endl;
    cout<<"Cada segundo RESTA puntaje"<<endl;
    cout<<"I: Jugador"<<endl;
    cout<<"X: Objetivo"<<endl;
    cout<<"#: Paredes"<<endl;
    cout<<"Controles: "<<endl;
    cout<<"w: moverse para arriba"<<endl;
    cout<<"s: moverse para abajo"<<endl;
    cout<<"d: moverse para derecha"<<endl;
    cout<<"a: moverse para izquierda"<<endl;
    cout<<"ESC: Salir"<<endl;
    system("PAUSE");
}
void crearlaberinto(int n){
    int contador=1;
    int pi,pj;  //posicion 
    //Algoritmo de generacion de laberinto backtracking
    srand (time(NULL));
    pi=rand()%n;
    pj=rand()%n;
    celdas[pi][pj].visitado=true;
    while(contador<n*n){
        if(!VecinoVisitados(pi,pj,n)){
            mover(pi,pj,n);
            contador++;                
        }else{
            pi=recuri.back();
            pj=recurj.back();
            recurj.pop_back();
            recuri.pop_back();
        }
    }
    //Matriz todo pared
    for(int i=0; i<2*n+1; i++){
        for(int j=0; j<2*n+1; j++){
            laberinto[i][j]='#';
        }
    }
    //Remueve paredes
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            laberinto[2*i+1][2*j+1]=' ';
            for (int k=0; k<4;k++){
                if(celdas[i][j].paredes[k]==false){
                    switch (k){
                        case 0:
                            laberinto[2*i][2*j+1]=' ';
                            break;
                        case 1:
                            laberinto[1+2*i][2+2*j]=' ';
                            break;
                        case 2:
                            laberinto[2+2*i][2*j+1]=' ';
                            break;
                        case 3:
                            laberinto[1+2*i][2*j]=' ';
                            break;    
                    }
                }
            }
        }
    }
    //Posicion Inicial
    laberinto[1][1]='I';
    //Posicion Final
    laberinto[2*n-1][2*n-1]='X';
    //Imprimir laberinto
    system("cls");
    for(int i=0; i<2*n+1; i++){
        for(int j=0; j<2*n+1; j++){
            cout<<laberinto[i][j]<<" ";
        }
        cout<<endl;
    }
} 
bool VecinoVisitados(int i, int j, int n){
    int mov[]={1,1,1,1};
    if(i-1<0) mov[0]=0;
    if(j+1==n) mov[1]=0;
    if(i+1==n) mov[2]=0;
    if(j-1<0) mov[3]=0;
    return celdas[i-mov[0]][j].visitado and celdas[i][j+mov[1]].visitado and celdas[i+mov[2]][j].visitado and celdas[i][j-mov[3]].visitado;  
                    //arriba                          derecha                          abajo                 izquierda
}
void mover(int &i, int &j,int n){
    int mov;
    bool cambiocelda=false;;
    while (!cambiocelda){
        mov=rand()%4;
        switch (mov){
            case 0:
                if(i-1>=0){//Arriba
                    if(celdas[i-1][j].visitado==false){
                        celdas[i][j].paredes[0]=false;
                        celdas[i-1][j].paredes[2]=false;
                        celdas[i-1][j].visitado=true;
                        cambiocelda=true;
                        i--;
                    }
                }
                break;
            case 1:
                if(j+1<n){//Derecha
                    if(celdas[i][j+1].visitado==false){
                        celdas[i][j].paredes[1]=false;
                        celdas[i][j+1].paredes[3]=false;
                        celdas[i][j+1].visitado=true;
                        cambiocelda=true;
                        j++;
                    }
                }
                break;
            case 2:
                if(i+1<n){//Abajo
                    if(celdas[i+1][j].visitado==false){
                        celdas[i][j].paredes[2]=false;
                        celdas[i+1][j].paredes[0]=false;
                        celdas[i+1][j].visitado=true;
                        cambiocelda=true;
                        i++;
                    }
                }
                break;
            case 3:
                if(j-1>=0){//Izquierda
                    if(celdas[i][j-1].visitado==false){
                        celdas[i][j].paredes[3]=false;
                        celdas[i][j-1].paredes[1]=false;
                        celdas[i][j-1].visitado=true;
                        cambiocelda=true;
                        j--;
                    }
                }
                break;
        }
    }
    recuri.push_back(i); recurj.push_back(j);
}
void mover_jugador(int &i, int &j, int n, bool &gameover){
    char input;
    while((i!=2*n-1 or j!=2*n-1) and !gameover){    
        input=getch();
        switch (input){
            case 'w' ://Arriba
                if(laberinto[i-1][j]!='#'){
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    i--;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 'd' :
                if(laberinto[i][j+1]!='#'){ //derecha
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    j++;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 's':
                if(laberinto[i+1][j]!='#'){//abajo
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    i++;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 'a':
                if(laberinto[i][j-1]!='#'){//izquierda
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    j--;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case '\e': //salir del juego
                gameover=true;
                break;
        }   
    }
}
void globalreset(int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            celdas[i][j].visitado=false;
            for (int k=0; k<4;k++){
                celdas[i][j].paredes[k]=true;
            }
         }
    }
    recuri.clear();
    recurj.clear();
}
void puntmaximo(int puntos){
    int holder;
    string nombre;
    for(int i=0;i<3;i++){
        if(puntos>max_punt[i]){
            cout<<"Felicitaciones Puntaje Alto Obtenido"<<endl;
            cout<<"Ingrese su nickname: ";
            cin>>nombre;
            for(int j=2;j>i;j--){
                max_punt[j]=max_punt[j-1];
                nombres[j]=nombres[j-1];
            }
            max_punt[i]=puntos;
            nombres[i]=nombre;
            break;
        }
    }
    guardar();
}
void guardar(){
    ofstream puntajes("max_puntajes.txt");
    for(int i=0;i<3;i++){
        puntajes<<max_punt[i]<<","<<nombres[i]<<endl;
    }
    puntajes.close();
}
void cursor_coor(int i, int j){
    printf("\e[%d;%df",i,j); //Codigo ESC para el posicionamiento de cursor en la terminal
}
//Funciones a continuacion tomadas de la documentacion de microsoft Windows, https://docs.microsoft.com/en-us/.
void Mostrarcursor(bool bandera){
        HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = bandera; 
        SetConsoleCursorInfo(out, &cursorInfo);
}  
void DimVentana(int Width, int Height){ 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);     
    SetConsoleScreenBufferSize(Handle, coord); 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
} 