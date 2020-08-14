#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <armadillo>
#include <algorithm>

using std::vector;
using arma::dmat;




// input peakDays check: they cant be on day 0 or _dOI by definition (debugging)
bool PeakCheck(const int peak, const int dOI) { 
	if ((peak<=0)||(peak>=dOI)) return 1;
	else return 0;
}

// Finds the closest boundary between end and beginning of illnes and
// peak day 
int MinDist(const int dOI, const int peakDay) { return std::min(peakDay, dOI-peakDay); }

// Finds the gaussian integral between -inf and x
double CumGauss(const double& x) {
    double PAYLOAD;
    PAYLOAD = 0.5*(erf(10) + erf(x));
    return PAYLOAD;
}


// Cretes a square matrix of zeros setting the first row equal to the
// vector<double> given as argument (broadcast).
// NB: it converts std::vectors tu arma::dmat-s
dmat CastVecMat(const vector<double>& vec) {
	// we need to make vec a row vector first
	arma::drowvec temp(vec);
	
	// building the payload
	int size = temp.n_elem;
	dmat PAYLOAD(temp);
	PAYLOAD.resize(size, size);
	
	// initializing setting to zero the zero elements
	PAYLOAD(1,0,arma::size(size-1,size)) = arma::zeros(size-1,size);
	return PAYLOAD;
}


// Very specific function, build the propagation matrix of a status change
// given its discrete cumulative function. 
dmat BuildDistribMat(vector<double> vec) {
	
	// calculate the distribution from a cumulative
	for (int i= vec.size()-1; i!=0; i--) vec[i] -= vec[i-1];
	
	// insert a zero at the beginning (as the model requires it)
	vec.insert(vec.begin(),0);
	
	// now add the zeroes underneath to make it a matrix
	dmat PAYLOAD(CastVecMat(vec));
	
	return PAYLOAD;
}

	

// Computes the discrete cumulative probability function of a status change given 
// its parameters
vector<double> CumProbFunc(const int dOI, const int peakDay, const double finalProb,const std::string type) {

	// Dictionary {1 = Gaussian, 2 = Uniform}
	std::unordered_map<std::string, int> Map;
		Map["Gaussian"] = 1;
		Map["Uniform"] = 2;
	
	vector<double> PAYLOAD(dOI);
	
    // switch depending on what type the distribution is
	switch(Map[type]) {
                case 1: {
						// we assume that the distance between end/beginning of illness and
						// the peak day of a status change is 5 sigma
                        double sigma = static_cast<double>(MinDist(dOI, peakDay))/5;
                        // filling the gaussian cumulative
                        for (int i=0; i<dOI; i++)
                            PAYLOAD[i] = finalProb*CumGauss((i-peakDay+1)/sqrt(2)/sigma);
                        break;
                }
                case 2: {
						// slope
                        double distrValue = 1./static_cast<double>(dOI)*finalProb;
                        // filling the uniform cumulative
						for (int i=0; i<dOI; i++)
							PAYLOAD[i] = distrValue*static_cast<double>(i+1);
                        break;
                }
	};	
	
	return PAYLOAD;
}






	
