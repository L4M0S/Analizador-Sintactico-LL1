#include"scanner.h"

#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
#include<map>

#define udef -1

using namespace std;

int p=0,q=0;

int findearchivo=0;
bool cfin=false;

int lineas=1;

string cadena="";

FILE *file;

string getCadena()
{
	string cadenaR=cadena;
	cadena="";
	return cadenaR;
}

int getLineas()
{
	return lineas;
}

void agregar(char a)
{
	cadena=cadena+a;
}

bool open(char* archivo)
{	
	file=fopen(archivo,"r");
	if(file)
	{
		fseek(file,0,SEEK_END);
		findearchivo=ftell(file);
		fseek(file,q,SEEK_SET);
		return true;
	}
	
	return false;	
}

void close()
{
	fclose(file);
}

int read()
{
	char r=fgetc(file);
	if(r==10) p++;
	
	p++;
	return r;
}

void fail()
{
	p=q;
	fseek(file,q,SEEK_SET);
}

void success()
{
	q=p;
}

void fallback()
{
	p--;
	fseek(file,p,SEEK_SET);
}

void wsp()
{	
	int e=read();
	while(e==10 || e==32 || e==9)
	{
		if(e==10) 
		{
			lineas++;
			
			fallback();
			success();			
		}
		e=read();
	}
	fallback();
	success();
}

bool eof()
{
	if(ftell(file)>=findearchivo || cfin==true)
	{
		return true;
	}
	return false;
}

token identificador()
{
	int actual=0, prior=0;
	int c;
	
	while (actual>udef)
	{
		prior=actual;
		c=read();
		
		
		switch(actual)
		{
			case 0:
				if(c=='_') actual=1;
				else if(isalpha(c)) actual=2;                                   
				else actual=udef;
				break;
			case 1:
				if(isdigit(c) || c=='_') actual=1;
				else if(isalpha(c)) actual=2;
				else actual=udef;
				break;
			case 2:
				if(isalpha(c) || isdigit(c) || c=='_') actual=2;
				else if(c==39) actual=3;
				else actual=udef;
				break;
			case 3:
				if(c==39) actual=3;
				else actual=udef;
				break;
		}
		if(actual!=udef)agregar(c);
	}
	
	if(prior==2 || prior==3)
	{
		if(cadena=="or")
		{
				fallback();
				success();
				return _or;	
		}
		else if(cadena=="and")
		{
				fallback();
				success();
				return _and;	
		}
		else if(cadena=="not")
		{
				fallback();
				success();
				return _not;	
		}
		else if(cadena=="true")
		{
				fallback();
				success();
				return _true;	
		}
		else if(cadena=="false")
		{
				fallback();
				success();
				return _false;	
		}
		else
		{
			fallback();
	 		success();
			return _id;		
		}
	}
	else
	{
		cadena="";
		fail();
		return _error;
	}
}

token numero()
{
	int actual=0, prior=0;
	int c=0;
	
	while (actual>udef)
	{
		prior=actual;
		c=read();
		
		switch(actual)
		{
			case 0:
				if(c=='0')actual=1;
				else if(c>='1' && c<='9') actual=5;
				else if((isalpha(c) && (c!='x'||c!='X')) || c=='_') actual=11; 
				else actual=udef;
				break;
			case 1:
				if(c>='0' && c<='7') actual=1;
				else if(c=='x' || c=='X') actual=2;
				else if(c=='.') actual=6;
				else actual=udef;
				break;
			case 2:
				if(isdigit(c) || (c>='a' && c<='f') || (c>='A' && c<='F')) actual=3;
				else actual=udef;
				break;
			case 3:
				if(isdigit(c) || (c>='a' && c<='f') || (c>='A' && c<='F')) actual=4;
				else actual=udef;
				break;
			case 4:
				if(isdigit(c) || (c>='a' && c<='f') || (c>='A' && c<='F')) actual=3;
				else if((isalpha(c) && ((c>='a' && c<='f')||(c>='A' && c<='F'))) || c=='_') actual=11;
				else actual=udef;
				break;
			case 5:
				if(isdigit(c)) actual=5;
				else if(c=='.') actual=6;
				else if(c=='E' || c=='e') actual=8;
				else if((isalpha(c) && (c!='e'||c!='E')) || c=='_') actual=11;
				else actual=udef;
				break;
			case 6:
				if(isdigit(c)) actual=7;
				else actual=udef;
				break;
			case 7:
				if(isdigit(c)) actual=7;
				else if(c=='E' || c=='e') actual=8;
				else if((isalpha(c) && (c!='e'||c!='E')) || c=='_') actual=11;
				else actual=udef;
				break;
			case 8:
				if(c=='+' || c=='-') actual=9;
				else if(isdigit(c)) actual=10;
				else actual=udef;
				break;
			case 9:
				if(isdigit(c)) actual=10;
				else actual=udef;
				break;
			case 10:
				if(isdigit(c)) actual=10;
				else if((isalpha(c) && (c!='e'||c!='E')) || c=='_') actual=11;
				else actual=udef;
				break;
			case 11:
				actual=udef;
				break;
		}
		if(actual!=udef)agregar(c);
	}
	
	if(prior==1)
	{
		fallback();
		success();
		return _num;		
	}
	
	else if(prior==4)
	{
		fallback();
		success();
		return _num;		
	}
	
	else if(prior==5 || prior==7 || prior==10)
	{
		fallback();
		success();
		return _num;
	}
	else
	{
		cadena="";
		fail();
		return _error;
	}
}

token comentario()
{
	int actual=0, prior=0;
	int c=0;
	
	while (actual>udef)
	{
		prior=actual;
		c=read();
		
		switch(actual)
		{
			case 0:
				if(c=='#') actual=1;
				else actual=udef;
				break;
			case 1:
				if(c!=10 && c!=-1) actual=1;
				else if(c==10) {actual=2;lineas++;}
				else actual=udef;
				break;
			case 2:
				actual=udef;
				break;
		}
		
		if(c==-1) cfin=true;
	}
	
	if(prior==2)
	{
		fallback();
		success();
		return _comentario;		
	}
	else
	{
		cadena="";
		fail();
		return _error;
	}
}

token especiales()
{
	int actual=0, prior=0;
	int c=0;
	
	while (actual>udef)
	{
		prior=actual;
		c=read();
		
		switch(actual)
		{
			case 0:
				if(c=='(') actual=1;
				else if(c==')') actual=2;
				else if(c=='<') actual=3; 
				else if(c=='>') actual=4;
				else if(c=='+') actual=5;
				else if(c=='-') actual=6;
				else if(c=='*') actual=7;
				else if(c=='/') actual=8;
				else if(c=='=') actual=9;
				else if(c=='!') actual=10;
				else if(c==':') actual=11;
				else if(c=='?') actual=12;
				else actual=udef;
				
				break;
			default: actual=udef;
			break;
			
		}
		if(actual!=udef)agregar(c);
	}
	
	if(prior>=1 && prior<=12)
	{
		fallback();
		success();
		
		if(prior==1) return _parIzq;
		else if(prior==2) return _parDer;	
		else if(prior==3) return _menor;	
		else if(prior==4) return _mayor;	
		else if(prior==5) return _suma;
		else if(prior==6) return _resta;	
		else if(prior==7) return _multi;	
		else if(prior==8) return _divi;		
		else if(prior==9) return _igual;
		else if(prior==10) return _diferente;
		else if(prior==11) return _dosPuntos;
		else if(prior==12) return _interrogacion;
	}
	else
	{
		cadena="";
		fail();
		return _error;
	}
}

token next()
{
	wsp();
	
	switch(comentario())
	{
		case _comentario: return _comentario; 
			break;
	}
	
	switch(identificador())
	{
		case _or:  cout<<cadena<<" "; return _or;
			break;
		case _and:  cout<<cadena<<" ";return _and;
			break;
		case _not:  cout<<cadena<<" ";return _not;
			break;
		case _true:  cout<<cadena<<" ";return _true;
			break;
		case _false:  cout<<cadena<<" ";return _false;
			break;
		case _id: cout<<cadena<<" "; return _id; 
			break;
	}
	switch(numero())
	{
		case _num: cout<<cadena<<" "; return _num; 
			break;
	}
	
	switch(especiales())
	{
		case _parDer: cout<<cadena<<" ";return _parDer; 
	 		break;
		case _parIzq: cout<<cadena<<" ";return _parIzq; 
	 		break;
		case _menor: cout<<cadena<<" ";return _menor; 
	 		break;
		case _mayor: cout<<cadena<<" ";return _mayor; 
	 		break;	
		case _suma: cout<<cadena<<" ";return _suma; 
	        break;
		case _resta: cout<<cadena<<" ";return _resta; 
	        break;
		case _multi: cout<<cadena<<" ";return _multi; 
	        break;
		case _divi: cout<<cadena<<" ";return _divi; 
	        break;
		case _igual: cout<<cadena<<" ";return _igual; 
	    	break;
		case _diferente: cout<<cadena<<" ";return _diferente; 
	    	break;
        case _dosPuntos: cout<<cadena<<" ";return _dosPuntos; 
	 		break;	
		case _interrogacion: cout<<cadena<<" ";return _interrogacion; 
	 		break;	 
	}
	
	if(eof()){cout<<"eof ";return _eof;}
	
	cout<<"error ";
	return _error;
}
