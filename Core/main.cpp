#include "Plague.h"
#include "Plague.cpp"
#include <iostream>

using namespace std;

int main() {

		statusChange recovery;
		recovery.peak = 15;
		recovery.finalProb = 1;
		recovery.distrType = "Gaussian";
		
		statusChange death;
		death.peak = 3;
		death.finalProb = 0;
		death.distrType = "Gaussian";
		
		
		PlagueModel myPlague(30, death, recovery, 0.3);
		
		
		vector<vector<double>> pandemy = myPlague.DetPredict(150,100);
		cout << endl;
		for (int i=0; i<150; i++) 
		//~ printf("%.2f ",myPlague.RecovCumDistr()[i]);
		printf("%.2f \t %.2f \t %.2f \t %.2f \n",
		pandemy[0][i],pandemy[1][i],pandemy[2][i],pandemy[3][i]);
		
		return 0;
}
