#include <iostream>
#include "ConfigReader.h"
#include "FTCSSchemeSolver.h"
using namespace std;

int main()
{
	string configFileName("difex.dat");
	ConfigReader *configReader = new ConfigReader(configFileName);
	configReader->readConfig();

	FTCSSchemeSolver *solver = new FTCSSchemeSolver(configReader);
	solver->run();

	return EXIT_SUCCESS;
}