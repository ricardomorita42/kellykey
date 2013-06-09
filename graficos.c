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
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

    /*Carregando teclado*/
    if(!al_install_keyboard()) {
        fprintf(stderr,"nao consegui iniciar o teclado");
        exit(EXIT_FAILURE);
    }

    /*Iniciando a fila de eventos*/
    eventQueue= al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr,"nao consegui iniciar a fila de eventos");
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
    
    /*Desenhando o Menu*/
    al_draw_scaled_bitmap(imagem,0,0,640,480,0,0,800,500,0);
    al_draw_text(fonte,al_map_rgb(255,255,255),largura/2+2,92,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
    al_draw_text(fonte,al_map_rgb(0,0,0),largura/2,90,ALLEGRO_ALIGN_CENTRE,"Extreme Canoeing");
    al_flip_display();
    al_rest(0.5);

    al_draw_text(fonte2,al_map_rgb(255,255,255),largura/2+1,altura/2+51,ALLEGRO_ALIGN_CENTRE,"Digite uma opção:");
    al_draw_text(fonte2,al_map_rgb(0,0,0),largura/2,altura/2+50,ALLEGRO_ALIGN_CENTRE,"Digite uma opção:");
    al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+110,ALLEGRO_ALIGN_CENTRE,"(1) Iniciar o Jogo");
    al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+130,ALLEGRO_ALIGN_CENTRE,"(2) Setup");
    al_draw_text(fonte3,al_map_rgb(0,0,160),largura/2,altura/2+150,ALLEGRO_ALIGN_CENTRE,"(3) Sair");
    al_flip_display();

    while (!done) {
        al_wait_for_event(eventQueue,&event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_1)
                return TRUE;
            else if (event.keyboard.keycode == ALLEGRO_KEY_2) {
                return 2;
                }
            else if (event.keyboard.keycode == ALLEGRO_KEY_3) {
                al_destroy_event_queue(eventQueue);
                return 3;
            }
            else
                continue;
        }

    }
    return FALSE;
}

void desenhaSetup() {
    int sair = FALSE;
    int trocar = FALSE;
    int valor,novo, i;
    float novof;
    char str[3];
    char str2[10];

    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fonte2 = NULL;
    ALLEGRO_FONT *fonte3 = NULL;
    ALLEGRO_FONT *fonte4 = NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

    /*Carregando fontes para serem usadas*/
    fonte = al_load_font("fonts/pirulen.ttf",12,0);
    if (!fonte) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte2 = al_load_font("fonts/metalord.ttf",48,0);
    if (!fonte2) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte3 = al_load_font("fonts/metalord.ttf",24,0);
    if (!fonte3) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }
    fonte4 = al_load_font("fonts/pirulen.ttf",12,0);
    if (!fonte4) {
        fprintf(stderr,"nao consegui abrir o ttf_addon");
        exit(EXIT_FAILURE);
    }

    /*Iniciando a fila de eventos*/
    eventQueue= al_create_event_queue();
    if (!eventQueue) {
        fprintf(stderr,"nao consegui iniciar a fila de eventos");
        exit(EXIT_FAILURE);
    }
    /* Adicionando eventos para a fila*/
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    for (i = 0; i < 4; i++)
        str[i] = '\0';

    for (i = 0; i < 11; i++)
        str2[i] = '\0';

    while (sair != TRUE) {
        al_wait_for_event(eventQueue,&event);


        if (trocar == FALSE) {
            if(event.type == ALLEGRO_EVENT_KEY_CHAR) {
                if (strlen(str) < 2) {
                    if (event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9')
                        str[strlen(str)] = event.keyboard.unichar;
                    if (event.keyboard.unichar == '.' || event.keyboard.unichar == ',' )
                        str[strlen(str)] = '.';
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0) 
                    str[strlen(str)-1] = '\0';
            }
        }

        else {
            if(event.type == ALLEGRO_EVENT_KEY_CHAR) {
                if (strlen(str2) < 9) {
                    if (event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9')
                        str2[strlen(str2)] = event.keyboard.unichar;
                    if (event.keyboard.unichar == '.' || event.keyboard.unichar == ',' )
                        str2[strlen(str2)] = '.';
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0) 
                    str2[strlen(str2)-1] = '\0';
            }
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            if (trocar == FALSE) {
                sscanf(str,"%d",&valor);
                if (valor == 14) {
                    if (strlen(checaAtributosGraf()) == 0)
                        break;
                    for (i = 0; i < 4; i++)
                        str[i] = '\0';
                }

                else
                    trocar = TRUE;
            }

            else {
                if (valor <= 10) {
                    sscanf(str2,"%d",&novo);
                    switch (valor) {
                        case 1:
                            setParametro("NUM_LINES",novo);
                            break;
                        case 2:
                            setParametro("NUM_COLUMNS",novo);
                            break;
                        case 3:
                            setParametro("LEFT_MARGIN_LIMIT",novo);
                            break;
                        case 4:
                            setParametro("RIGHT_MARGIN_LIMIT",novo);
                            break;
                        case 5:
                            setParametro("NSEED",novo);
                            break;
                        case 6:
                            setParametro("REFRESH_RATE",novo);
                            break;
                        case 7:
                            setParametro("MIN_ISLE_DIST",novo);
                            break;
                        case 8:
                            setParametro("REPORT_DATA",novo);
                            break;
                        case 9:
                            setParametro("NUM_ITERATIONS",novo);
                            break;
                        case 10:
                            setParametro("NUM_SECONDS",novo);
                            break;
                    }
                }

                else {
                    sscanf(str2,"%f",&novof); 
                    if (valor == 11) setParametrof("H20_MAX_SPEED", novof);
                    else if (valor == 12) setParametrof("PROB_GEN_ISLE",novof);
                    else if (valor == 13) setParametrof("RIVER_FLUX",novof);
                }

                for (i = 0; i < 11; i++)
                    str2[i] = '\0';
                for (i = 0; i < 4; i++)
                    str[i] = '\0';
                trocar =  FALSE;
            }
            
        }
        
	    al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(fonte2,al_map_rgb(255,255,255),50,30,ALLEGRO_ALIGN_LEFT,"Setup");
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,100,5,0, "(1) Num linhas do rio:%d\n",getNumLines());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,120,5,0, "(2) Num colunas do rio:%d\n", getNumColumns());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,140,5,0, "(3) Posicao margem esquerda: %d\n", getLeftMargin());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,160,5,0, "(4) Posicao margem direita: %d\n", getRightMargin());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,180,5,0, "(5) Seed (< 0 = aleatorio): %d\n", getSeed());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,200,5,0, "(6) Frequencia de atualizacao: %d\n", getRefreshRate());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,220,5,0, "(7) Distancia minima entre ilhas: %d\n", getIsleDist());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,240,5,0, "(8) Opção de debugagem (1 = ligado, 2 = testes automaticos): %d\n", getReportData());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,260,5,0, "(9) Numero de iteracoes (< 0 -> infinito): %d\n",getNumIterations());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,280,5,0, "(10) Numero de segundos (< 0 -> infinito): %d\n",getNumSeconds());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,300,5,0, "(11) Velocidade maxima da agua: %.2f\n",getWaterSpeed());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,320,5,0, "(12) Probabilidade de gerar uma ilha: %.2f\n", getIsleProb());
        al_draw_justified_textf(fonte, al_map_rgb(255,255,255),75,500,340,5,0, "(13) Fluxo do Rio: %.2f\n", getRiverFlux());
        al_draw_text(fonte3,al_map_rgb(255,255,255),50,370,ALLEGRO_ALIGN_LEFT,"Escolha (14 = sair):");
        al_draw_text(fonte3,al_map_rgb(255,255,255),260,370,ALLEGRO_ALIGN_LEFT,str);
        if (trocar == TRUE) {
            al_draw_text(fonte3,al_map_rgb(255,255,255),50,400,ALLEGRO_ALIGN_LEFT,"Digite o novo valor:");
            al_draw_text(fonte3,al_map_rgb(255,255,255),300,400,ALLEGRO_ALIGN_LEFT,str2);
        }
        al_draw_text(fonte4,al_map_rgb(255,255,255),50,440,ALLEGRO_ALIGN_LEFT,checaAtributosGraf());
        al_flip_display();
    }
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
	al_rest(0.05);
	al_destroy_bitmap(copia);
	freeGrade(grade);
}
