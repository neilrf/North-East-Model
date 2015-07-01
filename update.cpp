
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
		
		double u = gsl_rng_uniform(sim.rand_gen);
		
		//flip (1->0)
		if (u < flip_prob){
			//std::cout << "(1->0)" << std::endl;
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
			(*site_ptr).mob_index = sys.num_mob_zero - 1;
			//remove site from list of mobile 1's
			if (m == sys.num_mob_one -1){
				sys.mob_one[sys.num_mob_one-1] = nullptr;
			}
			else {
				sys.mob_one[m] = sys.mob_one[sys.num_mob_one-1];
				sys.mob_one[sys.num_mob_one-1] = nullptr;
				sys.mob_one[m]->mob_index = m;
			}
			sys.num_mob_one -= 1;
			// check if sites influenced by active site become mobile and add to appropriate mobile list if so
			for (i=0; i<=1; i++){
				if (site_ptr->influence[i] != nullptr){
					if (site_ptr->influence[i]->constraint[0]->spin == 0 && site_ptr->influence[i]->constraint[1]->spin == 0){
						if(site_ptr->influence[i]->spin == 1){
							sys.num_mob_one += 1;
							sys.mob_one[sys.num_mob_one-1] = site_ptr->influence[i];
							site_ptr->influence[i]->mob_index = sys.num_mob_one - 1;
						}
						else {
							sys.num_mob_zero += 1;
							sys.mob_zero[sys.num_mob_zero-1] = site_ptr->influence[i];
							site_ptr->influence[i]->mob_index = sys.num_mob_zero - 1;
						}
					}
				}
			}
		}
		else {
			//std::cout << "(0->1)" << std::endl;
			//flip (0->1)
			//choose site from mobile 0's
			m = gsl_rng_uniform_int(sim.rand_gen, sys.num_mob_zero);
			site_ptr = sys.mob_zero[m];
			//update spin at site
			(*site_ptr).spin=1;
			//change index to show site has updated
			(*site_ptr).update_index = 1;
			//add site to list of mobile 1's
			sys.num_mob_one += 1;
			sys.mob_one[sys.num_mob_one - 1] = site_ptr;
			(*site_ptr).mob_index = sys.num_mob_one - 1;
			//remove site from list of mobile 0's
			if (m == sys.num_mob_zero -1){
				sys.mob_zero[sys.num_mob_zero-1] = nullptr;
			}
			else {
				sys.mob_zero[m] = sys.mob_zero[sys.num_mob_zero-1];
				sys.mob_zero[sys.num_mob_zero-1] = nullptr;
				sys.mob_zero[m]->mob_index = m;
			}
			sys.num_mob_zero -= 1;
			// check if sites influenced by active site were mobile and remove from appropriate mobile list if so
			for (i=0; i<=1; i++){
				if (site_ptr->influence[i] != nullptr){
					if (site_ptr->influence[i]->mob_index != -1){
						if (site_ptr->influence[i]->spin == 1){
							if (site_ptr->influence[i]->mob_index = sys.num_mob_one - 1){
								sys.mob_one[sys.num_mob_one - 1] = nullptr;
							}
							else {
								
								sys.mob_one[site_ptr->influence[i]->mob_index] = sys.mob_one[sys.num_mob_one - 1];
								sys.mob_one[sys.num_mob_one - 1] = nullptr;
								sys.mob_one[site_ptr->influence[i]->mob_index]->mob_index = site_ptr->influence[i]->mob_index; 
								
							}
							sys.num_mob_one -= 1;
							site_ptr->influence[i]->mob_index = -1;
						}
						else {
							if (site_ptr->influence[i]->mob_index = sys.num_mob_zero - 1){
								sys.mob_zero[sys.num_mob_zero - 1] = nullptr;
							}
							else {
								sys.mob_zero[site_ptr->influence[i]->mob_index] = sys.mob_zero[sys.num_mob_zero - 1];
								sys.mob_zero[sys.num_mob_zero - 1] = nullptr;
								sys.mob_zero[site_ptr->influence[i]->mob_index]->mob_index = site_ptr->influence[i]->mob_index; 
								
							}
							sys.num_mob_zero -= 1;
							site_ptr->influence[i]->mob_index = -1;
						}
					}
				}
			}
			
		}
	}
	
}
