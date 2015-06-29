
#include "NorthEast.hpp"

void update(class system &sys, class simulation &sim, int i){
	
	double rate, t_add, flip_prob;
	class site* site_ptr; //pointer for site we choose to flip
	int m;
	while (sys.t < sim.sample_times[i]){
		// calculate transition rate and update time
		rate = (double) sys.num_mob_one * sys.q + (double) sys.num_mob_zero * (1.0-sys.q);
		t_add = gsl_ran_exponential(sim.rand_gen,1.0/rate);
		sys.t += t_add;
		
		//calculate probability of flipping (1->0) and choose transition
		flip_prob = ((double)sys.num_mob_one * sys.q)/(((double)sys.num_mob_one * sys.q)+((double)sys.num_mob_zero * (1.0-sys.q)));
		std::cout << flip_prob << std::endl;
		
		double u = gsl_rng_uniform(sim.rand_gen);
		
		//flip (1->0)
		if (u < flip_prob){
			//choose a site from mobile 1's
			m = gsl_rng_uniform_int(sim.rand_gen, sys.num_mob_one);
			site_ptr = sys.mob_one[m];
			//update spin at site
			(*site_ptr).spin =0;
			//change index to show site has updated
			(*site_ptr).update_index = 1;
			//add site to list of mobile zeros
			sys.num_mob_zero += 1;
			sys.mob_zero[sys.num_mob_zero - 1] = site_ptr;
			//remove site from list of mobile 1's
			if (m == sys.num_mob_one -1){
				sys.mob_one[sys.num_mob_one-1] = nullptr;
			}
			else {
				sys.mob_one[m] = sys.mob_one[sys.num_mob_one-1];
				sys.mob_one[sys.num_mob_one-1] = nullptr;
			}
			sys.num_mob_one -= 1;
			
			
			
		}
		else {
			
		}
	}
	
}
