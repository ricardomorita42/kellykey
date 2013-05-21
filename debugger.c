/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP:6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    debugger.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "rio.h"
#include "grade.h"
#include "debugger.h"
#include "config.h"

/*FUNCOES AUXILIARES*/
/*------------------*/

/* calculaFLuxo: calcula o fluxo de uma linha normalizada */
float calculaFluxo(Rio *linha) {
	float fluxoCalculado;
	int i;
	
	fluxoCalculado = 0;
	for (i = 0; i < getNumColumns(); i++)
		if (linha[i].velocidade > 0)
			fluxoCalculado += linha[i].velocidade;
	
	/*envia para verificaFluxo o fluxo calculado*/
	verificaFluxo(fluxoCalculado);	
	return fluxoCalculado;
}

/* calculaVelMedia: encontra a menor, a maior e a velocidade media de uma linha normalizada */
float calculaVelMedia(Rio *linha) {
	float velMedia, velMenor, velMaior, velAtual;
	int i, cnt;
	
	velMedia = velMenor = velMaior = 0;
	for (i = 0, cnt = 0; i < getNumColumns(); i++)
	{
		if (linha[i].velocidade > 0) 
		{
			velAtual = linha[i].velocidade;
			if (velMenor == 0 && velMaior == 0) 
			{
				velMenor = velAtual;
				velMaior = velAtual;
			}
			if (velAtual > velMaior)
				velMaior = velAtual;
			if (velAtual < velMenor)
				velMenor = velAtual;
			velMedia += linha[i].velocidade;
			cnt++;
		}
	}
	if (cnt != 0)
		velMedia /= cnt;
	/*envia para calculaVarVelocidade as velocidades encontradas*/
	calculaVarVelocidade(velMenor, velMaior, velMedia);
	return velMedia;
}

/*--1--printInfoTopo*/
void printInfoTopo(float tempoDecorrido) {
	printf("Modo Depuracao\n");
	printf ("Linhas x Colunas: %d x %d   Tempo: %0.2f segundos\n"
		     "--------------------------------------------------\n", getNumLines(), 
		     getNumColumns(), tempoDecorrido);
}

/*--2--printInfoLinha*/
void printInfoLinha(Rio *linha) 
{
	printf(" Fluxo: %.1f  V Media: %.3f",
	       calculaFluxo(linha), calculaVelMedia(linha));
}

/*--3--printRelatio*/
void printRelatorio() 
{	
    int c;
	printf("\033[2J\033[;H");
	printf("\n*************************************\n"
		    "|||||||||||| RELATORIO ||||||||||||||\n"
		    "-------------------------------------\n"
		    " > Calculando variacao das margens...\n");
	calculaVarMargens(-1,-1);
	printf("\n > Calculando variacao das velocidades...\n");
	calculaVarVelocidade(-1,-1,-1);
	printf("\n > Verificando comportamento do fluxo... \n");
	verificaFluxo(-1);
	printf("||||||||| FIM DO RELATORIO ||||||||||\n"
		    "*************************************\n\n");
    
    printf("Pressione <enter> para continuar. ");
    fflush(stdout);
    while ((c = getchar()) != '\n' && c != EOF) {
            /* aguarde um enter */
    }
    clearScreen();
}

/*--4--calculaVarVelocidade*/
void calculaVarVelocidade(float vMenor, float vMaior, float vMedia)
{
	static float vMenorFnl = 0, 
			       vMenorSoma = 0,
			       vMaiorFnl = 0,
			       vMaiorSoma = 0,
			       vMediaSoma = 0,
			       cnt = 0;
			       
	if (vMenor < 0 && vMaior < 0 && vMedia < 0)
	{
		if (cnt == 0)
			cnt = 1;
		printf("=====================================\n"
				 "Menor velocidade de um ponto: %f\n"
				 "Maior velocidade de um ponto: %f\n"
				 "Media das velocidades minimas: %f\n"
				 "Media das velocidades maximas: %f\n"
				 "Media geral das velocidades: %f\n"
				 "=====================================\n",
				 vMenorFnl, vMaiorFnl, vMenorSoma/cnt, 
				 vMaiorSoma/cnt, vMediaSoma/cnt);
	}
	if (cnt == 0)
	{
		vMenorFnl = vMenor;
		vMaiorFnl = vMaior;
	}
	if (vMenor < vMenorFnl)
		vMenorFnl = vMenor;
	if (vMaior > vMaiorFnl)
		vMaiorFnl = vMaior;
	vMenorSoma += vMenor;
	vMaiorSoma += vMaior;
	vMediaSoma += vMedia;
	cnt++;
}

/*--5--calculaVarMargens*/
void calculaVarMargens(int esq, int dir)
{
	static int esqIni = 0, 
			     esqFnl = 0, 
			     somaEsq = 0,
			     dirIni = 0,
			     dirFnl = 0,
			     somaDir = 0,
			     cnt = 0;
			     
	if (esq < 0 && dir < 0)
	{
		if (cnt == 0)
			cnt = 1;
		printf("=====================================\n"
				 "Variacao da margem esquerda:\n"
				 "menor: %d   maior: %d\n\n"
				 "Variacao da margem direita:\n"
				 "menor: %d   maior: %d\n\n", 
				 esqIni, esqFnl, dirIni, dirFnl);
		printf("Media de variacao das margens:\n"
				 "margem esquerda: %f\n"
				 "margem direita: %f\n"
				 "=====================================\n",
				 somaEsq/(float)cnt, somaDir/(float)cnt);
	}
	
	if (cnt == 0)
	{
		esqIni = esqFnl = esq;
		dirIni = dirFnl = dir;
	}
	else
	{
		if (esq > esqFnl)
			esqFnl = esq;
		if (esq < esqIni)
			esqIni = esq;
		if (dir > dirFnl)
			dirFnl = dir;
		if (dir < dirIni)
			dirIni = dir;
	}
	somaEsq += esq;
	somaDir += dir;
	cnt++;
}

/*--6--verificaFLuxo*/
void verificaFluxo(float fluxo)
{
	static float fluxoMin, fluxoMax, fluxoSoma = 0, cnt = 0;
	char result[4] = "NAO";
	float erro = 1.0E-3;
	
	if (fluxo < 0)
	{
		if (fabs(fluxoMax - fluxoMin) < erro)
			strcpy(result, "SIM");
		if (cnt == 0)
			cnt = 1;
		printf("=====================================\n"
				 "Fluxo estavel em todo o rio: %s\n"
				 "Menor fluxo encontrado: %f\n"
				 "Maior fluxo encontrado: %f\n"
				 "Media dos fluxos encontrados: %f\n"
				 "=====================================\n",
				 result, fluxoMin, fluxoMax, fluxoSoma/cnt);
	}
	if (cnt == 0)
		fluxoMin = fluxoMax = fluxo;
	if (fluxoMin > fluxo)
		fluxoMin = fluxo;
	if (fluxoMax < fluxo)
		fluxoMax = fluxo;
	fluxoSoma += fluxo;
	cnt++;
}

