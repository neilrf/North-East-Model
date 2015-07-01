

#include "NorthEast.hpp"
void setup(class system &sys, class simulation &sim){
	
	//initial system time set to 0
	sys.t = 0.0;
	
	//set up initial lattice
	sys.lattice = std::vector<std::vector<site> > (sys.L+1,std::vector<site>(sys.L+1));
	
	//lower left corner
	int i=0;
	int j=0;
	sys.lattice[i][j].num_con = 0;
	sys.lattice[i][j].num_inf = 0;
	sys.lattice[i][j].spin = 0;
	sys.lattice[i][j].update_index = 0;
	sys.lattice[i][j].mob_index = -1;
	sys.lattice[i][j].constraint[0] = nullptr;
	sys.lattice[i][j].influence[0] = nullptr;
	
	if (sys.lattice[i][j].constraint[1] == nullptr){
		std::cout << "hurrah" << std::endl; 
	}
	
	//left boundary
	j=0;
	for (i=1; i<=sys.L; i++){
		sys.lattice[i][j].num_con = 0;
		sys.lattice[i][j].num_inf = 1;
		sys.lattice[i][j].spin = 0;
		sys.lattice[i][j].update_index = 0;
		sys.lattice[i][j].mob_index = -1;
		sys.lattice[i][j].constraint[0] = nullptr;
		sys.lattice[i][j].influence[0] = &(sys.lattice[i][j+1]);
	}
	
	//lower boundary
	i=0;
	for (j=1; j<=sys.L; j++){
		sys.lattice[i][j].num_con = 0;
		sys.lattice[i][j].num_inf = 1;
		sys.lattice[i][j].spin = 0;
		sys.lattice[i][j].update_index = 0;
		sys.lattice[i][j].mob_index = -1;
		sys.lattice[i][j].constraint[0] = nullptr;
		sys.lattice[i][j].influence[0] = &(sys.lattice[i+1][j]);
	}
	
	//main part of lattice
	for (i=1; i<sys.L; i++){
		for (j=1; j<sys.L; j++){
			sys.lattice[i][j].num_con = 2;
			sys.lattice[i][j].num_inf = 2;
			sys.lattice[i][j].spin = 1;
			sys.lattice[i][j].update_index = 0;
			sys.lattice[i][j].mob_index = -1;
			sys.lattice[i][j].constraint[0] = &(sys.lattice[i-1][j]);
			sys.lattice[i][j].constraint[1] = &(sys.lattice[i][j-1]);
			sys.lattice[i][j].influence[0] = &(sys.lattice[i+1][j]);
			sys.lattice[i][j].influence[1] = &(sys.lattice[i][j+1]);
		}
	}
	
	//upper boundary
	i=sys.L;
	for (j=1; j<sys.L; j++){
		sys.lattice[i][j].num_con = 2;
		sys.lattice[i][j].num_inf = 1;
		sys.lattice[i][j].spin = 1;
		sys.lattice[i][j].update_index = 0;
		sys.lattice[i][j].mob_index = -1;
		sys.lattice[i][j].constraint[0] = &(sys.lattice[i-1][j]);
		sys.lattice[i][j].constraint[1] = &(sys.lattice[i][j-1]);
		sys.lattice[i][j].influence[0] = &(sys.lattice[i][j+1]);
	}
	
	//right boundary
	j=sys.L;
	for (i=1; i<sys.L; i++){
		sys.lattice[i][j].num_con = 2;
		sys.lattice[i][j].num_inf = 1;
		sys.lattice[i][j].spin = 1;
		sys.lattice[i][j].update_index = 0;
		sys.lattice[i][j].mob_index = -1;
		sys.lattice[i][j].constraint[0] = &(sys.lattice[i-1][j]);
		sys.lattice[i][j].constraint[1] = &(sys.lattice[i][j-1]);
		sys.lattice[i][j].influence[0] = &(sys.lattice[i+1][j]);
	}
	
	//top right corner
	i=sys.L;
	j=sys.L;
	sys.lattice[i][j].num_con = 2;
	sys.lattice[i][j].num_inf = 0;
	sys.lattice[i][j].spin = 1;
	sys.lattice[i][j].update_index = 0;
	sys.lattice[i][j].mob_index = -1;
	sys.lattice[i][j].constraint[0] = &(sys.lattice[i-1][j]);
	sys.lattice[i][j].constraint[1] = &(sys.lattice[i][j-1]);
	sys.lattice[i][j].influence[0] = nullptr;
	
	//set up mobile site lists	
	sys.num_mob_one = 1;
	sys.num_mob_zero = 0;
	
	sys.mob_one = std::vector<site*>(sys.L * sys.L);
	sys.mob_zero = std::vector<site*>(sys.L * sys.L);
	sys.mob_one[0] = &(sys.lattice[1][1]);
	
	sys.lattice[1][1].mob_index = 0;
	
		
}
