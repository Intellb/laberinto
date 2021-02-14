#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include"objetos.hpp"
// Funciones del main 
int menu(){
    int opcion;
    system ("CLS");
    cout<<"Menu"<<endl;
    cout<<"1: Jugar"<<endl;
    cout<<"2: Puntajes Maximos"<<endl;
    cout<<"3: Creditos"<<endl;
    cout<<"4: Salir"<<endl;
    cout<<"Opcion: ";
    cin>>opcion;
    while(opcion<0 or opcion>4){
        cout<<"Ingrese una opcion valida: ";
        cin>>opcion;
    }
    return opcion;
}


void instrucciones(){
    system ("CLS");
    cout<<"Instrucciones para jugar"<<endl;
    cout<<"Cruza el laberinto antes de que se acabe el tiempo"<<endl;
    cout<<"Cada nivel aumenta el multiplicador de puntos"<<endl;
    cout<<"Controles: "<<endl;
    cout<<"W: moverse para arriba"<<endl;
    cout<<"S: moverse para abajo"<<endl;
    cout<<"D: moverse para derecha"<<endl;
    cout<<"A: moverse para izquierda"<<endl;
    system("PAUSE");
}

void jugar(){
    instrucciones();
    system ("CLS");
    cout<<"Juego ejecutandose";
    system("PAUSE");
    
    //Juego usa clases laberinto y jugador
}

void max_puntajes(){
// Top 3 puntajes de maxpuntajes.txt
    system ("CLS");
    string line;
    ifstream puntajes("max_puntajes.txt");
    while (getline (puntajes, line)) {
         cout << line<<endl;
    }   
    system("PAUSE");
    puntajes.close();
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