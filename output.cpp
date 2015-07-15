
#include "NorthEast.hpp"

void output(class system sys, class simulation sim, int k, int N){
	
	std::string spin_file = std::string("NE_Spin") + std::to_string(k) + std::string("_") + std::to_string(N);
	std::ofstream write(spin_file.c_str());
	
	//~ for (int i=1; i<=sys.L; i++){
		//~ for (int j=1; j<=sys.L; j++){
			//~ write << sys.lattice[i][j].update_index + (1 - sys.lattice[i][j].spin) << " ";
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
	}
	std::vector<std::vector<int> > new_points(2*sys.L,std::vector<int>(2));
	for (int j=0; j<sys.L-current_pos[0]; j++){
		new_points[j][0] = 0;
		new_points[j][1] = sys.L - j;
	}
	int count = sys.L-current_pos[0];
	for (int n=0; n<sys.L; n++){
		new_points[count][0] = n;
		new_points[count][1] = current_pos[n];
		count += 1;
		int diff = current_pos[n] - current_pos[n+1];
		for (int m=1; m<=diff; m++){
			new_points[count][0] = n;
			new_points[count][1] = current_pos[n] - m;
			count += 1;
		}
	}
	std::vector<std::vector<int> > rotate_points(2*sys.L,std::vector<int>(2));
	for (int j=0; j<2*sys.L; j++){
		rotate_points[j][0] = new_points[j][0] - new_points[j][1];
		rotate_points[j][1] = new_points[j][0] + new_points[j][1];
	}
	double time = sim.sample_times[k];
	for (int j=0; j<2*sys.L; j++){
		write << rotate_points[j][0]/time << " " << rotate_points[j][1]/time << std::endl;
	}
}
