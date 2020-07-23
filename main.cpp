#include "utils.cpp"
#include <iostream>

using namespace std;

int main() {

	vector<float> vec = cumDistrFunc(10,4,0.2,"Uniform");
	
	for (int i=0; i<10; i++) printf("Day %i: probability %.2f \n", i, vec[i]);
	
	return 0;
}
