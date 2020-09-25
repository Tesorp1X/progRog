#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#define MAX_VALUE 10 //Max value for matrix elements
#define MAX_ELEMENTS 15 //Max ammount of elements
#define MAX_SIZE 10 //Max size of the matrix
#define AMMOUNT_OF_EVALUATIONS 1000
#define AMMOUNT_OF_DIFFERENT_DATA 2


typedef struct Matrix {
    int size; // number of rows
    int **data; // a pointer to an array of n_rows = size pointers to rows; a row is an array of n_row = size integers
}Matrix;


void Matrix_swap(Matrix **a, Matrix **b) {
    Matrix *temp = *a;
    *a = *b;
    *b = temp;
    temp = NULL;
}
void Matrix_printf(Matrix *m);

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
    return matrix;
}


Matrix *Matrix_delete(Matrix *m) {
    for (int i = 0; i < m->size; ++i)  free(m->data[i]);
    free(m->data);
    free(m);
}

Matrix *Matrix_copy(Matrix *dst, Matrix *src) {
    int dsize = dst->size;
    for (int i = 0; i < dsize; ++i)
        for (int j = 0; j < dsize; ++j)
            dst->data[i][j] = src->data[i][j];
        printf("Matrix Copied!");
    return dst;
}

int Matrix_det(Matrix *a) {
    char isPlus = 1;
    int det = 0;
    int size = a->size;
    if (size == 1) return a->data[0][0];
    for (int i = 0; i < size; ++i) {
        Matrix *m = Matrix_make(size - 1);
        for (int j = 0; j < size - 1; ++j)
            for (int k = 0; k < size - 1; ++k)
                if (k < i)
                    m->data[j][k] = a->data[j + 1][k];
                else m->data[j][k] = a->data[j + 1][k + 1];
        
        int elem = a->data[0][i];
        if (isPlus) {
            det += elem * Matrix_det(m);
            isPlus = 0;
        } else {
            det -= elem * Matrix_det(m);
            isPlus = 1;
        }
        Matrix_delete(m);
    }
    return det;
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

Matrix *Matrix_random() {
    
    size_t size = 1 + rand() % MAX_SIZE; 
    Matrix *m = Matrix_make(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            m->data[i][j] = rand() % MAX_VALUE; // generating "random" number between 0 and MAX_VALUE - 1
    
    return m;
}

void Matrix_printf(Matrix *m) {
    int size = m->size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            printf("%d ", m->data[i][j]);
        if (i < size - 1) printf("\n");
    }
}


int main() {
    srand(time(NULL));
    int n = 1 + rand() % MAX_ELEMENTS; 
    Matrix **array = (Matrix **) malloc(n * sizeof(Matrix *));
    for (int i = 0; i < n; ++i) {
        array[i] = Matrix_random();
        Matrix_det(array[i]);
        Matrix_printf(array[i]);
        putchar('\n');
        putchar('\n');
    }
    
    return 0;
}