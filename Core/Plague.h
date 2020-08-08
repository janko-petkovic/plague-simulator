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
	int _dOI;
	double _beta;
	vector<double> _deathCumDistr;
	vector<double> _recovCumDistr;
	
public:
	PlagueModel(int, statusChange, statusChange, double);
	
	vector<double> RecovCumDistr() const;
	vector<double> DeathCumDistr() const;

	vector<vector<double>> DetPredict(int,int) const;
	vector<vector<long int>> StocPredict(int,int) const;
};

#endif	
	
	
