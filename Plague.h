#ifndef PLAGUE_H
#define PLAGUE_H

#include <armadillo>
#include <string>


struct statusChange {
	int peak;
	float totProb;
	std::string distrType; // Gaussian or Uniform e.g.
};


class PlagueModel {
private:
	float _r0;
	std::vector<float> _deathCumDistr;
	std::vector<float> _recovCumDistr;
	
	public:
	PlagueModel(int, statusChange, statusChange, float);
	
	long int Flow(int t) const;
	std::vector<float> RecovCumDistr() const;
};

#endif	
	
	
