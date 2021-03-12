#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<chrono>
#include <time.h>  
#include<conio.h>
using namespace std;
//VARIABLES GLOBALES
struct Celda{
    bool visitado=false;
    bool paredes[4]={true,true,true,true};
};
Celda celdas[30][30];
char laberinto[61][61];
vector<int> recuri, recurj;
string nombres[3];
int max_punt[3];

//Declaracion Funciones
int menu();
void instrucciones();
void jugar();
void max_puntajes();
void creditos();




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



int main(){
    bool go=true;
    int opcion;
    leerpuntajes();
    while(go){
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
void cursor_coor(int i, int j){
    printf("\e[%d;%df",i,j);
}


int menu(){
    int opcion;
    int valido=true;
    system ("CLS");
    cout<<"Menu"<<endl;
    cout<<"1: Jugar"<<endl;
    cout<<"2: Puntajes Maximos"<<endl;
    cout<<"3: Creditos"<<endl;
    cout<<"4: Salir"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    while(valido){
        while(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
            cursor_coor(6, 0);cout<<"\e[2K"<<"Ingrese un valor entero\n"; // \e[2K  escape code para borrar linea
            cout<<"\e[2K"<<"Opcion: ";cin >> opcion;
        }
        if(opcion<0 or opcion>4){
            cursor_coor(6, 0);cout<<"\e[2K"<<"Ingrese una opcion valida\n";
            cout<<"\e[2K"<<"Opcion: ";cin >> opcion;
        }else{
            valido=false;
        }
    }
    return opcion;
}


void instrucciones(){
    system ("CLS");
    cout<<"Instrucciones para jugar"<<endl;
    cout<<"Cruza los 10 niveles lo mas rapido posible"<<endl;
    cout<<"Cada nivel aumenta el multiplicador de puntos"<<endl;
    cout<<"Controles: "<<endl;
    cout<<"W: moverse para arriba"<<endl;
    cout<<"S: moverse para abajo"<<endl;
    cout<<"D: moverse para derecha"<<endl;
    cout<<"A: moverse para izquierda"<<endl;
    cout<<"ESC: Salir"<<endl;
    system("PAUSE");
}

void mover(int &i, int &j,int n){
    int mov;
    bool cambiocelda=false;;
    while (!cambiocelda){
        mov=rand()%4;
        switch (mov){
            case 0:
                if(i-1>=0){
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
                if(j+1<n){
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
                if(i+1<n){
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
                if(j-1>=0){
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

bool VecinoVisitados(int i, int j, int n){
    int mov[]={1,1,1,1};
    if(i-1<0) mov[0]=0;
    if(j+1==n) mov[1]=0;
    if(i+1==n) mov[2]=0;
    if(j-1<0) mov[3]=0;
    return celdas[i-mov[0]][j].visitado and celdas[i][j+mov[1]].visitado and celdas[i+mov[2]][j].visitado and celdas[i][j-mov[3]].visitado;  
                    //arriba                          //derecha                          //abajo                 //izquierda
}

void crearlaberinto(int n){
    int contador=1;
    int pi,pj;  //posicion 
    //Algoritmo de generacion de laberinto recursivo
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

void mover_jugador(int &i, int &j, int n, bool &gameover){
    char input;
    while((i!=2*n-1 or j!=2*n-1) and !gameover){    
        input=getch();
        switch (input){
            case 'w':
                if(laberinto[i-1][j]!='#'){
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    i--;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 'd':
                if(laberinto[i][j+1]!='#'){
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    j++;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 's':
                if(laberinto[i+1][j]!='#'){
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    i++;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case 'a':
                if(laberinto[i][j-1]!='#'){
                    cursor_coor(i+1,2*j+1);cout<<' ';
                    j--;
                    cursor_coor(i+1,2*j+1);cout<<'I';
                }
                break;
            case '\e':
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
void guardar(){
    ofstream puntajes("max_puntajes.txt");
    for(int i=0;i<3;i++){
        puntajes<<max_punt[i]<<","<<nombres[i]<<endl;
    }
    puntajes.close();
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

void jugar(){
    bool gameover=false;
    int nivel=1, mapsize=10, puntaje=0;
    //instrucciones();
    while (!gameover and nivel<=5){
        int pji=1,pjj=1;
        system("CLS");
        if(nivel==5) cout<<"Ultimo nivel\n";
        cout<<"\nNivel: "<<nivel<<endl; 
        system("Pause");
        crearlaberinto(mapsize);
        mover_jugador(pji,pjj,mapsize,gameover);
        if(!gameover){
            globalreset(mapsize);
            puntaje=puntaje+nivel*100;
            nivel++;
            mapsize++;
        }
    }
    globalreset(mapsize);
    system("CLS");
    cursor_coor(1,1);cout<<"Fin de juego\n";
    puntmaximo(puntaje);
    system("Pause");
}

// Top 3 puntajes de maxpuntajes.txt
void max_puntajes(){
    system ("CLS");
    cout<<"Puntajes Maximos\n";
    cout<<"Nombre ";
    cursor_coor(1,30);cout<<"Puntaje "<<endl;
    for(int i=0; i<3; i++){
        cout<<nombres[i]; 
        cursor_coor(2+i,30);cout<<max_punt[i]<<endl;
    }   
    system("PAUSE");
}

void creditos(){
    system ("CLS");
    cout<<"Grupo #3"<<endl;
    cout<<"Burbano Nicolas"<<endl;
    cout<<"Salome Garzon"<<endl;
    cout<<"Feria Danna"<<endl;
    cout<<"Galo Lopez"<<endl;
    cout<<"Fundamentos de programacion"<<endl;
    cout<<"Proyecto Final: Laberinto\n\n"<<endl;
    system("PAUSE");
}
