#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int floors;
  int *floorsizes;
  string ***trojans;
  int **num_possessions;
  string curr;

  input >> floors;
  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];
  num_possessions = new int*[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  num_possessions[i] = NULL;
  }

  string garbageLine;
  getline(input, garbageLine);
  //int count = 0;
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "MOVEIN") {
		  int i,k;
		  ss >> i;
		  ss >> k;
		  if (ss.fail()) {
			output << "Error - incorrect command" << endl;
		  }
		  else {
		  	 if (i <=0 || i > floors) {
		  	 	output << "Error - floor " << i << " does not exist" << endl;
		  	 } else if (trojans[i-1] != NULL) {
		  	 	output << "Error - floor " << i << " is not empty" << endl;
		  	 //} else if (i <= 0 || i > floors) {
		  	 	//output << "Error - floor " << i << " does not exist" << endl;
		  	 } else {
		  	 	trojans[i-1] = new string*[k];
		  	 	num_possessions[i-1] = new int[k];
		  	 	for (int a = 0; a < k; a++) {
		  	 		trojans[i-1][a] = NULL;
		  	 		num_possessions[i-1][a] = 0;
		  	 	}
		  	 	floorsizes[i-1] = k;
		  	 	//num_possessions[i-1] = new int[k];
		  	 }
		  }
	  }
	  else if (curr == "MOVEOUT") {
		int i;
		ss >> i;
		if (ss.fail()) {
			output << "Error - incorrect command" << endl;
		}
		else {
			if (i<= 0 || i > floors) { 
				output << "Error - floor " << i << " does not exist" << endl; 
			} else if (trojans[i-1] == NULL) {
				output << "Error - floor " << i << " is already empty" << endl;
			} else {
				//DELETE
				for (int a = 0; a < floorsizes[i]; a++) {
					if (trojans[i-1][a] != NULL) {
						delete [] trojans[i][a];
						trojans[i-1][a] = NULL;

						//delete [] num_possessions[i][a];
						//trojans[i][a] = NULL;
					}
				}
				delete [] trojans[i-1];
				trojans[i] = NULL;

				delete [] num_possessions[i-1];
				num_possessions[i-1] = NULL;

				floorsizes[i] = 0;
			}
		}
	  }
	  else if (curr == "OBTAIN") {
	  	int i, j, k;
	  	ss >> i;
	  	ss >> j;
	  	ss >> k;
	  	if (ss.fail()) {
	  		output << "Error - incorrect command" << endl;
	  	} else {
	  		if (trojans[i-1] == NULL) {
	  			output << "Error - floor" << i << " is already empty" << endl;
	  		} else if (i <= 0 || i > floors) {
	  			output << "Error - floor " << i << " does not exist" << endl;
	  		} else if (j <= 0 || j > floorsizes[i-1]) {
	  			output << "Error - student " << j << " does not exist on floor " << i << endl;
	  		} else if (trojans[i-1][j-1] != NULL) {
	  			output << "Error - student " << j << " on floor " << i << " already has possessions" << endl;
	  		} else {
	  			trojans[i-1][j-1] = new string[k];
	  			num_possessions[i-1][j-1] = k;
	  			for (int a = 0; a < k; a++) {
	  				string n;
	  				ss >> n;
	  				if (ss.fail()) {
	  					output << "Error - discrepancy between the number of possessions listed and the number of strings following" << endl;
		  			} else {
		  				trojans[i-1][j-1][a] = n;
		  			}
	  			}
	  		}
	  	}
	  }
	  else if (curr == "OUTPUT") {
	  	int i, j;
	  	ss >> i;
		ss >> j;
		if (ss.fail()) {
			output << "Error - incorrect command" << endl;
		}
		else {
			if (trojans[i] != NULL) {
		  		output << "Error - floor " << i << " is not empty" << endl;
		  	} else if (i < 0 || i >= floors) {
		  		output << "Error - floor " << i << " does not exist" << endl;
		  	} else if (j < 0 || j >= floorsizes[i]) {
	  			output << "Error - student " << j << " does not exist on floor " << i << endl;
		  	} else if (trojans[i][j] == NULL) {
	  			output << "Error - student " << j << " on floor " << i << " has no possessions" << endl;
	  		} else {
	  			int k=0;
	  			while (trojans[i][j][k] != "") {
	  				output << trojans[i][j][k] << endl;
	  				k++;
	  			}
	  		}
		}
	  }
	  else {
	  	//cerr an error
	  }
  }

  for (int i=0; i<floors; i++) {
	  		for (int j=0; j<floorsizes[i]; j++) {
	  			if (trojans[i] != NULL && trojans[i][j] != NULL) {
	  				delete [] trojans[i][j];
	  				trojans[i][j] = NULL;
	  			}
	  		}
	  		if (trojans[i] != NULL) {
	  			delete [] trojans[i];
	  			trojans[i] = NULL;

	  			delete [] num_possessions[i];
	  			num_possessions[i] = NULL;
	  		}
	  	}
	  	delete [] trojans;
	  	trojans = NULL;
	  	delete [] floorsizes;
	  	floorsizes = NULL;
	  	delete [] num_possessions;
	  	num_possessions = NULL;
  return 0;
}
