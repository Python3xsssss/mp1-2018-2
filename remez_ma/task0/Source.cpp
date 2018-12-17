#include <stdio.h>
#include <math.h>
#include <locale.h>

void main()
{
	setlocale(LC_ALL,"Rus");
	float R1, R2, x1, y1, x2, y2;
	float S; // расстояние между центрами окружностей
	float tmp;

	x1 = 5.0;
	y1 = 7.0;
	x2 = 5.0;
	y2 = 2.0;

	R1 = 2.0;
	R2 = 2.0;

	S = sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));

	if (S == 0)
	{	
		if(R1 == R2)
			printf("Окружности совпадают");
		if(R1 > R2)
			printf("Вторая окружность внутри первой");
		if(R2 > R1)
			printf("Первая окружность внутри второй");
	}
	else
	{
		if (S > R1 + R2)
			printf("Окружности не пересекаются");
		if (S == R1 + R2)
			printf("Окружности касаются");
		if(S < R1 + R2)
			printf("Окружности пересекаются");
	}

	scanf_s("%f", &tmp);
}