// Lab2_Shell.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "conio.h"
#include "locale.h"
#include "Windows.h"
#include <iostream>

void shell(int *items, int count)
{
	int i, j, gap, k;
	int x, a[5];

	a[0]=9; a[1]=5; a[2]=3; a[3]=2; a[4]=1;

	for(k=0; k < 5; k++) {
		gap = a[k];
		for(i=gap; i < count; ++i) {
			x = items[i];
			for(j=i-gap; (x < items[j]) && (j >= 0); j=j-gap)
				items[j+gap] = items[j];
			items[j+gap] = x;
		}
	}
}

void qs(int *items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
	int i, j;
	int x, y;



	i = left; j = right;

	/* выбор компаранда */
	x = items[(left+right)/2];
  
	do {
		while((items[i] < x) && (i < right)) i++;
		while((x < items[j]) && (j > left)) j--;

		if(i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while(i <= j);

	if(left < j) qs(items, left, j);
	if(i < right) qs(items, i, right);
}

int compare(const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int start = 0, end = 0, val = 0;
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	HANDLE f = CreateFile(L"Res.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int size = 1000000;
	DWORD num = 0;
	char buf[150] = {0};
	OVERLAPPED ol = {0};

	// A - случайные, B - возрастающие, C - убывающие
	int *A1 = new int[size];
	int *B1 = new int[size];
	int *C1 = new int[size];
	int *A2 = new int[size];
	int *B2 = new int[size];
	int *C2 = new int[size];
	int *A3 = new int[size];
	int *B3 = new int[size];
	int *C3 = new int[size];
	for(int i = 0; i < size; i++) {
		A1[i] = -100 + rand() % 201;
		A2[i] = A1[i];
		A3[i] = A1[i];
	}
	for(int i = 0; i < size; i++, val += 37) {
		B1[i] = val;
		B2[i] = B1[i];
		B3[i] = B1[i];

	}
	for(int i = 0, val = 0x7FFFFFFF; i < size; i++, val -= 278) {
		C1[i] = val;
		C2[i] = C1[i];
		C3[i] = C1[i];
	}
	
/*-------shell-------*/
	start = GetTickCount();
	shell(A1, size);
	end = GetTickCount();
	sprintf(buf, "Размер массива: %d\r\nЗатрачено времени на сортировку Шелла на массиве произвольных величин: %d ms.\r\n", size, end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	shell(B1, size);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на сортировку Шелла на возрастающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	shell(C1, size);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на сортировку Шелла на убывающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");

/*-------qs-------*/
	start = GetTickCount();
	qs(A2, 0, size - 1);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на быструю сортировку на массиве произвольных величин: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	qs(B2, 0, size - 1);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на быструю сортировку на возрастающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	qs(C2, 0, size - 1);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на быструю сортировку на убывающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");

/*-------qsort-------*/
	start = GetTickCount();
	qsort(A3, size, sizeof(int), compare);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на функцию qsort на массиве произвольных величин: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	qsort(B3, size, sizeof(int), compare);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на функцию qsort на возрастающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);
	ol.Offset += num;
	strcpy(buf, "");
	start = GetTickCount();
	qsort(C3, size, sizeof(int), compare);
	end = GetTickCount();
	sprintf(buf, "Затрачено времени на функцию qsort на убывающей последовательности чисел: %d ms.\r\n", end - start);
	WriteFile(f, buf, strlen(buf), &num, &ol);

	return 0;
}

