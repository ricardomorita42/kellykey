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

#include "graficos.h"
#include "rio.h"

/* int main()
 * {
 * 	pintaRio();
 * 	return 0;
 * }
 */
void pintaRio()
{
 
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_VERTEX v[4];
	ALLEGRO_BITMAP *image = NULL;

   	v[0].x = 128; v[0].y = 50; v[0].z = 0; v[0].color = al_map_rgb(150, 150, 150);
	v[1].x = 50; v[1].y = 256; v[1].z = 0; v[1].color = al_map_rgb(150, 150, 150);
	v[2].x = 256; v[2].y = 256; v[2].z = 0; v[2].color = al_map_rgb(150, 150, 150);
	v[3].x = 340; v[3].y = 340; v[3].z = 0; v[3].color = al_map_rgb(150, 150, 150);
	/*v[3].x = 140; v[3].y = 128; v[3].z = 0; v[3].u = 128; v[3].v = 128;*/

	if(!al_init())
   	{
		fprintf(stderr, "Nao consegui inicializar o allegro!\n");
		exit(-1);
   	}

	if(!al_init_primitives_addon())
	{
		fprintf(stderr, "Xiiii\n");
		exit(-1);
	}

	if(!al_init_image_addon()) 
	{
		fprintf(stderr, "Nao consegui abrir a imagem!\n");		
		exit(-1);
	}
 
	display = al_create_display(640, 480); /*substituir por get_tamanho()*/
	if(!display)
	{
		fprintf(stderr, "nao consegui criar o display!\n");
		exit(-1);
  	}
	al_clear_to_color(al_map_rgb(40,30,30));
	al_flip_display();

	image = al_load_bitmap("image.png");
	al_draw_prim(v, NULL, 0, 0, 4, ALLEGRO_PRIM_LINE_LOOP);
	al_flip_display();
	al_rest(5.0);
 
	al_destroy_display(display);
}



