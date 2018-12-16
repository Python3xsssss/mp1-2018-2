#include <stdio.h>
#include <conio.h>
#include <math.h>

#define SINE 0
#define COSINE 1
#define EXPONENT 2
#define SQROOT 3
#define LOGN 4

#define INFINITY 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0

double((*Func[5]))(double x) = { sin, cos, exp, sqrt, log };

bool myinf(double x)
{
	return fabs(x) >= INFINITY;
}

double derivative (short numFunc, int step)
{
	switch (numFunc)
	{
		case SINE:
			return (step % 2) * (-1) * (step % 4 - 2);
		case COSINE: 
			return (((step % 2) + 1) % 2) * (-1) * (step % 4 - 1);
		case EXPONENT:
		{
			return 1;
		}
		case SQROOT: 
		{
			double nom = 1, denom = 1;
			for (int i = 1; i <= step; i++)
			{
				if (i > 1)
					nom *= (-1) * (2 * i - 3);
				denom *= 2;
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

double TaylorSeries (double x, short numFunc, int * nSteps, double accuracy, double goal)
{
	double a = 0, diff = 1, fact = 1, result = derivative(numFunc, 0);
	int i;

	for (i = 1; i <= *nSteps; i++)
	{
		diff *= (x - a);
		fact *= i;
		if (myinf(fact))
			break;
		result += derivative(numFunc, i) * diff / fact;
		if ((accuracy != -1) && (fabs(goal - result) <= accuracy))
			break;
	}
	*nSteps = i - 1;
	return result;
}

void firstMode (short numFunc)
{
	double x, accuracy, arg;
	int nSteps;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	printf("Enter the number of steps (from 1 to 1000) and the accuracy (>= 0.000001): ");
	scanf_s("%d %lf", &nSteps, &accuracy);

	if ((numFunc == 3) || (numFunc == 4))
		arg = x + 1;
	else
		arg = x;
	double goal = Func[numFunc](arg);
	printf("\nGoal: %.6lf\n", goal);

	double result = TaylorSeries(x, numFunc, &nSteps, accuracy, goal);
	printf("Result: %.6lf\n", result);
	printf("Difference: %.6lf\n", fabs(goal - result));
	printf("Number of steps: %d\n", nSteps);
}

void secondMode (short numFunc)
{
	double x, arg;
	int nSteps;

	printf("Enter x: ");
	scanf_s("%lf", &x);
	printf("Enter the number of steps (from 1 to 25): ");
	scanf_s("%d", &nSteps);
	if ((numFunc == 3) || (numFunc == 4))
		arg = x + 1;
	else
		arg = x;
	double goal = Func[numFunc](arg);
	printf("\nGoal: %.6lf\n", goal);
	printf("STEP   RESULT %15c  DIFFERENCE\n", ' ');
	printf("----   ------ %15c  ----------\n", ' ');
	for (int i = 1; i <= nSteps; i++)
	{
		int step = i;
		double result = TaylorSeries(x, numFunc, &step, 0, -1);
		double diff = fabs(goal - result);
		printf("%-4d   %-21.6lf   %-21.6lf\n", i, result, diff);
	}
}

short mainMenu()
{
	short mode;
	printf("\nModes:\n");
	printf("1 - Single calculation\n");
	printf("2 - Serial experiment\n");
	printf("0 - Exit the program\n");
	printf("\nSelect the mode: ");
	scanf_s("%hd", &mode);
	return mode;
}

short funcMenu()
{
	short numFunc;
	printf("\nList of available functions:\n");
	printf("1 - sin(x)\n");
	printf("2 - cos(x)\n");
	printf("3 - exp(x)\n");
	printf("4 - sqrt(1+x), x in [-1; 1]\n");
	printf("5 - ln(1+x), x in (-1; 1]\n");
	printf("0 - Exit to main menu\n");
	printf("\n");
	printf("Select the function: ");
	scanf_s("%hd", &numFunc);
	return numFunc - 1;
}

short endOfMode()
{
	short next;
	printf("\nWhat's next?\n");
	printf("1 - Calculate for another x \n2 - Select another function \n0 - Exit to main menu\n");
	scanf_s("%hd", &next);
	printf("\n");
	return next;
}

void main ()
{
	short mode, numFunc, next;

	printf("Welcome to the Taylor Function Calculator!\n");
	do 
	{
		mode = mainMenu();
		if (mode == 0)
			printf("Zzz...");
		else if ((mode < 0) || (mode > 2))
			printf("Incorrect mode!\n");
		else
			do
			{
				numFunc = funcMenu();
				next = 1;
				if ((numFunc < -1) || (numFunc > 4))
				{
					printf("This function does not exist!\n");
					next = 2;
				}
				else
					while ((next == 1) && (numFunc != -1))
					{
						if (mode == 1)
							firstMode(numFunc);
						else
							secondMode(numFunc);
						next = endOfMode();
					}
			} while ((next == 2) && (numFunc != -1));
	} while (mode != 0);
	_getch();
}
