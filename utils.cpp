/* Includes the following auxiliary methods:
 *
 * int MinDist(int, int)
 * float CumGauss(F)
 * vector<float> CumDistrFunc(I, I, F, string)
 */

#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>



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
		
			
	
