#include <stdio.h>

#define TAM 10
#define TAM_HAB 5

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Posiciona navio de forma segura (horizontal, vertical ou diagonal)
int posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    int dl = 0, dc = 0;

    // Define o deslocamento com base na direção
    switch (direcao) {
        case 'H': dc = 1; break;
        case 'V': dl = 1; break;
        case 'D': dl = 1; dc = 1; break;
        case 'A': dl = 1; dc = -1; break;
        default: return 0;
    }

    // Verifica se cabe e não sobrepõe
    for (int i = 0; i < 3; i++) {
        int l = linha + i * dl;
        int c = coluna + i * dc;
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != 0) {
            return 0; // fora do tabuleiro ou sobreposição
        }
    }

    // Posiciona o navio com valor 3
    for (int i = 0; i < 3; i++) {
        int l = linha + i * dl;
        int c = coluna + i * dc;
        tabuleiro[l][c] = 3;
    }

    return 1;
}

// Constrói matriz de habilidade baseada no tipo: Cone, Cruz, Octaedro
void construirHabilidade(int habilidade[TAM_HAB][TAM_HAB], char tipo) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            habilidade[i][j] = 0;
        }
    }

    switch (tipo) {
        case 'C': // Cone
            for (int i = 0; i < TAM_HAB; i++) {
                for (int j = 0; j < TAM_HAB; j++) {
                    if (j >= (TAM_HAB - 1)/2 - i && j <= (TAM_HAB - 1)/2 + i) {
                        habilidade[i][j] = 1;
                    }
                }
            }
            break;

        case '+': // Cruz
            for (int i = 0; i < TAM_HAB; i++) {
                habilidade[i][TAM_HAB / 2] = 1;
                habilidade[TAM_HAB / 2][i] = 1;
            }
            break;

        case 'O': // Octaedro
            for (int i = 0; i < TAM_HAB; i++) {
                for (int j = 0; j < TAM_HAB; j++) {
                    if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2) {
                        habilidade[i][j] = 1;
                    }
                }
            }
            break;
    }
}

// Aplica a matriz da habilidade ao tabuleiro (marca com valor 5)
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int l = origemLinha + i - offset;
            int c = origemColuna + j - offset;

            if (l >= 0 && l < TAM && c >= 0 && c < TAM && habilidade[i][j] == 1) {
                if (tabuleiro[l][c] == 0) {
                    tabuleiro[l][c] = 5; // Marca área afetada pela habilidade
                }
            }
        }
    }
}

// Exibe o tabuleiro com 0, 3 e 5
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posiciona 4 navios fixos: 2 normais, 2 diagonais
    posicionarNavio(tabuleiro, 1, 1, 'H');
    posicionarNavio(tabuleiro, 4, 0, 'V');
    posicionarNavio(tabuleiro, 7, 2, 'D');
    posicionarNavio(tabuleiro, 5, 8, 'A');

    // Construção das 3 habilidades
    int habilidadeCone[TAM_HAB][TAM_HAB];
    int habilidadeCruz[TAM_HAB][TAM_HAB];
    int habilidadeOctaedro[TAM_HAB][TAM_HAB];

    construirHabilidade(habilidadeCone, 'C');
    construirHabilidade(habilidadeCruz, '+');
    construirHabilidade(habilidadeOctaedro, 'O');

    // Aplicação das habilidades em pontos fixos
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCone, 2, 5);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCruz, 6, 6);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeOctaedro, 3, 8);

    // Exibe o tabuleiro final com números (0, 3, 5)
    exibirTabuleiro(tabuleiro);

    return 0;
}