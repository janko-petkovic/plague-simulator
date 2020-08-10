#include <iostream>
#include <armadillo>
#include "Plague.h"
#include "Plague.cpp"


using namespace std;
using namespace arma;

int main() {
	
		
	vector<double> vec{1,2,3,4};
	dmat mat = BuildDistribMatCheat(vec);
	
	cout << mat;
		
     return 0;
}
