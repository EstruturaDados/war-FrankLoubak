

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIOS 5
#define MAX_MISSOES 10
#define MAX_STRING 100
#define MAX_TROPAS 5
#define MAX_BATALHAS 3

        int contTerritorios = 0;
        int terrCadastrados = 0;
        int contBatalha     = 0;
        
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorios
{
    char nome[MAX_STRING];
    char cor_exercito[MAX_STRING];
    int tropas;
};

struct missao
{
    char nome[MAX_STRING];
    int idMissao;
};


// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
void limpaBufferEntrada();
void liberarMemoria(struct territorios **territorio);
void cadastrarTerritorio (struct territorios *territorio );
void listarTerritorio(struct territorios *territorio);
void ataque(struct territorios *terriTorio);
void sortearMissao(struct missao *missao, int *missaoId,struct territorios *territorio);
void verificarmissao(struct territorios *territorio, int missaoId, struct territorios *terrEstadoIni);



// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// 1. Configuração Inicial, cadastra territórios, lista territórios cadastrados e encerra sistema  (Setup):
int main() {      
    
    struct territorios *territorio=NULL;
    struct missao *missao=NULL;
    int opcao = -1;
    struct territorios terrEstadoIni[5];
    int missaoId = -1;
    srand(time(NULL));
    {
        do{
            printf("\n.........[  JOGO WAR  ].............\n\n");
            printf("OPÇÃO - 1 : CADASTRAR TERRITÓRIO\n");
            printf("OPÇÃO - 2 : LISTAR TERRITÓRIOS\n");
            printf("OPÇAO - 3 : ATACAR TERRITÓRIO\n");
            printf("OPÇÃO - 4 : SORTEAR MISSÃO\n");
            printf("OPÇÃO - 0 : SAIR\n");
            printf("==================================\n");
            printf("ESCOLHA UMA OPÇÃO :  ");

            scanf("%d", &opcao);
            limpaBufferEntrada();

            switch (opcao)
            {
            case 1:
                   if(contTerritorios==0){
                     do {
                         printf("digite o número de territórios para cadastrar (1 a 5): ");
                         scanf("%d", &terrCadastrados);
                         limpaBufferEntrada();

                            if (terrCadastrados <= 0 || terrCadastrados > 5) {
                              printf("Valor inválido! O número de territórios  deve ser entre 1 e 5.\n");
                            } 

                        } while (terrCadastrados <= 0 || terrCadastrados > 5);   
                        territorio = (struct territorios*)malloc(terrCadastrados*sizeof(struct territorios));
                        if (territorio == NULL) {
                            printf("Erro ao alocar memória!\n");
                            exit(1);
                        }
                    }
                    if(territorio !=NULL){
                        cadastrarTerritorio(territorio);
                        memcpy(terrEstadoIni,territorio,sizeof(struct territorios) * contTerritorios);
                       
                        
                    }                                
                                                   
                             
                break;
            case 2:
                 if (territorio != NULL) {
                     listarTerritorio(territorio);
                     
                    }                
                break;

            case 3:
                 if(contTerritorios>0){
                     ataque(territorio);
                     printf("\n------novo mapa com tropas atualizadas----\n");
                     listarTerritorio(territorio);
                     verificarmissao(territorio,missaoId,terrEstadoIni);
                    } else {
                        printf("nehum território cadastrado ainda !\n");
                    }
                
                 break;

            case 4:
                
                missao = (struct missao*)malloc(5*sizeof(struct missao));
                sortearMissao(missao, &missaoId,territorio);
                verificarmissao(territorio,missaoId,terrEstadoIni);
                free(missao);
                missao = NULL;

                 break;    
                
            
            case 0:
                printf("saindo");
                
                break;
            }




        } while (opcao != 0);

        if (territorio != NULL){

           liberarMemoria(&territorio);
        }

        
        
    };
    
    

    return 0;
}

// --- Implementação das Funções ---


// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void cadastrarTerritorio(struct territorios *territorio)
{
    // ===== PROTEÇÕES CRÍTICAS =====
    if (territorio == NULL) {
        printf("Erro: memória de territórios não foi alocada!\n");
        return;
    }

    if (contTerritorios >= terrCadastrados) {
        printf("\n!!!Número máximo de territórios já cadastrados!!\n");
        return;
    }

    printf("\n---Cadastrar Novo Território---\n\n");

    // Nome do território
    printf("Digite o nome do território: ");
    if (fgets(territorio[contTerritorios].nome, MAX_STRING, stdin) == NULL) {
        printf("Erro ao ler nome.\n");
        return;
    }
        territorio[contTerritorios].nome[
        strcspn(territorio[contTerritorios].nome, "\n")
    ] = '\0';

    // Cor do exército
    printf("Digite a cor do exército: ");
    if (fgets(territorio[contTerritorios].cor_exercito, MAX_STRING, stdin) == NULL) {
        printf("Erro ao ler cor.\n");
        return;
    }
    territorio[contTerritorios].cor_exercito[
        strcspn(territorio[contTerritorios].cor_exercito, "\n")
    ] = '\0';

    // Tropas — leitura segura
    int valorValido = 0;
    while (!valorValido) {
        printf("Digite o número de tropas (1 a 5): ");

        if (scanf("%d", &territorio[contTerritorios].tropas) != 1) {
            printf("Entrada inválida. Digite apenas números.\n");
            limpaBufferEntrada();
            continue;
        }

        limpaBufferEntrada();

        if (territorio[contTerritorios].tropas < 1 || 
            territorio[contTerritorios].tropas > 5) {
            printf("Valor inválido! O número de tropas deve ser entre 1 e 5.\n");
        } else {
            valorValido = 1;
        }
    }

    // Incrementa somente após TUDO válido
    contTerritorios++;

    printf("\nTerritório cadastrado com sucesso!\n");
}



// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(struct territorios **territorio){
    if(*territorio != NULL){
        free(*territorio);
        *territorio = NULL;
    }
}


// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
void listarTerritorio(struct territorios *territorio)
{ 
      if (territorio == NULL) {
        printf("Mapa não alocado!\n");
        return;
       }   
        
     printf("\n----LISTA DE TERRITÓRIOS CADASTRADOS---\n\n");

                if(contTerritorios==0){
                    printf("NEHUM TERRRITORIO FOI CADASTRADO AINDA\n");
                    }else{
                        for(int i =0; i < contTerritorios; i++){
                            printf("------------------------\n");
                            printf("TERRITORIO  %d: - ( %s , exercito %s, tropas %d)\n",
                                i+1,territorio[i].nome,
                                territorio[i].cor_exercito,
                                territorio[i].tropas);
                                                                               
                        }
                        printf("------------------------\n");
                    }

                    printf("\nfim da lista pressione enter para continuar...\n\n");
                    getchar();

}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
// faseDeAtaque():
void ataque(struct territorios *terriTorio){
    if (terriTorio == NULL || contTerritorios<2) {
    printf("--\nTerritórios não alocados nó mínimo dois territórios precisam ser cadastrados!---\n");
    return;
    }

    int a,  d,  atacante,  defensor,sair;   
   

     do
     {
         do{printf("\ndigite o número do  atacante : ");
            scanf("%d",&atacante);
            limpaBufferEntrada();
            printf("\ndigite o número do defensor : ");
            scanf("%d",&defensor);
            limpaBufferEntrada();	
            if(defensor==atacante){
            printf("\nDefensor deve ser diferente do atacante, digite os numeros novamente!\n ");
            }
           }while(defensor==atacante);
            a = 1+rand() % 6;
	        d = 1+rand() % 6;
              if (atacante < 1 || atacante > contTerritorios ||
                  defensor < 1 || defensor > contTerritorios) {
                  printf("Território inválido!\n");
                  continue;  // volta para o inicio do loop
                }

             int *pttropasAt=&terriTorio[atacante-1].tropas;
             int *pttropasDF=&terriTorio[defensor-1].tropas;

	
	         printf(" \no atacante %d  %s : tirou  %d | o defensor  %d %s : tirou %d\n",atacante,terriTorio[atacante-1].nome,a,defensor,terriTorio[defensor-1].nome,d);
	         if(a>d){
	         printf("\natacante venceu\n");
              (*pttropasAt)++;
              (*pttropasDF)--;
              listarTerritorio(terriTorio);
             if(*pttropasDF==0){
             strcpy(terriTorio[defensor-1].cor_exercito,
                    terriTorio[atacante-1].cor_exercito);
                    listarTerritorio(terriTorio);
       }
	  }else if(a<d){
       (*pttropasAt)--;
       (*pttropasDF)++;
       listarTerritorio(terriTorio);

       if(*pttropasAt==0){
       strcpy(terriTorio[atacante-1].cor_exercito,
              terriTorio[defensor-1].cor_exercito);
              listarTerritorio(terriTorio);
       }
	   printf("\no defensor venceu\n");
	  }else printf("\nempate\n"); 
      contBatalha++;
      printf("\nvoce já executou %d batalhas restam %d\n",contBatalha,MAX_BATALHAS-contBatalha);
      printf("\nsair do jogo ?(1-sim , 2- Não) :");
      scanf("%d",&sair);
      //printf("\npressione enter para continuar...\n\n");
      //getchar();
     } while (contBatalha < MAX_BATALHAS && sair==2);
     printf("\nNúmero máximo de batalhas executadas! missão não cumprida");  

}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
void sortearMissao(struct missao *missao, int *missaoId,struct territorios *territorio) {
    if(contTerritorios!=0){
    missao[0].idMissao = 1;
    strcpy(missao[0].nome, "\nderrotar exercito 1");

    missao[1].idMissao = 2;
    strcpy(missao[1].nome, "\nderrotar exercito 2");

     missao[2].idMissao = 2;
    strcpy(missao[2].nome, "\nderrotar exército 3");

     missao[3].idMissao = 2;
    strcpy(missao[3].nome, "\nderrotar  exercito 4");

     missao[4].idMissao = 2;
    strcpy(missao[4].nome, "\nderrotar  exercito 5");

     
    *missaoId = 1 + rand() % contTerritorios;
    
    printf("missão %d - %s\n", *missaoId, missao[*missaoId-1].nome);
    printf("\nmissão sorteada pressione enter para continuar...\n\n");
    printf("territorio selecionado %s",territorio[*missaoId-1].nome);

    getchar();} 
    else{
         printf("sem territórios cadastrados");
        }

}
void verificarmissao(struct territorios *territorio, int missaoId, struct territorios *terrEstadoIni)

{
      
    if (contTerritorios!=0){

        printf("conteúdo de missaoId  : %d ",missaoId);

        for(int i =0; i <contTerritorios;i++){
            if(terrEstadoIni[i].tropas != territorio[i].tropas){
                printf("\nhouve alteração nas tropas do exercito %s\n",territorio[i].nome);
            }
        }  
  
    }
     switch (missaoId)
     {
     case 1:
        printf("missão %s verificando território",territorio[missaoId-1].nome);
        break;
    
    case 2:
         printf("\nmissão %s verificando território\n",territorio[missaoId-1].nome);
        break;

    case 3:
        printf("\nmissão %s verificando território\n",territorio[missaoId-1].nome);
        break;
    
    case 4:
         printf("\nmissão %s verificando território\n",territorio[missaoId-1].nome);
        break; 
        
    case 5:
         printf("\nmissão %s verificando território\n",territorio[missaoId-1].nome);
        break;    
     
     default:
        break;
     }
}


// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
void limpaBufferEntrada(){
    int c;
    while ((c=getchar())!='\n' && c != EOF);   
    
}
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
