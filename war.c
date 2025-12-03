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
        int contTerritorios = 0;
        int terrCadastrados = 0;
        
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorios
{
    char nome[MAX_STRING];
    char cor_exercito[MAX_STRING];
    int tropas;
};






// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// função para limpar buffer

void liberarMemoria(struct territorios *territorio){
    free(territorio);

}

void limpaBufferEntrada(){
    int c;
    while ((c=getchar())!='\n' && c != EOF);
    
    
}

// Funções de interface com o usuário:


void cadastrarTerritorio (struct territorios *territorio )
{    
   
    
    printf("\n---Cadastrar Novo Território---\n\n");
                if(contTerritorios<terrCadastrados){
                    printf("digite o nome do território: ");
                    fgets(territorio[contTerritorios].nome,MAX_STRING,stdin);

                    printf("digite a cor do exercito :  ");
                    fgets(territorio[contTerritorios].cor_exercito,MAX_STRING,stdin);

                    territorio[contTerritorios].nome[strcspn(territorio[contTerritorios].nome,"\n")] = '\0';
                    territorio[contTerritorios].cor_exercito[strcspn(territorio[contTerritorios].cor_exercito,"\n")] ='\0'; 


                    do {
                         printf("digite o número de tropas (1 a 5): ");
                         scanf("%d", &territorio[contTerritorios].tropas);
                         limpaBufferEntrada();

                       if (territorio[contTerritorios].tropas <= 0 || territorio[contTerritorios].tropas > 5) {
                       printf("Valor inválido! O número de tropas deve ser entre 1 e 5.\n");
    }

                        } while (territorio[contTerritorios].tropas <= 0 || territorio[contTerritorios].tropas > 5);

                    contTerritorios++;
                    printf("\n territóriocadastrado com sucesso!\n");
                
                }
                else {
                    printf("Número máximo de territórios já cadastrados");
                }    



}
void listarTerritorio(struct territorios *territorio)
{
    
        
     printf("\n----LISTA DE TERRITÓRIOS CADASTRADOS---\n\n");

                if(contTerritorios==0){
                    printf("NEHUM TERRRITORIO FOI CADASTRADO AINDA\n");
                    }else{
                        for(int i =0; i < contTerritorios; i++){
                            printf("------------------------\n");
                            printf("TERRITORIO : %d - ( %s , exercito %s, tropas %d)\n",
                                i+1,territorio[i].nome,
                                territorio[i].cor_exercito,
                                territorio[i].tropas);
                                                                               
                        }
                        printf("------------------------\n");
                    }

                    printf("\nfim da lista pressione enter para continuar...\n\n");
                    getchar();

}

// Funções de lógica principal do jogo:
int ataque(struct territorios *terriTorio){
    int a,  d,  atacante,  defensor;

	printf("digite o número do  atacante : ");
    scanf("%d",&atacante);
    limpaBufferEntrada();
    
    do{
      printf("digite o número do defensor : ");
      scanf("%d",&defensor);
      limpaBufferEntrada();	
      if(defensor==atacante){
        printf("Defensor deve ser diferente do atacante\n ");
      }
    }while(defensor==atacante);
    a = 1+rand() % 6;
	d = 1+rand() % 6;

    int *pttropasAt=&terriTorio[atacante-1].tropas;
    int *pttropasDF=&terriTorio[defensor-1].tropas;
   


	
	printf(" o atacante %d tirou  %d no jogo de dados e o defensor :  %d  tirou %d\n",atacante,a,defensor,d);
	if(a>d){
	   printf("\natacante venceu\n");
       (*pttropasAt)++;
       (*pttropasDF)--;
       if(*pttropasDF==0){
        strcpy(terriTorio[defensor-1].cor_exercito,
               terriTorio[atacante-1].cor_exercito);
       }
	}else if(a<d){
       (*pttropasAt)--;
       (*pttropasDF)++;
       if(*pttropasAt==0){
       strcpy(terriTorio[atacante-1].cor_exercito,
              terriTorio[defensor-1].cor_exercito);
       }
	   printf("\no defensor venceu\n");
	}else printf("empate");
    
    

	
	
    return 0;
}


// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
// 1. Configuração Inicial, cadastra territórios, lista territórios cadastrados e encerra sistema  (Setup):
int main() {
      
    
    struct territorios *territorio;
    //territorio = (struct territorios*)malloc(MAX_TERRITORIOS*sizeof(struct territorios));
   
    srand(time(NULL));
    

    int opcao;
    {
        do{
            printf("\n.........[  JOGO WAR  ].............\n\n");
            printf("OPÇÃO - 1 : CADASTRAR TERRITÓRIO\n");
            printf("OPÇÃO - 2 : LISTAR TERRITÓRIOS\n");
            printf("OPÇAO - 3 : ATACAR TERRITÓRIO\n");
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
                              printf("Valor inválido! O número de tropas deve ser entre 1 e 5.\n");
                            } 

                        } while (terrCadastrados <= 0 || terrCadastrados > 5);   
                        territorio = (struct territorios*)malloc(terrCadastrados*sizeof(struct territorios));
                    }
                cadastrarTerritorio(territorio);
                             
                break;
            case 2:
                 listarTerritorio(territorio);
                
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
                
                
            
            case 0:
                printf("saindo");
                
                break;
            }




        } while (opcao != 0);

        liberarMemoria(territorio);
        
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

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
