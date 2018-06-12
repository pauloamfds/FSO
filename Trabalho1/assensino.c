//programa 2 do trabalho de fso
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

int numEstudantes;
int *estudantes;
int *buscaAjuda;//fazer o sum de ajuda, se 3 encerra programacao 
int *cadeiras;
int *programando;
int c;
int AE = 0; //0 = disponivel, 1 = ocupado
int acordado = 0; //1 = acordado, 0 = dormindo
int count = 0;
sem_t sema;
pthread_t *t;
pthread_t ae;
pthread_mutex_t mutex;

void ctrl_c();
void *assistente(void *valor);
void *programar(void *valor);

int main(){

	signal(SIGINT, ctrl_c);
	int i, m[50];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&sema, 0, 1);
	srand(time(0));
	numEstudantes = (rand()%37 + 3);
	if(numEstudantes%2 == 1)
		c = numEstudantes/2 + 1;
	else 
		c = numEstudantes/2;
	cadeiras = (int*)malloc(c * sizeof(int));	
	estudantes = (int *)malloc(numEstudantes * sizeof(int));
	buscaAjuda = (int *)malloc(numEstudantes * sizeof(int));
	programando = (int *)malloc(numEstudantes * sizeof(int));
	t = (pthread_t *)malloc(numEstudantes * sizeof(pthread_t));
	if(estudantes==NULL){
		printf("Falha na alocacao\n");
		exit(0);
	}
	printf("\nNumero de estudantes: %d, \ncadeiras = %d\n", numEstudantes,c);

	for (i = 0; i < numEstudantes; i ++){
		estudantes[i] = i;
		buscaAjuda[i] = 0;
		programando[i] = 0;
		printf("Estudande: %d -> buscaAjuda %d \n", estudantes[i], buscaAjuda[i]);
				
	}
	printf("\nok\n\n");
	for (i = 0; i < c; i ++){
		cadeiras[i] = 0;
		printf("Cadeiras%d: %d\n", i, cadeiras[i]);
	}
	puts(" ");
	i = 0;
	while (i < numEstudantes){
		m[i] = i;
		pthread_create(&(t[i]), NULL, &programar, &m[i]);
		//printf("\nPassando thread %d\n", i);
		i++;
	}
	
	i = 0;
	while(i < numEstudantes){
	pthread_join(t[i],NULL);
	//printf("\nTerminando thread %d\n", i);
	i++;
	}
	printf("\nokkkk\n");
	free(estudantes);
	free(buscaAjuda);
	free(cadeiras);
	free(t);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&sema);
	//free(ptr);
	//*estudantes = NULL;
	return 0;
}


void *programar(void *valor){
	/*pthread_mutex_lock(&mutex);
	count ++; 
	pthread_mutex_unlock(&mutex);*/
	int i = *((int*)valor);
	int sumc = 0;
	printf("Thread: %d \n", i);
	int temp;
	int j;
	programando[i] = 1; //comeca programando
	while(1){
		printf("Passando por inicio do laco\n");
		temp = rand()%100;
		usleep(temp);
		if(AE == 0){
			//pthread_mutex_lock(&mutex);
			pthread_create(&ae,NULL, assistente, &i);
			pthread_join(ae,NULL);
			//pthread_mutex_unlock(&mutex);
		}
		/*else{
			if(cadeiras[0] == 0)
				cadeiras[0] = estudantes[i];
		
			else if(cadeiras[0] != 0){
				for (j = 0; j < c; j ++){
					if (cadeiras[j] == 0){
						cadeiras[j] = estudantes[i];
						sumc++;
					}
				}
			}
		}
		
		
		if(sumc==c){
			acordado = 0;
		}*/
		sleep(1);
		printf("Passando por aqui antes da condicao\n");
		if( buscaAjuda[i] == 3){
			printf("\n\nAluno %d terminou sua execucao!!\n\n", i);
			printf("J = %d\n", buscaAjuda[i]);
			pthread_exit(NULL);
		}
	}
	
	return NULL;


}

void *assistente(void *valor){

	int i = *((int*)valor);
	int j;
	//usleep(100);
	//AE = 1;
	/*if(acordado == 0){
			sem_wait(&sema);
				//critica
				acordado = 1;
				printf("Acordando AE\n");
			sem_post(&sema);		
		}*/
	//printf("Saida do semaforo\n");
	pthread_mutex_lock(&mutex);
	printf("Incrementado ajuda\n");
	sleep(1);
	
	for (j = 0; j < c - 1; j ++){
		cadeiras[0] = 0;
		cadeiras[j] = cadeiras[j+1];
	}
	cadeiras[c] = 0;	
	buscaAjuda[i] ++;
	programando[i] = 1;
	AE = 0;
	pthread_mutex_unlock(&mutex);
	printf("Ajudando estudante %d\n", i);
	return NULL;
	

}

void ctrl_c(){

	printf("Finalizando o programa e liberando todos os ponteiros\n");
	free(estudantes);
	free(buscaAjuda);
	free(cadeiras);
	free(t);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&sema);
	exit(0);


}
