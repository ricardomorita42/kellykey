/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

Nomes:
    Ricardo Mikio Morita (N.USP: 5412562)
    Carlos Eduardo Elmadjian (N.USP: 5685741)
    Gil Santaella (N.USP:6883598)

Profs:
    Kelly Rosa Braghetto

Arquivo:
    debugger.h

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
void printInfoTopo(float);
/*--2--*/
void printInfoLinha();
/*--3--*/
void printRelatorio();
/*--4--*/
void calculaVarVelocidade(float vMenor, float vMaior, float vMedia);
/*--5--*/
void calculaVarMargens(int esq, int dir);
/*--6--*/
void verificaFluxo(float fluxo);
/*--7--*/
void testeIntegridade(char** argv);

float calculaVelMediaRio(Rio **grade);

/*--1--printInfoTopo: imprime o tamanho da matriz (linhas X colunas) e o tempo decorrido
       no topo da tela
       parametros: tempo decorrido */
      
/*--2--printInfoLinha: imrprime o fluxo e a velocidade media calculada na linha
       parametros: nenhum */
       
/*--3--printRelatorio: exibe um conjunto de informacoes relacionadas a variacao das margens,
       variacao das velocidades, correcao do fluxo (e mais...)
       parametros: nenhum */
       
/*--4--calculaVarVelocidade: encontra a menor e a maior velocidade do jogo e calcula suas
       variacoes e a variacao das velocidades medias, imprimindo o resultado
       parametros: menor velocidade, maior velocidade e velocidade media de uma linha */

/*--5--calculaVarMargens: encontra a menor e a maior margem de cada lado de um rio gerado e
       calcula suas variacoes, imprimindo o resultado
       parametros: margem esquerda e direita de uma linha */
       
/*--6--verificaFLuxo: encontra o menor e o maior fluxo de um rio gerado, verifica se esse
       fluxo e' constante dentro de uma margem de erro e calcula sua variacao
       media, imprimindo o resultado
       parametros: fluxo de uma linha */

/*--7--testeIntegridade: realiza uma bateria de testes com o programa para verificar sua robustez*/
       

