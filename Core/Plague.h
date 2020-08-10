#ifndef PLAGUE_H
#define PLAGUE_H

#include <armadillo>
#include <string>


using std::vector;


// remember: Gaussian = 1, Uniform = 2
struct statusChange {
	int peak;
	double finalProb;
	std::string distrType;
};


class PlagueModel {
private:
	int _dOI;						// total days of possible illness
	double _beta;					// daily reproduction rate
	vector<double> _deathCumFunc;   // death probability cumulative func
	vector<double> _recovCumFunc;	// recovery probability cumulative func
	
public:
	// Constructors
	PlagueModel();
	PlagueModel(const int, const statusChange, const statusChange, const double);
	
	// Getters
	int DOI() const;
	double Beta() const;
	vector<double> RecovCumFunc() const;
	vector<double> DeathCumFunc() const;
	
	// Setters
	void SetDOI(const int);
	void SetBeta(const double);
	void SetRecovCumFunc(const vector<double>);
	void SetDeathCumFunc(const vector<double>);

	// Predictions: deterministic model
	vector<vector<double>> DetPredict(const int,const vector<double>) const;
	vector<vector<double>> DetPredict(const int,const int) const;
	// Predictions: stochastic model
	vector<vector<long int>> StocPredict(const int,const vector<long int>) const;
	vector<vector<long int>> StocPredict(const int,const int) const;
};

#endif	
	
	
