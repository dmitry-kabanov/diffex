#include <iostream>
#include <fstream>
#include "ConfigReader.h"
using namespace std;

ConfigReader::ConfigReader(string filename)
	: configFileName(filename)
{

}

void ConfigReader::readConfig()
{
	ifstream f(configFileName);

	if (!f)
	{
		cerr << "Unable to open config file '" << configFileName << "'." << endl;
		exit(EXIT_FAILURE);
	}

	f >> ME >> IPR >> JMAX >> MAXEX >> NMAX >> ALPH >> S >> TMAX >> TST >> GAM;
}