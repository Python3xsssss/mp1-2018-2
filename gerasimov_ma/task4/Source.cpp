#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#pragma warning(disable:4996)

typedef struct
{
	int code[4];
	char name[100];
	int price;
	int discount;
	int quantity = 0;
	int sum = 0, nondisc_sum = 0;
} PRODUCT;

PRODUCT sklad[30];

int main()
{
	int i, j, length, check;
	int average = 0, nondisc_average = 0;
	int code_in[4];
	bool flag;


	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	FILE * ptrfile_in = fopen("input.txt", "r");
	i = 0;
	flag = true;
	do
	{
		fscanf(ptrfile_in, "%d", &sklad[i].code[0]);
		if (sklad[i].code[0] != -1)
		{
			for (j = 1; j < 4; j++)
				fscanf(ptrfile_in, "%d", &sklad[i].code[j]);
			fscanf(ptrfile_in, "%s", &sklad[i].name);
			fscanf(ptrfile_in, "%d %d", &sklad[i].price, &sklad[i].discount);
			i++;
		}
		else
			flag = false;
	} while ((flag) && (i < 30));
	fclose(ptrfile_in);

	length = i;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < 4; j++)
			printf("%d ", sklad[i].code[j]);
		printf("%s ", sklad[i].name);
		printf("%d %d", sklad[i].price, sklad[i].discount);
		printf("\n");
	}
	do
	{
		printf("Введите штрих-код: \n");
		for (i = 0; i < 4; i++)
			scanf("%d", &code_in[i]);
		for (i = 0; i < length; i++)
		{
			for (j = 0; j < 4; j++)
				if (code_in[j] != sklad[i].code[j])
					break;
			if (j == 4)
			{
				sklad[i].sum += sklad[i].price * (1 - sklad[i].discount * 0.01);
				sklad[i].nondisc_sum += sklad[i].price;
				sklad[i].quantity++;
				printf("%s\n", sklad[i].name);
				printf("Цена: %d\n", sklad[i].price);
				break;
			}
		}
		if (i == length)
			printf("На складе отсутствует данный товар!\n");
		printf("Хотите считать еще один товар? 1 - Да; 0 - Распечатать чек\n");
		scanf("%d", &check);
	} while (check == 1);
	for (i = 0; i < length; i++)
		if (sklad[i].quantity > 0)
		{
			printf("%s: %d шт. Стоимость: %d Скидка: %d\n", sklad[i].name, sklad[i].quantity, sklad[i].sum, sklad[i].discount);
			average += sklad[i].sum;
			nondisc_average += sklad[i].nondisc_sum;
		}
	printf("Сумма: %d\n", average);
	printf("Сумма без скидки: %d\n", nondisc_average);
	_getch();
}