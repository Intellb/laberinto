#include <fstream>
#include<iostream>
using namespace std;

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

void jugar(){
//Juego usa clases laberinto y jugador
}

void max_puntajes(){
// Top 3 puntajes de maxpuntajes.txt
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