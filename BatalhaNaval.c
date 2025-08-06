#include <stdio.h>
#include <math.h>

// Tamanho do tabuleiro e dos navios.
#define TAMANHO_TABULEIRO 11 // O tabuleiro agora tem 11x11 para acomodar a imagem.
#define TAMANHO_NAVIO 3

// Valores que representam o estado do tabuleiro.
#define AGUA 0
#define NAVIO_INTACTO 3

// Valores para as habilidades.
#define VALOR_CRUZ 1
#define VALOR_CONE 2
#define VALOR_OCTAEDRO 4 // Valor do Octaedro alterado para 4.

// Tamanho fixo para as matrizes de habilidade.
#define TAMANHO_HABILIDADE 5

// --- Funções de Batalha Naval ---

// Inicializa o tabuleiro com o valor de AGUA.
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Exibe o tabuleiro no console, com formatação para melhor alinhamento.
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona um navio (horizontal, vertical ou diagonal) no tabuleiro.
// Retorna 1 em caso de sucesso, 0 em caso de falha.
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
        return 0;
    }
    int i, j;

    if (orientacao == 'h' || orientacao == 'H') {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (j = 0; j < TAMANHO_NAVIO; j++) {
            if (tabuleiro[linha][coluna + j] != AGUA) return 0;
        }
        for (j = 0; j < TAMANHO_NAVIO; j++) {
            tabuleiro[linha][coluna + j] = NAVIO_INTACTO;
        }
        return 1;
    } else if (orientacao == 'v' || orientacao == 'V') {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != AGUA) return 0;
        }
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = NAVIO_INTACTO;
        }
        return 1;
    } else if (orientacao == 'd' || orientacao == 'D') {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;
        }
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna + i] = NAVIO_INTACTO;
        }
        return 1;
    } else if (orientacao == 'a' || orientacao == 'A') {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - TAMANHO_NAVIO + 1 < 0) return 0;
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;
        }
        for (i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha + i][coluna - i] = NAVIO_INTACTO;
        }
        return 1;
    }
    return 0;
}

// --- Funções de Habilidades ---

void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        int largura = i * 2 + 1;
        int centro_cone = TAMANHO_HABILIDADE / 2;
        for (int j = 0; j < largura; j++) {
            if (centro_cone - i + j >= 0 && centro_cone - i + j < TAMANHO_HABILIDADE) {
                habilidade[i][centro_cone - i + j] = 1;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        habilidade[centro][i] = 1;
        habilidade[i][centro] = 1;
    }
}

void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        int distancia_centro = abs(i - centro);
        int largura = (centro - distancia_centro) * 2 + 1;

        for (int j = 0; j < largura; j++) {
            habilidade[i][distancia_centro + j] = 1;
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro.
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int centro_linha, int centro_coluna, int valor_habilidade) {
    int metade_habilidade = TAMANHO_HABILIDADE / 2;

    int inicio_linha = centro_linha - metade_habilidade;
    int inicio_coluna = centro_coluna - metade_habilidade;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int tabuleiro_linha = inicio_linha + i;
            int tabuleiro_coluna = inicio_coluna + j;

            if (tabuleiro_linha >= 0 && tabuleiro_linha < TAMANHO_TABULEIRO &&
                tabuleiro_coluna >= 0 && tabuleiro_coluna < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[tabuleiro_linha][tabuleiro_coluna] == AGUA) {
                    tabuleiro[tabuleiro_linha][tabuleiro_coluna] = valor_habilidade;
                }
            }
        }
    }
}

// --- Função Principal ---

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidade_matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Posicionamento dos navios de acordo com a imagem.
    posicionarNavio(tabuleiro, 0, 0, 'v');
    posicionarNavio(tabuleiro, 0, 1, 'd');
    posicionarNavio(tabuleiro, 7, 5, 'v');
    posicionarNavio(tabuleiro, 7, 10, 'a');
    posicionarNavio(tabuleiro, 9, 1, 'h');

    // --- POSICIONAMENTO DAS HABILIDADES ---
    // As coordenadas foram ajustadas para corresponder à imagem.

    // Habilidade CONE (valor: 2) - Centro em (4, 2)
    criarHabilidadeCone(habilidade_matriz);
    sobreporHabilidade(tabuleiro, habilidade_matriz, 4, 2, VALOR_CONE);

    // Habilidade CRUZ (valor: 1) - Centro em (0, 6)
    criarHabilidadeCruz(habilidade_matriz);
    sobreporHabilidade(tabuleiro, habilidade_matriz, 2, 6, VALOR_CRUZ);

    // Habilidade OCTAEDRO (valor: 4) - Centro em (5, 8)
    criarHabilidadeOctaedro(habilidade_matriz);
    sobreporHabilidade(tabuleiro, habilidade_matriz, 5, 8, VALOR_OCTAEDRO);

    // Exibe o tabuleiro final.
    printf("--- Tabuleiro Final com Navios e Habilidades ---\n");
    exibirTabuleiro(tabuleiro);
    
    printf("\nLegenda");
    printf("0 = Agua\n");
    printf("1 = Habilidade Cruz\n");
    printf("2 = Habilidade Cone\n");
    printf("3 = Navio\n");
    printf("4 = Habilidade Octaedro\n");

    return 0;
}
