// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

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
void sortearMissao(struct missao *missao);

// Funções de setup e gerenciamento de memória:
// função para limpar buffer





// Funções de interface com o usuário:





// Funções de lógica principal do jogo:



// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// 1. Configuração Inicial, cadastra territórios, lista territórios cadastrados e encerra sistema  (Setup):
int main() {
      
    
    struct territorios *territorio=NULL;
    struct missao *missao=NULL;
    int opcao = -1;
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
                    } else {
                        printf("nehum território cadastrado ainda !\n");
                    }
                
                 break;

            case 4:
                missao = (struct missao*)malloc(5*sizeof(struct missao));
                sortearMissao(missao);
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
    
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

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
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
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


// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

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
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
void sortearMissao(struct missao *missao) {
    missao[0].idMissao = 1;
    strcpy(missao[0].nome, "derrotar exercito 1");

    missao[1].idMissao = 2;
    strcpy(missao[1].nome, "derrotar exercito 2");

    int M = 1 + rand() % 2;
    printf("missão %d - %s\n", M, missao[M-1].nome);
    printf("\nmissão sorteada pressione enter para continuar...\n\n");
    getchar();

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
