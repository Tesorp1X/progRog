#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Matrix {
    int size; // number of rows
    int det; // number of columns
    int **data; // a pointer to an array of n_rows = size pointers to rows; a row is an array of n_row = size integers
}Matrix;

void swap(Matrix **a, Matrix **b) {
    Matrix *temp = *a;
    *a = *b;
    *b = temp;
}

Matrix *make_matrix(int size) {
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

Matrix *delete_matrix(Matrix *m) {
    for (int i = 0; i < m->size; ++i)  free(m->data[i]);
    free(m->data);
    free(m);
}

int det_matrix(Matrix *a) {
    char isPlus = 1;
    int det = 0;
    if (a->size == 1) {
        a->det = a->data[0][0];
        return a->data[0][0];
    }
    for (int i = 0; i < a->size; ++i) {
        Matrix *m = make_matrix(a->size - 1);
        for (int j = 0; j < m->size; ++j)
            for (int k = 0; k < m->size; ++k)
                if (k < i)
                    m->data[j][k] = a->data[j + 1][k];
                else m->data[j][k] = a->data[j + 1][k + 1];
        
        int elem = a->data[0][i];
        if (isPlus) {
            det += elem * det_matrix(m);
            isPlus = 0;
        } else {
            det -= elem * det_matrix(m);
            isPlus = 1;
        }
        delete_matrix(m);
    }
    a->det = det;
    return det;
}

void print_matrix(FILE *out, Matrix *m) {
    for(int i = 0; i < m->size; i++) {
        for(int j = 0; j < m->size; j++)
            fprintf(out, "%d ", m->data[i][j]);
        fprintf(out, "\n");
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
    if (m == NULL) {
        printf("Error: allocation failed.");
        return 1;
    }
    for (int mat = 0; mat < n; ++mat) {
        fscanf(in, "%d", &matrSize);
        m[mat] = make_matrix(matrSize);
        if (m == NULL) {
            printf("Error: allocation failed.");
            return 1;
        }
        for (int i = 0; i < matrSize; ++i)
            for (int j = 0; j < matrSize; ++j)
                fscanf(in, "%d", &(m[mat])->data[i][j]);        
        flag++;
        det_matrix(m[mat]);
    }


    swap(&m[0], &m[1]);
    if (flag == n) fprintf(out, "Read.\n");
    for (int mat = 0; mat < n; ++mat) {
        print_matrix(out, m[mat]);
        fprintf(out, "Determinant is %d\n", m[mat]->det);
        delete_matrix(m[mat]);
    }
    free(m);
    
    return 0;
}