#include <math.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* input_file;
FILE* output_file;



typedef struct  {
  char code[12]; 
  char cnpj[19];
  double wieght;
} Merchandise;

void printMerchandises(Merchandise* merchandise, int size){
  for(int i = 0; i < size; i++){
    printf("%s %s %f\n",merchandise[i].code,merchandise[i].cnpj,merchandise[i].wieght);
  }
}

Merchandise* getData(int* quant, FILE* input_file){
  fscanf(input_file, "%d", quant);
  Merchandise* merchandise = calloc(*quant, sizeof(Merchandise));
  for(int i = 0; i < *quant; i++){
    fscanf(input_file, "%s", merchandise[i].code);
    merchandise[i].code[11] = '\0';
    fscanf(input_file, "%s", merchandise[i].cnpj);
    merchandise[i].cnpj[18] = '\0';
    fscanf(input_file, "%lf", &merchandise[i].wieght);
  }
  return merchandise;
}


int binary_search(Merchandise* vector,Merchandise element, int begin, int end){
  int middle = (begin + end)/2;
  if(begin <= end){
    if(!strcmp(element.code, vector[middle].code)){
      printf("\n\n\n");
      printf("wanted: ");
      printMerchandises(&element, 1);
      printf("found: ");
      printMerchandises(&vector[middle], 1);
      return middle;
    }
    // if(element < vector[middle]){
    if (strcmp(element.code, vector[middle].code) < 0) {
            // 2. FIX: Must be (middle - 1) to avoid infinite loop
            return binary_search(vector, element, begin, middle - 1);
        }
        
        // Search Right Half (cmp > 0)
        return binary_search(vector, element, middle + 1, end);  }
      printf("\n\n\n");
      printf("wanted: ");
      printMerchandises(&element, 1);
      printf("found: -1");
  return -1;
}


void merge(Merchandise* vector, int begin, int middle, int end){

  int left_len = middle - begin + 1;
  int right_len =   end - middle;

  Merchandise left[left_len];
  Merchandise right[right_len];

  for (int i = 0; i < left_len; i++){
    left[i] = vector[begin + i];
  }
  for(int i = 0; i < right_len; i++){
    right[i] = vector[middle + i + 1];
  }
  int i = 0;
  int j = 0;
  
  for(int k = begin; k <= end; k++){
    if(j >= left_len) {
      vector[k] = right[i];
      i++;
    } 
    else if (i >= right_len) {
      vector[k] = left[j];
      j++;
    }
    // else if (left[j] <= right[i]) {
    else if (strcmp(left[j].code,right[i].code)<=0) {
      vector[k] = left[j];
      j++;
    }
    else {
      vector[k] = right[i];
      i++;
    }
  }
}

void mergeSort(Merchandise* vector, int begin, int end){
  if(begin < end){
    int middle = (begin+end)/2;
    mergeSort(vector,begin, middle);
    mergeSort(vector, middle+1,end);
    merge(vector,begin,middle,end);
  }
}

int main(int argc, char *argv[])
{
  char* file_out_path = argv[2];
  printf("%s\n",file_out_path);
  char* file_input_path = argv[1];
  printf("%s\n",file_input_path);
  input_file = fopen(file_input_path, "r");
  output_file = fopen(file_out_path, "w+");

  int arrival_quant = 0;
  int inspection_quant = 0;

  Merchandise* arrival_merchandise = getData(&arrival_quant, input_file);
  printMerchandises(arrival_merchandise, arrival_quant);
  Merchandise* inspection_merchandise = getData(&inspection_quant, input_file);
  printf("---------------------\n");
  printMerchandises(inspection_merchandise, inspection_quant);
  printf("merging sort inspections arr\n");
  mergeSort(inspection_merchandise, 0, inspection_quant-1);
  printf("inspections arr in order based in there code\n");
  printMerchandises(inspection_merchandise, inspection_quant);

  int index = 0;
  float percentWidth = 0;

  char moreWeight[inspection_quant][50];
  int counter = 0;

  for(int i = 0; i<arrival_quant;i++){
    index = binary_search(inspection_merchandise, arrival_merchandise[i], 0,inspection_quant-1);
    if(index>=0){
      if(strcmp(inspection_merchandise[index].cnpj,arrival_merchandise[i].cnpj)){
        fprintf(output_file,"%s:%s<->%s\n", arrival_merchandise[i].code,arrival_merchandise[i].cnpj,inspection_merchandise[index].cnpj);
      }else{
        percentWidth = round((fabs( inspection_merchandise[index].wieght - arrival_merchandise[i].wieght)/arrival_merchandise[i].wieght)*100);
        if(percentWidth>=10){
          sprintf(moreWeight[counter], "%s:%0.fkg(%0.f%%)", arrival_merchandise[i].code,fabs(arrival_merchandise[i].wieght - inspection_merchandise[index].wieght),percentWidth);
          moreWeight[counter][49] = '\0';
          counter++;
        }
      }
    }
  }
  for(int i =0;i<counter;i++){
    fprintf(output_file, "%s\n",moreWeight[i]);
  }
  
  fclose(output_file);
  fclose(input_file);
  return 0;
}
