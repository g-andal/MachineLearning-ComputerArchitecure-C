#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float** values;
    int r, c;
}Matrix;

Matrix read_file(FILE*);
Matrix init_inverse(int);
Matrix transpose(Matrix);
Matrix multiply(Matrix, Matrix);
void printMat(Matrix);

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("error\n");
        return 1;
    }

    Matrix original = read_file(fp);
    Matrix tr = transpose(original);
    Matrix mult = multiply(original,tr);

    printMat(original);
    printf("\n");
    printMat(tr);
    printf("\n");
    printf("%d   %d\n", mult.r, mult.c);
    printMat(mult);

    return 0;
}

Matrix read_file(FILE* fp){
    Matrix og;
    fscanf(fp, "%d", &(og.c));
    fscanf(fp, "%d", &(og.r));
    og.c++;

    og.values = malloc(sizeof(float*)*(og.r));
    for (int i = 0; i < og.r; i++)
        og.values[i] = malloc((og.c) * sizeof(float));
    
    for (int i = 0; i < og.r; i++)
        for (int j = 0; j < og.c; j++)
            fscanf(fp, "%f,", &(og.values[i][j]));
    
    return og;
}

Matrix init_inverse(int n){
    Matrix in;
    in.r = n;
    in.c = n;

    in.values = malloc(sizeof(float*)*in.r);
    for (int i = 0; i < in.r; i++)
        in.values[i] = malloc((in.c) * sizeof(float));

    for (int i = 0; i < in.r; i++)
        for (int j = 0; j < in.c; j++){
            if (i==j)
                in.values[i][j] = 1;
            else
                in.values[i][j] = 0;
        }
    return in;
}

Matrix transpose(Matrix mat){
    Matrix tr;
    tr.r = mat.c;
    tr.c = mat.r;

    tr.values = malloc(sizeof(float*)*tr.r);
    for (int i = 0; i < tr.r; i++)
        tr.values[i] = malloc((tr.c) * sizeof(float));
    
    for (int i = 0; i < tr.r; i++)
        for (int j = 0; j < tr.c; j++)
            tr.values[i][j] = mat.values[j][i];
    
    return tr;

}

Matrix multiply(Matrix A, Matrix B){
    Matrix result;
    result.r = A.r;
    result.c = B.c;

    result.values = malloc(sizeof(float*)*result.r);
    for (int i = 0; i < result.r; i++)
        result.values[i] = malloc((result.c) * sizeof(float));
    
    for (int i = 0; i < result.r; i++)
        for (int j = 0; j < result.c; j++){
            result.values[i][j] = 0;
            for (int x = 0; x < B.r; x++)
                result.values[i][j] += (A.values[i][x] * B.values[x][j]);
        }

    return result;



}

void printMat(Matrix mat){
    for (int i = 0; i < mat.r; i++){
        for (int j = 0; j < mat.c; j++){
            printf("%f ", mat.values[i][j]);
        }
        printf("\n");
    }
}