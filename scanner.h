#ifndef scanner_h
#define scanner_h

#include<cstdio>
#include<string>

using namespace std;

typedef enum {_id,
			_true,_false,_or,_and,_not,
			_num,
			_parDer,_parIzq,_menor,_mayor,_igual,_diferente,
			_suma,_resta,_multi,_divi,
			_dosPuntos,_interrogacion,
			_comentario,
			_eof,_error,
			_MAIN,
			_QUEST,_QUESTP,
			_PROP,_PROPP,
			_CLAUSE,_CLAUSEP,
			_REL,_RELP,_RELPP,
			_EXP,_EXPP,
			_TERM,_TERMP,
			_FACT} token;


bool open(char*);
void close();

int read();
void fail();
void success();
void fallback();

void wsp();
bool eof();
token identificador();
token numero();
token next();
token comentario();
token especiales();

void scanner();

void agregar(char);

string getCadena();
int getLineas();

#endif


