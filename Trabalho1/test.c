#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int numEstudantes, i, *estudantes, sum = 0;
	srand(time(0));
	
    //printf("Enter number of elements: ");
    //scanf("%d", &num);
	numEstudantes = rand()%10;
    estudantes = (int*) malloc(numEstudantes * sizeof(int));  //memory allocated using malloc
    if(estudantes == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
	printf("Numero rand: %d\n", numEstudantes);
    printf("Enter elements of array: ");
    for(i = 0; i < numEstudantes; ++i)
    {
        estudantes[i] = i;
	printf("\n%d ", estudantes[i]);
        sum += estudantes[i];
    }

    printf("Sum = %d\n", sum);
    free(estudantes);
    return 0;
}
