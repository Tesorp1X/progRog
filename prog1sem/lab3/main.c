#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define MAX_VALUE 10 //Max value for matrix elements
#define MAX_ELEMENTS 100 //Max ammount of elements
#define MAX_SIZE 5 //Max size of the matrix
#define AMMOUNT_OF_EVALUATIONS 1000
#define AMMOUNT_OF_DIFFERENT_DATA 5
#define MIN_SIZE 1 //Min size of matrix or an array

typedef struct Matrix {
    int size; // number of rows
    int det; // determinant
    int **data; // a pointer to an array of n_rows = size pointers to rows; a row is an array of n_row = size integers
}Matrix;

typedef struct TimeValues {
    double avarage;
    double deviation;
}TimeValues;

void Matrix_swap(Matrix **a, Matrix **b) {
    Matrix *temp = *a;
    *a = *b;
    *b = temp;
    temp = NULL;
}


Matrix *Matrix_make(int size) {
    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    matrix->size = size;
    int **data = (int **) malloc(sizeof(int *) * size); 
    if (data == NULL) return NULL;
    for(int i = 0; i < size; i++){
        data[i] =  (int *) malloc(size * sizeof(int));
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
  /*  case 3:
        a->det = a->data[0][0] * a->data[1][1] * a->data[2][2] + a->data[0][2] * a->data[1][0] * a->data[2][1]
         + a->data[1][2] * a->data[0][1] * a->data[2][0] - ; */
    default:
        break;
    }
    Matrix *m = (Matrix *) Matrix_make(a->size - 1);
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

void Matrix_bubleSort(Matrix **m, size_t size) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (m[j]->det > m[j + 1]->det)
                Matrix_swap(&m[j], &m[j + 1]);
}

/*Sorts m by raising determinant value. m - array of matrices */
void Matrix_qSort(Matrix **m, int first, int last) {
    //srand(time(NULL));
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

void Matrix_printf(Matrix *m) {
    int size = m->size;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            printf("%d ", m->data[i][j]);
        if (i < size - 1) printf("\n");
    }
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

Matrix *Matrix_random() {
    size_t size = MIN_SIZE + rand() % MAX_SIZE; 
    Matrix *m = Matrix_make(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            m->data[i][j] = rand() % MAX_VALUE; // generating "random" number between 0 and MAX_VALUE - 1
    
    return m;
}

void timeTest(Matrix **array, size_t size, TimeValues *time, char type) {
    time->avarage = 0;
    time->deviation = 0;
    double fTimeStart; 
    double fTimeStop;
    double *res = malloc(AMMOUNT_OF_EVALUATIONS * sizeof(double));
    if (type == 1) {
        for (int i = 0; i < AMMOUNT_OF_EVALUATIONS; ++i) {
            fTimeStart = clock()/(double)CLOCKS_PER_SEC;
            Matrix_qSort(array, 0, size - 1);
            fTimeStop = clock()/(double)CLOCKS_PER_SEC;
            res[i] = (fTimeStop - fTimeStart) / AMMOUNT_OF_EVALUATIONS;
            time->avarage += res[i] / AMMOUNT_OF_EVALUATIONS;
        }
        for (int i = 0; i < AMMOUNT_OF_EVALUATIONS; ++i)
            time->deviation += pow((time->avarage - res[i]), 2);
        free(res);
        time->deviation = sqrt(time->deviation);
    } else if (type == 0) {
        for (int i = 0; i < AMMOUNT_OF_EVALUATIONS; ++i) {
            fTimeStart = clock()/(double)CLOCKS_PER_SEC;
            Matrix_bubleSort(array, size);
            fTimeStop = clock()/(double)CLOCKS_PER_SEC;
            res[i] = (fTimeStop - fTimeStart) / AMMOUNT_OF_EVALUATIONS;
            time->avarage += res[i] / AMMOUNT_OF_EVALUATIONS;
        }
        for (int i = 0; i < AMMOUNT_OF_EVALUATIONS; ++i)
            time->deviation += pow((time->avarage - res[i]), 2);
        free(res);
        time->deviation = sqrt(time->deviation);
    }
}

void testSys(char type) {
    /*          Calculating time
    double fTimeStart = clock()/(double))CLOCKS_PER_SEC; 
    double fTimeStop = clock()/(double)CLOCKS_PER_SEC; */ 
    srand(time(NULL));
    TimeValues bestTime;
    TimeValues worstTime;
    Matrix **bestData;
    Matrix **worstData;
    size_t bsize;
    size_t wsize;
    int flag = 1;
    for (int test = 0; test < AMMOUNT_OF_DIFFERENT_DATA; ++test) {
        int n = MIN_SIZE + rand() % MAX_ELEMENTS;
        TimeValues tempTime;
        Matrix **array = (Matrix **) malloc(n * sizeof(Matrix *));
        for (int i = 0; i < n; ++i) {
            array[i] = Matrix_random();
            Matrix_det(array[i]);
        }
        timeTest(array, n, &tempTime, type);
        printf("Iteration #%d:\n", test + 1);
        printf("Average time: %.12lf; Deviation: %.12lf\n", tempTime.avarage, tempTime.deviation);
        if (flag) {
            bestTime = tempTime;
            worstTime = tempTime;
            bestData = array;
            worstData = array;
            bsize = n;
            wsize = n;
            array = NULL;
        } else if (!flag && tempTime.avarage > worstTime.avarage) {
            for (int j = 0; j < wsize; ++j) Matrix_delete(worstData[j]);
            free(worstData);
            worstTime = tempTime;
            worstData = array;
            wsize = n;
            array = NULL;
        } else if (!flag && tempTime.avarage < bestTime.avarage) {
            for (int j = 0; j < wsize; ++j) Matrix_delete(bestData[j]);
            free(bestData);
            bestTime = tempTime;
            bestData = array;
            bsize = n;
            array = NULL;
        } else {
            for (int j = 0; j < n; ++j) Matrix_delete(array[j]);
            free(array);
        }
    }
    printf("Best average time is: %.12lf and best diviation: %.12lf\nAnd data is:\n", bestTime.avarage, bestTime.deviation);
    for (int i = 0; i < bsize; ++i) {
        Matrix_printf(bestData[i]);
        Matrix_delete(bestData[i]);
        putchar('\n');
        printf("Det is %d\n", bestData[i]->det);
        putchar('\n');
    } 
    printf("Worst average time is: %.12lf and worst diviation: %.12lf\nAnd data is:\n", worstTime.avarage, worstTime.deviation);
    for (int i = 0; i < wsize; ++i) {
        Matrix_printf(worstData[i]);
        Matrix_delete(worstData[i]);
        putchar('\n');
        printf("Det is %d\n", worstData[i]->det);
        putchar('\n');
    }
    free(worstData);
    free(bestData);
}

int main() {
    
    Matrix **m;
    FILE *in, *out;
    int n, matrSize, flag = 0;

    /*Input*/
 /*   in = fopen("input.txt", "r");
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
        Matrix_det(m[mat]);
    }

    /*Sorting array of matrices.*/
 //   Matrix_qSort(m, 0, n - 1);

    /*Output*/
 /*   out = fopen("output.txt", "w+");
    if (out == NULL) {
        printf("Error: No such file as output.txt.");
        return 1;
    }
    for (int mat = 0; mat < n; ++mat) {
        Matrix_fprintf(out, m[mat]);
        if (mat < n - 1) fprintf(out, "\n");
        Matrix_delete(m[mat]);
    }
    free(m);
    */
    char type;
    printf("Type 0 if you want to test a bubleSort or 1 if quickSort.\n");
    scanf("%d", &type);
   // srand(time(NULL));
    testSys(type);

    return 0;
}