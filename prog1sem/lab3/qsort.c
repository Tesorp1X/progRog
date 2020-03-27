#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print_arr(int *a, int n) {
    for (int i = 0; i < n; ++i)
        printf("%d\t", a[i]);
}

void qSort(int *a, int first, int last) {
    srand(time(NULL));
    int pivot = a[first + rand() % (last - first)];
    int l = first, r = last;
    while (l < r) {
        while (a[l] < pivot) l++;
        while (a[r] > pivot) r--;
        if (l <= r) swap(&a[r--], &a[l++]);
    }
    if (first < r) qSort(a, first, r);
    if (l < last) qSort(a, l, last);
}

int main() {
    int a[8] = {4, 5, 1, -9, 6, 10, -1, -2};
    print_arr(a, 8);
    putchar('\n');
    qSort(a, 0, 7);
    print_arr(a, 8);
    return 0;
}