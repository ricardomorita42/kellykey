/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    config.h

Materia:
    Canoagem    

Referências:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 80
#define TRUE 1
#define FALSE 0

#define LEFTMARGIN ('-' + 'l' + 'm')
#define RIGHTMARGIN ('-' + 'r' + 'm')
#define H20MAXSPEED ('-' + 's' + 'p')
#define SEED ('-' + 's' + 'd')
#define REFRESHRATE ('-' + 'r' + 'r')
#define MINISLEDIST ('-' + 'i' + 'd')
#define PROBGENISLE ('-' + 'i' + 'g')
#define NUMLINES ('-' + 'n' + 'l')
#define NUMCOLUMNS ('-' + 'n' + 'c')
#define NUMITERATIONS ('-' + 'i' + 't')
#define NUMSECONDS ('-' + 'n' + 's')
#define RIVERFLUX ('-' + 'f' + 'l')
#define REPORTDATA ('-' + 'r' + 'd')
#define IGNOREERROR ('-' + 'i' + 'e')
#define WATERSYMBOL ('-' + 'w' + 's')
#define EARTHSYMBOL ('-' + 'e' + 's')
#define ISLESYMBOL ('-' + 'i' + 's')

/*Funcoes para setar as variaveis do jogo */
void setEntradas(FILE*, int, char*[]);

/*Funcoes para pegar dados*/
int getLeftMargin();            
int getRightMargin();           
float getWaterSpeed();          
int getSeed();                  
int getRefreshRate();           
int getIsleDist();              
float getIsleProb();            
int getNumLines();              
int getNumColumns();            
int getNumIterations();         
int getNumSeconds();
float getRiverFlux();           
int getReportData();            
int getDebugMode();
char getWaterChar();            
char getEarthChar();            
char getIsleChar();             

/*Mostra menu e permite mudar variaveis "on the fly".*/
void mudaAtributos();

/*Limpa a tela */
void clearScreen();
