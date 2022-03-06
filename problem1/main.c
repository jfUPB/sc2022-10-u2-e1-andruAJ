#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr)
{
   printf("Entro al GetArray\n"); 
  //ESta funciòn se debe encargar de recibir los datos del usuario y construir el array
  char *endptr;
  long val;
  long val1;
  char number[40];
  //u_int32_t *psize = parr->size;

  if (fgets(number, 40, stdin) != NULL)
  {
    number[strlen(number) -1 ] = 0;
  }
  errno = 0;
  val = strtol(number, &endptr, 10);
  if (errno != 0)
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

  if (endptr == number) {
        fprintf(stderr, "No se identifico ningún número\n");
        exit(EXIT_FAILURE);
    } 
  //psize = val;
  parr->size = val;
  printf("el valor que ingreso fue:%d \n", parr->size);

  for (int i = 0; i < val; i)
  {
     printf("Entro al for\n"); 
    if (fgets(number, 40, stdin) != NULL)
    {
        number[strlen(number) -1 ] = 0;
        i++;
    }
    errno = 0;
    val1 = strtol(number, &endptr, 10);

    if (errno != 0)
    {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == number) 
    {
        fprintf(stderr, "No se identifico ningún número\n");
        exit(EXIT_FAILURE);
    }
    parr->pdata[i-1] == val1;
    printf("el valor que ingreso fue:%d \n", parr->pdata[i-1]);

  }
}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
    
}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
