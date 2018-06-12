#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //deve add -lpthread para compilar
#include <unistd.h>

int sudoku[9][9];
int leituraArquivo[81];
int subSudoku[3][3][9];

int verificacaoSudoku[11];
int test[2];
int veri[9];
int sumlinha = 0;
void *verificarLinha(void *valor);
void *verificarColuna(void *valor);
void *verificarSubSudoku(void *valor);


int main(){
    int i,j,k;
    int a = 0;
    int okSudoku = 0; 
    FILE *fp;
	int a0 = 0;
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	int a6 = 6;
	int a7 = 7;
	int a8 = 8;
    char c;
	pthread_t linha;
	pthread_t coluna;
	pthread_t subSu[9]; //verificar as nove matrizes menores

   fp = fopen("1.txt","r"); /* Arquivo ASCII, para leitura */
   if(!fp)
   {
       printf( "Erro na abertura do arquivo");
       exit(-1);
   }
   while((c = getc(fp) ) != EOF){  /* Enquanto não chegar ao final do arquivo */
    
        if(c!= ' ' && c!= 10 && c!=13){//condicao para ignorar espaco e quebra de linha
            leituraArquivo[a] = c - '0';
            printf("n%d = %d\n",a, leituraArquivo[a]);
            a++;
        }

   }fclose(fp);
   printf("\n");

	a = 0;
    for (i = 0; i < 9; i ++){
        for (j = 0; j < 9; j ++){
            sudoku[i][j] = leituraArquivo[a];
            printf("%d ", sudoku[i][j]);
	//dividindo o sudoku em pequenas matrizes para verificar condicoes
		if (i >=0 && i <= 2){
			if(j>=0 && j<=2){
				subSudoku[i][j][0] = sudoku[i][j];
			}
			if(j>=3 && j<=5){
				subSudoku[i][j-3][1] = sudoku[i][j];
			}
			if(j>=6 && j<=8){
				subSudoku[i][j-6][2] = sudoku[i][j];
			}
	
		}
		if (i >=3 && i <= 5){
			if(j>=0 && j<=2){
				subSudoku[i-3][j][3] = sudoku[i][j];
			}
			if(j>=3 && j<=5){
				subSudoku[i-3][j-3][4] = sudoku[i][j];
			}
			if(j>=6 && j<=8){
				subSudoku[i-3][j-6][5] = sudoku[i][j];
			}
	
		}
		if (i >=6 && i <= 8){
			if(j>=0 && j<=2){
				subSudoku[i-6][j][6] = sudoku[i][j];
			}
			if(j>=3 && j<=5){
				subSudoku[i-6][j-3][7] = sudoku[i][j];
			}
			if(j>=6 && j<=8){
				subSudoku[i-6][j-6][8] = sudoku[i][j];
			}
	
		}
            a++;}
            printf("\n");

    }
    printf("ok\n\n");
    
       for(k = 0; k < 9; k++){
        for(i = 0; i < 3; i ++){
            for(j = 0; j < 3; j++)
                printf("%d ", subSudoku[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
	pthread_create(&linha, NULL, verificarLinha, NULL);
	pthread_create(&coluna, NULL, verificarColuna, NULL);
	
	pthread_create(&subSu[0],NULL,&verificarSubSudoku, &a0);
	pthread_create(&subSu[1],NULL,&verificarSubSudoku, &a1);
	pthread_create(&subSu[2],NULL,&verificarSubSudoku, &a2);
	pthread_create(&subSu[3],NULL,&verificarSubSudoku, &a3);
	pthread_create(&subSu[4],NULL,&verificarSubSudoku, &a4);
	pthread_create(&subSu[5],NULL,&verificarSubSudoku, &a5);
	pthread_create(&subSu[6],NULL,&verificarSubSudoku, &a6);
	pthread_create(&subSu[7],NULL,&verificarSubSudoku, &a7);
	pthread_create(&subSu[8],NULL,&verificarSubSudoku, &a8);
	for(i = 0; i<9; i++){
		pthread_join(subSu[i],NULL);	
	}
	pthread_join(linha,NULL);
	pthread_join(coluna,NULL);
	
	
	for(i = 0; i < 11; i++){
		printf("Valor subSu %d = %d\n", i, verificacaoSudoku[i]);
		if(verificacaoSudoku[i] == 1)
			okSudoku++;
	}

	if(okSudoku ==11)
		printf("\nSudoku com solucao correta!!\n");
	else{
		printf("\nSudoku com solucao incorreta!!!\n");}
    return 0;
  
}

void *verificarLinha(void *valor){

	int i,j,k;
	int sum = 0;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			for (k = 0; k < 9; k++){
				if(sudoku[i][j] == sudoku[i][k]){
					sum ++;}
			}		
		}	
		
	}
	if(sum == 81)
		verificacaoSudoku[9] = 1;
	else 
		verificacaoSudoku[9] = 0;
		
		printf("Valor de sum %d\n", sumlinha);

}

void *verificarColuna(void *valor){

	int i,j,k;
	int sum = 0;
	for(j = 0; j < 9; j++){
		for(i = 0; i < 9; i++){
			for (k = 0; k < 9; k++){
				if(sudoku[i][j] == sudoku[k][j])
					sum ++;
			}		
		}	
		
	}
	if(sum == 81)
		verificacaoSudoku[10] = 1;
		
	else 
		verificacaoSudoku[10] = 0;
		

}

void *verificarSubSudoku(void *valor){
	int *k = (int *) valor;
	int sum = 0;
	printf("veri subsudoku %d\n", *k);
	for(int i =0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for(int m = 0; m < 3; m++)
				for (int n = 0; n< 3; n++)
					if(subSudoku[i][j][*k] == subSudoku[m][n][*k])
						sum++;	
	if(sum == 9)	
		verificacaoSudoku[*k] = 1;
	else 
		verificacaoSudoku[*k] = 0;
	
}
