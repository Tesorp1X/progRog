#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

typedef struct Matrix {
    int size; // number of rows
    int det; // number of columns
    int **data; // a pointer to an array of n_rows = size pointers to rows; a row is an array of n_row = size integers
}Matrix;


Matrix *make_matrix(int size) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->size = size;
    int **data = malloc(sizeof(int *) * size); 
    for(int i = 0; i < size; i++){
        data[i] = calloc(size, sizeof(int));
    }
    matrix->data = data;
    return matrix;
}

void print_matrix(Matrix *m) {
    for(int i = 0; i < m->size; i++) {
        for(int j = 0; j < m->size; j++)
            printf("%d ", m->data[i][j]);
        printf("\n");
    }
}

int main() {
    Matrix **m;
    FILE *in, *out;
    int n, matrSize, flag = 0;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w+");
    fscanf(in, "%d", &n);
    m = (Matrix **) malloc(n * sizeof(Matrix **));
    for (int mat = 0; mat < n; ++mat) {
        fscanf(in, "%d", &matrSize);
        m[mat] = make_matrix(matrSize);

        for (int i = 0; i < matrSize; ++i)
            for (int j = 0; j < matrSize; ++j)
                fscanf(in, "%d", &(m[mat])->data[i][j]);        
        flag++;
    }
    printf("\n");
    if (flag == n) fprintf(out, "Read.\n");
    for (int mat = 0; mat < n; ++mat) {
        print_matrix(m[mat]);
    }
    
    return 0;
}