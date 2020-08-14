#include "Plague.h"
#include "Plague.cpp"
#include <iostream>

using namespace std;

int main() {

		statusChange recovery;
		recovery.peak =14;
		recovery.finalProb = 0.87;
		recovery.distrType = "Gaussian";
		
		statusChange death;
		death.peak = 12;
		death.finalProb = 0.13;
		death.distrType = "Gaussian";
		
		
		PlagueModel myPlague(30, death, recovery, 0.04);
		
		int days = 20;
		
		vector<double> infectedTemp{
			12953,
			12924,
			12694,
			12646,
			12482,
			12474,
			12456,
			12457,
			12422,
			12330,
			12230,
			12616,
			12608,
			12601,
			12583,
			12462,
			12322,
			12425,
			12343,
			12269,
			12425,
			12461,
			12389,
			12477,
			12494,
			12514,
			12940,
			13178,
			13200,
			13324,
			13449};
			
		int dim = infectedTemp.size();
		
		vector<double> infected;

		
		for (int i=0; i<dim; i++) {
			infected.push_back(infectedTemp[dim-i-1]);
			cout << infected[i] << " ";
		}
			
		
		vector<vector<double>> pandemy = myPlague.DetPredict(days,infected);
		cout << endl;
		for (int i=0; i<days; i++) 
		//~ printf("%.2f ",myPlague.RecovCumDistr()[i]);
		printf("%.2f \t %.2f \t %.2f \t %.2f \n",
		pandemy[0][i],pandemy[1][i],pandemy[2][i],pandemy[3][i]);
		
		return 0;
}
