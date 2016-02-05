#include<iostream>
#include<fstream>
#include<stdio.h>
#include "torneo.h"   
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>


using namespace std;


void Menu();
void MenuEditarEquipos();
void MenuSimular();
void GenerarFixture();
void AgregarEquipo();
void EliminarEquipo();
void VerEquipos();
void generarPartido();
void simularPartido();
void TablaPosiciones();
void PartidosPorFecha();
void PartidosPorEquipo();

// INICIALIZACION Y DECLARACION VARIABLES:


char Id[3];
char AuxId[3];
char Nombre[31];
int Pa;
int Pd;
bool encontrado=false;


// PROGRAMA PRINCIPAL:


int main(){
	
    Menu();
    return 0;
    system("PAUSE");

}




// FUNCIONES




void Menu(){
	
    int opcion=1;
    
	while(opcion!=0){
		
        cout<<"----------Simulacion de torneo de futbol----------"<<endl;
        cout<<"1. Editar Equipo"<<endl;
        cout<<"2. Simular"<<endl;
        cout<<"3. Generacion del Fixture"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Elija una opcion: ";
        
		cin>>opcion;
        
		switch(opcion){
            case 1:
                MenuEditarEquipos();
            break;
            case 2:
                MenuSimular();
            break;
            case 3:
                GenerarFixture();
            break;
            case 0:
                cout<<"Programa Finalizado, Gracias"<<endl;
            break;
            default:
                cout<<"Opcion no valida"<<endl;
        }
}

}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void MenuSimular(){
	
	int opcion=0;
    
	do{
		
        cout<<"----------Simulacion de torneo de futbol----------"<<endl;
        cout<<"1. Ver tabla de posiciones"<<endl;
        cout<<"2. Ver partidos por equipo"<<endl;
        cout<<"3. Ver partidos por fecha"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Elija una opcion: ";
        
		cin>>opcion;
        
		switch(opcion){
            case 1:
                TablaPosiciones();
            break;
            case 2:
                PartidosPorEquipo();
            break;
            case 3:
                PartidosPorFecha();
            break;
            case 0:
                cout<<"Programa Finalizado, Gracias"<<endl;
            break;
            default:
                cout<<"Opcion no valida"<<endl;
        }
    }while(opcion!=0);
	
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void MenuEditarEquipos(){
	
    int opcion=0;
    
	do{
		
        cout<<"----------Simulacion de torneo de futbol----------"<<endl;
        cout<<"1. Agregar Equipo"<<endl;
        cout<<"2. Eliminar equipo"<<endl;
        cout<<"3. Ver equipos"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Elija una opcion: ";
        
		cin>>opcion;
        
		switch(opcion){
            case 1:
                AgregarEquipo();
            break;
            case 2:
                EliminarEquipo();
            break;
            case 3:
                VerEquipos();
            break;
            case 0:
                cout<<"Programa Finalizado, Gracias"<<endl;
            break;
            default:
                cout<<"Opcion no valida"<<endl;
        }
    }while(opcion!=0);

}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void GenerarFixture(){
	
	int equipos=0;
	int fecha=1;
	int partido=1;
	int contador=0;
	int local=0;
	int visitante=0;
	int golesLocal;
	int golesVisitante;
	
	
	struct InfoEquipo{
		string ID;
		string NOMBRE;
		int PA,PD;
		int Punto= 0;
		int PJ=0;
		int PG=0;
		int PE=0;
		int PP=0;
		int GF=0;
		int GC=0;
		int DG=0; // trabajamos con estas pero estan tambien en LocalVisitante
	};
	
    struct InfoEquipo ArrEquipo[50];
    
    struct LocalVisitante{
    	string IdLocal,IdVisitante,NombreLocal,NombreVisitante;
    	int PALocal,PAVisitante,PDLocal,PDVisitante,goleslocales,golesvisitantes;
    	int Punto,PJ,PG,PE,PP,GF,GC,DG;
	};
    
    struct LocalVisitante ArrPartido[50];
		
	ifstream lectura;
    lectura.open("EQUIPOS.txt",ios::out|ios::in);
   	
   	ofstream aux;
   	aux.open("PARTIDOS.txt",ios::out);
   	
   	ofstream ArchiPartidoPorFecha;
   	ArchiPartidoPorFecha.open("PartidosPorFecha.txt",ios::out);
   	
	if(lectura.is_open()){
	
    	lectura>>Id>>Nombre>>Pa>>Pd;
    		
			while(!lectura.eof()){   
	    				    			
				ArrEquipo[equipos].ID = Id;
				ArrEquipo[equipos].NOMBRE = Nombre;
				ArrEquipo[equipos].PA = Pa;
				ArrEquipo[equipos].PD = Pd;
				
				equipos++;
				
			 	lectura>>Id>>Nombre>>Pa>>Pd;	
		}
	}
lectura.close();


   
   while(fecha != equipos){
   	
   	 cout<<"------------   Fecha N"<< fecha<< "   ---------------------"<<endl;
   	
   	while(partido <= (equipos/2) ){
	
	cout<<"-----------------------"<<endl;		
	cout<<"Partido"<< partido<<endl;
				
generarPartido( equipos, fecha, partido, local,visitante);
        
        	ArrPartido[partido].IdLocal=ArrEquipo[local].ID;
			ArrPartido[partido].NombreLocal=ArrEquipo[local].NOMBRE;
			ArrPartido[partido].PALocal=ArrEquipo[local].PA;
			ArrPartido[partido].PDLocal=ArrEquipo[local].PD;
		
		    ArrPartido[partido].IdVisitante=ArrEquipo[visitante].ID;
			ArrPartido[partido].NombreVisitante=ArrEquipo[visitante].NOMBRE;
			ArrPartido[partido].PAVisitante=ArrEquipo[visitante].PA;
			ArrPartido[partido].PDVisitante=ArrEquipo[visitante].PD;

	 // Simular Partido
		
simularPartido(ArrPartido[partido].PALocal, ArrPartido[partido].PDLocal, ArrPartido[partido].PAVisitante,ArrPartido[partido].PDVisitante, golesLocal,golesVisitante);
		
	    ArrPartido[partido].goleslocales=golesLocal;
		ArrPartido[partido].golesvisitantes=golesVisitante;
		
	// Calcular Puntos y Goles
	    
	    // Partidos Jugados
	    ArrEquipo[local].PJ++;
	    ArrEquipo[visitante].PJ++;
	    
	    
	    // Goles
	    ArrEquipo[local].GF=ArrEquipo[local].GF+golesLocal;
	    ArrEquipo[visitante].GF=ArrEquipo[visitante].GF+golesVisitante;
	    
	    
	   // Goles en contra
	    ArrEquipo[local].GC=ArrEquipo[local].GC+golesVisitante;
	    ArrEquipo[visitante].GC=ArrEquipo[visitante].GC+golesLocal;
	   
	   
	   // Diferencia de gol
	  
	    ArrEquipo[local].DG=ArrEquipo[local].GF-ArrEquipo[local].GC;
	    ArrEquipo[visitante].DG=ArrEquipo[visitante].GF-ArrEquipo[visitante].GC;
	   
	    
	    // Puntos por partidos jugados y contador de partidos ganados/empatados/perdidos
	    
		if(golesLocal>golesVisitante){
			
			ArrEquipo[local].Punto=ArrEquipo[local].Punto+3;
			ArrEquipo[local].PG++;
			ArrEquipo[visitante].PP++;
			
		} else {
			
			if(golesLocal==golesVisitante){
			
				ArrEquipo[local].Punto++;
		    	ArrEquipo[visitante].Punto++;
		    	ArrEquipo[local].PE++;
				ArrEquipo[visitante].PE++;
		    	
		    }else{
		    	
		    	ArrEquipo[visitante].Punto=ArrEquipo[visitante].Punto+3;
		    	ArrEquipo[local].PP++;
				ArrEquipo[visitante].PG++;
			}
		}
		
		
	
			
		partido++;	
		
		cout<<"Local: "<<local<<" - ";
		cout<<"Visitante: "<<visitante<<endl;
		cout << ArrEquipo[local].ID<< " - ";
		cout << ArrEquipo[visitante].ID<<endl;
		cout<<"Resultados :"<<golesLocal<<" - "<<golesVisitante<<endl<<endl;
		cout<<"Puntos Local:"<<ArrEquipo[local].Punto<<endl;
		cout<<"Partidos Jugados Local:"<<ArrEquipo[local].PJ<<endl;
		cout<<"GF Local:"<<ArrEquipo[local].GF<<endl;
		cout<<"GC Local:"<<ArrEquipo[local].GC<<endl;
		cout<<"DG Local:"<<ArrEquipo[local].DG<<endl;
	
		if(aux.is_open() && ArchiPartidoPorFecha.is_open()){
		
		
		//Guarda en archivo "PARTIDOS.txt" toda la tabla de posiciones ordenado por fecha
		

		
		aux<<fecha<<" "
		<<ArrEquipo[local].ID<<" "
		<<ArrEquipo[local].NOMBRE<<" "
		<<ArrEquipo[local].Punto<<" "
		<<ArrEquipo[local].PJ<<" "
		<<ArrEquipo[local].PG<<" "
		<<ArrEquipo[local].PE<<" "
		<<ArrEquipo[local].PP<<" "
		<<ArrEquipo[local].GF<<" "
		<<ArrEquipo[local].GC<<" "
		<<ArrEquipo[local].DG<<endl;	
		 
		aux<<fecha<<" "
		<<ArrEquipo[visitante].ID<<" "
		<<ArrEquipo[visitante].NOMBRE<<" "
		<<ArrEquipo[visitante].Punto<<" "
		<<ArrEquipo[visitante].PJ<<" "
		<<ArrEquipo[visitante].PG<<" "
		<<ArrEquipo[visitante].PE<<" "
		<<ArrEquipo[visitante].PP<<" "
		<<ArrEquipo[visitante].GF<<" "
		<<ArrEquipo[visitante].GC<<" "
		<<ArrEquipo[visitante].DG<<endl;		


	//Guarda en archivo "PartidosPorFecha.txt" los resultados por fecha
	
	
	ArchiPartidoPorFecha
	<<fecha<<" "
	<<ArrEquipo[local].ID<<" "
	<<ArrEquipo[local].NOMBRE<<" "
	<<golesLocal<<" "
	<<golesVisitante<<" "
	<<ArrEquipo[visitante].ID<<" "
	<<ArrEquipo[visitante].NOMBRE<<endl;
	
	}

}  
	
	partido=1;  	
   	fecha++;
   	
   }

aux.close();
ArchiPartidoPorFecha.close();

}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void TablaPosiciones(){

	int contador=0;
	int opcion;
	int fecha, Punto, PJ, PG, PE, PP, GF, GC, DG;
	int indice;
	int longitud;
	string AuxNOMBRE;

	struct InfoEquipo{
		int FECHA;
		string ID;
		string NOMBRE;
		int PUNTO=0;
		int PJ=0;
		int PG=0;
		int PE=0;
		int PP=0;
		int GF=0;
		int GC=0;
		int DG=0; 
	};

	struct InfoEquipo ArrEquipo[50];
	struct InfoEquipo Auxiliar;			// Variable auxiliar para ordenamiento de arreglo

	ifstream lectura;
	
	    lectura.open("PARTIDOS.txt",ios::out|ios::in);
	   	
	   	   	
		if(lectura.is_open()){
		
	    	
	    		
	    	
			
			lectura>>fecha>>Id>>Nombre>>Punto>>PJ>>PG>>PE>>PP>>GF>>GC>>DG;
			
				while(!lectura.eof()){   
		    				    			
					ArrEquipo[contador].FECHA = fecha;
					ArrEquipo[contador].ID = Id;
					ArrEquipo[contador].NOMBRE = Nombre;
					ArrEquipo[contador].PUNTO = Punto;
					ArrEquipo[contador].PJ = PJ;
					ArrEquipo[contador].PG = PG;
					ArrEquipo[contador].PE = PE;
					ArrEquipo[contador].PP = PP;
					ArrEquipo[contador].GF = GF;
					ArrEquipo[contador].GC = GC;
					ArrEquipo[contador].DG = DG;
					
					contador++;
					
					lectura>>fecha>>Id>>Nombre>>Punto>>PJ>>PG>>PE>>PP>>GF>>GC>>DG;
					
			}
		
			//Se cierra archivo y se trabaja con arreglo "ArrEquipo"
		
			lectura.close();
		
			cout<<"Ingrese una fecha: ";
			cin>>opcion;
			
			cout<<endl;
			
			//FALTA AJUSTAR PARA QUE QUEDE PROLIJO EL LISTADO
			
			
			cout<<"Tabla de Posiciones"<<endl<<endl;
			cout<<"Equipo"<<"             "<<"Puntos "<<"PJ "<<"PG "<<"PE "<<"PP "<<"GF "<<"GC "<<"DG "<<endl;
				
						
				
				//Ordenar por Puntos y Dif.Gol
				
				
				
				indice=1;
				
				for(indice;contador>=indice;indice++)
				{
					while (opcion==ArrEquipo[indice-1].FECHA)
					{
						if ((ArrEquipo[indice-1].PUNTO < ArrEquipo[indice].PUNTO) || (ArrEquipo[indice-1].PUNTO == ArrEquipo[indice].PUNTO && ArrEquipo[indice-1].DG < ArrEquipo[indice].DG))
						{
							Auxiliar=ArrEquipo[indice-1];
							ArrEquipo[indice-1]=ArrEquipo[indice];
							ArrEquipo[indice]=Auxiliar;
							indice=0;
						}
						
						indice++;
						
					}
					
					indice++;
					
				}
		
			
			
			//Mostrar por fecha elegida una vez ordenada la tabla
						
				
				indice=0;
				while(contador>=indice){
				
					if (opcion == ArrEquipo[indice].FECHA)
					{
												
						cout<<ArrEquipo[indice].ID<<" ";
						cout<<ArrEquipo[indice].NOMBRE;
						AuxNOMBRE = ArrEquipo[indice].NOMBRE;
						longitud = AuxNOMBRE.size();
												
						while (longitud<15)
						{
							cout<<" ";
							longitud++;
						}
						cout<<ArrEquipo[indice].PUNTO<<"      ";
						cout<<ArrEquipo[indice].PJ<<"  ";
						cout<<ArrEquipo[indice].PG<<"  ";
						cout<<ArrEquipo[indice].PE<<"  ";
						cout<<ArrEquipo[indice].PP<<"  ";
						cout<<ArrEquipo[indice].GF<<"  ";
						cout<<ArrEquipo[indice].GC<<"  ";
						cout<<ArrEquipo[indice].DG<<"  ";
						cout<<endl;
					}
					
					
					indice++;
					
				}
		
		

		}
		

}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void PartidosPorFecha(){
	
	string IdLocal; 
	string IdVisitante;
	string NombreLocal;
	string NombreVisitante;
	string AuxNOMBRE;
	int longitud;
	short golesLocal, golesVisitante, Fecha;
	int opcion;	
	bool bandera=false;
	
	
	ifstream ArchiPartidoPorFecha;
   	ArchiPartidoPorFecha.open("PartidosPorFecha.txt",ios::out);
   	
   	
   	cout<<"Ingrese una fecha: ";
   	cin>>opcion;
   	
	      	
   	if(ArchiPartidoPorFecha.is_open())
   	{
   		ArchiPartidoPorFecha>>Fecha>>IdLocal>>NombreLocal>>golesLocal>>golesVisitante>>IdVisitante>>NombreVisitante;
   		
   		cout<<"Partidos de la fecha "<<opcion<<endl<<endl;   	
   		
	   	while(!ArchiPartidoPorFecha.eof())
	   	{
	   		if(opcion==Fecha)
   			{
				cout<<IdLocal<<" "<<NombreLocal;
				
				AuxNOMBRE = NombreLocal;
				longitud = AuxNOMBRE.size();
												
				while (longitud<14)
				{
					cout<<" ";
					longitud++;
				}
				
				cout<<golesLocal<<" - "<<golesVisitante<<"      "<<IdVisitante<<" "<<NombreVisitante<<endl;	
				bandera=true;			   
			}
		
	
			
			ArchiPartidoPorFecha>>Fecha>>IdLocal>>NombreLocal>>golesLocal>>golesVisitante>>IdVisitante>>NombreVisitante;
				
   		
		}
   		if (bandera!=true)
   		{
   			cout<<"No ha ingresado una fecha valida o existente."<<endl<<endl;
		}
   		
	}
	
	ArchiPartidoPorFecha.close();
	
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void PartidosPorEquipo(){
	
	int Pa,Pd;
	string Id, Nombre, aux;
	
	string IdLocal; 
	string IdVisitante;
	string NombreLocal;
	string NombreVisitante;
	string AuxNOMBRE;
	int longitud;
	short golesLocal, golesVisitante, Fecha;
	string opcion;	
	bool bandera=false;
	int i=0, j=0;
	
	struct PartidoEquipo
	{
		string IDLOCAL, IDVISITANTE, NOMBRELOCAL, NOMBREVISITANTE;
		short GOLESLOCAL, GOLESVISITANTE, FECHA;
	};
	
	struct PartidoEquipo ArrEquipo[50];
	
	ifstream ArchiPartidoPorFecha;
   	ArchiPartidoPorFecha.open("PartidosPorFecha.txt",ios::out);
   	
   	ifstream ArchEquipos;
   	ArchEquipos.open("EQUIPOS.txt",ios::out);
   	
   	
   	cout<<"Ingrese el ID (3 caracteres en mayuscula) de equipo: ";
   	cin>>opcion;
   	
   	// Abrimos Equipos.txt para guardar el nombre correspondiente al ID para luego mostrarlo en el menu
   	
	if (ArchEquipos.is_open())
	{
		ArchEquipos>>Id>>Nombre>>Pa>>Pd;
		
		while(!ArchEquipos.eof() && Id!=opcion)
		{
			
			ArchEquipos>>Id>>Nombre>>Pa>>Pd;
			
		}
	}
	
	
	// Pasamos el archivo a un arreglo donde solo este el equipo que se quiere mostrar
	
	
   	if(ArchiPartidoPorFecha.is_open())
   	{
   		ArchiPartidoPorFecha>>Fecha>>IdLocal>>NombreLocal>>golesLocal>>golesVisitante>>IdVisitante>>NombreVisitante;	
   		
	   	while(!ArchiPartidoPorFecha.eof())
	   	{
	   				
			if((opcion==IdLocal) || (opcion==IdVisitante))
   			{	
				ArrEquipo[i].FECHA = Fecha;
				ArrEquipo[i].IDLOCAL = IdLocal;
				ArrEquipo[i].NOMBRELOCAL = NombreLocal;
				ArrEquipo[i].GOLESLOCAL = golesLocal;
				ArrEquipo[i].GOLESVISITANTE = golesVisitante;
				ArrEquipo[i].IDVISITANTE = IdVisitante;
				ArrEquipo[i].NOMBREVISITANTE = NombreVisitante;	
				i++;
				bandera=true;
			}
			
			
			
			ArchiPartidoPorFecha>>Fecha>>IdLocal>>NombreLocal>>golesLocal>>golesVisitante>>IdVisitante>>NombreVisitante;
				
   		
		}
		
		// Mostramos el menu
		
		cout<<"Partidos de "<<Nombre<<endl<<endl;   	
		
		while(i>j)
		{
			cout<<ArrEquipo[j].IDLOCAL<<" "<<ArrEquipo[j].NOMBRELOCAL;
			
			AuxNOMBRE = ArrEquipo[j].NOMBRELOCAL;
			longitud = AuxNOMBRE.size();
												
			while (longitud<14)
			{
				cout<<" ";
				longitud++;
			}
			
			longitud=0;
			
			cout<<ArrEquipo[j].GOLESLOCAL<<" - "<<ArrEquipo[j].GOLESVISITANTE;
			
			AuxNOMBRE = ArrEquipo[j].GOLESVISITANTE;
			longitud = AuxNOMBRE.size();
												
			while (longitud<14)
			{
				cout<<" ";
				longitud++;
			}
			
			cout<<ArrEquipo[j].IDVISITANTE<<" "<<ArrEquipo[j].NOMBREVISITANTE<<endl;
			j++;
		}
		
		// Damos un mensaje en caso de tipeo erroneo
		
   		if (bandera!=true)
   		{
   			cout<<"No ha ingresado el ID de un equipo valido o existente."<<endl;
   			cout<<"Revise si puso en MAYUSCULAS el ID e intente nuevamente."<<endl<<endl;
		}
		else
		{
			cout<<endl;
		}
   		
	}
	
	ArchEquipos.close();
	ArchiPartidoPorFecha.close();
	
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void AgregarEquipo(){
    
	int c=0;
    int d=0;
    int a;
	
	ofstream aux;
    ifstream lectura;
    encontrado=false;
    char AgregarId[3];
    aux.open("AUXILIAR.txt",ios::out);
    lectura.open("EQUIPOS.txt",ios::in);
    
	if(aux.is_open() && lectura.is_open()){
    
	    cout<<"Ingresa El ID del equipo que desea agregar: ";
        cin>>AgregarId;
        lectura>>Id;
      
	    while(!lectura.eof()){
           
		    lectura>>Nombre>>Pa>>Pd;
           
		    if((AgregarId[0]==Id[0])&&(AgregarId[1]==Id[1])&&(AgregarId[2]==Id[2])){
                
				encontrado=true;
                cout<<endl<<endl<<"*****Registro ya existente, desea modificarlo?*****"<<endl<<endl;
                cout<<"1. Modificar"<<endl;
        		cout<<"2. No modificar"<<endl;
               
			    cin>>a;
               
			    switch(a){
                	case 1:
                		cout<<endl<<"Ingrese el NOMBRE del equipo: "<<endl;
            			cin>>Nombre;
						while (c==0){
						cout << "ingrese la POTENCIA DE ATAQUE del equipo(entre 0  y 100): "<<endl;
						cin >>Pa;
						if ((0<=Pa)&&(Pa<=100)){
						c=1;
						}else{
						cout << "error, la potencia de ataque no esta en el rango solicitado: " << endl;
						}
						}
						while (d==0){
						cout << "ingrese la POTENCIA DE DEFENSA del equipo (entre 0  y 100): "<<endl;
						cin >>Pd;
						if ((0<=Pd)&&(Pd<=100)){
						d=1;
						}else{
						cout << "error, la potencia de defensa no esta en el rango solicitado" << endl;
						}
						}
							aux<<AgregarId<<" "<<Nombre<<" "<<Pa<<" "<<Pd<<endl;
            				cout<<"Equipo modificado correctamente"<<endl;
            		break;
            		case 2:
                		aux<<Id<<" "<<Nombre<<" "<<Pa<<" "<<Pd<<" "<<endl;
                			cout<<"Equipo no modificado"<<endl;
            		break;
            		
					default:
                		cout<<"Opcion no valida"<<endl;
                }
            }else{
                aux<<Id<<" "<<Nombre<<" "<<Pa<<" "<<Pd<<" "<<endl;
            }
            lectura>>Id;
        }
    }else{
        cout<<"Error al abrir el Archivo o no Existe"<<endl;
    }
   
    if(encontrado==false){
        
		cout<<endl<<"Ingrese el NOMBRE del equipo: "<<endl;
            cin>>Nombre;
	
		while (c==0){
		
			cout << "ingrese la POTENCIA DE ATAQUE del equipo(entre 0  y 100): "<<endl;
			cin >>Pa;
			if ((0<=Pa)&&(Pa<=100)){
			c=1;
			
		}else{
			
			cout << "error, la potencia de ataque no esta en el rango solicitado: " << endl;
		}
	}
		while (d==0){
		
			cout << "ingrese la POTENCIA DE DEFENSA del equipo (entre 0  y 100): "<<endl;
			cin >>Pd;
			if ((0<=Pd)&&(Pd<=100)){
			d=1;
		
		}else{
			cout << "error, la potencia de defensa no esta en el rango solicitado" << endl;
		}
	}
						
            aux<<AgregarId<<" "<<Nombre<<" "<<Pa<<" "<<Pd<<endl;
            cout<<"Equipo Agregado correctamente"<<endl;
        }
	   
    aux.close();
    lectura.close();
    
    remove("EQUIPOS.txt");
    rename("AUXILIAR.txt","EQUIPOS.txt");
    
	}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void EliminarEquipo(){
	
    ofstream aux;
    ifstream lectura;
    encontrado=false;
    char EliminarId[3];
    aux.open("AUXILIAR.txt",ios::out);
    lectura.open("EQUIPOS.txt",ios::in);
    
	if(aux.is_open() && lectura.is_open()){
       
	    cout<<"Ingresa El ID del equipo que desea eliminar: ";
        cin>>EliminarId;
        lectura>>Id;
       
	    while(!lectura.eof()){
           
		    lectura>>Nombre>>Pa>>Pd;
            if((EliminarId[0]==Id[0])&&(EliminarId[1]==Id[1])&&(EliminarId[2]==Id[2])){
                encontrado=true;
                cout<<endl<<endl<<"*****Registro Eliminado Corrrectamente*****"<<endl<<endl;
            }else{
                aux<<Id<<" "<<Nombre<<" "<<Pa<<" "<<Pd<<" "<<endl;
            }
            lectura>>Id;
        }
    }else{
        cout<<"Error al abrir el Archivo o no Existe"<<endl;
    }
   
    if(encontrado==false){
        
		cout<<endl<<endl<<"No se encontro ningun equipo con Identificador:  "<<EliminarId<<endl<<endl;
    }
   
   	aux.close();
    lectura.close();
    remove("EQUIPOS.txt");
    rename("AUXILIAR.txt","EQUIPOS.txt");
    
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void VerEquipos(){
	
	ifstream lectura;
    lectura.open("EQUIPOS.txt",ios::out|ios::in);
   
    if(lectura.is_open()){
       
	    cout<<endl<<endl<<"-------Lista de equipos-------"<<endl<<endl;
        	cout<<"________________________________"<<endl;
        lectura>>Id;
       
	    while(!lectura.eof()){
          
		    lectura>>Nombre>>Pa>>Pd;
            cout<<"Identificador: "<<Id<<endl;
            cout<<"Nombre: "<<Nombre<<endl;
            cout<<"Potencia de ataque: "<<Pa<<endl;
            cout<<"Potencia de defensa: "<<Pd<<endl;
            lectura>>Id;
            cout<<"________________________________"<<endl<<endl<<endl;
        }
    }else{
        cout<<"Error en la apertura del archivo, o aun no ha sido creado"<<endl;
    }
    lectura.close();
}



void generarPartido(int equipos, int fecha, int partido, int &local, int &visitante)
{
    local = equipos + fecha - partido;
    visitante = equipos + fecha + partido;
    if (equipos % 2 == 0) {
        if(fecha < partido - 1) {
            visitante--;
        }
        else if(fecha * 2 >= equipos && fecha + partido >= equipos) {
            local++;
        }
        else if(partido - fecha == 1 || partido + fecha == equipos - 1) {
            local = fecha;
            visitante = equipos - 1;
        }
    }
    if(fecha % 2 == 0) {
        int aux = local;
        local = visitante;
        visitante = aux;
    }
    local = local % equipos;
    visitante = visitante % equipos;
}



double randomNumber()
{
    return ((double)rand()) / RAND_MAX;
}

void trimString(char *txt)
{
    size_t len = strlen(txt);
    size_t s = 0;
    while(txt[s] == ' ' && txt[s] != '\0') {
        s++;
    }
    for(size_t i = 0; i <= len - s; i++) {
        txt[i] = txt[i + s];
    }
    len -= s;
    if (len > 0 && txt[len - 1] == '\n') {
        txt[len - 1] = '\0';
    }
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void simularPartido(int ataqueLocal, int defensaLocal, int ataqueVisitante, int defensaVisitante, int &golesLocal, int &golesVisitante)
{
    golesLocal = round(sqrt(100 + ataqueLocal - defensaVisitante) * pow(randomNumber(), 2) * randomNumber());
    golesVisitante = round(sqrt(100 + ataqueVisitante - defensaLocal) * pow(randomNumber(), 2) * randomNumber());
}
