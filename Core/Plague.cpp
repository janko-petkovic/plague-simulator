#include "Plague.h"
#include "utils.cpp"

#include <cassert>
#include <iostream>


using std::vector;
using std::cout;
using std::endl;


// Auxiliary struct print function (debugging purpouses)
void printStatChangeParams(statusChange status) {
	cout << " parameters: " << endl;
	cout << " Peak: " << status.peak << endl;
	cout << " Final prob: " << status.finalProb << endl;
	cout << " Distribution: " << status.distrType << endl;	
}


// Default constructor: instantiation without initialization. Gives a
// class istance that is NOT ready to simulate (you have to set all the
// parameters first by hand using setters
PlagueModel::PlagueModel() {
	cout << "Plague model creation: successfull.\n";
	cout << "All parameters are uninitialized, please procede to set them";
}

// Advanced constructor: produces a class istance ready for simulation
PlagueModel::PlagueModel(const int dOI, const statusChange death, const statusChange recov,
						const double beta) : _dOI(dOI), _beta(beta) {
							
	// input checks: unnecessary if you are using a GUI, still useful
	assert(dOI>=2);
	assert(!PeakCheck(death.peak,dOI));
	assert(!PeakCheck(death.peak,dOI));

	
	// distributions computation
	_deathCumFunc = CumProbFunc(dOI, death.peak, death.finalProb,
									death.distrType);
	_recovCumFunc = CumProbFunc(dOI, recov.peak, recov.finalProb,
									recov.distrType);
									
	// logging where we are
	cout << "Plague model creation: successfull.\n";
	cout << "Days of illness: " << _dOI << endl;
	cout << "Death status change";
	printStatChangeParams(death);
	cout << "Recovery status change";
	printStatChangeParams(recov);									
}		

// Getters
int PlagueModel::DOI() const { return _dOI; }
double PlagueModel::Beta() const { return _beta; }
vector<double> PlagueModel::RecovCumFunc() const { return _recovCumFunc; }
vector<double> PlagueModel::DeathCumFunc() const { return _deathCumFunc; }

// Setters
void PlagueModel::SetDOI(const int val) { _dOI = val; }
void PlagueModel::SetBeta(const double val) { _beta = val; }
void PlagueModel::SetRecovCumFunc(const vector<double> vec) { _recovCumFunc = vec; }
void PlagueModel::SetDeathCumFunc(const vector<double> vec) { _deathCumFunc = vec; }



// Deterministic prediction: the initial infected value is already given in its vector representation.
// Not that this is necessary if you want to start you prediction from an intermediate point of an
// epidemic process as the values in t+1 depend on the _dOI days before and not just on t.
vector<vector<double>> PlagueModel::DetPredict(const int endTime,const vector<double> Nvector) const {
	
	// Running a dimension check on Nvector; more logging
	int temp = Nvector.size();
	cout << "\nRUN PREDICTION\nType: deterministic\n";
	cout << " Checking N0 vector size...";
	assert(temp=(_dOI+1));
	cout << " done.\nDays of prediction: " << endTime << endl << endl;
	cout << "Begin computation...\n";
	
	// infected population vector 
	arma::dcolvec Nvec(Nvector);
	
	// recovery and death distributions matrixes
	arma::mat deadMat(BuildDistribMat(_deathCumFunc));
	arma::mat recovMat(BuildDistribMat(_recovCumFunc));

	// infection propagation matrix 
	arma::mat infectMat(_dOI+1, _dOI+1, arma::fill::zeros);
	infectMat(0,0) += 1+_beta;
	infectMat(1,0,arma::size(_dOI, _dOI)) = arma::eye(_dOI,_dOI);
	
	// final payload elements
	vector<double> infected(endTime);
	vector<double> cumInfected(endTime);
	vector<double> dead(endTime);
	vector<double> recovered(endTime);
	
	cumInfected[0] = Nvec(0);
	dead[0] = 0.;
	recovered[0] = 0.;
	infected[0] = Nvec(0);
	
	// Core cylce setup and execution
	arma::dcolvec deadIncr(_dOI+1);
	arma::dcolvec recovIncr(_dOI+1);
	arma::dcolvec infectIncr(_dOI+1);
	
	for (int i=1; i<=endTime; i++) {
		// total infected at time i
		cumInfected[i] = cumInfected[i-1] + Nvec(0)*_beta;
		
		// total dead at time i
		deadIncr = deadMat*Nvec*_beta;
		dead[i] = dead[i-1] + deadIncr(0);
		
		// total recovered at time i
		recovIncr = recovMat*Nvec*_beta;
		recovered[i] = recovered[i-1]+recovIncr(0);
		
		// active infected at time i
		infectIncr = infectMat*Nvec;
		Nvec = infectIncr - recovIncr - deadIncr;
		infected[i] = Nvec(0);
	}
	
	
	// Build payload and return
	vector<vector<double>> PAYLOAD(4);
	PAYLOAD[0] = cumInfected;
	PAYLOAD[1] = infected;
	PAYLOAD[2] = dead;
	PAYLOAD[3] = recovered;
	
	// Last checks (were crucial in GUI debugging)
	cout << "Payload check: 2nd day" << endl;
	cout  << PAYLOAD[0][2] << " " << PAYLOAD[1][2] << " ";
	cout  << PAYLOAD[2][2] << " " << PAYLOAD[3][2] << endl;

	cout << "Successful. Returning the payload\n\n";
	
	return PAYLOAD;
}

// Deterministic prediction overload starting from first day of infection
vector<vector<double>> PlagueModel::DetPredict(const int endTime, const int N0) const {
	
	cout << "\nBuilding N0 vector<double>...";
	
	// Build infected at time 0 vector
	vector<double> Nvector(_dOI+1,0);
	Nvector[0] = N0;
	
	// This value has no real world meaning and is defined as follows in order
	// to allow the prediction to run as supposed
	Nvector[1] = double(N0)/_beta;
	
	cout << "successfull.\n";
	
	// We use the other function overload
	vector<vector<double>> PAYLOAD = DetPredict(endTime, Nvector);	
	
	return PAYLOAD;
}


//~ // Stochastic prediction: still not implemented
//~ vector<vector<long int>> PlagueModel::StocPredict(const int endTime, const vector<long int>) const {
	//~ vector<vector<long int>> PAYLOAD(4);
	//~ return PAYLOAD;
//~ }

//~ vector<vector<long int>> PlagueModel::StocPredict(const int endTime, const int N0) const {
	//~ vector<vector<long int>> PAYLOAD(4);
	//~ return PAYLOAD;
//~ }
