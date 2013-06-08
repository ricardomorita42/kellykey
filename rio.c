/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    rio.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "rio.h"
#include "grade.h"
#include "debugger.h"
#include "config.h"

/*--1--Gera rio */
Rio** geraRio(int primeiraLinha, int linha, float fluxoEsperado, Rio **grade) {
	int linhaAnterior;
	
	/*linha = primeiraLinha;*/

	/*gera uma grade completa*/
	do {
		linhaAnterior = linha - 1;
		if (linhaAnterior < 0) 
			linhaAnterior = getNumLines() - 1;
		if (linha == primeiraLinha)
			grade[linha] = geraLinha(grade[linha], NULL, fluxoEsperado);
		else
			grade[linha] = geraLinha(grade[linha], grade[linhaAnterior], fluxoEsperado);

		linha++;
		if (linha == getNumLines()) 
			linha = 0;
		
	} while (linha != primeiraLinha);
	
	/*if (getDebugMode() || getReportData() == 1)
		printRelatorio();*/

	return grade;
}

/*--2--geraLinha*/
Rio* geraLinha(Rio *linhaNova, Rio *linhaAnterior, float fluxo)
{
	int esq, dir;	

	/*define as margens da linha nova*/
	if (linhaAnterior == NULL)
	{
		esq = sorteiaMargem('e', NULL);
		dir = sorteiaMargem('d', NULL);
		linhaNova = preencheTerreno(esq, dir, linhaNova);
		linhaNova = preencheVelocidade(fluxo, NULL, linhaNova);
		if (getDebugMode() || getReportData())
			calculaVarMargens(esq, dir);
		return linhaNova;
	}
	/*define a posicao das margens*/
	esq = sorteiaMargem('e', linhaAnterior);
	dir = sorteiaMargem('d', linhaAnterior);
	if (esq >= dir)
		printf("Entrando em modo off-road...\n");
	if (getDebugMode() || getReportData())
		calculaVarMargens(esq, dir);
	/*define o terreno*/
	linhaNova = preencheTerreno(esq, dir, linhaNova);
	/*define a velocidade*/
	linhaNova = preencheVelocidade(fluxo, linhaAnterior, linhaNova);
	
	/*devolve liha nova*/
	return linhaNova;
}

/*--3--sorteiaMargem*/
int sorteiaMargem(char lado, Rio *linAnterior)
{
	int i, margem, normalizador, variacao;

	/*define se a margem ira pra esquerda, centro ou direita*/
	normalizador = (int)(((double)rand() / RAND_MAX)*100);

	/*define o nivel de variacao em relacao 'a margem anterior*/
	variacao = (int)ceil(((double)rand() / RAND_MAX)*2);

	/*caso: primeira linha gerada*/
	if (linAnterior == NULL)
	{
		if (lado == 'e')
			return (int)((rand() / ((double)RAND_MAX + 1)) * getLeftMargin()) ;
		if (lado == 'd')
			return (int)(((rand() / ((double)RAND_MAX + 1 )) * (getNumColumns() - getRightMargin())) + 
				getRightMargin() );
	}
	
	/*calcula o destino da proxima margem esquerda*/
	else if (lado == 'e')
	{
		for (i = 0; linAnterior[i].terreno != getWaterChar() && i < getNumColumns()-1; i++)
			margem = i;
		if (normalizador < 33 && margem > 2)
			return margem - variacao;
		else if (normalizador > 66 && margem < getLeftMargin()-1)
			return margem + variacao;
		else
			return margem;

	}

	/*calcula o destino da proxima margem direita*/
	else if (lado == 'd')
	{
		for (i = getNumColumns()-1; linAnterior[i].terreno != getWaterChar(); i--)
			margem = i;
		if (normalizador < 33 && margem > getRightMargin()-1)
			return margem - variacao;
		else if (normalizador > 66 && margem < getNumColumns()-2)
			return margem + variacao;
		else
			return margem;
	}
	
	return -1;		
}

/*--4--geraIlha*/
Rio* geraIlha(int n, int esq, int dir, Rio *linNova)
{
	int i, ponto, tamanhoIlha, diff;
	float P;
	diff = (dir-1) - (esq+1);
	P = rand() / ((double)RAND_MAX + 1);
	ponto = (int)((rand() / ((double)RAND_MAX + 1)) * diff + esq + 2);
	tamanhoIlha = (int)(((double)rand() / RAND_MAX) * diff / 1.6 + 5);
	
	/*Se a probabilidade calculada for maior que a de gerar uma ilha, gere-a*/
	if (P > 1 - getIsleProb())
	{
		for (i = ponto; i < ponto + tamanhoIlha / 2.0; i++)
		{
			if (i < dir-3)
				linNova[i].terreno = getIsleChar();
		}
		for (i = ponto-1; i > ponto - tamanhoIlha / 2.0; i--)
		{
			if (i > esq+3)
				linNova[i].terreno = getIsleChar();
		}
	}
	return linNova;
}

/*--5--preencheTerreno*/
Rio* preencheTerreno(int esquerda, int direita, Rio *linhaNova)
{
	int i;
	int static ultimaIlha = 0;
	
	ultimaIlha++;
	
	for (i = 0; i < getNumColumns(); i ++)
	{
		if (i <= esquerda || i >= direita)
			linhaNova[i].terreno = getEarthChar();
		else
			linhaNova[i].terreno = getWaterChar();	
	}
	/*gera uma ilha com probabilidade aleatoria*/
	if (ultimaIlha >= getIsleDist()) {
		linhaNova = geraIlha(ultimaIlha - getIsleDist(), esquerda, direita, linhaNova);
		ultimaIlha = 0;
	}
	
	return linhaNova;
}

/*--6--normalizaVelocidade*/
Rio* normalizaVelocidade(Rio *linNova, float phi, float fluxo)
{
	int i;
	if (phi == 0)
		return linNova;
	for (i = 0; i < getNumColumns(); i++)
		linNova[i].velocidade = linNova[i].velocidade * fluxo / phi;
	return linNova;
}

/*--7--preencheVelocidade*/
Rio* preencheVelocidade(float fluxo, Rio *linAnterior, Rio *linNova)
{
	int i;
	float phi = 0, variacao, ajuste, interpolacao;
	linNova[0].velocidade = 0;
	linNova[getNumColumns()-1].velocidade = 0;

	/*caso 1: primeira linha*/
	if (linAnterior == NULL)
	{
		for (i = 1; i < getNumColumns()-1; i++)
		{
			/*velocidade = 0 do lado de terra*/
			if (linNova[i].terreno == getEarthChar() || linNova[i]. terreno == getIsleChar() ||
			(linNova[i].terreno == getWaterChar() && (linNova[i+1].terreno == getEarthChar() ||
			linNova[i-1].terreno == getEarthChar() || linNova[i+1].terreno == getIsleChar() || 
			linNova[i-1].terreno == getIsleChar())))
				linNova[i].velocidade = 0;
			/*velocidade aleatoria e calculo parcial do fluxo da linha */
			else 
			{
				linNova[i].velocidade = ((double)(rand() + 1) / RAND_MAX) * getWaterSpeed();
				phi += linNova[i].velocidade;
			}
		}
		/*devolve linha normalizada*/
		return normalizaVelocidade(linNova, phi, fluxo);
	}
	for (i = 1; i < getNumColumns()-1; i++)
	{
		variacao = ((double)(rand() + 1) / RAND_MAX) * (getWaterSpeed() / 10);
		/*velocidade = 0 do lado de terra*/
		if (linNova[i].terreno == getEarthChar() || linNova[i]. terreno == getIsleChar() ||
		(linNova[i].terreno == getWaterChar() && (linNova[i+1].terreno == getEarthChar() ||
		linNova[i-1].terreno == getEarthChar() || linNova[i+1].terreno == getIsleChar() || 
		linNova[i-1].terreno == getIsleChar())))
			linNova[i].velocidade = 0;
		/*velocidade pequena se o ponto anterior era terra*/
		else if (linNova[i].terreno == getWaterChar() && (linAnterior[i].terreno == getEarthChar() 
		||	linNova[i]. terreno == getIsleChar()))
		{
			linNova[i].velocidade = variacao;
			phi += linNova[i].velocidade;
		}
		/*velocidade aleatoria em funcao da velocidade da linha anterior*/
		else
		{
			ajuste = rand() / RAND_MAX;
			if (linAnterior[i].velocidade > 0)
			{
				interpolacao = (linAnterior[i-1].velocidade + linAnterior[i].velocidade +
						linAnterior[i+1].velocidade) / 3;
				if (ajuste >= 0.5)
					linNova[i].velocidade = (interpolacao + variacao);
				else 
					linNova[i].velocidade = fabs(interpolacao - variacao);
			}
			else
				linNova[i].velocidade = variacao;

			phi += linNova[i].velocidade;
		}
	}
	/*devolve velocidade normalizada*/
	return normalizaVelocidade(linNova, phi, fluxo);
}
