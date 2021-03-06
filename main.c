/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

main.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "rio.h"
#include "grade.h"
#include "config.h"
#include "debugger.h"
#include "graficos.h"
#include "grade.h"
#define LARGURA 640
#define ALTURA 480

/*Prototipos*/
void testeIntegridade(char** argv);
void menu();

/*MAIN*/
int main (int argc, char **argv) 
{
	int i, checagem, seed, depuracao, linha;
	char nomeArquivo[MAXLINE];
	float fluxo;
	FILE* entrada;
	Rio **grade, **atual;
	int primeiraLinha, rep;

	ALLEGRO_BITMAP *fundo = NULL;
	ALLEGRO_BITMAP *canoa = NULL;

    strcpy(nomeArquivo,"debug/config.txt");

    /*lendo arquivo de entrada*/
    for (i = 1; i < argc; i++) {
        checagem = argv[i][0] + argv[i][1] + argv[i][2];
        if (checagem == ('-' + 'f' +'n'))
           strcpy(nomeArquivo,&argv[i][3]);
    }
    entrada = fopen(nomeArquivo,"r");
    if (entrada == NULL) {
        fprintf(stderr,"oh noes, o arquivo de config nao existe!\n");
        exit(EXIT_FAILURE);
    }
    
    /*Setando variaveis dadas ao jogo*/
    setEntradas(entrada, argc, argv);
	depuracao = getReportData();

	if (criaJanela(LARGURA, ALTURA) == -1) {
		fprintf(stderr, "Desculpe, nao consegui gerar uma janela...\n");
		exit(-1);
	}
	
    /*Criando um menu para o jogo*/
    if (depuracao != 2 && getDebugMode() != 1) 
        menu();

    /*Caso queira testar a integridade do programa*/
	if (getReportData() == 2) {
        testeIntegridade(argv);
    }
    
    /*Chama o jogo*/
    else {
		if (getSeed() <= 0)
			seed = time(NULL);
		else
			seed = getSeed();
		srand(seed);
		fluxo = getRiverFlux();

		primeiraLinha = linha = 0;
      	rep = getNumIterations();

		/*carregando imagens apenas uma vez*/
		fundo = al_load_bitmap("textures/texture.png");
		canoa = al_load_bitmap("images/canoe_b.png");

		/*alocando grade de atualizacao do rio*/
		grade = alocaGrade();
		atual = alocaGrade();

			while (rep > 0 || rep < 0) {
        
        	atual = geraRio(primeiraLinha, linha, fluxo, atual);
			grade = criaImagemGrade(atual, grade, primeiraLinha);
			
			desenhaRio(grade, fundo);
			desenhaCanoa(canoa);
			al_flip_display();
			al_rest(0.05);
			al_clear_to_color(al_map_rgb(0, 0, 0));
		
        	primeiraLinha++;
        	if (primeiraLinha == getNumLines()) 
				primeiraLinha = 0;

			linha = primeiraLinha - 1;
			if (linha < 0) 
				linha = getNumLines() - 1;

			if (rep > 0)
				rep--;
		}
		/*liberando o entulho*/
		freeGrade(grade);
		freeGrade(atual);
		al_destroy_bitmap(fundo);
		al_destroy_bitmap(canoa);
	}
    
    fclose(entrada);
	destroiJanela();
	return 0;
}


/*FUNCOES AUXILIARES*/
void menu() {
    int opcao;

    opcao = desenhaMenu(LARGURA,ALTURA);
    if (opcao == 2) {
       desenhaSetup(); 
    }

    else if (opcao == 3) {
       destroiJanela();
       exit(1);
    }
}

