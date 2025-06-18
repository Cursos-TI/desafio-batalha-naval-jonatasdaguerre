#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAMANHO_TABULEIRO 10
// Tamanho fixo dos navios
#define TAMANHO_NAVIO 3
// Valor que representa uma parte do navio
#define NAVIO 3
// Valor que representa água
#define AGUA 0

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe horizontalmente no tabuleiro
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // posição inválida
    }

    // Verifica se já há outro navio na posição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) {
            return 0; // sobreposição detectada
        }
    }

    // Posiciona o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }

    return 1; // sucesso
}

// Função para posicionar um navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se o navio cabe verticalmente no tabuleiro
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0; // posição inválida
    }

    // Verifica se já há outro navio na posição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) {
            return 0; // sobreposição detectada
        }
    }

    // Posiciona o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }

    return 1; // sucesso
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Coordenadas definidas diretamente no código
    int linha_horizontal = 2;
    int coluna_horizontal = 4;
    int linha_vertical = 5;
    int coluna_vertical = 7;

    // Posiciona o navio horizontalmente
    if (!posicionarNavioHorizontal(tabuleiro, linha_horizontal, coluna_horizontal)) {
        printf("Erro ao posicionar o navio horizontal.\n");
        return 1;
    }

    // Posiciona o navio verticalmente
    if (!posicionarNavioVertical(tabuleiro, linha_vertical, coluna_vertical)) {
        printf("Erro ao posicionar o navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}