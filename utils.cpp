#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>



// Auxiliary function to find the closest boundary between end and beginning of illnes and
// peak day
int minDist(int dOI, int peakDay) {
	if (peakDay < (dOI - peakDay)) return peakDay;
	else return (dOI - peakDay);
}


// Computes the discrete cumulative distribution function of a given parameter
template <class I, class F>
std::vector<float> cumDistrFunc(I dOI, I peakDay, F scale, std::string type) {

	std::unordered_map<std::string, int> Map;
		Map["Gaussian"] = 1;
		Map["Uniform"] = 2;
	
	std::vector<float> PAYLOAD(dOI);
	
	switch(Map[type]) {
		case 1:
			break;
		case 2:
			float distrValue = 1/static_cast<float>(dOI)*scale;
			for (int i=0; i<dOI; i++)
				PAYLOAD[i] = distrValue*static_cast<float>(i+1);
			break;
			
	};	
	
	return PAYLOAD;
}
		
			
	
