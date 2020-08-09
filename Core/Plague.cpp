#include "Plague.h"
#include "utils.cpp"

#include <cassert>
#include <iostream>


using std::vector;
using std::clog;
using std::endl;


// struct print function
void printStatChangeParams(statusChange status) {
	clog << " parameters: " << endl;
	clog << " Peak: " << status.peak << endl;
	clog << " Final prob: " << status.finalProb << endl;
	clog << " Distribution: " << status.distrType << endl;	
}


// constructor: crea le due distribuzioni di guarigione e decesso
PlagueModel::PlagueModel(int dOI, statusChange death, statusChange recov,
						double beta) : _dOI(dOI), _beta(beta) {
	// input checks: may be unnecessary but in case we are not using a GUI
	assert(dOI>=2);
	assert(!PeakCheck(death.peak,dOI));
	assert(!PeakCheck(death.peak,dOI));

	
	// distribution computation
	_deathCumDistr = CumDistrFunc(dOI, death.peak, death.finalProb,
									death.distrType);
	_recovCumDistr = CumDistrFunc(dOI, recov.peak, recov.finalProb,
									recov.distrType);
									
	//~ // logging where we are: very useful for debubbing purpouses
	clog << "Plague model creation: successfull.\n";
	clog << "Days of illness: " << _dOI << endl;
	clog << "Death status change";
	printStatChangeParams(death);
	clog << "Recovery status change";
	printStatChangeParams(recov);									
}		

// getter per le distribuzioni (usate solo in debugging per ora)
vector<double> PlagueModel::RecovCumDistr() const { return _recovCumDistr; }
vector<double> PlagueModel::DeathCumDistr() const { return _deathCumDistr; }


// previsione deterministica
vector<vector<double>> PlagueModel::DetPredict(int endTime, vector<double> Nvector) const {
	
	int temp = Nvector.size();
	clog << "\nRUN PREDICTION\nType: deterministic\n";
	clog << " Checking N0 vector size...";
	assert(temp=(_dOI+1));
	clog << " done.\nDays of prediction: " << endTime << endl << endl;
	clog << "Begin computation...\n";
	
	//vettore della popolazione infetta al tempo t
	arma::dcolvec Nvec(Nvector);
	
	//matrici di propagazione morti e guariti
	arma::mat deadMat(BuildDistribMatCheat(_deathCumDistr));
	arma::mat recovMat(BuildDistribMatCheat(_recovCumDistr));

	
	//matrice di propagazione infetti
	arma::mat infectMat(_dOI+1, _dOI+1, arma::fill::zeros);
	infectMat(0,0) += 1+_beta;
	infectMat(1,0,arma::size(_dOI, _dOI)) = arma::eye(_dOI,_dOI);
	
	
	// componenti della payload finale
	vector<double> infected(endTime);
	vector<double> cumInfected(endTime);
	vector<double> dead(endTime);
	vector<double> recovered(endTime);
	
	
	//CALCOLO DELL'ANDAMENTO È QUI QUESTA COSA E IL CORE
	cumInfected[0] = Nvec(0);
	dead[0] = 0.;
	recovered[0] = 0.;
	infected[0] = Nvec(0);
	
	arma::dcolvec deadIncr(_dOI+1);
	arma::dcolvec recovIncr(_dOI+1);
	arma::dcolvec infectIncr(_dOI+1);
	

	for (int i=1; i<=endTime; i++) {
		
		cumInfected[i] = cumInfected[i-1] + Nvec(0)*_beta;
		
		deadIncr = deadMat*Nvec*_beta;
		dead[i] = dead[i-1] + deadIncr(0);
		
		recovIncr = recovMat*Nvec*_beta;
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
	
	clog << "Payload check: 2nd day" << endl;
	clog  << PAYLOAD[0][2] << " " << PAYLOAD[1][2] << " ";
	clog  << PAYLOAD[2][2] << " " << PAYLOAD[3][2] << endl;

	clog << "Successful. Returning the payload\n\n";
	
	return PAYLOAD;
}



// previsione deterministica
vector<vector<double>> PlagueModel::DetPredict(int endTime, int N0) const {
	
	clog << "\nBuilding N0 vector<double>...";
	
	//vettore della popolazione infetta al tempo t
	vector<double> Nvector(_dOI+1,0);
	Nvector[0] = N0;
	Nvector[1] = double(N0)/_beta;
	
	clog << "successfull.\n";
	
	vector<vector<double>> PAYLOAD = DetPredict(endTime, Nvector);	
	
	return PAYLOAD;
}


//previsione stocastica qua
vector<vector<long int>> PlagueModel::StocPredict(int endTime, int N0) const {
	vector<vector<long int>> PAYLOAD(4);
	return PAYLOAD;
}
