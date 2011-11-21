#ifndef FTCSSchemeSolver_h__
#define FTCSSchemeSolver_h__

class ConfigReader;
class Plotter;

class FTCSSchemeSolver
{
public:
	FTCSSchemeSolver(const ConfigReader *configReader);
	~FTCSSchemeSolver();
	void obtainInitialConditionsFromExactSolution();
	void calculateBoundaryConditions();
	void run();
	double getRmsError() const { return rmsError; }
	double getCurrentTime() const { return time; }
	double *getSolution() const { return temperatureDimension; }

private:
	void advance();
	void obtainRmsError();

	const ConfigReader *configReader;
	double *temperaturePreviousLayer;
	double *temperatureCurrentLayer;
	double *temperatureExactSolution;
	double *temperatureDimension;
	double deltaX;
	double deltaT;
	double time;
	double rmsError;
	Plotter *plotter;
};

#endif // FTCSSchemeSolver_h__