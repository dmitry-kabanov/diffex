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

void Plotter::printParameters()
{
	outputFile << "JMAX = " 
		<< configReader->getSpatialCoordinatPointsQuantity() 
		<< ", MAXEX = " << configReader->getExactSolutionMembersQuantity()
		<< ", NMAX = " << configReader->getTimeStepsQuantity()
		<< ", TMAX = " << configReader->getMaxTime()
		<< ", TST = " << configReader->getInitialTime()
		<< ", GAM = " << configReader->getGammaValue()
		<< endl;
	outputFile << "S = "
		<< configReader->getSParameterValue()
		<< ", ALPH = " << configReader->getDiffusionCoefficient()
		<< ", DELT = " << " Fill me with values"
		<< ", DELX = " << " Fill me with values"
		<< endl;
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
}

void Plotter::printRmsError(const FTCSSchemeSolver &solver)
{
	outputFile << "RMS Error = " << solver.getRmsError() << endl;
}
