#include <stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter = 0;
pthread_mutex_t mutex;

void* func(void *ptr){

	pthread_mutex_lock(&mutex); //trava a thread aqui e não executa outra
	//região critica do programa a ser executada
	counter++;

	for(int i = 0; i < 5; i ++){
		printf("Counter = %d\n", counter);
		printf("Thread number %ld\n", pthread_self()); //informa o id da thread
		
	}

	pthread_mutex_unlock(&mutex);
}


int main(){

	int i;

	pthread_mutex_init(&mutex, NULL);
	
	for(i = 0; i < 2; i ++)
		pthread_create(&tid[i], NULL, func, NULL);

	for(i = 0; i < 2; i++)
		pthread_join(tid[i], NULL);

	pthread_mutex_destroy(&mutex);


	return 0;
}
