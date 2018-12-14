#include <stdio.h>
#include <conio.h>
#include <math.h>

#define SINE 0
#define COSINE 1
#define EXPONENT 2
#define SQROOT 3
#define LOGN 4


double derivative (short numFunc, unsigned int step)
{
	switch (numFunc)
	{
		case SINE:
			return (step % 2) * (-1) * (step % 4 - 2);
		case COSINE: 
			return (((step % 2) + 1) % 2) * (-1) * (step % 4 - 1);
		case EXPONENT:
			return 1;
		case SQROOT: 
		{
			double nom = 1, denom = 0.5;
			for (int i = 1; i <= step; i++)
			{
				if (i > 1)
					nom *= (-1) * (2 * i - 3);
				denom *= 8;
			}
			return nom / denom;
		}
		case LOGN:
		{
			if (step == 0)
				return 0;
			double fact = 1;
			for (int i = 2; i <= step; i++)
				fact *= (-1) * (i - 1);
			return fact;
		}
		default:
			return 0;
	}
}

double TaylorSeries (double x, short numFunc, unsigned int nSteps, double accuracy)
{
	double a, diff = 1, fact = 1, result = derivative(numFunc, 0);

	if (numFunc == SQROOT)
		a = 3;
	else
		a = 0;
	for (int i = 1; i <= nSteps; i++)
	{
		diff *= (x - a);
		fact *= i;
		result += derivative(numFunc, i) * diff / fact;
	}
	return result;
}

void main ()
{
	short numFunc, next;
	double x, accuracy;
	unsigned int nSteps;
	do 
	{
		printf("0 - sin(x)\n");
		printf("1 - cos(x)\n");
		printf("2 - exp(x)\n");
		printf("3 - sqrt(1+x) (NE RABOTAET)\n");
		printf("4 - ln(1+x) (mdaaaa...)\n");
		printf("\n");
		printf("Select the function: ");
		scanf_s("%hd", &numFunc);

		do
		{
			printf("Enter x: ");
			scanf_s("%lf", &x);
			printf("Enter the number of steps and the accuracy: ");
			scanf_s("%d %lf", &nSteps, &accuracy);

			printf("\nResult: %lf\n", TaylorSeries(x, numFunc, nSteps, accuracy));
			printf("What's next?\n");
			printf("1 - Calculate for another x \n2 - Select another function \n0 - Exit\n");
			scanf_s("%hd", &next);
		} while (next == 1);

	} while (next == 2);
	printf("Zzz...");
	_getch();
}