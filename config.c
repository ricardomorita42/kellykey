/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP: 6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    config.c

Materia:
    Canoagem    

Referencias:
	Muitas paginas do man
    clearScreen(): http://stackoverflow.com/questions/2347770/how-do-you-clear-console-screen-in-c

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include "config.h"

/*Prototipos de funcoes que sao usadas pelo config.c*/
void setParametro(char*, int);
void setParametrof(char*, float);
void setParametroc(char*, char);
void queroInt(int);
void queroFloat(int);
void queroChar(int);
void checaEntradas(int);
int checaAtributos();
void imprimeAtributos();
int converteString(char*);   

/*variaveis para usar no config.c*/
static int leftMargin=30,
           rightMargin=70,
           seed=-1,
           refreshRate=100,
           isleDist=4,
           numLines=30,
           numColumns=100,
           numIterations=0,
           numSeconds=0,
           reportData=0,
           debugMode=0;
static float waterSpeed=-1,
             isleProb=0.5,
             riverFlux=40;
static char water='.',
            earth='#',
            isle='#';


/* Esta funcao le do arquivo de entrada e seta as variaveis do jogo.
 * Tambem le do STDIN e sobrescreve o que foi lido do arquivo. */
void setEntradas(FILE* entrada, int numEntradas, char* entradaUsuario[]) {
    char caract, c, word[10];
    char parametro[MAXLINE];
    int i, checagem, valor;
    float valorf;

    /*Leitura do arquivo (padrao:config.txt)*/
    while ((c = fgetc(entrada)) != EOF ){
        /*Ignora comentários*/
        if (c == ';' || c == '\n') { 
            while ((fgetc(entrada)) != '\n') {
            }
            continue;
        }

        /*Achou uma potencial linha de argumento*/
        if (c >= 'A' && c <= 'Z') {
            ungetc(c, entrada);
            
            /*Checa qual e' o parâmetro*/
            checagem = fscanf(entrada,"%s =", parametro);
            
            /*se for float, usa o setParametrof(proprio para floats)*/
            if (strcmp(parametro,"PROB_GEN_ISLE") == 0 || strcmp(parametro,"RIVER_FLUX") == 0 
                    || strcmp(parametro,"H20_MAX_SPEED") == 0) {
                fscanf(entrada, "%f", &valorf);
                setParametrof(parametro,valorf);
            }

            /*se for char, usa o setParametroc(proprio para chars)*/
            else if (strcmp(parametro,"DEF_WATER") == 0|| strcmp(parametro,"DEF_EARTH") == 0 
                    || strcmp(parametro,"DEF_ISLE") == 0) {
                fscanf(entrada," ");
                fscanf(entrada,"%1c",&caract);
                setParametroc(parametro,caract);
            }

            /*caso contrario, usa o setParametro(proprio para ints)*/
            else {
                fscanf(entrada, "%d", &valor); 
                setParametro(parametro,valor);
           }
        }
    }

    /*Leitura das entradas do usuario*/
    for (i = 1; i < numEntradas; i++) {

        checagem = entradaUsuario[i][0] + entradaUsuario[i][1] + entradaUsuario[i][2];

        switch (checagem) {
            case LEFTMARGIN: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("LEFT_MARGIN_LIMIT",valor);
                break;

            case RIGHTMARGIN: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("RIGHT_MARGIN_LIMIT",valor);
                break;

            case H20MAXSPEED: 
                strcpy(word,&entradaUsuario[i][3]);
                valorf = atof(word);
                setParametrof("H20_MAX_SPEED",valorf);
                break;

            case SEED: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("NSEED",valor);
                break;

            case REFRESHRATE: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("REFRESH_RATE",valor);
                break;

            case MINISLEDIST: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("MIN_ISLE_DIST",valor);
                break;

            case PROBGENISLE: 
                strcpy(word,&entradaUsuario[i][3]);
                valorf = atof(word);
                setParametrof("PROB_GEN_ISLE",valorf);
                break;

            case NUMLINES: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("NUM_LINES",valor);
                break;

            case NUMCOLUMNS:
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("NUM_COLUMNS",valor);
                break;

            case NUMITERATIONS: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("NUM_ITERATIONS",valor);
                break;

            case NUMSECONDS: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("NUM_SECONDS",valor);
                break;

            case RIVERFLUX: 
                strcpy(word,&entradaUsuario[i][3]);
                valorf = atof(word);
                setParametrof("RIVER_FLUX",valorf);
                break;

            case REPORTDATA: 
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                setParametro("REPORT_DATA",valor);
                break;

            case IGNOREERROR:
                strcpy(word,&entradaUsuario[i][3]);
                valor = atoi(word);
                if (valor == 1 || valor == 0)
                    debugMode = valor;
                break;

            case WATERSYMBOL: 
                setParametroc("DEF_WATER",entradaUsuario[i][3]);
                break;

            case EARTHSYMBOL: 
                setParametroc("DEF_EARTH",entradaUsuario[i][3]);
                break;

            case ISLESYMBOL: 
                setParametroc("DEF_ISLE",entradaUsuario[i][3]);
                break;

            default:
                printf("%s nao e' um argumento valido.\n", entradaUsuario[i]);
                break;
        }
    }
    checaEntradas(debugMode);
}

/*Atribui o valor do argumento ao parametro (versao para int)*/
void setParametro(char *parametro, int argumento) {
    int entrada;

    entrada = converteString(parametro); 

   if (entrada == converteString("NUM_LINES"))
        numLines = argumento;

    else if (entrada == converteString("NUM_COLUMNS"))
        numColumns = argumento;

    else if (entrada == converteString("NUM_ITERATIONS"))
        numIterations = argumento;

    else if (entrada == converteString("NUM_SECONDS"))
        numSeconds = argumento;

    else if  (entrada == converteString("LEFT_MARGIN_LIMIT"))
        leftMargin = argumento;

    else if (entrada == converteString("RIGHT_MARGIN_LIMIT"))
        rightMargin = argumento;

    else if (entrada == converteString("NSEED"))
        seed = argumento;

    else if (entrada == converteString("REFRESH_RATE"))
        refreshRate = argumento;

    else if (entrada == converteString("MIN_ISLE_DIST"))
        isleDist = argumento;

    else if (entrada == converteString("REPORT_DATA"))
        reportData = argumento;
    
    else
        printf("%s nao e' um argumento valido.", parametro);
}

/*Atribui o valor do argumento ao parametro (versao para float)*/
void setParametrof(char *parametro, float argumento) {
    int entrada;

    entrada = converteString(parametro); 

    if (entrada == converteString("H20_MAX_SPEED"))
        waterSpeed = argumento;

    else if (entrada == converteString("PROB_GEN_ISLE"))
        isleProb = argumento;

    else if (entrada == converteString("RIVER_FLUX"))
        riverFlux = argumento;

    else
        printf("%s nao e' um argumento valido.", parametro);
}

/*Atribui o valor do argumento ao parametro (versao para char)*/
void setParametroc(char* parametro, char argumento) {
    int entrada;

    entrada = converteString(parametro); 

    if (entrada == converteString("DEF_WATER"))
        water = argumento;

    else if (entrada == converteString("DEF_ISLE"))
        isle = argumento;

    else if (entrada == converteString("DEF_EARTH"))
        earth = argumento;

    else
        printf("%s nao e' um argumento valido.", parametro);
}

/*Funcoes para retornar os valores ao main*/
int getLeftMargin()     { return leftMargin; }
int getRightMargin()    { return rightMargin; }
float getWaterSpeed()   { return waterSpeed; }
int getSeed()           { return seed; }
int getRefreshRate()    { return refreshRate; }
int getIsleDist()       { return isleDist; }
float getIsleProb()     { return isleProb; }
int getNumLines()       { return numLines;}
int getNumColumns()     { return numColumns; }
int getNumIterations()  { return numIterations; }
int getNumSeconds()     { return numSeconds; }
float getRiverFlux()    { return riverFlux; }
int getReportData()     { return reportData; }
int getDebugMode()      { return debugMode; }
char getWaterChar()     { return water; }
char getEarthChar()     { return earth; }
char getIsleChar()      { return isle; }

/*Funcoes Auxiliares*/
int converteString(char* x) {
    int i, valor = 0;

    for (i = 0; i < strlen(x);i++)
        valor +=x[i];
    return valor;
}

/*Checa se existe algum atributo conflitante*/
int checaAtributos(int debug) {
    int n = 0;

    clearScreen();
    if (debug != TRUE) { 
        if (numLines < 1) 
            { printf("Numero de linhas invalido!\n"); n++; }

    	if (numColumns < 1) 
            { printf("Numero de colunas invalido!\n"); n++;	}

   	    if (numColumns <= leftMargin) 
            { printf("Numero de colunas e' menor que a margem esquerda.\n"); n++; }

   	    if (numColumns <= rightMargin) 
            { printf("Numero de colunas e' menor que a margem direita.\n"); n++; }

       	if (leftMargin >= rightMargin) 
            { printf("Margem esquerda nao pode ser maior ou igual 'a direita.\n"); n++; }

   	    if (numIterations > 0 && numSeconds > 0) 
            { printf("Dentre (9) e (10), apenas uma das duas pode ter um valor.\n"); n++; }

   	    if (reportData < 0 || reportData > 2) 
            { printf("Debugagem deve ser (2=testador), (1=on) ou (0=off)\n"); n++; }

   	    if (refreshRate <= 0) 
            { printf("Frequencia de atualizacao deve ser maior que 0.\n"); n++; }

   	    if (isleDist <= 0) 
            { printf("Distancia entre as ilhas deve ser maior que 0.\n"); n++; }

   	    if (waterSpeed <= 0) 
            { printf("Velocidade maxima da agua deve ser maior que 0.\n"); n++; }

   	    if (isleProb >1 || isleProb < 0) 
            { printf("Probabilidade de gerar ilha deve estar no interavalo [0;1].\n"); n++; }

   	    if (n != 0) 
            { printf("\nPor favor corrija os %d erros acima.\n",n); }
    }
    return n;
}

char* checaAtributosGraf() {
    char *temp;
    if (numLines < 1) {
        temp = "Numero de linhas invalido!";
        return temp;
    }

    else if (numColumns < 1) {
        temp = "Numero de colunas invalido!";
        return temp;
    }

   	if (numColumns <= leftMargin) { 
        temp = "Numero de colunas e' menor que a margem esquerda.";
        return temp;
    }

   	if (numColumns <= rightMargin) {
        temp = "Numero de colunas e' menor que a margem direita.";
        return temp;
    }

    if (leftMargin >= rightMargin) {
        temp = "Margem esquerda nao pode ser maior ou igual 'a direita.";
        return temp;
    }

   	if (numIterations > 0 && numSeconds > 0) { 
        temp = "Dentre (9) e (10), apenas uma das duas pode ter um valor.";
        return temp;
    }

   	if (reportData < 0 || reportData > 2) { 
        temp = "Debugagem deve ser (2=testador), (1=on) ou (0=off)";
        return temp;
    }

   	if (refreshRate <= 0) { 
        temp = "Frequencia  de atualizacao deve ser maior que 0.";
        return temp;
    }

   	if (isleDist <= 0) { 
        temp = "Distancia entre as ilhas deve ser maior que 0.";
        return temp;
    }

   	if (waterSpeed <= 0) { 
        temp = "Velocidade maxima da agua deve ser maior que 0.";
        return temp;
    }

   	if (isleProb >1 || isleProb < 0) { 
        temp = "Probabilidade de gerar ilha deve estar no interavalo [0;1].";
        return temp;
    }

    else {
        temp = "";
        return temp;
    }
}

/*Caso haja algum parametro invalido, so libera caso os parametros se tornem validos.*/
void checaEntradas(int debugagem) {
    int n, item;
    char entrada[MAXLINE];

    while ((n = checaAtributos(debugagem)) != 0) {
        imprimeAtributos();
        printf("Parametro para mudar:");

        fgets(entrada,MAXLINE,stdin);
        item = atoi(entrada);

        if (item >= 1 && item <= 10)
            queroInt(item);

        if (item >= 11 && item <= 13)
            queroFloat(item);

        if (item >= 14 && item <= 16) 
            queroChar(item);
    }
}

/*Chamado dentro do programa para mudar as variaveis.
So permite o retorno caso todas as variaveis sejam validas.*/
void mudaAtributos() {
    int n, item;
    char entrada[MAXLINE];

    clearScreen();

    while (TRUE) {
        n = checaAtributos(FALSE);
        imprimeAtributos();
        printf("Parametro para mudar (17 para CANOAR!):");

        fgets(entrada,MAXLINE,stdin);
        item = atoi(entrada);

        if (item >= 1 && item <= 10)
            queroInt(item);

        if (item >= 11 && item <= 13)
            queroFloat(item);

        if (item >= 14 && item <= 16) 
            queroChar(item);

        if (item == 17 && n == 0) 
            break;

        clearScreen();
    }
}

void queroInt(int valor) {
    char entrada[MAXLINE];
    int saida;

    printf("Insira um novo valor para (%d):",valor);
    fgets(entrada,MAXLINE,stdin);
    saida = atoi(entrada);

    switch (valor) {
        case 1:
            numLines = saida;
            break;

        case 2:
            numColumns = saida;
            break;

        case 3:
            leftMargin = saida;
            break;

        case 4:
            rightMargin = saida;
            break;

        case 5:
            seed = saida;
            break;

        case 6:
            refreshRate = saida;
            break;

        case 7:
            isleDist = saida;
            break;

        case 8:
            reportData = saida;
            break;

        case 9:
            numIterations = saida;
            break;

        case 10:
            numSeconds = saida;
            break;

        default:
            break;
    }
    fflush(stdin);
}

void queroFloat(int valor) {
    char entrada[MAXLINE];
    float saida;

    printf("Insira um novo valor para (%d):",valor);
    fgets(entrada,MAXLINE,stdin);
    saida = atof(entrada);

    switch (valor) {
        case 11:
            waterSpeed = saida;
            break;

        case 12:
            isleProb = saida;
            break;

        case 13:
            riverFlux = saida;
            break;

        default:
            break;
    }
    fflush(stdin);
}

void queroChar(int valor) {
    printf("Insira um novo valor para (%d):",valor);

    switch (valor) {
        case 14:
            water = fgetc(stdin);
            break;

        case 15:
            earth = fgetc(stdin);
            break;

        case 16:
            isle = fgetc(stdin);
            break;

        default:
            break;
    }
    fflush(stdin);
}

void imprimeAtributos() {
    printf("**********************************\n");
    printf("(1) Num linhas do rio: %d\n", numLines);
    printf("(2) Num colunas do rio: %d\n", numColumns);
    printf("(3) Posicao margem esquerda: %d\n", leftMargin);
    printf("(4) Posicao margem direita: %d\n", rightMargin);
    printf("\n");
    printf("(5) Seed (< 0 = aleatorio): %d\n", seed);
    printf("(6) Frequencia de atualizacao: %d\n", refreshRate);
    printf("(7) Distancia minima entre ilhas: %d\n", isleDist);
    printf("(8) Opção de debugagem (1 = ligado, 2 = testes automaticos): %d\n", reportData);
    printf("(9) Numero de iteracoes (< 0 -> infinito): %d\n",numIterations);
    printf("(10) Numero de segundos (< 0 -> infinito): %d\n",numSeconds);
    printf("\n");
    printf("(11) Velocidade maxima da agua: %.2f\n",waterSpeed);
    printf("(12) Probabilidade de gerar uma ilha: %.2f\n", isleProb);
    printf("(13) Fluxo do Rio: %.2f\n", riverFlux);
    printf("\n");
    printf("(14) Simbolo da agua: %c\n", water);
    printf("(15) Simbolo da terra: %c\n", earth);
    printf("(16) Simbolo das ilhas: %c\n", isle);
    printf("**********************************\n");
}

/*Limpa a tela*/
void clearScreen() {
    const char* CLEAR_SCREE_ANSI = "\x1b[1;1H\x1b[2J";
    int i;
    for (i = 0; i < 12; i++)
        printf("%s",CLEAR_SCREE_ANSI);
}
