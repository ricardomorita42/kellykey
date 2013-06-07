/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP:6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    grade.h

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


/*------------------------*/
/* prototipos das funcoes */
/*------------------------*/
/*--1--*/
Rio **alocaGrade();
/*--2--*/
void freeGrade(Rio **grade);
/*--3--*/
void printGrade(Rio **grade, int primeiraLinha, float tempoDecorrido);
/*TESTE!*/
Rio** criaImagemGrade(Rio **grade, int primeiraLinha);

/*--1--alocaGrade: aloca espaco para uma matriz do tipo Rio (linhas x colunas)
       parametros: linhas e colunas da matriz */

/*--2--freeGrade: libera espaco alocado para a matriz do tipo Rio
       parametros: matriz do tipo Rio */

/*--3--printGrade: imprime uma matriz do tipo Rio na tela
       parametros: matriz do tipo Rio, indice da primeira linha, tempo decorrido */
