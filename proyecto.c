//Librerías
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>

//Matrices
#define MAXLINEAS 1000
#define MAXLEN 1000

//Definiendo variables globales
int i, i1, i2, i3, i4, i5, op;
int qtd1 = 0, qtd2 = 0;
float soma = 0;
char rec_arq[15];
char *separa;
char texto[100];
char fecha[100];

FILE *archivo;       //define utilización de archivo con punteiro en "archivo"

//Estructura para las variables de ingreso
struct item{
	char p[50];      //Producto
	int q;           //Cantidad
	float v;         //Precio
};

struct item pilha[10000]; //Vector para pilha de items
struct item fila[10000];  //Vector para fila de items

//Funcion principal con el menu
int main(void){
	
	system("color 0a");            //cambia el color de pantalla para verde
	
	while(true){
		printf("\n\n\n\n\t\t\t\t      -----------------------------------------------\n");
		printf("\t\t\t\t\t        SISTEMA CONTROL DE VENTAS\n\n");
		printf("\t\t\t\t\t[1] - Ingresar ventas\n");
		printf("\t\t\t\t\t[2] - Registrar solo un item del ingreso\n");
		printf("\t\t\t\t\t[3] - Registrar todos los items del ingreso\n");
		printf("\t\t\t\t\t[4] - Mostrar registro anteriormente hecho\n");
		printf("\t\t\t\t\t[5] - Mostrar todas las ventas registradas\n");
		printf("\t\t\t\t\t[6] - Salir\n\n");
		printf("\t\t\t\t      -----------------------------------------------\n");
		printf("\t\t\t\t\t\t   Elije una opcion: ");
		scanf("%d", &i);           //Lee la opcion ingresas por el usuario
		
		switch(i){
			case 1:                //Caso elija la opcion [1] 
				ingresarItem();    //Llama la función ingresarItem
				break;
				
			case 2:                //Caso elija la opcion [2]
				registrarItem();   //Llama la función registrarItem
				break;
				
			case 3:                //Caso elija la opcion [3]
				registrarItems();  //Llama la función registrarItems
				break;
			
			case 4:                //Caso elija la opcion [4]
				mostrarRegistro(); //Llama la funcion guardar los items
				break;
			
			case 5:                //Caso elija la opcion [5]
				mostrarTodo();     //Llama la funcion mostrarTodo lo registrado
				break;
			
			case 6:                //Caso elija la opcion [6]
				exit(0);           //Exit hace que el programa se cierre y retorne 0
		}
	}
}

//Funcion de ingresar los datos
void ingresarItem(){

	system("cls");      //Limpio la pantalla
	printf("\n\n\n\n\t\t\t\t      -----------------------------------------------\n");	
	
	if(qtd1<10000){               //Define el limite de 10000 productos guardados en el sistema                    
		printf("\t\t\t\t\t\t\tProducto:\n\t\t\t\t\t\t\t  ");
		scanf("%s", pilha[qtd1].p);
		printf("\n\t\t\t\t\t\t\tCantidad:\n\t\t\t\t\t\t\t   ");
		scanf("%d", &pilha[qtd1].q);
		printf("\n\t\t\t\t\t\t\t Precio:\n\t\t\t\t\t\t\t   ");
		scanf("%f", &pilha[qtd1].v);
		printf("\t\t\t\t      -----------------------------------------------\n");
		printf("           \t\t\t\t %dx %.2f %s\n", pilha[qtd1].q, pilha[qtd1].v, pilha[qtd1].p);   //Muestra lo que fue ingresado ordenadamente
		qtd1 = qtd1 + 1;          //Aumenta el numero de items en la pilha
		
		printf("\n\t\t\t\t\t Queres ingresar mas items? [1/0]: ");
		scanf("%d", &op);        //Opicion de salida
		
		if(op==1){               //Si ingresado 1
			ingresarItem();      //Llama la funcion de ingreso nuevamente
		} 
		else{                    //Si ingresado 0
			main();              //Llama la funcion main con el menu
		}
	}
	
	else{
		printf("\t\t\t\t\tNo hay mas espacio en el sistema!\n");
	}
}

//Funcion de guardar solamente 1 item
void registrarItem(){
	
	system("cls");        //Limpio la pantalla
	
	printf("\t\t\t\t      -----------------------------------------------\n");
	printf("\t\t\t\t\t    Ingrese la fecha de hoy [dia/mes]: \n\t\t\t\t\t\t\t   ");
	scanf("%s", &fecha);                 
	
	archivo = fopen("registro.txt","a+");                //Abre el archivo para escritura, sin borrar los datos anteriores
	
	fprintf(archivo,"\nFecha: %s | ", fecha);           //Guarda en el archivo la fecha
	
	if(archivo == NULL){                                //En caso no abra el archivo
		printf("Error a la hora de abrir el archivo."); //Muestra la mensage de error
  		return 1;
	}
	else{
		printf("\t\t\t\t      -----------------------------------------------\n");
			
		if(qtd1>0){                            //Verifica si tiene algun item ingresado
			if(qtd2<10000){                    //Verifica si hay menos del limite de items ingresados
				fila[qtd2] = pilha [qtd1-1];   //El vector llamado pilha recibe el valor del vetor pilha con diminuir -1
					
				fprintf(archivo,"%dx %s %.2f - ", fila[qtd2].q, fila[qtd2].p, (float)fila[qtd2].q*fila[qtd2].v);  //Guarda en el archivo los datos
					
				printf("\t\t\t\t\t %dx %s %.2f\n", fila[qtd2].q, fila[qtd2].p, (float)fila[qtd2].q*fila[qtd2].v);  //Muestra en el display los datos
				
				qtd1 = qtd1 - 1;               //Diminui el numero de items en la pilha
				qtd2 = qtd2 + 1;               //Aumenta el numero de items na fila
			}
			else{                                                         //Si passa del limite
				printf("\t\t\t\t\tNo hay mas espacio en el sistema.\n");  //Muestra la mensage de error
			}
		}
		else{                                                     //Si no tiene item ingresado
			printf("\t\t\t\t\tNo hay ningun item registrado.\n"); //Muestra la mensage de error
		}		
			
		fclose(archivo);    //Cierra el archivo
	}	
}

//Funcion de guardar todos los items
void registrarItems(){
	
	system("cls");        //Limpio la pantalla
	
	printf("\t\t\t\t      -----------------------------------------------\n");
	printf("\t\t\t\t\t    Ingrese la fecha de hoy [dia/mes]: \n\t\t\t\t\t\t\t   ");
	scanf("%s", &fecha);
	
	archivo = fopen("registro.txt","a+");        //Abre el arhcivo para escritura, sin borrar los datos anteriores
	
	fprintf(archivo,"\nFecha: %s | ", fecha);    //Guarda en el archivo la fecha
	
	if(archivo == NULL){                         //En caso no abra el archivo
		printf("Error na abertura do arquivo!"); //Muestra la mensage de error
  		return 1;
	}
	else{
		printf("\t\t\t\t      -----------------------------------------------\n");
							
		for(i3 = qtd1-1; qtd2 < 10000 && qtd1 > 0; i3--)
		{
			fila[qtd2] = pilha[qtd1-1];
						
			fprintf(archivo,"%dx %s %.2f - ", fila[qtd2].q, fila[qtd2].p, (float)fila[qtd2].q*fila[qtd2].v); //Guarda en el archivo los datos
						
			printf("\t\t\t\t\t%dx %s %.2f\n", fila[qtd2].q, fila[qtd2].p, (float)fila[qtd2].q*fila[qtd2].v); //Muestra en display los datos
			qtd1 = qtd1 - 1;
			qtd2 = qtd2 + 1;
		}
		fclose(archivo); //Cierra el archivo
	}
}

//Funcion de mostrar registro
void mostrarRegistro(){
	
	system("cls");   //Limpio la pantalla
	
	printf("\t\t\t\t      -----------------------------------------------\n");
	printf("\t\t\t\t\t\t   REGISTRO DE VENTAS\n\n");
	printf("\t\t\t\t\t Cantidad      Descripcion      Valor final        \n");
	printf("\t\t\t\t      ***********************************************\n");
	
	if(qtd2 != 0){                                   //Verifica si hay items en el registro
		for(i5 = 0; i5 < qtd2; i5++){                
			printf("\t\t\t\t\t    %d\t\t  %s          $ %.2f\t\n", fila[i5].q, fila[i5].p, fila[i5].q * fila[i5].v);
			soma += fila[i5].q * fila[i5].v;         //Hace el calculo para variable suma
		}
		printf("\t\t\t\t      ***********************************************\n");
		printf("\t\t\t\t\t  Total:\t\t\t $ %.2f\n\n",soma);     //variable para la suma total de registros
	}
	else{                                          //Si no hay items en el registro
		printf("\t\t\t\t\tRegistro vazio\n");      //Muestra la mensage de error      
		}
}

//Funcion de procurar en los archivos
void mostrarTodo(){
	
	system("cls");   //Limpio la pantalla
	//Define variables locales
	int k;
	int linea = 0;
	
	char datos[MAXLINEAS][MAXLEN];               //Define la matriz datos con variables globales
  	
	archivo = fopen("registro.txt", "r");        //Abre el archivo para lectura 
	
	if(archivo == NULL){                         //Si hay error al abrir el archivo
		printf("\t\t\t\t     Error al abrir el archivo o el archivo no existe.\n"); //Muestra el error
    	return 1;
	}
  
	while(!feof(archivo) && !ferror(archivo)){                 //Mientras no sea el final del archivo y mientras no hay error
		if(fgets(datos[linea], MAXLINEAS, archivo) != NULL)    //Si pegas una linea del archivo
		linea++;                                               //Acumulador de lineas
	}
    
	fclose(archivo);           //Cerra el archivo
   
	for(k=0;k<linea;k++){      //Matriz para mostrar los datos
		printf("\t\t\t\t      -----------------------------------------------\n");
		printf("\t\t\t\t      %s", datos[k]);    //Muestra la matriz
	}
}



