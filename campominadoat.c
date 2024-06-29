#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define hack '$'

typedef struct {
    int bombs;      // número de bombas ao redor
    int boolean;    // booleana = 0 -> não é bomba, booleana = 1 -> é bomba
    int flag;       // 0 -> não marcada, 1 -> aberta, -1 -> marcada com bandeira
} casa;

void gerar_bombas(int max, casa matrix[max][max], int num_bombas) {
    int bombas_colocadas = 0;
    while (bombas_colocadas < num_bombas) {
        int i = rand() % max;
        int j = rand() % max;
        if (matrix[i][j].boolean == 0) {
            matrix[i][j].boolean = 1;
            bombas_colocadas++;
        }
    }
}

void contador_bombs(int MAX, casa matrix[MAX][MAX]) {
    for (int pi = 0; pi < MAX; pi++) {
        for (int pj = 0; pj < MAX; pj++) {
            matrix[pi][pj].bombs = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (pi + i >= 0 && pi + i < MAX && pj + j >= 0 && pj + j < MAX) {
                        if (matrix[pi + i][pj + j].boolean == 1) {
                            matrix[pi][pj].bombs++;
                        }
                    }
                }
            }
        }
    }
}

void printa_ou_n(int MAX, casa matrix[MAX][MAX], int pi, int pj){
    if (matrix[pi][pj].flag != 0) {
        return;
    }
    matrix[pi][pj].flag = 1;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (pi + i >= 0 && pi + i < MAX && pj + j >= 0 && pj + j < MAX) {
                if (matrix[pi + i][pj + j].bombs == 0) {                
                    printa_ou_n(MAX, matrix, pi + i, pj + j);
                }
                else {
                    matrix[pi + i][pj + j].flag = 1;
                }
            }
        }
    }
}

void printarMatriz(int MAX, casa matrix[MAX][MAX]){
    printf("  "); 
    for (int i = 1; i <= MAX; i++) {
        printf("%02d ", i );
    }
    printf("\n");

    for (int l = 0; l < MAX; l++) {
        printf("%c ", 'A' + l);
        for (int c = 0; c < MAX; c++) {
            if (matrix[l][c].flag == 1) {
                if (matrix[l][c].bombs != 0) {
                    printf(" %d ", matrix[l][c].bombs);
                }
                else {
                    printf(" □ ");
                }
            }
            else if (matrix[l][c].flag == 0) {
                printf(" ■ ");
            }
            else if (matrix[l][c].flag == -1) {
                printf(" 🚩");
            }
        }
        printf("\n");
    }
}

int vitoria(int MAX, casa matrix[MAX][MAX], int num_bombas){
    int casas_abertas = 0;
    int bandeira_certa = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (matrix[i][j].flag == 1) {
                casas_abertas++;
            }
            if (matrix[i][j].flag == -1 && matrix[i][j].boolean == 1) {
                bandeira_certa++;
            }
        }
    }

    if (casas_abertas == MAX * MAX - num_bombas || bandeira_certa == num_bombas) {
        return 1;
    }
    return 0;
}

int main() {
    char jogardnv[4] = "Sim";
    printf("\n\tBEM VINDO AO JOGO CAMPO MINADO\n Escolha uma coordenada para marcar que voce tem certeza que nao eh bomba colocando a letra maiuscula seguida do numero, por exemplo A1.\n Caso queira marcar uma coordenada onde voce acha que tem uma bomba, marque essa coordenada colocando a letra minuscula seguida do numero da coluna, por exemplo b5.\n\n");

    while (jogardnv[0] == 'S' || jogardnv[0] == 's') {
        printf("Escolha o nivel de dificuldade:\n");
        printf("1 - Facil\n");
        printf("2 - Intermediario\n");
        printf("3 - Dificil\n");

        int escolha;
        scanf("%d", &escolha);

        int MAX, num_bombas;

        switch (escolha) {
            case 1:
                MAX = 10;
                num_bombas = 10;
                break;
            case 2:
                MAX = 15;
                num_bombas = 35;
                break;
            case 3:
                MAX = 20;
                num_bombas = 90;
                break;
            default:
                printf("Opcao invalida. Escolha novamente.\n");
                continue;
        }

        casa matriz[MAX][MAX];
        srand(time(NULL));

        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                matriz[i][j].flag = 0;
                matriz[i][j].bombs = 0;
                matriz[i][j].boolean = 0;
            }   
        }

        gerar_bombas(MAX, matriz, num_bombas);
        contador_bombs(MAX, matriz);

        printarMatriz(MAX, matriz);

        char letra;
        int coluna, linha;

        while (scanf(" %c", &letra) != EOF) {
            scanf("%d", &coluna);

            if (letra == hack) {
                printf("\n");
                for (int i = 0; i < MAX; i++) {
                    for (int j = 0; j < MAX; j++) {
                        if (matriz[i][j].boolean == 1) {
                            printf("%c%d  ", 'A' + i, j + 1);
                        }
                    }
                }
                letra = 'A' + MAX;
                printf("\n\n");  
            }

            if (coluna > 0 && coluna <= MAX) {
                linha = letra - 'A';
                coluna--;

                if (letra >= 'A' && letra <= 'A' + MAX - 1) {
                    if (matriz[linha][coluna].boolean == 0) {
                        if (matriz[linha][coluna].bombs == 0) {
                            printa_ou_n(MAX, matriz, linha, coluna);
                        }
                        else {
                            matriz[linha][coluna].flag = 1;
                        }
                    }
                    else   // ACHOU BOMBA
                        {
                        //matriz[linha][coluna].flag = 1;
                        printf("   "); 
                        for (int i = 1; i <= MAX; i++) //printar o numero das colunas
                        {
                            printf("%02d ", i );
                        }
                        printf("\n");
                        
                        for (int l = 0; l < MAX; l++)
                        {
                            printf("%c ", 'A' + l); //printar as letras da coluna ao lado
                            for (int c = 0; c < MAX; c++)
                            {
                                if(matriz[l][c].boolean == 1){
                                    printf(" 💥");
                                }
                                else if(matriz[l][c].bombs != 0){
                                    printf(" %d ", matriz[l][c].bombs);
                                }
                                else{
                                    printf(" □ ");
                            
                                }
                            }
                            printf("\n");
                        }  
                        printf("\nPERDEU OTARIO KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n");
                        break;
                    }
                }
                else if (letra >= 'a' && letra <= 'a' + MAX - 1) { // BANDEIRA
                    linha = letra - 'a';
                    if (matriz[linha][coluna].flag == -1) {
                        matriz[linha][coluna].flag = 0;
                    }
                    else if (matriz[linha][coluna].flag != 1) {
                        matriz[linha][coluna].flag = -1;
                    }
                }
            }
            printarMatriz(MAX, matriz);

            if (vitoria(MAX, matriz, num_bombas)) {
                printf(" VOCE VENCEU ");
                break;
            }
        }
        printf("\nDeseja jogar mais uma vez? (sim ou nao): ");     
        scanf("%s", jogardnv);  
    }
    return 0;
}
