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
