#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float** values;
    int r, c;
}Matrix;

Matrix read_file(FILE*);
Matrix init_inverse(int);
Matrix init_Mat(int, int);

Matrix transpose(Matrix);
Matrix multiply(Matrix, Matrix);
Matrix inverse(Matrix);

void row_mult(Matrix, int, int);
void printMat(Matrix);

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("error\n");
        return 1;
    }

    Matrix original = read_file(fp);
    // Matrix tr = transpose(original);

    Matrix ex;
    ex.r = 2;
    ex.c = 3;
    ex.values = malloc(sizeof(float*)*(ex.r));
    for (int i = 0; i < ex.r; i++)
        ex.values[i] = malloc((ex.c) * sizeof(float));

    for (int i = 0; i < ex.r; i++)
        for (int j = 0; j < ex.c; j++)
            ex.values[i][j] = i*ex.c+j+1;

    Matrix mult = multiply(original,ex);

    printMat(original);
    printf("\n");
    printMat(ex);
    printf("\n");
    printMat(mult);

    return 0;
}

Matrix read_file(FILE* fp){
    int row, col;
    fscanf(fp, "%d", &col);
    fscanf(fp, "%d", &row);
    Matrix og = init_Mat(row,col+1);
    
    for (int i = 0; i < og.r; i++)
        for (int j = 0; j < og.c; j++)
            fscanf(fp, "%f,", &(og.values[i][j]));
    
    return og;
}

Matrix init_inverse(int n){
    Matrix in = init_Mat(n,n);

    for (int i = 0; i < in.r; i++)
        for (int j = 0; j < in.c; j++){
            if (i==j)
                in.values[i][j] = 1;
            else
                in.values[i][j] = 0;
        }
    return in;
}

Matrix init_Mat(int row, int col){
    Matrix new;
    new.r = row;
    new.c = col;

    new.values = malloc(sizeof(float*)*new.r);
    for (int i = 0; i < new.r; i++)
        new.values[i] = malloc((new.c) * sizeof(float));
    
    return new;
}

// Matrix inverse(Matrix A){
//     Matrix in = init_inverse(A.r);

// }

Matrix transpose(Matrix mat){
    Matrix tr = init_Mat(mat.c, mat.r);

    for (int i = 0; i < tr.r; i++)
        for (int j = 0; j < tr.c; j++)
            tr.values[i][j] = mat.values[j][i];
    
    return tr;
}

Matrix multiply(Matrix A, Matrix B){
    Matrix result = init_Mat(A.r, B.c);

    for (int i = 0; i < result.r; i++)
        for (int j = 0; j < result.c; j++){
            result.values[i][j] = 0;
            for (int x = 0; x < B.r; x++)
                result.values[i][j] += (A.values[i][x] * B.values[x][j]);
        }

    return result;
}

// Matrix duplicate(){

// }

// void row_mult(Matrix A, int row, int num){

// }

void printMat(Matrix mat){
    for (int i = 0; i < mat.r; i++){
        for (int j = 0; j < mat.c; j++){
            printf("%f ", mat.values[i][j]);
        }
        printf("\n");
    }
}