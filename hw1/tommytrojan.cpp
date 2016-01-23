#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool is_floor_valid(int floor_number, int floors, string ***trojans, bool need_floor_empty, ofstream &output) {
	if (floor_number <= 0 || floor_number > floors) {
		output << "Error - floor " << floor_number << " does not exist" << endl;
		return false;
	} else {
		if (trojans[floor_number-1] != NULL && need_floor_empty) {
			output << "Error - floor " << floor_number << " is not empty" << endl;
			return false;
		} else if (trojans[floor_number-1] == NULL && !need_floor_empty) {
			output << "Error  floor " << floor_number << " is currently empty" << endl;
			return false;
		}
	}
	return true;
}

bool is_student_valid_on_floor(int student_number, int floor_number, int floors, int *floorsizes, string ***trojans, ofstream &output, bool need_possessions) {
	if (is_floor_valid(floor_number, floors, trojans, false, output)) {
		if (student_number <= 0 || student_number > floorsizes[floor_number-1]) {
			output << "Error - student " << student_number << " does not exist on floor " << floor_number << endl;
			return false;
		} else if (trojans[floor_number-1][student_number-1] != NULL && !need_possessions) {
			output << "Error - student " << student_number << " on floor " << floor_number << " already has possessions" << endl;
			return false;
		} else if (trojans[floor_number-1][student_number-1] == NULL && need_possessions) {
			output << "Error - student " << student_number << " on floor " << floor_number << " does not have possessions" << endl;
		}
		return true;
	} else {
		return false;
	}
}

void initialize_variables(string ***&trojans, int &floors, int *&floorsizes, int **&num_possessions, ifstream &input) {
	input >> floors;
  	trojans = new string**[floors];

  	floorsizes = new int[floors];
  	num_possessions = new int*[floors];

  	for (int i = 0; i < floors; i++) {
		floorsizes[i] = 0;
	  	trojans[i] = NULL;
	  	num_possessions[i] = NULL;
  	}

  	string garbageLine;
  	getline(input, garbageLine);
}

void move_in(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream &ss, ofstream &output) {
	int floor_number,num_students;
	ss >> floor_number;
	ss >> num_students;
	string garbageVal;
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		if (is_floor_valid(floor_number, floors, trojans, true, output)) {
		  	trojans[floor_number-1] = new string*[num_students];
			num_possessions[floor_number-1] = new int[num_students];
			for (int i=0; i<num_students; i++) {
				trojans[floor_number-1][i] = NULL;
				num_possessions[floor_number-1][i] = 0;
			} 	
			floorsizes[floor_number-1] = num_students;
		}
	}	  	 	
}

void move_out(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream &ss, ofstream &output) {
	int floor_number;
	ss >> floor_number;
	string garbageVal;
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		if (is_floor_valid(floor_number, floors, trojans, false, output)) {
			for (int i=0; i<floorsizes[floor_number-1]; i++) {
				if (trojans[floor_number-1][i] != NULL) {
					delete [] trojans[floor_number-1][i];
					trojans[floor_number-1][i] = NULL;
				}
			} 
			delete [] trojans[floor_number-1];
			trojans[floor_number-1] = NULL;

			delete [] num_possessions[floor_number-1];
			num_possessions[floor_number-1] = NULL;

			floorsizes[floor_number-1] - 0;	
		}
	}
}

void obtain_possessions(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream &ss, ofstream &output) {
	int floor_number, student_number, possessions;
	ss >> floor_number;
	ss >> student_number;
	ss >> possessions;
	if (ss.fail()) {
	  	output << "Error - incorrect command" << endl;
	} else {
	  	if (is_student_valid_on_floor(student_number, floor_number, floors, floorsizes, trojans, output, false)) {
	  		trojans[floor_number-1][student_number-1] = new string[possessions];
			num_possessions[floor_number-1][student_number-1] = possessions;
			for (int i=0; i<possessions; i++) {
				string n;
				ss >> n;
				trojans[floor_number-1][student_number-1][i] = n;
			}	
	  	}
	}  			
}

void output_possessions(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream& ss, ofstream &output) {
	int floor_number, student_number;
	ss >> floor_number;
	ss >> student_number;
	string garbageVal;
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		if (is_student_valid_on_floor(student_number, floor_number, floors, floorsizes, trojans, output, true)) {
	  		for (int i = 0; i < num_possessions[floor_number-1][student_number-1]; i++) {
	  			output << trojans[floor_number-1][student_number-1][i] << endl;
	  		}
		}
	}
}

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

  initialize_variables(trojans, floors, floorsizes, num_possessions, input);

  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  if (curr == "MOVEIN") {
		move_in(trojans, floors, num_possessions, floorsizes, ss, output);
	  } else if (curr == "MOVEOUT") {
		move_out(trojans, floors, num_possessions, floorsizes, ss, output);
	  } else if (curr == "OBTAIN") {
	  	obtain_possessions(trojans, floors, num_possessions, floorsizes, ss, output);
	  } else if (curr == "OUTPUT") {
	  	output_possessions(trojans, floors, num_possessions, floorsizes, ss, output);
	  }	else if (curr != "") {
	  	output << "Error - line does not begin with one of four commands: MOVEIN, MOVEOUT, OBTAIN, OUTPUT" << endl;
	  }
  }

  clear_building(floors, floorsizes, trojans, num_possessions);
  return 0;
}
