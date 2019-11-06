#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

#include"scanner.h" 
#include"parser.h"

using namespace std;

char nombrearchivo[50];

int main()
{
	cout<<"nombre y extencion del archivo: ";
	cin>>nombrearchivo;
	cout<<endl;
	
	if(open(nombrearchivo))
	{
		if(parser()) cout<<"Parser correcto"<<endl;
		else cout<<"Parser fallo"<<endl;
	}
	else cout<<endl<<"el archivo no existe"<<endl;
	
	close();
	
	printf("\n");
	system("pause");
	return 0;
}


/*

token a;
		
		do
		{
			a=next();
			switch(a)
			{
				case _true:	printf("true: ");cout<<getCadena()<<endl;
					break;
				case _false: printf("false: ");cout<<getCadena()<<endl;
					break;
				case _id: printf("id: ");cout<<getCadena()<<endl;
					break;
				case _num: printf("num: ");cout<<getCadena()<<endl;
					break;
				case _or: printf("or: ");cout<<getCadena()<<endl;
					break;
				case _and: printf("and: ");cout<<getCadena()<<endl;
					break;
				case _not: printf("not: ");cout<<getCadena()<<endl;
					break;
				case _parDer:  printf("parDer: ");cout<<getCadena()<<endl;
	 				break;
				case _parIzq: printf("parIzq: ");cout<<getCadena()<<endl; 
					break;
				case _menor: printf("menor: ");cout<<getCadena()<<endl; 
					break;
				case _mayor: printf("mayor: ");cout<<getCadena()<<endl;
					break;	
				case _suma: printf("suma: ");cout<<getCadena()<<endl;
			        break;
				case _resta: printf("resta: ");cout<<getCadena()<<endl; 
			        break;
				case _multi: printf("multi: ");cout<<getCadena()<<endl;
			        break;
				case _divi: printf("divi: ");cout<<getCadena()<<endl;
			        break;
				case _igual: printf("igual: ");cout<<getCadena()<<endl;
			    	break;
				case _diferente: printf("diferente: ");cout<<getCadena()<<endl; 
			    	break;
		        case _dosPuntos: printf("dosPuntos: ");cout<<getCadena()<<endl;
			 		break;	
				case _interrogacion: printf("interrogacion: ");cout<<getCadena()<<endl;
			 		break;	 
					
				case _eof:
					printf("\neof\n");
					printf("Analisis finalizado. Lineas analizadas: %i \n",getLineas());
					break;
				case _error:
					printf("\nerror\n");
					printf("Analisis interrumpido por error en la linea %i \n",getLineas());
					break;		
			}
		}while(a!=_eof && a!=_error);
		
		*/

