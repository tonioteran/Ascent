/**
 *
 * Hill-Clohessy-Wiltshire equations simulator
 * 
 */

/**
 * @brief      HCW equations
 * @author     Antonio Teran
 * @date       08/05/18
 */

#include <iostream>
#include "ascent/Ascent.h"
#include <math.h>

double n = 0.000113; // [s^-1], for low earth orbit

// Create custom struct
struct HCW{
	void operator()(const asc::state_t& x, asc::state_t& xd, const double t){
		xd[0] = x[3];
		xd[1] = x[4];
		xd[2] = x[5];
		xd[3] = 3*pow(n,2)*x[0] + 2*n*x[4];
		xd[4] = -2*n*x[3];
		xd[5] = -pow(n,2)*x[5];
	}// end of operator
};// end of struct

int main(int argc, char** argv){

	std::cout << "Hello HCW World! Sim:" << std::endl;

	// Create the initial conditions:
	asc::state_t x = {50.0, 50.0, 50.0, -0.1, -0.1, -0.1}; // Check units and modify
	double t = 0.0;
	double dt = 0.1;
	double t_end = 100000.0;

	asc::RK4 integrator;
	HCW system;

	asc::Recorder recorder;

	while(t < t_end){
		recorder({t, x[0], x[1], x[2], x[3], x[4], x[5] });
		integrator(system, x, t, dt);
	}// end of while

	// generate file with comma separated values:
	recorder.csv("HCW", {"t", "x0", "x1", "x2", "x3", "x4", "x5"});

	// Finish
	return 0;

}// end of main

