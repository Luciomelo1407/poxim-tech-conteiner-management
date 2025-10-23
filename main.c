#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

FILE* arq;

typedef struct  {
  char code[11]; 
  char cnpj[18];
  int wieght;
} Merchandise;

typedef struct{
  int size;
  Merchandise* merchandise;
} Merchandise_Array ;

int main(int argc, char *argv[])
{

  char* file_input_path = argv[1];
  arq = fopen(file_input_path, "r");
  Merchandise_Array expected;

  int quant;
  
  fscanf(arq, "%d", &quant);
  printf("quantidade: %d\n",quant);

  expected.size = quant;
  expected.merchandise = calloc(quant, sizeof(Merchandise));

  for(int i = 0; i < quant; i++){
    fscanf(arq, "%s", expected.merchandise[i].code);
    printf("merchandise code: %s\n",expected.merchandise[i].code);
    fscanf(arq, "%s", expected.merchandise[i].cnpj);
    printf("merchandise cnpj: %s\n",expected.merchandise[i].cnpj);
    fscanf(arq, "%d", &expected.merchandise[i].wieght);
    printf("merchandise peso: %d\n",expected.merchandise[i].wieght);
  }
  
  return 0;
}
