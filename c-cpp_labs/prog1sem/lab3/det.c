#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

typedef struct Matrix {
    int size; // number of rows
    int det; // determinant
    int **data; // a pointer to an array of n_rows = size pointers to rows; a row is an array of n_row = size integers
}Matrix;


void Matrix_swap(Matrix **a, Matrix **b) {
    Matrix *temp = *a;
    *a = *b;
    *b = temp;
    temp = NULL;
}


Matrix *Matrix_make(int size) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->size = size;
    int **data = malloc(sizeof(int *) * size); 
    if (data == NULL) return NULL;
    for(int i = 0; i < size; i++){
        data[i] =  malloc(size * sizeof(int));
        if (data == NULL) return NULL;
    }
    matrix->data = data;
    matrix->det = 0;
    return matrix;
}


void Matrix_delete(Matrix *m) {
    for (int i = 0; i < m->size; ++i)  free(m->data[i]);
    free(m->data);
    free(m);
}

void Matrix_printf(Matrix *m) {
    for (int i = 0; i < m->size; ++i) {
        for (int j = 0; j < m->size; ++j)
            printf("%d ", m->data[i][j]);
        if (i < m->size - 1) printf("\n");
    }
}

int Matrix_det(Matrix *a) {
    char isPlus = 1;
    int det = 0;
    switch (a->size)
    {
    case 1:
        a->det = a->data[0][0];
        return a->data[0][0];
        break;
    case 2:
        a->det = a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0];
        return a->det;
        break;
    default:
        break;
    }
    Matrix *m = Matrix_make(a->size - 1);
    for (int i = 0; i < a->size; ++i) {
        for (int j = 0; j < m->size; ++j)
            for (int k = 0; k < m->size; ++k)
                if (k < i)
                    m->data[j][k] = a->data[j + 1][k];
                else m->data[j][k] = a->data[j + 1][k + 1];
        Matrix_printf(m);
        putchar('\n');
        putchar('\n');
        int elem = a->data[0][i];
        if (isPlus) {
            det += elem * Matrix_det(m);
            isPlus = 0;
        } else {
            det -= elem * Matrix_det(m);
            isPlus = 1;
        }   
    }
    Matrix_delete(m);
    a->det = det;
    return det;
}
void Matrix_fscanf(FILE *in, Matrix *m) {
    for (int i = 0; i < m->size; ++i)
        for (int j = 0; j < m->size; ++j)
            fscanf(in, "%d", &(m)->data[i][j]);
}


void Matrix_fprintf(FILE *out, Matrix *m) {
    for (int i = 0; i < m->size; ++i) {
        for (int j = 0; j < m->size; ++j)
            fprintf(out, "%d ", m->data[i][j]);
        if (i < m->size - 1) fprintf(out, "\n");
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    int n;
    fscanf(in, "%d", &n);
    Matrix *m = Matrix_make(n);
    Matrix_fscanf(in, m);
    printf("%d", Matrix_det(m));
    Matrix_delete(m);
    return 0;
}