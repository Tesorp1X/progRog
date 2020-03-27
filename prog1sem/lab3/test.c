#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


typedef struct Matrix {
    int size; // number of rows
    int det; // number of columns
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


Matrix *Matrix_delete(Matrix *m) {
    for (int i = 0; i < m->size; ++i)  free(m->data[i]);
    free(m->data);
    free(m);
}


int Matrix_det(Matrix *a) {
    char isPlus = 1;
    int det = 0;
    if (a->size == 1) {
        a->det = a->data[0][0];
        return a->data[0][0];
    }
    for (int i = 0; i < a->size; ++i) {
        Matrix *m = Matrix_make(a->size - 1);
        for (int j = 0; j < m->size; ++j)
            for (int k = 0; k < m->size; ++k)
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
    a->det = det;
    return det;
}

/*Sorts m by raising determinant value. m - array of matrices */
void Matrix_qSort(Matrix **m, int first, int last) {
    srand(time(NULL));
    int pivot = m[first + rand() % (last - first)]->det;
    printf("Pivot is %d\n", pivot);
    int left = first, right = last;
    while (left < right) {
        while (m[left]->det < pivot)
            left++;
        while (m[right]->det > pivot)
            right--;
        if (left <= right)
            Matrix_swap(&m[left++], &m[right--]);
    }
    /*Recursive callouts for both left and right parts if array contains more than 1 element.*/
    if (first < right) Matrix_qSort(m, first, right);
    if (left < last) Matrix_qSort(m, left, last);
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
    Matrix **m;
    FILE *in, *out;
    int n, matrSize, flag = 0;

    /*Input*/
    in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);
    m = (Matrix **) malloc(n * sizeof(Matrix **));
    if (m == NULL) {
        printf("Error: allocation failed.");
        return 1;
    }

    for (int mat = 0; mat < n; ++mat) {
        fscanf(in, "%d", &matrSize);
        m[mat] = Matrix_make(matrSize);
        if (m == NULL) {
            printf("Error: allocation failed.");
            return 1;
        }
        Matrix_fscanf(in, m[mat]);       
        flag++;
        Matrix_det(m[mat]);
    }
    
    /*Output*/
    out = fopen("output.txt", "w+");
    /*for (int mat = 0; mat < n; ++mat) {
        fprintf(out, "%d\t", m[mat]->det);
    }
    fprintf(out, "\n");*/
    Matrix_qSort(m, 0, n - 1);
    for (int mat = 0; mat < n; ++mat) {
        Matrix_fprintf(out, m[mat]);
        //fprintf(out, "%d\t", m[mat]->det);
        if (mat < n - 1) fprintf(out, "\n");
        Matrix_delete(m[mat]);
    }
    free(m);
    
    return 0;
}