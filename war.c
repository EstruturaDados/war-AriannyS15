#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// Estrutura principal
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

// Protótipos
Territorio* cadastrarTerritorios(int qtd);
void exibirMapa(Territorio* territorios, int qtd);
void compararTerritorios(Territorio* territorios, int qtd);
void gerarMissao(char missao[]);
void verificarMissao(Territorio* territorios, int qtd, char missao[]);

// Função principal
int main() {
    Territorio* territorios = NULL;
    char missao[100];
    int opcao;
    int cadastrados = 0; // indica se já cadastrou os territórios

    srand(time(NULL)); // inicializa aleatoriedade
    gerarMissao(missao); // gera missão aleatória

    do {
        printf("\n=== MENU WAR ===\n");
        printf("1 - Cadastrar territórios\n");
        printf("2 - Exibir mapa\n");
        printf("3 - Simular batalha\n");
        printf("4 - Ver missão atual\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // consome o '\n'

        switch (opcao) {
            case 1:
                if (territorios != NULL) {
                    free(territorios);
                }
                territorios = cadastrarTerritorios(QTD_TERRITORIOS);
                cadastrados = 1;
                break;

            case 2:
                if (!cadastrados) {
                    printf("\nNenhum território cadastrado ainda.\n");
                } else {
                    exibirMapa(territorios, QTD_TERRITORIOS);
                }
                break;

            case 3:
                if (!cadastrados) {
                    printf("\nCadastre os territórios antes de simular uma batalha.\n");
                } else {
                    compararTerritorios(territorios, QTD_TERRITORIOS);
                    verificarMissao(territorios, QTD_TERRITORIOS, missao);
                }
                break;

            case 4:
                printf("\nMissão atual: %s\n", missao);
                break;

            case 5:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 5);

    if (territorios != NULL) {
        free(territorios);
    }

    return 0;
}

// --- Funções ---

Territorio* cadastrarTerritorios(int qtd) {
    Territorio* territorios = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("\n=== Cadastro inicial dos territórios ===\n\n");

    for (int i = 0; i < qtd; i++) {
        printf("Território %d\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar();

        printf("\n");
    }

    printf("Cadastro concluído com sucesso!\n");
    return territorios;
}

void exibirMapa(Territorio* territorios, int qtd) {
    printf("\n=== Estado atual do mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].corExercito);
        printf("Número de tropas: %d\n", territorios[i].numeroTropas);
    }
}

void compararTerritorios(Territorio* territorios, int qtd) {
    int t1, t2;

    printf("\n=== BATALHA ===\n");
    printf("Escolha o território atacante (1 a %d): ", qtd);
    scanf("%d", &t1);
    printf("Escolha o território defensor (1 a %d): ", qtd);
    scanf("%d", &t2);
    getchar();

    t1--; 
    t2--;

    if (t1 < 0 || t1 >= qtd || t2 < 0 || t2 >= qtd) {
        printf("\nTerritório inválido!\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n%s (%d tropas) atacou %s (%d tropas)\n",
           territorios[t1].nome, territorios[t1].numeroTropas,
           territorios[t2].nome, territorios[t2].numeroTropas);
    printf("Dado de ataque: %d | Dado de defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("%s venceu a batalha!\n", territorios[t1].nome);
        territorios[t2].numeroTropas -= 1;
        if (territorios[t2].numeroTropas <= 0) {
            territorios[t2].numeroTropas = 0;
            printf("Território %s foi conquistado!\n", territorios[t2].nome);
            strcpy(territorios[t2].corExercito, territorios[t1].corExercito);
        }
    } else if (dadoAtaque < dadoDefesa) {
        printf("%s defendeu com sucesso!\n", territorios[t2].nome);
        territorios[t1].numeroTropas -= 1;
        if (territorios[t1].numeroTropas < 0) territorios[t1].numeroTropas = 0;
    } else {
        printf("Empate. Nenhum território foi conquistado.\n");
    }
}

void gerarMissao(char missao[]) {
    const char* missoes[] = {
        "Conquistar o exército Azul",
        "Destruir o exército Verde",
        "Dominar o território do Norte",
        "Expandir tropas em 3 territórios",
        "Defender todos os territórios com mais de 10 tropas"
    };

    int indice = rand() % 5;
    strcpy(missao, missoes[indice]);
}

void verificarMissao(Territorio* territorios, int qtd, char missao[]) {
    if (strstr(missao, "Azul")) {
        for (int i = 0; i < qtd; i++) {
            if (strcmp(territorios[i].corExercito, "Azul") == 0 && territorios[i].numeroTropas == 0) {
                printf("\nMissão cumprida: %s\n", missao);
                return;
            }
        }
    } else if (strstr(missao, "Verde")) {
        int destruido = 1;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(territorios[i].corExercito, "Verde") == 0 && territorios[i].numeroTropas > 0) {
                destruido = 0;
            }
        }
        if (destruido) {
            printf("\nMissão cumprida: %s\n", missao);
            return;
        }
    }

    printf("\nMissão ainda não concluída.\n");
}