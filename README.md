# plague-simulator

Mean field model for disease spread simulation.
Only valid as a first order approximation in the limit S -> infty; more 
refinements as well as a stochastic prediction algorithm will be implemented
in the future.

The program was coded on a Debian machine (Mint 19.3, Ubuntu 19) and the 
building instructions are given for a Debian system.

The author isn't very acquainted with non-debian Linux distros and cannot give 
useful information for an installation on those. Sorry for that.


## Prerequisites
For the correct program execution, Qt and Armadillo libraries have to be present
on the system. An installation from the ground up can be achieved running 
```
sudo apt install qt5-default libqt5charts5-dev liblapack-dev libblas-dev libarmadillo-dev libarmadillo9
```


## Download and install
All the building files can be downloaded from the git repository:

https://github.com/janko-petkovic/plague-simulator.git

Once downloaded the files unzip, go into your installation folder and
issue:

	$ mkdir build
	$ cd build
	$ qmake -o Makefile <path>/Plague-master/GUI/Plague_simulator.pro
	$ make -j8


Hope everything works, stay safe.

