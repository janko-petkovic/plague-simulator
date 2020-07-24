#include "Plague.h"
#include "utils.cpp"


PlagueModel::PlagueModel(int dOI, statusChange death, statusChange recov,
						float r0) : _r0(r0) {
	_deathCumDistr = CumDistrFunc(dOI, death.peak, death.totProb,
									death.distrType);
	_recovCumDistr = CumDistrFunc(dOI, recov.peak, recov.totProb,
									recov.distrType);
}		

std::vector<float> PlagueModel::RecovCumDistr() const { return _recovCumDistr; }
