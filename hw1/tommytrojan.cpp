#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void clear_building(int floors, int* &floorsizes, string ***&trojans, int **&num_possessions) {
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
}

string is_floor_valid(int floor_number, int floors, string ***trojans, bool need_floor_empty) {
	string return_string;
	stringstream ss;
	ss << "";
	if (floor_number <= 0 || floor_number > floors) {
		ss << "Error - floor " << floor_number << " does not exist" << endl;
	} else {
		if (trojans[floor_number-1] != NULL && need_floor_empty) {
			ss << "Error - floor " << floor_number-1 << " is not empty" << endl;
		} else if (trojans[floor_number-1] == NULL && !need_floor_empty) {
			ss << "Error  floor " << floor_number << " is already empty" << endl;
		}
	}

	ss >> return_string;
	return return_string;
}

string is_student_valid_on_floor(int student_number, int floor_number, int floors, int *floorsizes, string ***trojans) {
	string return_string;
	stringstream ss;
	ss << "";
	string floor_is_invalid = is_floor_valid(floor_number, floors, trojans, true);
	if (floor_is_invalid.compare("") != 0) {
		return floor_is_invalid;
	} else {
		if (student_number <= 0 || student_number > floorsizes[floor_number-1]) {
			ss << "Error - student " << student_number << " does not exist on floor " << floor_number << endl;
		} else if (trojans[floor_number-1][student_number-1] != NULL) {
			ss << "Error - student " << student_number << " on floor " << floor_number << " already has possessions" << endl;
		}
		ss >> return_string;
		return return_string;
	}
}

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
		  	string floor_is_valid = is_floor_valid(i, floors, trojans, true);
		  	if (floor_is_valid.compare("") != 0) {
		  		output << floor_is_valid << endl;
		  	} else {
		  	 	trojans[i-1] = new string*[k];
		  	 	num_possessions[i-1] = new int[k];
		  	 	for (int a = 0; a < k; a++) {
		  	 		trojans[i-1][a] = NULL;
		  	 		num_possessions[i-1][a] = 0;
		  	 	}
		  	 	floorsizes[i-1] = k;
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
			string floor_is_valid = is_floor_valid(i, floors, trojans, false);
			if (floor_is_valid.compare("") != 0) { 
				output << floor_is_valid << endl; 
			} else {
				for (int a = 0; a < floorsizes[i]; a++) {
					if (trojans[i-1][a] != NULL) {
						delete [] trojans[i][a];
						trojans[i-1][a] = NULL;
					}
				}
				delete [] trojans[i-1];
				trojans[i-1] = NULL;

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
	  		string student_is_valid_on_floor = is_student_valid_on_floor(j, i, floors, floorsizes, trojans);
	  		if (student_is_valid_on_floor.compare("") != 0) {
	  			output << student_is_valid_on_floor << endl;
	  		} else {
	  			trojans[i-1][j-1] = new string[k];
	  			num_possessions[i-1][j-1] = k;
	  			for (int a = 0; a < k; a++) {
	  				string n;
	  				ss >> n;
		  			trojans[i-1][j-1][a] = n;
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
			string student_is_valid_on_floor = is_student_valid_on_floor(j, i, floors, floorsizes, trojans);
			if (student_is_valid_on_floor.compare("") != 0) {
				output << student_is_valid_on_floor << endl;
			} else {
	  			for (int a = 0; a < num_possessions[i-1][j-1]; a++) {
	  				output << trojans[i-1][j-1][a] << endl;
	  			}
			}
	  	}
	  }	
	  else {
	  	output << "Error - line does not begin with one of four commands: MOVEIN, MOVEOUT, OBTAIN, OUTPUT" << endl;
	  }
  }

  clear_building(floors, floorsizes, trojans, num_possessions);
  return 0;
}
