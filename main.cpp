


#include "NorthEast.hpp"

int main(int argc, char*argv[]){
	
	//set up GSL rand environment
	
	const gsl_rng_type *T;
	gsl_rng *r;
	gsl_rng_env_setup();
	
	T=gsl_rng_default;
	r = gsl_rng_alloc(T);
	
	
	class system sys;
	class simulation sim;
	
	sim.rand_gen = r;
	sim.rand_type = T;
	
	// read in parameters from command line
	sys.L = atoi(argv[1]);
	sys.q = atof(argv[2]);
	sim.max_time = atoi(argv[3]);
	sim.num_samples = atoi(argv[4]);
	sim.num_runs = atoi(argv[5]);
	
	sim.delta_t = sim.max_time/(double)sim.num_samples;
	sim.sample_times = std::vector<double>(sim.num_samples+1);
	
	sim.sample_times[0] = 0.0;
	for (int i=1; i<=sim.num_samples; i++){
		sim.sample_times[i] = sim.sample_times[i-1]+sim.delta_t; 
	}
	
	for (int n=1; n<=sim.num_runs; n++){
		setup(sys,sim);
		for (int i=1; i<=sim.num_samples; i++){
			while (sys.t < sim.sample_times[i]){
				update(sys,sim,i);
			}
			
			output(sys,sim,i);
			std::cout << "Sample: " << i << std::endl;
		}
	}

	
	//~ for (int i=sys.L; i>=0; i--){
		//~ for (int j=0; j<=sys.L; j++){
			//~ std::cout << sys.lattice[i][j].update_index << " ";
		//~ }
		//~ std::cout << std::endl;
	//~ }
	
	
	gsl_rng_free(r);
	
	return 0;
}
