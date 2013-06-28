/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    controls.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "rio.h"
#include "config.h"
#include "controls.h"
#include "grade.h"
#include "graficos.h"
#define PI2 1.570796327
#define D 5
#define LARGURA 640
#define FALSE 0
#define TRUE 1

int* movimenta(ALLEGRO_EVENT_QUEUE *fila, ALLEGRO_TIMER *timer)
{
	ALLEGRO_EVENT ev;
	static int tecla = 0;
	int *mov = malloc(2*sizeof(int));
	mov[0] = 0;
	mov[1] = 0;

	/*enquanto houver um evento na fila de eventos*/
	while (!al_is_event_queue_empty(fila))
	{
		al_wait_for_event(fila, &ev);
		/*evento: enquanto a tecla estiver pressionada*/
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			/*decrementa pixels (esquerda)*/
			if (tecla == 1)
				mov[0] += 3;
			/*incrementa pixels (direita)*/
			if (tecla == 2)
				mov[1] += 3;
		}
		/*evento: tecla pressionada*/
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
				/*va para esquerda*/
				case ALLEGRO_KEY_LEFT:
					tecla = 1;
					break;
				/*va para direita*/
				case ALLEGRO_KEY_RIGHT:
					tecla = 2;
					break;
				default:
					break;
			}
		}
		/*evento: tecla levantada*/
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			tecla = 0;
	}
	return mov;
}

float* posicionaCanoa(ALLEGRO_BITMAP *canoa, int *remadas, Rio **grade, int pos)
{
	float Va[2], vd, ve;
	static float Vi[2] = {0, 0};
 	int posicao = (int)(pos/(float)D);


	ve = grade[getNumLines()-12][posicao+1].velocidade + remadas[0] * 0.8;
	vd = grade[getNumLines()-12][posicao+3].velocidade + remadas[1] * 0.8;

	if (grade[85][posicao+1].terreno == getEarthChar())
	{
		Vi[0] = remadas[1];
		Vi[1] = 0.025;
		return Vi;
	}
	else if (grade[85][posicao+3].terreno == getEarthChar())
	{
		Vi[0] = remadas[0];
		Vi[1] = -0.025;
		return Vi;
	}

	Va[0] = (vd + ve)/2;
	Va[1] = atan((vd - ve)/al_get_bitmap_width(canoa));

	Vi[0] = Vi[0] * 0.8 + Va[0];
	Vi[1] = Va[1] * 0.25 + Vi[1] * 0.75;
	free (remadas);

	return Vi;
}

int testaColisao(Rio** grade, int pos)
{
	int i;
	/*colisao com ilha*/
	for (i = 0; i < 5; i++)
	{
		if (grade[84+i][(int)(pos/(float)D)+2].terreno == getIsleChar())
			return TRUE;
	}

	/*colisao com margem*/
	for (i = 0; i < 5; i++)
	{
		if (grade[85+i][(int)(pos/D)].terreno == getEarthChar()
		|| grade[85+i][(int)(pos/D)+3].terreno == getEarthChar())
			return TRUE;
	}
	return FALSE;
}
