
#include "NorthEast.hpp"

void output(class system sys, class simulation sim, int k){
	
	std::string spin_file = std::string("Spin") + std::to_string(k);
	std::ofstream write(spin_file.c_str());
	
	for (int i=1; i<=sys.L; i++){
		for (int j=1; j<+sys.L; j++){
			write << sys.lattice[i][j].update_index << " ";
		}
		write << std::endl;
	}
	
}
