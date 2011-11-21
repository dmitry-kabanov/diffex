#ifndef Plotter_h__
#define Plotter_h__

#include <fstream>
#include <string>

class ConfigReader;
class FTCSSchemeSolver;

class Plotter
{
public:
	Plotter(const std::string &outputFileName, const ConfigReader *configReader);
	void printHeader();
	void printParameters(const FTCSSchemeSolver &solver);
	void printData(const FTCSSchemeSolver &solver);
	void printRmsError(const FTCSSchemeSolver &solver);

private:
	std::string outputFileName;
	const ConfigReader *configReader;
	std::ofstream outputFile;
	std::string delimiter;
};

#endif // Plotter_h__