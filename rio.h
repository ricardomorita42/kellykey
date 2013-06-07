/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP:6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
   rio.h 

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*--------------------*/
/* tipos e estruturas */
/*--------------------*/
/*rio: representa um ponto do rio que guarda o tipo
  de terreno e a velocidade desse ponto */
typedef struct rio
{
	char terreno;
	float velocidade;
} Rio;

/*------------------------*/
/* prototipos das funcoes */
/*------------------------*/
/*--1--*/
Rio** geraRio(int primeiraLinha, int linha, float fluxoEsperado, Rio **grade);
/*--2--*/
Rio* geraLinha(Rio *linhaNova, Rio *linhaAnterior, float fluxo);
/*--3--*/
int sorteiaMargem(char lado, Rio *linAnterior);
/*--4--*/
Rio* geraIlha(int n, int esq, int dir, Rio *linNova);
/*--5--*/
Rio* preencheTerreno(int esquerda, int direita, Rio *linhaNova);
/*--6--*/
Rio* normalizaVelocidade(Rio *linNova, float phi, float fluxo);
/*--7--*/
Rio* preencheVelocidade(float fluxo, Rio *linAnterior, Rio *linNova);

/*--1--geraRio: cria uma imagem a partir de uma matriz de varias linhas
                do tipo Rio
       parametros: fluxo esperado */
       
/*--2--geraLinha: gera uma linha do tipo Rio
       parametros: Rio novo pre-alocado, Rio anterior ao atual, fluxo desejado */ 

/*--3--sorteiaMargem: devolve a posicao de um dos lados da margem numa linha nova
       parametros: lado da margem, Rio anterior ao atual */

/*--4--geraIlha: devolve uma ilha a ser inserida no Rio atual
       parametros: numero de ensaios, posicao da margem esquerda
                   posicao da margem direita, Rio atual */

/*--5--preencheTerreno: devolve um Rio com terrenos preenchidos
       parametros: posicoes da margem esquerda e da direita */

/*--6--normalizaVelocidade: normaliza todas as velocidades para o fluxo desejado
       parametros: Rio atual, fluxo calculado, fluxo desejado */   

/*--7--preencheVelocidade: devolve um Rio com todas as velocidades preenchidas
       parametros: fluxo desejado, Rio anterior, Rio atual */
