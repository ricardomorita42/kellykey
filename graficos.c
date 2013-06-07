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
#include <allegro5/allegro_primitives.h>
#include "rio.h"
#include "config.h"
#include "graficos.h"
#include "grade.h"
#define D 5

int criaJanela(int largura, int altura)
{
	ALLEGRO_DISPLAY *janela = NULL;

	if (!al_init())
		return -1;

	janela = al_create_display(largura, altura);
	if (!janela)
		return -1;
	return 0;
}

void desenhaMenu()
{
    return;
}

void desenhaRio(Rio** grade)
{
	int i, j, margEsqInf[2], margEsqSup[2], margDirInf[2], margDirSup[2],
		ilhaEsq[2], ilhaDir[2];
	ALLEGRO_VERTEX vtx[4];
	al_clear_to_color(al_map_rgb(90, 90, 0));
	/*al_flip_display();*/

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
			al_draw_filled_rounded_rectangle(ilhaEsq[1], ilhaEsq[0]+D, ilhaDir[1], ilhaDir[0], 0.5, 0.5, al_map_rgb(90, 90, 0));
		/*al_flip_display();
		al_rest(0.01);*/
	}	
    al_flip_display();
	al_rest(0.1);
	free(grade);
}
