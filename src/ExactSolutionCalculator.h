#ifndef ExactSolutionCalculator_h__
#define ExactSolutionCalculator_h__

class ExactSolutionCalculator
{
public:
	ExactSolutionCalculator(int JMAX, int MAXEX, double deltaX, double alpha, double time);
	~ExactSolutionCalculator();
	void calculate(double *temperatureExactSolution);

private:
	int JMAX;
	int MAXEX;
	double deltaX;
	double alpha;
	double time;
	double *x;
};

#endif // ExactSolutionCalculator_h__