#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <locale.h>
#include <string.h>


#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


typedef struct
{
	char name[260];
	char date[30];
	long size;
} ELEMENT;

ELEMENT file[1000];

void KapitanovBubbleSort(ELEMENT * mas, int down, int up, int mode)
{
	bool flag = true;

	for (int i = down; flag; i++)
	{
		flag = false;
		for (int j = down; j < up - i; j++)
			if ((mas[j].size < mas[j + 1].size) && (mode == -1) || (mas[j].size > mas[j + 1].size) && (mode == 1))
			{
				ELEMENT tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = tmp;
				flag = true;
			}
	}
}


void SelectionSort(ELEMENT * mas, int down, int up, int mode)
{
	for (int i = down; i < up; i++)
	{
		int maxim = mas[i].size;
		int num = i;
		for (int j = i + 1; j < up + 1; j++)
			if ((mas[j].size > maxim) && (mode == -1) || (mas[j].size < maxim) && (mode == 1))
			{
				maxim = mas[j].size;
				num = j;
			}
		ELEMENT tmp = mas[num];
		mas[num] = mas[i];
		mas[i] = tmp;
	}
}


int BinarySearch(ELEMENT * mas, int down, int up, int mode, int insert)
{
	while (down < up)
	{
		int mid = int(up + (down - up) / 2.0);
		if ((mas[mid].size < insert) && (mode == -1) || (mas[mid].size > insert) && (mode == 1))
			up = mid;
		else if ((mas[mid].size > insert) && (mode == -1) || (mas[mid].size < insert) && (mode == 1))
			down = mid + 1;
		else
		{
			up = mid;
			down = mid;
		}
	}
	return up;
}

void InsertionSort(ELEMENT * mas, int down, int up, int mode)
{
	for (int i = down + 1; i < up + 1; i++)
	{
		if ((mas[i].size > mas[i - 1].size) && (mode == -1) || (mas[i].size < mas[i - 1].size) && (mode == 1))
		{
			int num;
			if ((mas[i].size < mas[0].size) && (mode == -1) || (mas[i].size > mas[0].size) && (mode == 1))
				num = BinarySearch(mas, down, i - 1, mode, mas[i].size);
			else
				num = down;
			ELEMENT tmp = mas[i];
			for (int j = i; j > num; j--)
				mas[j] = mas[j - 1];
			mas[num] = tmp;
		}
	}
}


void Merge(ELEMENT * mas, int down, int mid, int up, int mode)
{
	ELEMENT * tmp = new ELEMENT[up - down + 1];
	int i = down, j = mid + 1;

	while ((i < mid + 1) && (j < up + 1))
		if ((mas[i].size < mas[j].size) && (mode == -1) || (mas[i].size > mas[j].size) && (mode == 1))
		{
			tmp[i + j - down - mid - 1] = mas[j];
			j++;
		}
		else
		{
			tmp[i + j - down - mid - 1] = mas[i];
			i++;
		}
	if (i == mid + 1)
		for (; j < up + 1; j++)
			tmp[i + j - down - mid - 1] = mas[j];
	else
		for (; i < mid + 1; i++)
			tmp[i + j - down - mid - 1] = mas[i];
	for (i = down; i < up + 1; i++)
		mas[i] = tmp[i - down];
}

void MergeSort(ELEMENT * mas, int down, int up, int mode)
{
	if (down < up)
	{
		int mid = int(up + (down - up) / 2.0);
		MergeSort(mas, down, mid, mode);
		MergeSort(mas, mid + 1, up, mode);
		Merge(mas, down, mid, up, mode);
	}
}


void QuickSort(ELEMENT * mas, int down, int up, int mode)
{
	int i = down, j = up, fixik = mas[int(up + (down - up) / 2.0)].size;

	while (i <= j)
	{
		while ((mas[j].size < fixik) && (mode == -1) || (mas[j].size > fixik) && (mode == 1))
			j--;
		while ((mas[i].size > fixik) && (mode == -1) || (mas[i].size < fixik) && (mode == 1))
			i++;
		if (i <= j)
		{
			ELEMENT tmp = mas[i];
			mas[i] = mas[j];
			mas[j] = tmp;
			i++;
			j--;
		}
	}
	if (down < j)
		QuickSort(mas, down, j, mode);
	if (up > i)
		QuickSort(mas, i, up, mode);
}


int IncCount(int * inc, int len)
{
	int i = -1, shift, shift_chet, shift_nechet;

	shift = shift_chet = shift_nechet = 1;
	do
	{
		i++;
		if (i % 2 == 0)
		{
			inc[i] = 9 * shift - 9 * shift_chet + 1;
			shift_chet *= 2;
			shift_nechet *= 2;
		}
		else
			inc[i] = 8 * shift - 6 * shift_nechet + 1;
		shift *= 2;
	} while (inc[i] * 3 < len);
	if (i == 0)
		return 0;
	else
		return i - 1;
}

void ShellSort(ELEMENT * mas, int down, int up, int mode)
{
	int * inc = new int[int(log2(up + 1))];
	int index = IncCount(inc, up + 1);

	for (int i = index; i >= 0; i--)
		for (int j = inc[i]; j < up + 1; j++)
		{
			int k;
			ELEMENT tmp = mas[j];
			for (k = j - inc[i]; (k >= down) && ((mas[k].size < tmp.size) && (mode == -1) || (mas[k].size > tmp.size) && (mode == 1)); k -= inc[i])
				mas[k + inc[i]] = mas[k];
			mas[k + inc[i]] = tmp;
		}
}


void CombSort(ELEMENT * mas, int down, int up, int mode)
{
	const float factor = 1.247;

	for (int i = int((up + 1) / factor); i >= 1; i = int(i / factor))
	{
		for (int j = down; j < up + 1 - i; j++)
			if ((mas[j].size < mas[j + i].size) && (mode == -1) || (mas[j].size > mas[j + i].size) && (mode == 1))
			{
				ELEMENT tmp = mas[j];
				mas[j] = mas[j + i];
				mas[j + i] = tmp;
			}
	}
	KapitanovBubbleSort(mas, down, up, mode);
}


void main()
{
	setlocale(LC_ALL, "Rus");
	struct _finddata_t c_file;
	intptr_t hFile;
	char path[200];
	int count = -1;

	printf("Enter the path to the directory:\n");
	gets_s(path);
	strcat(path, "\\*.*");
	if ((hFile = _findfirst(path, &c_file)) == -1L)
		printf("No files in current directory!\n");
	else
	{
		printf("\nFILE         DATE %24c   SIZE\n", ' ');
		printf("----         ---- %24c   ----\n", ' ');
		do {
			char buffer[30];
			count++;
			ctime_s(buffer, _countof(buffer), &c_file.time_write);
			printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
			strcpy(file[count].name, c_file.name);
			strcpy(file[count].date, buffer);
			file[count].size = c_file.size;
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}

	void((*Sort[7]))(ELEMENT * mas, int down, int up, int mode);
	Sort[0] = KapitanovBubbleSort;
	Sort[1] = SelectionSort;
	Sort[2] = InsertionSort;
	Sort[3] = MergeSort;
	Sort[4] = QuickSort;
	Sort[5] = ShellSort;
	Sort[6] = CombSort;

	short next_sort;
	do
	{
		printf("\nSelect the sort:\n");
		printf("0 - Bubble Sort\n");
		printf("1 - Selection Sort\n");
		printf("2 - Binary Insertion Sort\n");
		printf("3 - Merge Sort\n");
		printf("4 - Quick Sort\n");
		printf("5 - Shell Sort\n");
		printf("6 - Comb Sort\n");
		short num_sort, mode;
		scanf("%hd", &num_sort);
		printf("How to sort?\n");
		printf("1: in ascending order of size\n");
		printf("-1: in descending order of size\n");
		scanf("%hd", &mode);

		clock_t time = clock();
		Sort[num_sort](file, 0, count, mode);
		time = clock() - time;
		printf("\nFILE         DATE %24c   SIZE\n", ' ');
		printf("----         ---- %24c   ----\n", ' ');
		for (int i = 0; i <= count; i++)
			printf("%-12.12s %.24s  %10ld\n", file[i].name, file[i].date, file[i].size);
		printf("\nTime: %d ms\n", int((double)time * 1000 / CLOCKS_PER_SEC));
		printf("\nWant to sort files again?\n");
		printf("1 - Sort again; 0 - Quit\n");
		scanf("%hd", &next_sort);
	} while (next_sort == 1);


	printf("\nZzz...");
	_getch();
}
