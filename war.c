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

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.


// definnição da struct 


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
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

   // return 0;
//}

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
// stdio.h, stdlib.h, string.h e time.h.
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// definnição da struct 
typedef struct 
{
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

// Função para cadastrar territorios
void

int main() {
    Territorio territorios[QTD_TERRITORIOS];
    int i;

    printf("=== Cadastro incial dos territorios ===\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) 
    {
        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o \n

        printf("Cor do exercito: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Números de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar(); //consome o \n deixado pelo scanf

        printf("\n");       
    }

    printf("\n=== Estado atual do mapa ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++);
    {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor Do Exército: %s\n", territorios[i].corExercito);
        printf("Número de tropas: %d\n", territorios[i].numeroTropas);
    }
    
    //
    return 0;

} */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char corExercito[15];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *territorios, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n=== Território %d ===\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", territorios[i].corExercito);
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
}

// Função para exibir o mapa de territórios
void exibirMapa(Territorio *territorios, int qtd) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | Exército: %s | Tropas: %d\n",
               i + 1, territorios[i].nome, territorios[i].corExercito, territorios[i].tropas);
    }
}

// Função para simular uma batalha entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("⚠ O território %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1;  // de 1 a 6
    int dadoDefesa = rand() % 6 + 1;

    printf("\n %s (Ataque) rolou: %d\n", atacante->nome, dadoAtaque);
    printf("%s (Defesa) rolou: %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--;
        printf("%s venceu a batalha! %s perdeu 1 tropa.\n", atacante->nome, defensor->nome);

        if (defensor->tropas <= 0) {
            printf(" %s conquistou o território %s!\n", atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas - 1;
            atacante->tropas = 1;
            strcpy(defensor->corExercito, atacante->corExercito);
        }
    } else {
        atacante->tropas--;
        printf(" %s defendeu com sucesso! %s perdeu 1 tropa.\n", defensor->nome, atacante->nome);
    }
}

int main() {
    srand(time(NULL));

    int qtdTerritorios;
    printf("=== JOGO WAR - NÍVEL AVENTUREIRO ===\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio *) calloc(qtdTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(territorios, qtdTerritorios);

    int opcao;
    do {
        exibirMapa(territorios, qtdTerritorios);

        printf("\n=== FASE DE ATAQUE ===\n");
        printf("Escolha o número do território atacante:\n ");
        int a, d;
        scanf("%d", &a);
        printf("Escolha o número do território defensor: \n");
        scanf("%d", &d);

        if (a > 0 && a <= qtdTerritorios && d > 0 && d <= qtdTerritorios && a != d) {
            atacar(&territorios[a - 1], &territorios[d - 1]);
        } else {
            printf(" Escolha inválida!\n");
        }

        printf("\nDeseja continuar atacando? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);

    } while (opcao != 0);

    free(territorios);
    printf("\n Fim do jogo!\n");

    return 0;
}