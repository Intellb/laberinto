//Objeto laberinto 
class laberinto{
/*Debe costruir en la pantalla el laberinto aleatorio  
contal nivel
pasar puntos al jugador  
tener inicio 
tener final
Tiempo que queda
posicion del jugador 
subir nivel 
*/
// top left bot rigt
    int paredes[4]={0,0,0,0};

    public:
        void dibujar(int n){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<"xd ";
                }
                cout<<endl;
            }
        }
};


