#include <stdio.h>

#define MAX 8  //TAMANHO BASE DA MATRIX

//CARACTERES DO JOGO
#define CDesmarcado '#'
#define CBomba 'X'

typedef struct {
    char simbolo;
    int bombs;      // numero de bombas ao redor
    int bouleana;   //boulena = 0 -> nn é bomba boulena = 1 -> é bomba
    int flag;
    
}casa;

void contador_bombs(casa matrix[MAX][MAX]) {
    for (int pi = 0; pi < MAX; pi++) {
        for (int pj = 0; pj < MAX; pj++) {
            matrix[pi][pj].bombs = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (pi + i >= 0 && pi + i < MAX && pj + j >= 0 && pj + j < MAX) {
                        if (matrix[pi + i][pj + j].bouleana == 1) {
                            matrix[pi][pj].bombs++;
                        }
                    }
                }
            }
        }
    }
}
void printa_ou_n(casa matrix[MAX][MAX], int pi, int pj){
    //printf("printa_ou_n %d pi=%d pj=%d \n", matrix[pi][pj].flag, pi, pj );
    if(matrix[pi][pj].flag==1){
        return;
    }
    matrix[pi][pj].flag = 1;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if(pi + i >= 0 && pi + i < MAX && pj + j >= 0 && pj + j < MAX){
                //printf("pi = %d; i = %d; pj = %d; j = %d\n", pi, i, pj, j);
                if(matrix[pi + i][pj + j].bombs == 0){                
                    printa_ou_n(matrix, pi + i, pj + j);
                }
                else{
                    matrix[pi + i][pj + j].flag = 1;
                }
            }
        }
    }
}
void printarMatriz(casa matrix[MAX][MAX]){
    
    printf("  "); 
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
            if(matrix[l][c].flag == 1){
                if(matrix[l][c].bombs != 0){
                    printf(" %d ", matrix[l][c].bombs);
                }
                else{
                    printf("   ");
                }
            }
            else{
                printf(" %c ", matrix[l][c].simbolo);
            }
        }
        printf("\n");
    }  
}

int main(int argc, char const *argv[])
{

    casa matriz[MAX][MAX];
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)   //zerar a matriz   0 == "-- "  ][  1 == "XX "
        {
            matriz[i][j].simbolo = CDesmarcado;
            matriz[i][j].flag = 0;
            matriz[i][j].bombs = 0;
            matriz[i][j].bouleana = 0;// [ APENAS PARA MOTIVOS DE TESTE, FUTURAMENTE ISSO DEVE SER SUBSTITUIDO PELA FUNÇÃO QUE GERA SE É BOMBA OU NN]
        }   
    }
    matriz[3][3].bouleana = 1;

    printarMatriz(matriz);

    contador_bombs(matriz);

    char letra;
    int coluna, linha;
    

    while (scanf(" %c", &letra) != EOF) //ler a letra da coluna ate EOF (ctrl + Z duas vezes)
    {
        scanf("%d", &coluna);
        linha = letra - 'A';
        coluna--;

        if (matriz[linha][coluna].bouleana == 0){
            //printf("%d \n", matriz[linha][coluna].bombs);
            if(matriz[linha][coluna].bombs == 0){
                printa_ou_n(matriz, linha, coluna);
            }else{
                matriz[linha][coluna].flag = 1;
            }
        }
        else if (matriz[linha][coluna].bouleana == 1)
        {
            matriz[linha][coluna].simbolo = CBomba;
        }

        printarMatriz(matriz);
    }



    return 0;
}
