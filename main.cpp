#include "Plague.h"
#include "Plague.cpp"
#include <iostream>

using namespace std;

int main() {

		statusChange recovery;
		recovery.peak = 1;
		recovery.cumProb = 1;
		recovery.distrType = "Uniform";
		
		statusChange death;
		death.peak = 3;
		death.cumProb = 0;
		death.distrType = "Gaussian";
		
		
		PlagueModel myPlague(2, death, recovery, 0.5);
		
		vector<vector<double>> pandemy = myPlague.Flow(10,100);
		cout << endl;
		for (int i=0; i<5; i++) 
		//~ printf("%.2f ",myPlague.RecovCumDistr()[i]);
		printf("%.2f \t %.2f \t %.2f \t %.2f \n",
		pandemy[0][i],pandemy[1][i],pandemy[2][i],pandemy[3][i]);
		
		return 0;
}
