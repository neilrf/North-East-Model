
#include "NorthEast.hpp"

void output(class system sys, class simulation sim, int k){
	
	std::string spin_file = std::string("Spin") + std::to_string(k);
	std::ofstream write(spin_file.c_str());
	
	//~ for (int i=1; i<=sys.L; i++){
		//~ for (int j=1; j<=sys.L; j++){
			//~ write << sys.lattice[i][j].update_index << " ";
		//~ }
		//~ write << std::endl;
	//~ }
	
	std::vector<int> current_pos(sys.L,0);
	int new_pos;
	int i;
	for (int j=1; j<=sys.L; j++){
		i = current_pos[j-1]+1;
		for (int n = i; n<=sys.L; n++){
			if (sys.lattice[n][j].update_index == 0 && n<sys.L){
				current_pos[j-1] = n-1;
				break;
			}
			else if (n == sys.L){
				current_pos[j-1] = sys.L;
				break;
			}
		} 
		write << j << " " << current_pos[j-1] << std::endl;
	}
	
}
