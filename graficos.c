/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    graficos.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "rio.h"
#include "config.h"
#include "graficos.h"
#include "grade.h"
#define D 5

ALLEGRO_DISPLAY *janela = NULL;

int criaJanela(int largura, int altura)
{

	if (!al_init())
		return -1;

	janela = al_create_display(largura, altura);
	if (!janela)
		return -1;
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
        return -1;
    }

	return 0;
}

void destroiJanela() {
    al_destroy_display(janela);
}

int desenhaMenu(int largura, int altura)
{
    int done = FALSE;
    /*Iniciando variaveis do Allegro*/
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fonte2 = NULL;
    ALLEGRO_FONT *fonte3 = NULL;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

    /*Carregando teclado*/
    if(!al_install_keyboard()) {
        fprintf(stderr,"nao consegui iniciar o teclado");
        exit(EXIT_FAILURE);
    }

    /*Iniciando o timer*/
    timer = al_create_timer(1.0 / 60);
    if (!timer) {
        fprintf(stderr,"nao consegui iniciar o timer");
        exit(EXIT_FAILURE);
    }

    /*Iniciando a fila de eventos*/
    eventQueue= al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr,"nao consegui iniciar o timer");
        exit(EXIT_FAILURE);
    }

    /*Carregando fundo*/
    al_init_image_addon();
    imagem = al_load_bitmap("images/background.jpg");
    if (!imagem) {
        fprintf(stderr,"nao consegui abrir a imagem de fundo");
        exit(EXIT_FAILURE);
    }

    /*Carregando fonte*/
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte = al_load_font("fonts/metalord.ttf",56,0);
    if (!fonte) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte2 = al_load_font("fonts/metalord.ttf",40,0);
    if (!fonte2) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte3 = al_load_font("fonts/pirulen.ttf",16,0);
    if (!fonte3) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }


    /* Adicionando eventos para a fila*/
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    
    /*Desenhando o Menu*/
    al_draw_scaled_bitmap(imagem,0,0,640,480,0,0,800,500,0);
    al_draw_text(fonte,al_map_rgb(255,255,255),largura/2+2,92,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
    al_draw_text(fonte,al_map_rgb(0,0,0),largura/2,90,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
    al_flip_display();
    al_rest(2.0);

    while (!done) {
        al_draw_text(fonte,al_map_rgb(255,255,255),largura/2+2,92,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
        al_draw_text(fonte,al_map_rgb(0,0,0),largura/2,90,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
        al_draw_text(fonte2,al_map_rgb(255,255,255),largura/2+1,altura/2+51,ALLEGRO_ALIGN_CENTRE,"Digite uma opção:");
        al_draw_text(fonte2,al_map_rgb(0,0,0),largura/2,altura/2+50,ALLEGRO_ALIGN_CENTRE,"Digite uma opção:");
        al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+110,ALLEGRO_ALIGN_CENTRE,"(1) Iniciar o Jogo");
        al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+130,ALLEGRO_ALIGN_CENTRE,"(2) Setup");
        al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+150,ALLEGRO_ALIGN_CENTRE,"(3) Sair");
        al_flip_display();

        al_wait_for_event(eventQueue,&event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_1)
                return TRUE;
            else if (event.keyboard.keycode == ALLEGRO_KEY_2)
                return TRUE;
            else if (event.keyboard.keycode == ALLEGRO_KEY_3) {
                al_destroy_timer(timer);
                al_destroy_event_queue(eventQueue);
                return 2;
            }
            else
                continue;
        }

    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    return FALSE;
}

void desenhaRio(Rio** grade, ALLEGRO_DISPLAY *janela, ALLEGRO_BITMAP *imagem)
{
	int i, j, k = al_get_bitmap_height(imagem)/(D);
	static int altura = 0;
	float margEsqInf[2], margEsqSup[2], margDirInf[2], margDirSup[2],
		ilhaEsq[2], ilhaDir[2];
	ALLEGRO_VERTEX vtx[4];
	/*ALLEGRO_VERTEX isl[4];*/
	ALLEGRO_BITMAP *copia = al_clone_bitmap(imagem);

	altura++;
	if (altura == k)
		altura = 0;

	al_draw_bitmap(imagem, 0, (-k*D + altura*D), 0);
	al_draw_bitmap(imagem, 0, (altura*D), 0);

	for (i = 0; i < (getNumLines() - 2); i++)
	{
		/*inicializando valores das ilhas*/
		ilhaEsq[0] = 0;

		/*extraindo os vertices*/
		for (j = 0; j < (getNumColumns() - 2); j++)
		{
			if (grade[i][j].terreno == getEarthChar() && grade[i][j+1].terreno == getWaterChar()) {
				margEsqSup[0] = i * D;
				margEsqSup[1] = j * D;
			}
			if (grade[i][j].terreno == getWaterChar() && grade[i][j+1].terreno == getEarthChar()) {
				margDirSup[0] = i * D;
				margDirSup[1] = (j+1) * D;
			}
			if (grade[i+1][j].terreno == getEarthChar() && grade[i+1][j+1].terreno == getWaterChar()) {
				margEsqInf[0] = (i+1) * D;
				margEsqInf[1] = j * D;
			}
			if (grade[i+1][j].terreno == getWaterChar() && grade[i+1][j+1].terreno == getEarthChar()) {
				margDirInf[0] = (i+1) * D;
				margDirInf[1] = (j+1) * D;
			}
			if (grade[i][j].terreno == getWaterChar() && grade[i][j+1].terreno == getIsleChar()) {
				ilhaEsq[0] = i * D;
				ilhaEsq[1] = (j+1) * D;
			}
			if (grade[i][j].terreno == getIsleChar() && grade[i][j+1].terreno == getWaterChar()) {
				ilhaDir[0] = i * D;
				ilhaDir[1] = j * D;
			}		
		}
		/*preenchendo os vertices do poligono*/
		vtx[0].x = margEsqSup[1]; vtx[0].y = margEsqSup[0]; vtx[0].color = al_map_rgb(0, 0, 200);
		vtx[1].x = margDirSup[1]; vtx[1].y = margDirSup[0]; vtx[1].color = al_map_rgb(0, 0, 200);
		vtx[2].x = margDirInf[1]; vtx[2].y = margDirInf[0]; vtx[2].color = al_map_rgb(0, 0, 200);
		vtx[3].x = margEsqInf[1]; vtx[3].y = margEsqInf[0]; vtx[3].color = al_map_rgb(0, 0, 200);
        /*for (i = 0; i < 4; i++)
            vtx[i].z = 0;*/
		
		/*desenhando*/
		al_draw_prim(vtx, NULL, 0, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
		if (ilhaEsq[0] != 0)
		{
			/*isl[0].x = ilhaEsq[1]; isl[0].y = ilhaEsq[0]-D; isl[0].color = al_map_rgb(200, 200, 0);
			isl[1].x = ilhaDir[1]; isl[1].y = ilhaDir[0]-D; isl[1].color = al_map_rgb(200, 200, 0);
			isl[2].x = ilhaDir[1]; isl[2].y = ilhaDir[0]; isl[2].color = al_map_rgb(200, 200, 0);
			isl[3].x = ilhaEsq[1]; isl[3].y = ilhaEsq[0]; isl[3].color = al_map_rgb(200, 200, 0);
			al_draw_prim(isl, NULL, copia, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);*/
			al_draw_tinted_bitmap_region(copia, al_map_rgb(50, 50, 0), ilhaEsq[1], ilhaEsq[0], 
					(ilhaEsq[1]-ilhaDir[1]), D, ilhaDir[1], ilhaDir[0], 0);
			/*al_draw_filled_rectangle(ilhaEsq[1], ilhaEsq[0]-D, ilhaDir[1], ilhaDir[0], al_map_rgb(100,100,0));*/

		}
		/*al_flip_display();
		al_rest(0.02);*/
	}
	copia = al_load_bitmap("images/canoe_b.png");
	al_draw_bitmap(copia, 320, 380, 0);
	al_flip_display();
	al_rest(0.5);
	al_destroy_bitmap(copia);
	freeGrade(grade);
}
