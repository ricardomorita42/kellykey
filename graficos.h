/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    graficos.h

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*--1--*/
void desenhaRio(Rio**, ALLEGRO_BITMAP*);
/*--2--*/
void desenhaCanoa(ALLEGRO_BITMAP*);
/*--3--*/
int desenhaMenu(int,int);
/*--4--*/
void desenhaSetup();
/*--5--*/
int criaJanela(int,int);
/*--6--*/
void destroiJanela();
/*--7--*/
void desenhaTeste(int);


/*-- 1 -- desenhaRio: Utiliza uma grade, ja com as velocidades calculadas
e terrenos em suas posicoes, e uma imagem, utilizada como textura das margens,
 para desenhar o rio. */

/*-- 2 -- desenhaCanoa: Utiliza uma imagem para representar a canoa do jogador.*/

/*-- 3 -- desenhaMenu: Desenha tela inicial do jogo.*/

/*-- 4 -- desenhaSetup: Desenha tela de opções do jogo.*/

/*-- 5 -- criaJanela: Cria uma janela e inicializa addons a serem utilizados durante o jogo.*/

/*-- 6 -- destroiJanel: Destroi janela criada.*/

/*-- 7 -- desenhaTeste: Desenha na tela os modos de teste que estão sendo executados durante 
a bateria de testes de robustez.*/