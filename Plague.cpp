#include "Plague.h"
#include "utils.cpp"
#include <iostream>

using std::vector;

PlagueModel::PlagueModel(int dOI, statusChange death, statusChange recov,
						float r0) : _dOI(dOI), _r0(r0) {
	_deathCumDistr = CumDistrFunc(dOI, death.peak, death.cumProb,
									death.distrType);
	_recovCumDistr = CumDistrFunc(dOI, recov.peak, recov.cumProb,
									recov.distrType);
}		

vector<float> PlagueModel::RecovCumDistr() const { return _recovCumDistr; }
vector<float> PlagueModel::DeathCumDistr() const { return _deathCumDistr; }



vector<vector<double>> PlagueModel::Flow(uint endTime, uint N0) const {
	//vettore della popolazione infetta al tempo t
	arma::dcolvec Nvec(_dOI+1);
	Nvec(0) = N0;
	Nvec(1) = double(N0)/_r0;
	
	std::cout<<Nvec<<std::endl;
	
	//matrici di propagazione morti e guariti
	arma::mat deadMat(BuildDistribMatCheat(_deathCumDistr));
	arma::mat recovMat(BuildDistribMatCheat(_recovCumDistr));

	std::cout<<recovMat << std::endl;
	
	//matrice di propagazione infetti
	arma::mat infectMat(_dOI+1, _dOI+1, arma::fill::zeros);
	infectMat(0,0) += 1+_r0;
	infectMat(1,0,arma::size(_dOI, _dOI)) = arma::eye(_dOI,_dOI);
	
	std::cout<<infectMat<<std::endl;
	
	// componenti della payload finale
	vector<double> infected(endTime);
	vector<double> cumInfected(endTime);
	vector<double> dead(endTime);
	vector<double> recovered(endTime);
	
	
	//CALCOLO DELL'ANDAMENTO È QUI QUESTA COSA E IL CORE
	cumInfected[0] = (double)N0;
	dead[0] = 0.;
	recovered[0] = 0.;
	infected[0] = (double)N0;
	
	arma::dcolvec deadIncr(_dOI+1);
	arma::dcolvec recovIncr(_dOI+1);
	arma::dcolvec infectIncr(_dOI+1);
	

	for (uint i=1; i<=endTime; i++) {
		
		cumInfected[i] = cumInfected[i-1] + Nvec(0)*_r0;
		
		deadIncr = deadMat*Nvec*_r0;
		dead[i] = dead[i-1] + deadIncr(0);
		
		recovIncr = recovMat*Nvec*_r0;
		recovered[i] = recovered[i-1]+recovIncr(0);
		
		infectIncr = infectMat*Nvec;
		Nvec = infectIncr - recovIncr - deadIncr;
		infected[i] = Nvec(0);
	}
	//costruzione della payload finale e return
	vector<vector<double>> PAYLOAD(4);
	PAYLOAD[0] = cumInfected;
	PAYLOAD[1] = infected;
	PAYLOAD[2] = dead;
	PAYLOAD[3] = recovered;
	
	return PAYLOAD;
}
