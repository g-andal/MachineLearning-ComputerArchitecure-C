#include <stdio.h>
#include <stdlib.h>

float** values;
float** inverse;
int r, c;

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("error\n");
        return 1;
    }

    fscanf(fp, "%d", &c);
    fscanf(fp, "%d", &r);
    c++;

    values = malloc(sizeof(float*)*r);
    for (int i = 0; i < r; i++)
        values[i] = malloc((c) * sizeof(float));
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            fscanf(fp, "%f,", &values[i][j]);

    return 0;
}

// void mult_row(int* row, int num){
//     for (int i = 0; i < ; i++)
//         row[i] *= num;
// }

// void mult_row(int* row, int num){
//     for (int i = 0; i < examples; i++)
//         for (int j = 0; j < attributes+1; j++)
//             row[i] *= num;
// }

void printMat(){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            printf("%f ", values[i][j]);
        }
        printf("\n");
    }
}