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

/*Sorts m by raising determinant value. m - array of matrices */
void Matrix_qSort(Matrix **m, int first, int last) {
    srand(time(NULL));
    int pivot = m[first + rand() % (last - first + 1)]->det;
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

Matrix *Matrix_random(size_t size) {
    Matrix *m = Matrix_make(size);
    int **a = m->data;
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            a[i][j] = rand() % 1000; // generating "random" number between 0 and 999
    return m;
}

void testSys() {
    /*          Calculating time
    float fTimeStart = clock()/(float)CLOCKS_PER_SEC; 
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;*/ 
    

}

int main() {
    Matrix **m;
    FILE *in, *out;
    int n, matrSize, flag = 0;

    /*Input*/
    in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Error: No such file as input.txt.");
        return 1;
    }
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
        //double fTimeStart = clock()/(float)CLOCKS_PER_SEC;
        Matrix_det(m[mat]);
        //double fTimeStop = clock()/(float)CLOCKS_PER_SEC;
        //printf("Det time is : %lf\n", fTimeStop - fTimeStart);
    }

    /*Sorting array of matrices.*/
    //double fTimeStart = clock()/(float)CLOCKS_PER_SEC; 
    Matrix_qSort(m, 0, n - 1);
    //double fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    //printf("Sort time is : %.9lf\n", fTimeStop - fTimeStart);

    /*Output*/
    out = fopen("output.txt", "w+");
    if (out == NULL) {
        printf("Error: No such file as output.txt.");
        return 1;
    }
    for (int mat = 0; mat < n; ++mat) {
        printf("Determinant is : %d\n", m[mat]->det);
        Matrix_fprintf(out, m[mat]);
        if (mat < n - 1) fprintf(out, "\n");
        Matrix_delete(m[mat]);
    }
    free(m);
    
    return 0;
}