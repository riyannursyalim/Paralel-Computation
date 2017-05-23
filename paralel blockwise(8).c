#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
/*int string_search(char* data, char* target) {


}*/


int main(int argc, char** argv) {
  FILE* file;
  unsigned int length;
  char* data;
  char target[256];
  int indeks[1000];
  int found;
  double time, tFinal;

  /* open the file */
  /*if (argc < 2) {
    printf("Please pass an input file.\n");
    return 0;
  }*/
  file = fopen("shakespeare.txt", "r");
  if (!file) {
    printf("Could not open %s for reading.\n", argv[1]);
    return 0;
  }

  /* find the length of the file */
  fseek(file, 0L, SEEK_END);
  length = ftell(file);
  fseek(file, 0L, SEEK_SET);

  /* read the file into memory */
  data = malloc(length * sizeof(char));
  memset(data, 0, length);
  fread(data, sizeof(char), length, file);

  /* ask what should be searched for */
  printf("Enter search term: ");
  scanf("%s", target);

  /* now do the searching
  found = string_search(data, target);
  if (found) {
    printf("Found it!\n");
  } else {
    printf("Not found...\n");
  }

  return 0;
}*/
    char *p1, *p2, *p3;
    int i=0,j=0,flag=0;

  p1 = data;
  p2 = target;

    time=clock();
    int z=0;
    int kataKetemu=0;
    //int chunk=strlen(data)/2;

    #pragma omp paralel private(i, j) num_thread(8)
    {
        #pragma omp for schedule(static, 2)
        for(i = 0; i<strlen(data); i++){
            if(*p1 == *p2){
                p3 = p1;
                for(j = 0;j<strlen(target);j++){
                    if(*p3 == *p2){
                        p3++;
                        p2++;
                    } else break;
                }
                p2 = target;
                if(j == strlen(target)){
                    flag = 1;
                    indeks[z++]=i;
                    kataKetemu++;
                }
            }
            p1++;
        }
        #pragma omp critical
        if(flag==0){
            printf("Substring NOT found");
        }
    }

    tFinal=(clock()-time)/1e3;
    printf("Jumlah Kata yang dicari: %i\n",kataKetemu);
    for(i=0; i<z; i++){
        printf("Substring berada pada Indeks ke %i\n",indeks[i]);
    }
    printf("Waktu: %lf\n",tFinal);
    return (0);
}

