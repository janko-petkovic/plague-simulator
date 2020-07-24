#include "Plague.h"
#include "Plague.cpp"
#include <iostream>
#include <armadillo>

using namespace std;

int main() {
	
	vector<float> vecR0(10);
	vecR0[0] = 0.3;
	arma::mat matR0 = CastRowMat(vecR0);
	arma::mat temp(10,10,arma::fill::eye);
	matR0 += temp;
	
	cout << matR0 << endl;
	
		//~ statusChange recovery;
		//~ recovery.peak = 9;
		//~ recovery.totProb = 0.9;
		//~ recovery.distrType = "Gaussian";
		
		//~ statusChange death;
		//~ death.peak = 6;
		//~ death.totProb = 0.1;
		//~ death.distrType = "Gaussian";
		
		
		//~ PlagueModel myPlague(10, death, recovery, 0.3);
		
		//~ for (int i=0; i<10; i++) printf("Distribuzione guariti giorno %i: %.2f\n",
		//~ i, myPlague.RecovCumDistr()[i]);
		
        return 0;
}
