/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    grade.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


#include <stdlib.h>
#include <stdio.h>
#include "rio.h"
#include "grade.h"
#include "debugger.h"
#include "config.h"

/*--1--alocaGrade */
Rio **alocaGrade() 
{
	int i;

	Rio **t = malloc(getNumLines() * sizeof(Rio *));
	for (i = 0; i < getNumLines(); i++)
		t[i] = malloc(getNumColumns() * sizeof (Rio));
	return t;
}

/*--2--freeGrade */
void freeGrade(Rio **grade) 
{
	int i;
	
	for (i = getNumLines()-1; i >= 0; i--)
		free(grade[i]);
	
	free(grade);
}

/*--3--printGrade */
void printGrade(Rio **grade, int primeiraLinha, float tempoDecorrido) 
{
	int i, j; 
	
	i = primeiraLinha;
	printf("\033[2J\033[;H");
	if (getReportData()) 
		printInfoTopo(tempoDecorrido);
	
	do {
		i--;
		if (i < 0)
			i = getNumLines()-1;
		for (j = 0; j < getNumColumns(); j++) 
			printf ("%c", grade[i][j].terreno);
		if (getReportData()) 
			printInfoLinha(grade[i]);
		printf("\n");
	} while ( i != primeiraLinha );
	printf ("\n\n");
}

/*PARA TESTE!*/
Rio** criaImagemGrade(Rio **grade, int primeiraLinha)
{
	int i, j, k;
   	Rio** imagem = alocaGrade();
	
	for (i = primeiraLinha-1, k = 0; k < getNumLines() - 1; k++, i--)
	{
		if (i < 0)
			i = getNumLines()-1;
		for (j = 0; j < getNumColumns(); j++) 
			imagem[k][j].terreno = grade[i][j].terreno;
	}
	return imagem;

}
