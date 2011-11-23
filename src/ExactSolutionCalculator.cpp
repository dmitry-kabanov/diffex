#include "ExactSolutionCalculator.h"
#include <cmath>

ExactSolutionCalculator::ExactSolutionCalculator(int JMAX, int MAXEX, double deltaX, double alpha, double time)
	: JMAX(JMAX),
	  MAXEX(MAXEX),
	  deltaX(deltaX),
	  alpha(alpha),
	  time(time)
{
	x = new double[JMAX];
}

ExactSolutionCalculator::~ExactSolutionCalculator()
{
	delete[] x;
}


void ExactSolutionCalculator::calculate(double *temperatureExactSolution)
{
	double numericalCoefficient;
	double sinusArgument;
	double exponentArgument;

	for (int j = 0; j < JMAX; j++)
	{
		x[j] = deltaX * j;
		temperatureExactSolution[j] = 100.0;

		for (int k = 1; k <= MAXEX; k++)
		{
			numericalCoefficient = (2.0 * k - 1.0);
			// TODO: обязательно добавить сюда нормировку по XMAX = 1.0,
			// так как опущенные множители в формуле - это жесть.
			sinusArgument = numericalCoefficient * M_PI * x[j];
			exponentArgument = -alpha * numericalCoefficient * numericalCoefficient * M_PI * M_PI * time;

			// LIMIT THE ARGUMENT SIZE OF EXP(DTM)
			if (exponentArgument < -25.0)
			{
				exponentArgument = -25.0;
			}

			if (exp(exponentArgument) < 1.0e-10)
			{
				break;
			}

            temperatureExactSolution[j] -= 400.0 / numericalCoefficient / M_PI * sin(sinusArgument) * exp(exponentArgument);
		}
	}
}