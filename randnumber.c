#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>   //deve se add -lm no gcc para compilar
#include <pthread.h> //deve add -lpthread para compilar
#include <unistd.h>

#define MAX 1
#define MIN -1
//pode ser uma solucao

struct MonteCarlo{
	int numPontos;
	int sumCirculo;
	float valorPi;

};

void *randNumber(void* num){
	struct MonteCarlo* Monte = (struct MonteCarlo*) num;
	Monte->sumCirculo = 0;
	//Monte->numPontos = 100;
	double x;
	double y;
	srand(time(NULL));
	double raio;
	for(int i = 0; i < Monte->numPontos; i++){
	x = (rand()%2000 - 1000)*0.001;
	y = (rand()%2000 - 1000)*0.001;
	
	x = x*x;
	y = y*y;
	raio = sqrt(x+y);
	if(raio<=1){
	Monte->sumCirculo++;}

	Monte->valorPi = 4 *((float)Monte->sumCirculo/(float)Monte->numPontos);
	
	}
	return NULL;		

}


int main(){
	
	pthread_t t0;
	struct MonteCarlo *M;
	int n;
	float piValor;
	printf("Entre com o numero de pontos:");
	scanf("%d", &n);
	M->numPontos = n;
	
	pthread_create(&t0, NULL,randNumber,M);
  	pthread_join (t0, NULL);
	printf("Numero total de pontos: %d\nNumero de ponsto dentro do circulo: %d\n", M->numPontos, M->sumCirculo);
	
	piValor = 4*((float)M->sumCirculo/(float)M->numPontos);
	printf("Valor calculado na main:   %f\n", piValor);
	printf("Valor calculado na thread: %f\n", M->valorPi);
	return 0;
}
