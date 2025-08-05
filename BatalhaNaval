#include <stdio.h>

int main(){

    int matrizNavio[10][10];
    int navio1[3] = {3,3,3};
    int navio2[3] = {3,3,3};
    int linhaNavio1 = 2, colunaNavio1 = 4; // Navio1 horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio2 vertical

    // iniciando o tabuleiro onde água é 0
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            matrizNavio[i][j] = 0;
        }
    }

    //testa e posiciona navio horizontal
    if(colunaNavio1 + 2 < 10){
        for(int i = 0; i < 3; i++){
            matrizNavio[linhaNavio1][colunaNavio1 + i] = 1;
        }
    } else {
        printf("Navio horizontal fora do tabuleiro.\n");
        return 1;
    }

    //testa eposiciona navio vertical
    if(linhaNavio2 + 2 < 10){
        for (int i = 0; i < 3; i++){
            matrizNavio[linhaNavio2 + i][colunaNavio2] = 1;
        }
    } else {
        printf("Navio vertical fora do tabuleiro.\n");
        return 1;
    }

    // Exibindo o tabuleiro
    printf("***Tabuleiro do Batalha Naval***\n");
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            printf("%d ", matrizNavio[i][j]);
        }
        printf("\n");
    }
    return 0;
}
