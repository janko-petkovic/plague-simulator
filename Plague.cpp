#include "Plague.h"
#include "utils.cpp"
#include <iostream>


using std::cout;
using std::vector;


PlagueModel::PlagueModel(int dOI, statusChange death, statusChange recov,
						float R0) : _dOI(dOI), _R0(R0) {
	_deathCumDistr = CumDistrFunc(dOI, death.peak, death.cumProb,
									death.distrType);
	vector<float> vec{0.5,0.5};
	_recovCumDistr = vec;//CumDistrFunc(dOI, recov.peak, recov.cumProb,
						//			recov.distrType);
}		

vector<float> PlagueModel::RecovCumDistr() const { return _recovCumDistr; }
vector<float> PlagueModel::DeathCumDistr() const { return _deathCumDistr; }



vector<vector<double>> PlagueModel::Flow(uint endTime, uint N0) const {
	//vettore della popolazione infetta al tempo t
	arma::dcolvec Nvec(_dOI);
	Nvec(0) = N0;
	
	//matrici di propagazione morti e guariti
	arma::mat deadMat(BuildDistribMatCheat(_deathCumDistr));
	arma::mat recovMat(BuildDistribMatCheat(_recovCumDistr));

	
	//matrice di propagazione infetti
	arma::mat infectMat(_dOI, _dOI, arma::fill::zeros);
	infectMat(0,0) = 1+_R0;
	infectMat(1,0,arma::size(_dOI-1,_dOI-1)).eye(); 

	
	// componenti della payload finale
	vector<double> infected(endTime);
	vector<double> cumInfected(endTime);
	vector<double> dead(endTime);
	vector<double> recovered(endTime);

	//CALCOLO DELL'ANDAMENTO È QUI QUESTA COSA E IL CORE
	cumInfected[0] = (double)N0;
	infected[0] = (double)(N0);
	recovered[0] = 0.;
	dead[0] = 0.;

	
	arma::dcolvec temp(_dOI);
	arma::dcolvec prev(_dOI);
	
	for (uint i=1; i<=endTime; i++) {
		// sneak peak infetti in t+1
		prev = (infectMat-deadMat-recovMat)*Nvec;
		if (prev(0)<0) break;

		// calcolo periodo t+1
		temp = deadMat*Nvec;
		dead[i] = temp(0) + dead[i-1];
		
		temp = recovMat*Nvec;
		recovered[i] = temp(0) + recovered[i-1];
		
		cumInfected[i] = cumInfected[i-1]+Nvec(0)*_R0;
		Nvec = prev;
		infected[i] = Nvec(0);
	}
	
	// calcolo delle uscite senza nuove infezioni

	
	//costruzione della payload finale e return
	vector<vector<double>> PAYLOAD(4);
	PAYLOAD[0] = cumInfected;
	PAYLOAD[1] = infected;
	PAYLOAD[2] = recovered;
	PAYLOAD[3] = dead;

	
	return PAYLOAD;
}
