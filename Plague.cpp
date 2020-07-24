#include "Plague.h"
#include "utils.cpp"

using std::vector;
using vector::push_back();

PlagueModel::PlagueModel(int dOI, statusChange death, statusChange recov,
						float r0) : _dOI(dOI), _r0(r0) {
	_deathCumDistr = CumDistrFunc(dOI, death.peak, death.totProb,
									death.distrType);
	_recovCumDistr = CumDistrFunc(dOI, recov.peak, recov.totProb,
									recov.distrType);
}		

vector<float> PlagueModel::RecovCumDistr() const { return _recovCumDistr; }
vector<float> PlagueModel::DeathCumDistr() const { return _deathCumDistr; }


vector<vector<double>> PlagueModel::Flow(uint endTime, uint N0) const {
	vector<vector<double>> a;
	return a;

}
