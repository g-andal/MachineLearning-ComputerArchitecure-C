#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float** values;
    int r, c;
}Matrix;

Matrix read_file(FILE*);
void init_inverse(Matrix);
void printMat(Matrix);

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("error\n");
        return 1;
    }

    Matrix original = read_file(fp);
    
    Matrix inverse;
    inverse.r = original.r;
    inverse.c = original.c;
    init_inverse(inverse);

    printMat(original);
    printf("\n");
    printMat(inverse);

    return 0;
}

Matrix read_file(FILE* fp){
    Matrix og;
    fscanf(fp, "%d", &(og.c));
    fscanf(fp, "%d", &(og.r));
    og.c++;

    og.values = malloc(sizeof(float)*(og.r));
    for (int i = 0; i < og.r; i++)
        og.values[i] = malloc((og.c) * sizeof(float));
    
    for (int i = 0; i < og.r; i++)
        for (int j = 0; j < og.c; j++)
            fscanf(fp, "%f,", &(og.values[i][j]));
    
    return og;
}

void init_inverse(Matrix in){
    in.values = malloc(sizeof(float)*in.r);
    for (int i = 0; i < in.r; i++)
        for (int j = 0; j < in.c; j++){
            if (i==j)
                in.values[i][j] = 1;
            else
                in.values[i][j] = 0;
        }
}

// void findInverse(){
//     float** copy = malloc((c) * sizeof(float));
//     for (int i = 0; i < r; i++)
//         values[i] = malloc((c) * sizeof(float));

//     for (int i = 0; i < r; i++)
//         for (int j = 0; j < c; j++)
//             copy[i][j] = values[i][j];

    
// }

// // rows of 1st x cols of 2nd
// float** multMat(float** matA, float** matB){
//     float** result = malloc((c) * sizeof(float));
// }

// void mult_row(int* row, int num){
//     for (int i = 0; i < ; i++)
//         row[i] *= num;
// }

// void mult_row(int* row, int num){
//     for (int i = 0; i < examples; i++)
//         for (int j = 0; j < attributes+1; j++)
//             row[i] *= num;
// }

void printMat(Matrix mat){
    for (int i = 0; i < mat.r; i++){
        for (int j = 0; j < mat.c; j++){
            printf("%f ", mat.values[i][j]);
        }
        printf("\n");
    }
}