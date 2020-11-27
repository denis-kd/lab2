// Lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "time.h"
#include "conio.h"
#include "locale.h"
#include <iostream>

#define SIZE 10000

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	
	DWORD Start = 0, End = 0;
	int elem_c = 0, i = 0, j = 0, r = 0;

	int **A = new int*[SIZE];
	for(int a = 0; a < SIZE; a++) {
		A[a] = new int[SIZE];
	}

	int **B = new int*[SIZE];
	for(int a = 0; a < SIZE; a++) {
		B[a] = new int[SIZE];
	}

	int **C = new int*[SIZE];
	for(int a = 0; a < SIZE; a++) {
		C[a] = new int[SIZE];
	}

	while(i < SIZE) {
		while(j < SIZE) {
			A[i][j] = rand() % 100 + 1;
			j++;
		}
		i++;
		j = 0;
	}
	i = 0; j = 0;
	while(i < SIZE) {
		while(j < SIZE) {
			B[i][j] = rand() % 100 + 1;
			j++;
		}
		i++;
		j = 0;
	}
	Start = GetTickCount();
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			elem_c = 0;
			for(r = 0; r < SIZE; r++) {
				elem_c = elem_c + A[i][r] * B[r][j];
				C[i][j] = elem_c;
			}
			//printf("%d\t%d\n", i, j);
		}
	}
	End = GetTickCount();
	printf("Размер матрицы: %d\nВремя выполнения: %d ms", SIZE, End - Start);
	getch();
	return 0;
}

