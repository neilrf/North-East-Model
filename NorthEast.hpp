#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class site {
	public:
		int num_con; // number of constraints
		int num_inf; // number of sites influenced
		std::vector<site*> constraint; // pointers to constraining neighbours
		std::vector<site*> influence; //pointers to influenced neighbours
		int spin; //spin of site
		int update_index; // keep track of whether site has ever updated
		int mob_index; // location of site in mobile list
};

class system {
	public:
		int L; //System size
		double q; // rate of flip 1->0
		std::vector<std::vector<site> > lattice; // lattice of sites
		std::vector<site*> mob_zero; // pointers to mobile 0 sites
		std::vector<site*> mob_one; // pointers to mobile 1 sites
		int num_mob_zero;
		int num_mob_one;
		double t; //time
};

class simulation {
	public:
		int num_runs; //number of runs for calculations
		int max_time;
		int num_samples; //number of snapshots of system for output
		double delta_t; //time between each measurement
		int init_cond; //flag for initial conditions
		const gsl_rng_type *rand_type;
		const gsl_rng *rand_gen;
		std::vector<double> sample_times; //times to take take sample for output
		int process_flag; //to determine between NE/East/Tree
};

void setup(class system &sys, class simulation &sim, int m);
void update(class system &sys, class simulation &sim, int i);
void output(class system sys, class simulation sim, int i, int N);


