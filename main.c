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
#include "rio.h"
#include "grade.h"
#include "config.h"
#include "debugger.h"

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
	Rio **grade;
	int primeiraLinha, rep;
	float cronometro, tempoDecorrido = 0.0;
	time_t t1;

	

    strcpy(nomeArquivo,"debug/config.txt");

    /*lendo arquivo de entrada*/
    for (i = 1; i < argc; i++) {
        checagem = argv[i][0] + argv[i][1] + argv[i][2];
        if (checagem == ('-' + 'f' +'n'))
           strcpy(nomeArquivo,&argv[i][3]);
    }
    printf("--%s--", nomeArquivo);
    entrada = fopen(nomeArquivo,"r");
    if (entrada == NULL) {
        fprintf(stderr,"oh noes, o arquivo de config nao existe!\n");
        exit(EXIT_FAILURE);
    }
    
    /*Setando variaveis dadas ao jogo*/
    setEntradas(entrada, argc, argv);
	 depuracao = getReportData();
	
    /*Criando um menu para o jogo*/
    if (depuracao != 2 && getDebugMode() != 1) 
        menu();
    clearScreen();

    /*Caso queira testar a integridade do programa*/
	if (getReportData() == 2) {
        testeIntegridade(argv);
    }
    
    /*Chama o jogo*/
	else {
		/*
		Tirar o modo por tempo;
		Colocar pra rodar infinitamente;
		*/
		grade = alocaGrade();

        if (getSeed() <= 0)
            seed = time(NULL);
        else
            seed = getSeed();
	    srand(seed);
        fluxo = getRiverFlux();

        primeiraLinha = linha = 0;
        
        rep = getNumIterations();
        /*printf("%d %d\n", rep, getNumIterations());*/
        while (rep > 0) {
        	
        	grade = geraRio(primeiraLinha, linha, fluxo, grade);

        	/*graficos*/
        	/*printf("%d\n", getNumIterations());*/
        	printGrade(grade, primeiraLinha, tempoDecorrido);

        	primeiraLinha++;
        	if (primeiraLinha == getNumLines()) 
				primeiraLinha = 0;

			linha = primeiraLinha - 1;
			if (linha < 0) 
				linha = getNumLines()-1;

			/*Delay entre a geracao de quadros*/
			usleep(getRefreshRate());

			if (rep > 0)
			rep--;
		}

		freeGrade(grade);
    }
    
    fclose(entrada);
	return 0;
}

/*FUNCOES AUXILIARES*/
void menu() {
    int opcao;
    char entrada[MAXLINE];

	while(TRUE) {
	    clearScreen();
	    printf("******************************\n");
	    printf("*     CANOAGEM SIMULATOR     *\n");
	    printf("******************************\n");
	    printf("* (1) Iniciar o jogo         *\n");
	    printf("* (2) Configuracoes          *\n");
	    printf("* (3) sair                   *\n");
	    printf("******************************\n");
	    printf("Escolha uma opcao:");
        fgets(entrada,MAXLINE,stdin);
        opcao = atoi(entrada);

	    if (opcao == 1)
	    	 break;
	
       else if (opcao == 2) {
       	 mudaAtributos();
       	 break;
	    }
       else if (opcao == 3)
	       exit(0);
       else
          continue;
	}
}

void testeIntegridade(char** argv) {
	char chamada[BUFSIZ];

	printf("******************************\n"
		   "Iniciando testes de robustez\n"
		   "******************************\n");
	sleep(1);
	printf("Teste 1: colunas muito grandes\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeColuna.txt -rd1 -ie1");
	system(chamada);

	printf("Teste 2: colunas muito pequenas\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeColuna2.txt -rd1 -ie1");
	system(chamada);

	printf("Teste 3: linhas muito grandes\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeLinha.txt -rd1 -ie1");
	system(chamada);

	printf("Teste 4: linhas muito pequenas\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeLinha2.txt -rd1 -ie1");
	system(chamada);

	printf("Teste 5: margens se tocando\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeMargens.txt -rd1 -ie1");
	system(chamada);

	printf("Teste 6: Fluxo muito pequeno\n"
		   "------------------------------\n");
	sleep(1);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/testeFluxo.txt -rd1 -ie1");
	system(chamada);

	printf("***********************************************\n"
         "Viva! O programa nao quebrou!\n"				
		   "Testes de robustez encerrados.\n"
		   "***********************************************\n");
	sleep(2);
	printf("Teste 7: Corretude do programa em condicoes normais\n"
			   "-------------------------------------------------\n");
	sleep(2);
	strcpy(chamada, argv[0]);
	strcat(chamada, " -fndebug/config.txt -rd1 -ie1");
	system(chamada);
	
	printf("***********************************************\n"
         "Bateria de testes terminada.\n"				
		   "Obrigado pela paciencia e ate mais!\n"
		   "(Lembre-se: voce pode testar manualmente se quiser)\n"
		   "***********************************************\n\n");
	sleep(1);
}

