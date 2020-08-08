#include "Plague.h"
#include "Plague.cpp"
#include <iostream>

using namespace std;

int main() {

		statusChange recovery;
		recovery.peak =14;
		recovery.finalProb = 0.95;
		recovery.distrType = "Gaussian";
		
		statusChange death;
		death.peak = 12;
		death.finalProb = 0.05;
		death.distrType = "Gaussian";
		
		
		PlagueModel myPlague(30, death, recovery, 0.1);
		
		int days = 100;
		
		vector<vector<double>> pandemy = myPlague.DetPredict(days,13000);
		cout << endl;
		for (int i=0; i<days; i++) 
		//~ printf("%.2f ",myPlague.RecovCumDistr()[i]);
		printf("%.2f \t %.2f \t %.2f \t %.2f \n",
		pandemy[0][i],pandemy[1][i],pandemy[2][i],pandemy[3][i]);
		
		return 0;
}
