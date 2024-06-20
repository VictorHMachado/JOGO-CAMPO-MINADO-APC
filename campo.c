#include <stdio.h>

#define MAX 8  //TAMANHO BASE DA MATRIX

//CARACTERES DO JOGO
#define CDesmarcado '#'
#define CBomba 'X'

typedef struct {
    char simbolo;
    int bombs;      // numero de bombas ao redor
    int bouleana;   //boulena = 0 -> nn é bomba boulena = 1 -> é bomba
    
}casa;

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
            printf(" %c ", matrix[l][c].simbolo);
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

            
            matriz[i][j].bouleana = 0;// [ APENAS PARA MOTIVOS DE TESTE, FUTURAMENTE ISSO DEVE SER SUBSTITUIDO PELA FUNÇÃO QUE GERA SE É BOMBA OU NN]
        }   
    }

    char letra;
    int coluna, linha;

    while (scanf(" %c", &letra) != EOF) //ler a letra da coluna ate EOF (ctrl + Z duas vezes)
    {
        scanf("%d", &coluna);
        linha = letra - 'A';
        coluna--;

        if (matriz[linha][coluna].bouleana == 0)
        {
            matriz[linha][coluna].simbolo = '0';//matriz[linha][coluna].bombs;
        }
        else if (matriz[linha][coluna].bouleana == 0)
        {
            matriz[linha][coluna].simbolo = CBomba;
        }
        
        
        printarMatriz(matriz);
  

    }



    return 0;
}
