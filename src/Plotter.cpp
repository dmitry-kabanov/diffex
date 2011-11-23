#include "Plotter.h"
#include <iostream>
#include "ConfigReader.h"
#include "FTCSSchemeSolver.h"
using namespace std;

Plotter::Plotter(const string &outputFileName, const ConfigReader *configReader)
	: outputFileName(outputFileName),
	  configReader(configReader),
	  outputFile(outputFileName),
	  delimiter("; ")
{

}

void Plotter::printHeader()
{
	if (configReader->getMethodNumber() == 1)
	{
		outputFile << "FTCS Scheme" << endl;
	}
}

void Plotter::printParameters(const FTCSSchemeSolver &solver)
{
	outputFile << "JMAX" << delimiter << configReader->getSpatialCoordinatPointsQuantity() << endl;
	outputFile << "MAXEX" << delimiter << configReader->getExactSolutionMembersQuantity() << endl;
	outputFile << "NMAX" << delimiter << configReader->getTimeStepsQuantity() << endl;
	outputFile << "TMAX" << delimiter << configReader->getMaxTime() << endl;
	outputFile << "TST" << delimiter << configReader->getInitialTime() << endl;
	outputFile << "GAM" << delimiter << configReader->getGammaValue() << endl;
	outputFile << "S" << delimiter << configReader->getSParameterValue() << endl;
	outputFile << "ALPH" << delimiter << configReader->getDiffusionCoefficient() << endl;
	outputFile << "DELT" << delimiter << solver.getTimeStep() << endl;
	outputFile << "DELX" << delimiter << solver.getSpatialStep() << endl;
}

void Plotter::printData(const FTCSSchemeSolver &solver)
{
	outputFile << solver.getCurrentTime() << delimiter;
	const double *solution = solver.getSolution();

	for (int i = 0; i < configReader->getSpatialCoordinatPointsQuantity(); i++)
	{
		outputFile << solution[i] << delimiter;
	}

	outputFile << endl;

	outputFile << solver.getCurrentTime() << delimiter;
	const double *exactSolution = solver.getExactSolution();

	for (int i = 0; i < configReader->getSpatialCoordinatPointsQuantity(); i++)
	{
		outputFile << exactSolution[i] << delimiter;
	}

	outputFile << endl;
}

void Plotter::printRmsError(const FTCSSchemeSolver &solver)
{
	outputFile << "RMS Error" << delimiter << solver.getRmsError() << endl;
}
