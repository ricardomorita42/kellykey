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
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "rio.h"
#include "grade.h"
#include "config.h"
#include "debugger.h"
#include "graficos.h"
#include "grade.h"
#include "controls.h"
#define LARGURA 640
#define ALTURA 480
#define TRUE 1
#define FALSE 0


ALLEGRO_DISPLAY *janela = NULL;

/*Prototipos*/
void testeIntegridade(char** argv);
void menu();

/*MAIN*/
int main (int argc, char **argv) 
{
	int i, checagem, seed, depuracao, linha, primeiraLinha, rep, pos, crash;
	char nomeArquivo[MAXLINE];
	float fluxo, refresh, *Vi;
	FILE* entrada;
	Rio **grade, **atual;

	ALLEGRO_BITMAP *fundo = NULL;
	ALLEGRO_BITMAP *canoa = NULL;
	ALLEGRO_BITMAP *gameover = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *fila = NULL;
	ALLEGRO_SAMPLE *musica = NULL;
	ALLEGRO_SAMPLE *ending = NULL;
	ALLEGRO_SAMPLE *smash = NULL;
	ALLEGRO_FONT *fonte = NULL;

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

	if (criaJanela(janela, LARGURA, ALTURA) == -1) {
		fprintf(stderr, "Desculpe, nao consegui gerar uma janela...\n");
		exit(EXIT_FAILURE);
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
		canoa = al_load_bitmap("images/canoe_c.tga");
		gameover = al_load_bitmap("images/gameover.jpg");

		/*alocando grade de atualizacao do rio*/
		grade = alocaGrade();
		atual = alocaGrade();

		/*criando uma fila de eventos*/
		fila = al_create_event_queue();
		if (!fila) {
			fprintf(stderr, "ERRO: Nao consegui criar uma fila de eventos!\n");
			exit(EXIT_FAILURE);
		}

		/*criando um timer*/
		timer = al_create_timer(1.0/60);
		if (!timer) {
			fprintf(stderr, "ERRO: Nao consegui criar um timer!\n");
			exit(EXIT_FAILURE);	
		}
		
		/*carregando arquivos de audio*/
		musica = al_load_sample("music/tirol.ogg");
		ending = al_load_sample("music/gameover.ogg");
		smash = al_load_sample("music/smash.ogg");
		if (!musica || !ending || !smash) {
			fprintf(stderr, "ERRO: Nao consegui carregar o audio do jogo!\n");
			exit(EXIT_FAILURE);
		}
		
		/*carregando fonte*/
    	fonte = al_load_font("fonts/pirulen.ttf",30,0);
    	if (!fonte) {
        	fprintf(stderr,"nao consegui encontrar a fonte pirulen.ttf\n");
        	exit(EXIT_FAILURE);
   		}

		al_register_event_source(fila, al_get_keyboard_event_source());
		al_register_event_source(fila, al_get_timer_event_source(timer));
		al_start_timer(timer);
		pos = LARGURA/2;
		al_play_sample(musica, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

		/*======== O JOGO ===========*/
		while (rep > 0 || rep < 0) {
        
        	atual = geraRio(primeiraLinha, linha, fluxo, atual);
			grade = criaImagemGrade(atual, grade, primeiraLinha);
				
			desenhaRio(grade, fundo, primeiraLinha);					
			Vi = posicionaCanoa(canoa, movimenta(fila, timer), grade, pos);
			pos = desenhaCanoa(canoa, Vi);
			crash = testaColisao(grade, pos);
			if (desenhaInfo(crash, Vi[0] * cos(Vi[1]), primeiraLinha) == 0)
			{
				al_destroy_sample(musica);
				al_rest(1.0);
				break;
			}

			al_flip_display();
			refresh  = 1/(Vi[0]*cos(Vi[1]) + 5);
			al_rest(refresh);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			if (crash == 1) {
				al_play_sample(smash, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				continue;
			}
			primeiraLinha++;
        	if (primeiraLinha == getNumLines()) 
				primeiraLinha = 0;

			linha = primeiraLinha - 1;
			if (linha < 0) 
				linha = getNumLines() - 1;

			if (rep > 0)
				rep--;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(gameover, 0, 0, 0);
		al_flip_display();
		al_play_sample(ending, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		al_rest(5.0);

		/*liberando o entulho*/
		freeGrade(grade);
		freeGrade(atual);
		al_destroy_bitmap(fundo);
		al_destroy_bitmap(canoa);
		al_destroy_sample(ending);
		al_destroy_sample(smash);
	}
    
    fclose(entrada);
	al_destroy_display(janela);
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
       al_destroy_display(janela);
       exit(1);
    }
}

