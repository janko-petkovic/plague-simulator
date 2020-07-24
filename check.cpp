#include "Plague.h"
#include "Plague.cpp"
#include <iostream>
#include <armadillo>

using namespace std;

int main() {
		statusChange recovery;
		recovery.peak = 9;
		recovery.totProb = 1;
		recovery.distrType = "Uniform";
		
		statusChange death;
		death.peak = 6;
		death.totProb = 0.8;
		death.distrType = "Gaussian";
		
		
		PlagueModel myPlague(10, death, recovery, 0.3);
		
		for (int i=0; i<10; i++) printf("Distribuzione guariti giorno %i: %.2f\n",
		i, myPlague.RecovCumDistr()[i]);
		
        return 0;
}
