#include <stdio.h>

// Definições constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
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

// Função para verificar se há sobreposição nas posições indicadas
int posicaoLivre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha[], int coluna[]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha[i]][coluna[i]] != AGUA) {
            return 0; // posição já ocupada
        }
    }
    return 1;
}

// Posiciona navio horizontal
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    int linhas[TAMANHO_NAVIO], colunas[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhas[i] = linha;
        colunas[i] = coluna + i;
    }

    if (!posicaoLivre(tabuleiro, linhas, colunas)) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha][coluna + i] = NAVIO;

    return 1;
}

// Posiciona navio vertical
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    int linhas[TAMANHO_NAVIO], colunas[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhas[i] = linha + i;
        colunas[i] = coluna;
    }

    if (!posicaoLivre(tabuleiro, linhas, colunas)) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna] = NAVIO;

    return 1;
}

// Posiciona navio na diagonal principal (↘)
int posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;

    int linhas[TAMANHO_NAVIO], colunas[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhas[i] = linha + i;
        colunas[i] = coluna + i;
    }

    if (!posicaoLivre(tabuleiro, linhas, colunas)) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna + i] = NAVIO;

    return 1;
}

// Posiciona navio na diagonal secundária (↙)
int posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;

    int linhas[TAMANHO_NAVIO], colunas[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        linhas[i] = linha + i;
        colunas[i] = coluna - i;
    }

    if (!posicaoLivre(tabuleiro, linhas, colunas)) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[linha + i][coluna - i] = NAVIO;

    return 1;
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona 2 navios retos (horizontal e vertical)
    if (!posicionarNavioHorizontal(tabuleiro, 1, 1)) {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    if (!posicionarNavioVertical(tabuleiro, 4, 0)) {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    // Posiciona 2 navios diagonais
    if (!posicionarNavioDiagonalPrincipal(tabuleiro, 0, 6)) {
        printf("Erro ao posicionar navio diagonal principal.\n");
        return 1;
    }

    if (!posicionarNavioDiagonalSecundaria(tabuleiro, 6, 9)) {
        printf("Erro ao posicionar navio diagonal secundária.\n");
        return 1;
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}