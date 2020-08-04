#ifndef PLAGUE_H
#define PLAGUE_H

#include <armadillo>
#include <string>

using std::vector;


struct statusChange {
	int peak;
	float finalProb;
	std::string distrType; // Gaussian or Uniform e.g.
};


class PlagueModel {
private:
	int _dOI;
	float _beta;
	vector<float> _deathCumDistr;
	vector<float> _recovCumDistr;
	
public:
	PlagueModel(int, statusChange, statusChange, float);
	
	vector<float> RecovCumDistr() const;
	vector<float> DeathCumDistr() const;

	vector<vector<double>> Flow(uint,uint) const;
	vector<vector<long int>> Simulate(int) const;
};

#endif	
	
	
