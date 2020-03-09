#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXLEN 255

//magic stuff, u know blin
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;

	return;
}


void colSwap(int col1, int col2, int n, int arr[][MAXLEN]) {
	for (int i = 0; i < n; ++i)
		swap(&arr[i][col1], &arr[i][col2]);

	return;
}

void charEval(int n, int m, int arr[][MAXLEN], int res[][MAXLEN]) {

	for (int j = 0; j < m; ++j)
		for (int i = 0; i < n; ++i)
			if (arr[i][j] % 2 && arr[i][j] < 0)
				res[0][j] += arr[i][j];
	return;
}

void sortCharVal(int m, int matr[][MAXLEN], int arr[][MAXLEN]) {
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m - i - 1; ++j)
			if (arr[0][j] > arr[0][j + 1])
				colSwap(j, j + 1, 2, arr);
	return;
}

void resultEval(int n, int m, int matr[][MAXLEN], int arr[][MAXLEN], int res[][MAXLEN]) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			res[i][j] = matr[i][arr[1][j]];
		return;
}

int main() {
	//var
	FILE* in, * out;
	int inmatr[MAXLEN][MAXLEN];
	int res[MAXLEN][MAXLEN];
	int charValues[MAXLEN][MAXLEN];
	int n, m;
	int maxVal, minVal;

	//input
	in = fopen("input.txt", "r");
	if (in == NULL) {
		printf("ERROR: No such file as input.txt !");
		return 1;
	}
	fscanf(in, "%d %d", &m, &n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			fscanf(in, "%d", &inmatr[i][j]);
	fclose(in);

	//evaluations
	for (int i = 0; i < m; ++i) {
		charValues[0][i] = 0;
		charValues[1][i] = i;
	}
	charEval(n, m, inmatr, charValues);
	sortCharVal(m, inmatr, charValues);
	resultEval(n, m, inmatr, charValues, res);
	minVal = charValues[0][0];
	maxVal = charValues[0][m - 1];

	//output
	out = fopen("output.txt", "w");
	if (out == NULL) {
		printf("ERROR: No such file as ouput.txt !");
		return 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			fprintf(out, "%d ", res[i][j]);
		fprintf(out, "\n");
	}
	fprintf(out, "%d %d", minVal, maxVal);
	fclose(out);

	printf("DONE!");

	return 0;
}