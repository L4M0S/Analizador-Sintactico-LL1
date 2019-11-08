#include"parser.h"

#include"scanner.h"

#include<cstdio>
#include<stack>
#include<map>
#include<set>
#include<vector>

token t;

set<token> Generadores;
set<token> Terminales;

typedef map<int,Produccion> Producciones;
Producciones producciones;

typedef vector<token> Par;
typedef map<Par,int> Controlador;

void llenarProducciones()
{
	Produccion P1={_MAIN,_QUEST}; producciones[1]=P1;
	Produccion P2{_QUEST,_PROP,_QUESTP}; producciones[2]=P2;
	Produccion P3{_QUESTP,_interrogacion,_QUEST,_dosPuntos,_QUEST}; producciones[3]=P3;
	Produccion P4{_QUESTP}; producciones[4]=P4;
	Produccion P5{_PROP,_CLAUSE,_PROPP}; producciones[5]=P5;
	Produccion P6{_PROPP,_or,_CLAUSE,_PROPP}; producciones[6]=P6;
	Produccion P7{_PROPP}; producciones[7]=P7;
	Produccion P8{_CLAUSE,_REL,_CLAUSEP}; producciones[8]=P8;
	Produccion P9{_CLAUSEP,_and,_REL,_CLAUSE}; producciones[9]=P9;
	Produccion P10{_CLAUSEP}; producciones[10]=P10;
	Produccion P11{_REL,_EXP,_RELP}; producciones[11]=P11;
	Produccion P12{_RELP,_igual,_igual,_EXP}; producciones[12]=P12;
	Produccion P13{_RELP,_diferente,_igual,_EXP}; producciones[13]=P13;
	Produccion P14{_RELP,_menor,_RELPP}; producciones[14]=P14;
	Produccion P15{_RELP,_mayor,_RELPP}; producciones[15]=P15;
	Produccion P16{_RELP}; producciones[16]=P16;
	Produccion P17{_RELPP,_EXP}; producciones[17]=P17;
	Produccion P18{_RELPP,_igual,_EXP}; producciones[18]=P18;
	Produccion P19{_EXP,_TERM,_EXPP}; producciones[19]=P19;
	Produccion P20{_EXPP,_suma,_TERM,_EXPP}; producciones[20]=P20;
	Produccion P21{_EXPP,_resta,_TERM,_EXPP}; producciones[21]=P21;
	Produccion P22{_EXPP}; producciones[22]=P22;
	Produccion P23{_TERM,_FACT,_TERMP}; producciones[23]=P23;
	Produccion P24{_TERMP,_multi,_FACT,_TERMP}; producciones[24]=P24;
	Produccion P25{_TERMP,_divi,_FACT,_TERMP}; producciones[25]=P25;
	Produccion P26{_TERMP}; producciones[26]=P26;
	Produccion P27{_FACT,_resta,_FACT}; producciones[27]=P27;
	Produccion P28{_FACT,_not,_FACT}; producciones[28]=P28;
	Produccion P29{_FACT,_parIzq,_QUEST,_parDer}; producciones[29]=P29;
	Produccion P30{_FACT,_num}; producciones[30]=P30;
	Produccion P31{_FACT,_id}; producciones[31]=P31;
	Produccion P32{_FACT,_false}; producciones[32]=P32;
	Produccion P33{_FACT,_true}; producciones[33]=P33;
}

void llenarGeneradores()
{
	Generadores.insert(_MAIN);
	Generadores.insert(_QUEST);
	Generadores.insert(_QUESTP);
	Generadores.insert(_PROP);
	Generadores.insert(_PROPP);
	Generadores.insert(_CLAUSE);
	Generadores.insert(_CLAUSEP);
	Generadores.insert(_REL);
	Generadores.insert(_RELP);
	Generadores.insert(_RELPP);
	Generadores.insert(_EXP);
	Generadores.insert(_EXPP);
	Generadores.insert(_TERM);
	Generadores.insert(_TERMP);
	Generadores.insert(_FACT);
}

void llenarTerminales()
{
	Terminales.insert(_id);
	Terminales.insert(_true);
	Terminales.insert(_false);
	Terminales.insert(_or);
	Terminales.insert(_and);
	Terminales.insert(_not);
	Terminales.insert(_num);
	Terminales.insert(_parDer);
	Terminales.insert(_parIzq);
	Terminales.insert(_menor);
	Terminales.insert(_mayor);
	Terminales.insert(_igual);
	Terminales.insert(_diferente);
	Terminales.insert(_suma);
	Terminales.insert(_resta);
	Terminales.insert(_multi);
	Terminales.insert(_divi);
	Terminales.insert(_dosPuntos);
	Terminales.insert(_interrogacion);
	Terminales.insert(_eof);
}

bool parser() 
{		
	//return recursivo();
	return ll1();
}

Produccion T(token A,token f)
{
	////////////CONTROLADOR////////////
	if(A==_MAIN && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[1];
	else if(A==_QUEST && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[2];
	else if(A==_QUESTP && (f==_interrogacion)) return producciones[3];
	else if(A==_QUESTP && (f==_dosPuntos || f==_parDer || f==_eof)) return producciones[4];
	else if(A==_PROP && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[5];
	else if(A==_PROPP && (f==_or)) return producciones[6];
	else if(A==_PROPP && (f==_interrogacion || f==_dosPuntos || f==_parDer || f==_eof)) return producciones[7];
	else if(A==_CLAUSE && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[8];
	else if(A==_CLAUSEP && (f==_and)) return producciones[9];
	else if(A==_CLAUSEP && (f==_interrogacion || f==_dosPuntos || f==_or || f==_parDer || f==_eof)) return producciones[10];
	else if(A==_REL && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[11];
	else if(A==_RELP && (f==_igual)) return producciones[12];
	else if(A==_RELP && (f==_diferente)) return producciones[13];
	else if(A==_RELP && (f==_menor)) return producciones[14];
	else if(A==_RELP && (f==_mayor)) return producciones[15];
	else if(A==_RELP && (f==_interrogacion || f==_dosPuntos || f==_or || f==_and || f==_parDer || f==_eof)) return producciones[16];
	else if(A==_RELPP && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[17];
	else if(A==_RELPP && (f==_igual)) return producciones[18];
	else if(A==_EXP && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[19];
	else if(A==_EXPP && (f==_suma)) return producciones[20];
	else if(A==_EXPP && (f==_resta)) return producciones[21];
	else if(A==_EXPP && (f==_interrogacion || f==_dosPuntos || f==_or || f==_and || f==_igual || f==_diferente || f==_menor || f==_mayor || f==_parDer || f==_eof)) return producciones[22];
	else if(A==_TERM && (f==_resta || f==_not || f==_parIzq || f==_num || f==_id || f==_true || f==_false)) return producciones[23];
	else if(A==_TERMP && (f==_multi)) return producciones[24];
	else if(A==_TERMP && (f==_divi)) return producciones[25];
	else if(A==_TERMP && (f==_interrogacion || f==_dosPuntos || f==_or || f==_and || f==_igual || f==_diferente || f==_menor || f==_mayor || f==_suma || f==_resta || f==_parDer || f==_eof)) return producciones[26];
	else if(A==_FACT && (f==_resta)) return producciones[27];
	else if(A==_FACT && (f==_not)) return producciones[28];
	else if(A==_FACT && (f==_parIzq)) return producciones[29];
	else if(A==_FACT && (f==_num)) return producciones[30];
	else if(A==_FACT && (f==_id)) return producciones[31];
	else if(A==_FACT && (f==_false)) return producciones[32];
	else if(A==_FACT && (f==_true)) return producciones[33];
	
	Produccion Perr{_error};
	return Perr;
}

bool match(token k)
{
	if(k==t)
	{
		t=next();
		return true;
	}
	return false;
}

bool ll1()
{
	init();
	
	token x;
	stack<token> pila;
	Produccion pi;
	
	t=next();
	pila.push(_MAIN);
	
	pi=T(_MAIN,_resta);
	
	do
	{
		x=pila.top(); pila.pop();
		if(esTerminal(x))
		{
			if(x==t)
			{
				t=next();
			}
			else
			{
				return false;
			}
		}
		else
		{
			pi=T(x,t);
			
			if(pi[0]==_error)
			{
				return false;			
			}
			else
			{
				for(int i=pi.size()-1; i>0; i--)
				{
					pila.push(pi[i]);
				}
			}
		}
	}while(!pila.empty());
	
	return t==_eof;
}

void init()
{
	llenarTerminales();
	llenarGeneradores();
	llenarProducciones();
}

bool esTerminal(token s)
{
	return Terminales.find(s) != Terminales.end();
}

bool esGenerador(token s)
{
	return Generadores.find(s) != Generadores.end();
}

bool recursivo()
{
	t=next();

	bool r=_main() && t==_eof;
	return r;
}

bool _main()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return quest();
	}
	
	return false;
}

bool quest()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return prop() && questp();
	}
	
	return false;
}

bool questp()
{
	if(t==_interrogacion)
	{
		return match(_interrogacion) && quest() && match(_dosPuntos) && quest();
	}
	if(t== _eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
	
	return false;
}

bool prop()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return clause() && propp();
	}
	
	return false;
}

bool propp()
{
	if(t==_or)
	{
		return match(_or) && clause() && propp();
	}
	if(t==_interrogacion || t==_eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
}

bool clause()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return rel() && clausep();
	}
	
	return false;
}

bool clausep()
{
	if(t==_and)
	{
		return match(_and) && rel() && clause();
	}
	if(t==_or || t==_interrogacion || t==_eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
	
	return false;
}

bool rel()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return exp() && relp();
	}
	
	return false;
}

bool relp()
{
	if(t==_igual)
	{
		return match(_igual) && match(_igual) && exp();
	}
	if(t==_diferente)
	{
		return match(_diferente) && match(_igual) && exp();
	}
	if(t==_menor)
	{
		return match(_menor) && relpp();
	}
	if(t==_mayor)
	{
		return match(_mayor) && relpp();
	}
	if(t==_and || t==_or || t==_interrogacion || t==_eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
	
	return false;
}

bool relpp()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return exp();
	}
	if(t==_igual)
	{
		return match(_igual) && exp();
	}
	
	return false;
}

bool exp()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return term() && expp();
	}
	
	return false;
}

bool expp()
{
	if(t==_suma)
	{
		return match(_suma) && term() && expp();
	}
	if(t==_resta)
	{
		return match(_resta) && term() && expp();
	}
	if(t==_igual || t==_diferente || t==_menor || t==_mayor || t==_and || t==_or || t==_interrogacion || t==_eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
}

bool term()
{
	if(t==_resta || t==_not || t==_parIzq || t==_num || t==_id || t==_false || t==_true)
	{
		return fact() && termp();
	}
	
	return false;
}

bool termp()
{
	if(t==_multi)
	{
		return match(_multi) && fact() && termp();
	}
	if(t==_divi)
	{
		return match(_divi) && fact() && termp();
	}
	if(t==_suma || t==_resta || t==_igual || t==_diferente || t==_menor || t==_mayor || t==_and || t==_or || t==_interrogacion || t==_eof || t==_dosPuntos || t==_parDer)
	{
		return true;
	}
}

bool fact()
{
	if(t==_resta)
	{
		return match(_resta) && fact();
	}
	if(t==_not)
	{
		return match(_not) && fact();
	}
	if(t==_parIzq)
	{
		return match(_parIzq) && quest() && match(_parDer);
	}
	if(t==_num)
	{
		return match(_num);
	}
	if(t==_id)
	{
		return match(_id);
	}
	if(t==_false)
	{
		return match(_false);
	}
	if(t==_true)
	{
		return match(_true);
	}
}

