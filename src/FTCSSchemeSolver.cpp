#include <string>
#include "FTCSSchemeSolver.h"
#include "ConfigReader.h"
#include "Plotter.h"
#include "ExactSolutionCalculator.h"
using namespace std;

FTCSSchemeSolver::FTCSSchemeSolver(const ConfigReader *configReader)
	: configReader(configReader)
{
	deltaX = 1.0 / (configReader->getSpatialCoordinatPointsQuantity() - 1.0);
	deltaT = deltaX * deltaX * configReader->getSParameterValue() /
		configReader->getDiffusionCoefficient();

	string outputFileName("difex.out");
	plotter = new Plotter(outputFileName, configReader);
	plotter->printHeader();
	plotter->printParameters(*this);

	int maxSpatialStep = configReader->getSpatialCoordinatPointsQuantity();
	temperatureCurrentLayer = new double[maxSpatialStep];
	temperatureDimension = new double[maxSpatialStep];
	temperatureExactSolution = new double[maxSpatialStep];
	temperaturePreviousLayer = new double[maxSpatialStep];
}

FTCSSchemeSolver::~FTCSSchemeSolver()
{
	delete plotter;
	delete [] temperatureCurrentLayer;
	delete [] temperatureDimension;
	delete [] temperatureExactSolution;
	delete [] temperaturePreviousLayer;
}

void FTCSSchemeSolver::obtainInitialConditionsFromExactSolution()
{
	time = configReader->getInitialTime() - 2 * deltaT;

	for (int i = 0; i < 2; i++)
	{
		time += deltaT;

		ExactSolutionCalculator *calculator = new ExactSolutionCalculator(
			configReader->getSpatialCoordinatPointsQuantity(),
			configReader->getExactSolutionMembersQuantity(),
			deltaX,
			configReader->getDiffusionCoefficient(),
			time
		);
		calculator->calculate(temperatureExactSolution);

		for (int j = 1; j < configReader->getSpatialCoordinatPointsQuantity() - 1; j++)
		{
			if (i == 0)
			{
				temperaturePreviousLayer[j] = temperatureExactSolution[j] / 100.0;
			}

			if (i == 1)
			{
				temperatureCurrentLayer[j] = temperatureExactSolution[j] / 100.0;
			}
		}

	}
}

void FTCSSchemeSolver::calculateBoundaryConditions()
{
	int maxSpatialPointNumber = configReader->getSpatialCoordinatPointsQuantity() - 1;
	temperaturePreviousLayer[0] = 1.0;
	temperaturePreviousLayer[maxSpatialPointNumber] = 1.0;
	temperatureCurrentLayer[0] = 1.0;
	temperatureCurrentLayer[maxSpatialPointNumber] = 1.0;

	temperatureDimension[0] = 100.0 * temperatureCurrentLayer[0];
	temperatureDimension[maxSpatialPointNumber] = 
		100.0 * temperatureCurrentLayer[maxSpatialPointNumber];
}

void FTCSSchemeSolver::run()
{
	obtainInitialConditionsFromExactSolution();
	calculateBoundaryConditions();

	for (int i = 0; i < configReader->getTimeStepsQuantity(); i++)
	{
		advance();
		plotter->printData(*this);

		if (time > configReader->getMaxTime())
		{
			break;
		}

		time += deltaT;
	}

	obtainRmsError();
	plotter->printRmsError(*this);
}

void FTCSSchemeSolver::advance()
{
	double s = configReader->getSParameterValue();

	for (int j = 1; j < configReader->getSpatialCoordinatPointsQuantity() - 1; j++)
	{
		temperatureCurrentLayer[j] = (1.0 - 2.0 * s) * temperaturePreviousLayer[j] +
			s * (temperaturePreviousLayer[j-1] + temperaturePreviousLayer[j+1]);
	}

	for (int j = 1; j < configReader->getSpatialCoordinatPointsQuantity() - 1; j++)
	{
		temperaturePreviousLayer[j] = temperatureCurrentLayer[j];
	}

	for (int j = 1; j < configReader->getSpatialCoordinatPointsQuantity() - 1; j++)
	{
		temperatureDimension[j] = 100.0 * temperatureCurrentLayer[j];
	}

	ExactSolutionCalculator *calculator = new ExactSolutionCalculator(
		configReader->getSpatialCoordinatPointsQuantity(),
		configReader->getExactSolutionMembersQuantity(),
		deltaX,
		configReader->getDiffusionCoefficient(),
		time
		);
	calculator->calculate(temperatureExactSolution);

	delete calculator;
}

void FTCSSchemeSolver::obtainRmsError()
{
	double sum = 0.0;

	ExactSolutionCalculator *calculator = new ExactSolutionCalculator(
		configReader->getSpatialCoordinatPointsQuantity(),
		configReader->getExactSolutionMembersQuantity(),
		deltaX,
		configReader->getDiffusionCoefficient(),
		time
	);
	calculator->calculate(temperatureExactSolution);

	for (int j = 0; j < configReader->getSpatialCoordinatPointsQuantity(); j++)
	{
		double dmp = temperatureExactSolution[j] - temperatureDimension[j];
		sum += dmp * dmp;
	}

	double avs = sum / (configReader->getSpatialCoordinatPointsQuantity());
	rmsError = sqrt(avs);
}