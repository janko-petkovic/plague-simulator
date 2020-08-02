/* Includes the following auxiliary methods:
 *
 * int MinDist(int, int)
 * float CumGauss(F)
 * fmat CastRowMat(vector<float>)
 * fmat BuildDistrMatCheat(vector<float>)
 * vector<float> CumDistrFunc(I, I, F, string)
 */

#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include <armadillo>



// Auxiliary function to find the closest boundary between end and beginning of illnes and
// peak day
int MinDist(int dOI, int peakDay) {
	if (peakDay < (dOI - peakDay)) return peakDay;
	else return (dOI - peakDay);
}

// Auxiliary function that finds the integral between -inf and x of the gaussian
template<class F>
float CumGauss(F x) {
    float PAYLOAD;
    PAYLOAD = 0.5*(erf(10) + erf(x));
    return PAYLOAD;
}


// Auxiliary function: casts vectors into square matrixes for further use
// Btw it converts vectors tu arma::mats
arma::fmat CastRowMat(std::vector<float> &vec) {
	arma::frowvec temp(vec);
	arma::fmat PAYLOAD(temp);
	PAYLOAD.resize(temp.n_elem, temp.n_elem);
	return PAYLOAD;
}


// Very chaty stuff to calculate the discrete prob distribution of the 
// status changes. Lets leave it like that
// NB there is a very sneaky cast from fmat to dmat care!!
arma::dmat BuildDistribMatCheat(std::vector<float> vec) {

	for (int i= vec.size()-1; i != 0; i--) vec[i] -= vec[i-1];
	
	vec.insert(vec.begin(),0);
	arma::fmat temp(CastRowMat(vec));
	arma::dmat PAYLOAD = arma::conv_to<arma::dmat>::from(temp);
	
	return PAYLOAD;
}

	

// Computes the discrete cumulative distribution function of a given plague parameter (death prob, healed prob,..)
template <class I, class F>
std::vector<float> CumDistrFunc(I dOI, I peakDay, F scale, std::string type) {

	std::unordered_map<std::string, int> Map;
		Map["Gaussian"] = 1;
		Map["Uniform"] = 2;
	
	std::vector<float> PAYLOAD(dOI);
	
        // switch depending on what type the distribution is
	switch(Map[type]) {
                case 1: {
                        float sigma = static_cast<float>(MinDist(dOI, peakDay))/3;
                        for (int i=0; i<dOI; i++)
                               PAYLOAD[i] = scale*CumGauss((i-peakDay+1)/sqrt(2)/sigma);
                        break; }
                case 2: {
                        float distrValue = 1./static_cast<float>(dOI)*scale;
			for (int i=0; i<dOI; i++)
				PAYLOAD[i] = distrValue*static_cast<float>(i+1);
                        break; }
			
	};	
	
	return PAYLOAD;
}




	
