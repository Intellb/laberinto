//Programa Principal 
#include<iostream>
#include<vector>
#include"header.hpp"
#include"objetos.hpp"

using namespace std;
int main{
    bool go=true;
    int opcion;
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
                do{
                    cout<<"Ingresar una opcion valida por favor";
                    cin>>opcion;
                }while(opcion=1 or opcion=2 or opcion=3)''
        }
    }

    return 0;
}