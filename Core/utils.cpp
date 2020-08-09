/* Includes the following auxiliary methods:
 *
 * int MinDist(int, int)
 * double CumGauss(F)
 * dmat CastRowMat(vector<double>)
 * dmat BuildDistrMatCheat(vector<double>)
 * vector<double> CumDistrFunc(I, I, F, string)
 */

#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <armadillo>
#include <algorithm>



// INPUT CHECK
// input peakDays check: they cant be on day 0 or _dOI by definition
bool PeakCheck(int& peak, int& dOI) {
	if ((peak==0)||(peak==dOI)) return 1;
	else return 0;
}


// Auxiliary function to find the closest boundary between end and beginning of illnes and
// peak day. 

int MinDist(int& dOI, int& peakDay) { return std::min(peakDay, dOI-peakDay); }

// Auxiliary function that finds the integral between -inf and x of the gaussian
template<class F>
double CumGauss(F x) {
    double PAYLOAD;
    PAYLOAD = 0.5*(erf(10) + erf(x));
    return PAYLOAD;
}


// Auxiliary function: casts vectors into square matrixes for further use
// Btw it converts vectors tu arma::mats
arma::dmat CastRowMat(std::vector<double> &vec) {
	arma::drowvec temp(vec);
	arma::dmat PAYLOAD(temp);
	PAYLOAD.resize(temp.n_elem, temp.n_elem);
	return PAYLOAD;
}


// Very chaty stuff to calculate the discrete prob distribution of the 
// status changes. Lets leave it like that
// NB there is a very sneaky cast from dmat to dmat care!!
arma::dmat BuildDistribMatCheat(std::vector<double> vec) {

	for (int i= vec.size()-1; i != 0; i--) vec[i] -= vec[i-1];
	
	vec.insert(vec.begin(),0);
	arma::dmat temp(CastRowMat(vec));
	arma::dmat PAYLOAD = arma::conv_to<arma::dmat>::from(temp);
	
	return PAYLOAD;
}

	

// Computes the discrete cumulative distribution function of a given plague parameter (death prob, healed prob,..)
template <class I, class F>
std::vector<double> CumDistrFunc(I dOI, I peakDay, F scale, std::string type) {

	std::unordered_map<std::string, int> Map;
		Map["Gaussian"] = 1;
		Map["Uniform"] = 2;
	
	std::vector<double> PAYLOAD(dOI);
	
    // switch depending on what type the distribution is
	switch(Map[type]) {
                case 1: {
                        double sigma = static_cast<double>(MinDist(dOI, peakDay))/5;
                        for (int i=0; i<dOI; i++)
                            PAYLOAD[i] = scale*CumGauss((i-peakDay+1)/sqrt(2)/sigma);
                        break;
                }
                case 2: {
                        double distrValue = 1./static_cast<double>(dOI)*scale;
						for (int i=0; i<dOI; i++)
							PAYLOAD[i] = distrValue*static_cast<double>(i+1);
                        break;
                }
			
	};	
	
	return PAYLOAD;
}






	
