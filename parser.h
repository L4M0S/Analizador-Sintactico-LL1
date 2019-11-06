#ifndef parser_h
#define parser_h

#include"scanner.h"

#include<vector>

/*
bool openp(char*);
void closep();
bool parser(char*);
*/
typedef vector<token> Produccion;

bool parser();
bool match(token);
bool recursivo();
bool ll1();
Produccion T(token,token);

bool esTerminal(token);
bool esGenerador(token);

void init();
void llenarTerminales();
void llenarGeneradores();
void llenarProducciones();

bool _main();
bool quest();
bool questp();
bool prop();
bool propp();
bool clause();
bool clausep();
bool rel();
bool relp();
bool relpp();
bool exp();
bool expp();
bool term();
bool termp();
bool fact();

#endif
