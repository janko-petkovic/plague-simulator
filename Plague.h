#ifndef "PLAGUE_H"
#define "PLAGUE_H"

#include <armadillo>

class PlagueModel() {
	private:
	int _dOI;  // duration of illness
	vec _r0;
	vec _healDist;
	
	public:
	PlagueModel();
	~PlagueModel();
	
	long int Project(int t) const;
}

#endif	
	
	
