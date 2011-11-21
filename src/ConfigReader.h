#ifndef ConfigReader_h__
#define ConfigReader_h__

#include <string>

class ConfigReader
{
public:
	ConfigReader(std::string filename);
	void readConfig();

	int getMethodNumber() const { return ME; }
	int getFormat() const { return IPR; }
	int getSpatialCoordinatPointsQuantity() const { return JMAX; }
	int getExactSolutionMembersQuantity() const { return MAXEX; }
	int getTimeStepsQuantity() const { return NMAX; }
	double getDiffusionCoefficient() const { return ALPH; }
	double getSParameterValue() const { return S; }
	double getMaxTime() const { return TMAX; }
	double getInitialTime() const { return TST; }
	double getGammaValue() const { return GAM; }

private:
	std::string configFileName;
	int ME;
	int IPR;
	int JMAX;
	int MAXEX;
	int NMAX;
	double ALPH;
	double S;
	double TMAX;
	double TST;
	double GAM;
};

#endif // ConfigReader_h__