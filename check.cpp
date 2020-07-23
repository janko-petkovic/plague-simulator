#include "utils.cpp"
#include <iostream>

using namespace std;

int main() {


        vector<float> vector = CumDistrFunc(10,8,1,"Gaussian");

        for (int i=0; i<10; i++) printf ("Probabilità al giorno %i del %.2f \n", i, vector[i]);

        return 0;
}
