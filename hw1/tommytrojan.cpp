/**
  * Name: Mitali Karmarkar
  * USC ID: 6162824079
  * Instructor: Aaron Cote T/Th 3:30
  * HW1: TommyTrojan.cpp 
  */

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/** is_floor_valid A helper function that checks if the floor is a valid one for further 
  * manipulations in the building and outputs appropriate error messages
  * @param int floor_number The floor in the building under consideration
  * @param int floors Number of floors in the building
  * @param string ***trojans The 3D array of the possessions of the students on the floor
  * @param bool need_floor_empty Whether the calling function needs the floor to be empty
  * @param ofstream &output A parameter referring to the output stream
  * @return bool False if the floor is invalid, True otherwise
  */
bool is_floor_valid(int floor_number, int floors, string ***trojans, bool need_floor_empty, 
			ofstream &output) {
	//checking to see if the floor number is within the range of the building
	if (floor_number <= 0 || floor_number > floors) {
		output << "Error - floor " << floor_number << " does not exist" << endl;
		return false;
	} else {
		//if the floor needs to be empty for the calling function, checking to see if the floor 
		//not empty
		if (trojans[floor_number-1] != NULL && need_floor_empty) {
			output << "Error - floor " << floor_number << " is not empty" << endl;
			return false;
		//if the floor needs to be occupied for the calling function, checking to see if the 
	    //floor is empty
		} else if (trojans[floor_number-1] == NULL && !need_floor_empty) {
			output << "Error  floor " << floor_number << " is currently empty" << endl;
			return false;
		}
	}
	return true;
}

/** is_student_valid_on_floor A helper function that checks if the given student is valid on the given floor for further manipulations in the building and outputs appropriate error messages
  * @param int student_number The index referring to the student under consideration
  * @param int floor_number The floor in the building under consideration
  * @param int floors Number of floors in the building
  * @param int *floorsizes An array keeping track of the number of students on each floor
  * @param string ***trojans The 3D array of the possessions of the students on the floor
  * @param ofstream &output A parameter referring to the output stream
  * @param bool need_possessions Whether the calling function needs the student to have possessions
  * @return bool False if the student is invalid, True otherwise
  */
bool is_student_valid_on_floor(int student_number, int floor_number, int floors, int *floorsizes, 
			string ***trojans, ofstream &output, bool need_possessions) {
	//if the floor is valid, check the conditions for the student
	if (is_floor_valid(floor_number, floors, trojans, false, output)) {
		//checking to see if the student index is within the range of the building
		if (student_number <= 0 || student_number > floorsizes[floor_number-1]) {
			output << "Error - student " << student_number << " does not exist on floor " 
				<< floor_number << endl;
			return false;
		//if the student should not have possessions for the calling function, checking to see 
		//if the student has possessions
		} else if (trojans[floor_number-1][student_number-1] != NULL && !need_possessions) {
			output << "Error - student " << student_number << " on floor " << floor_number 
				<< " already has possessions" << endl;
			return false;
		//if the student should have possessions for the calling function, checking to see if 
		//the student does not have possessions
		} else if (trojans[floor_number-1][student_number-1] == NULL && need_possessions) {
			output << "Error - student " << student_number << " on floor " << floor_number 
				<< " does not have possessions" << endl;
		}
		return true;
	} else {
		return false;
	}
}

/** initialize_variables A function that intializes all the values of the variables declared at 
  * the top of main
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions of 
  * the students on each floor
  * @param int &floors A reference to the number of floors in the building
  * @param int *&floorsizes A reference to the array keeping track of the number of students on 
  * each floor
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number of 
  * possessions each student has on each floor
  * @param ifstream &input A parameter referring to the input stream
  */
void initialize_variables(string ***&trojans, int &floors, int *&floorsizes, 
			int **&num_possessions, ifstream &input) {
	//initialize all the arrays to hold the information for the given number of floors
	input >> floors;
  	trojans = new string**[floors];
  	floorsizes = new int[floors];
  	num_possessions = new int*[floors];

  	//set further dimensions of the arrays to 0 or NULL, signifying an empty building
  	for (int i = 0; i < floors; i++) {
		floorsizes[i] = 0;
	  	trojans[i] = NULL;
	  	num_possessions[i] = NULL;
  	}

  	//read the line that has the number of floors 
  	string garbageLine;
  	getline(input, garbageLine);
}

/** move_in A function in which students move in on a given floor if possible
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions of
  * the students on each floor 
  * @param int floors The number of floors in the building
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number of 
  * possessions each student has on each floor
  * @param int *&floorsizes A reference to the array keeping track of the number of students on 
  * each floor
  * @param stringstream &ss A reference to the stringstream that parses through each line of the 
  * input file
  * @param ofstream &output A reference to the output stream
  */
void move_in(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, 
			stringstream &ss, ofstream &output) {
	//collect information on the number of students who want to move in on the given floor
	int floor_number, num_students;
	ss >> floor_number;
	ss >> num_students;
	string garbageVal;
	//print an error if the input is provided in an incorrect format
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		//check to see if the input numbers are valid
		if (is_floor_valid(floor_number, floors, trojans, true, output)) {
		  	//dynamically allocate memory for the given number of students and set the values 
		  	//to 0 or NULL
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

/** move_out A function in which students move out on a given floor if possible
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions of
  * the students on each floor 
  * @param int floors The number of floors in the building
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number of 
  * possessions each student has on each floor
  * @param int *&floorsizes A reference to the array keeping track of the number of students on 
  * each floor
  * @param stringstream &ss A reference to the stringstream that parses through each line of the 
  * input file
  * @param ofstream &output A reference to the output stream
  */
void move_out(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream &ss, ofstream &output) {
	//collect information on the floor that is supposed to be evacuated
	int floor_number;
	ss >> floor_number;
	string garbageVal;
	//print an error if the input is provided in an incorrect format
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		//check to see if the input number is valid
		if (is_floor_valid(floor_number, floors, trojans, false, output)) {
			//deallocate the memory dynamically allocated for the floor
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

/** obtain_possessions A function in which a given student on a given floor receives possessions 
  * if possible 
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions of 
  * the students on each floor 
  * @param int floors The number of floors in the building
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number of 
  * possessions each student has on each floor
  * @param int *&floorsizes A reference to the array keeping track of the number of students on 
  * each floor
  * @param stringstream &ss A reference to the stringstream that parses through each line of the 
  * input file
  * @param ofstream &output A reference to the output stream
  */
void obtain_possessions(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes,
			stringstream &ss, ofstream &output) {
	//collect information on the student that is supposed to obtain possessions
	int floor_number, student_number, possessions;
	ss >> floor_number;
	ss >> student_number;
	ss >> possessions;
	//print an error if the input is provided in an incorrect format 
	if (ss.fail()) {
	  	output << "Error - incorrect command" << endl;
	} else {
		//check to see if the input numbers are valid
	  	if (is_student_valid_on_floor(student_number, floor_number, floors, floorsizes, trojans, output, false)) {
	  		//allocate memory for the number of possessions and update other variables accordingly
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

/** output_possessions A function that prints the possessions of a given student on a given 
  * floor if possible
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions 
  * of the students on each floor 
  * @param int floors The number of floors in the building
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number of 
  * possessions each student has on each floor
  * @param int *&floorsizes A reference to the array keeping track of the number of students on 
  * each floor
  * @param stringstream &ss A reference to the stringstream that parses through each line of the 
  * input file
  * @param ofstream &output A reference to the output stream
  */
void output_possessions(string ***&trojans, int floors, int **&num_possessions, int *&floorsizes, stringstream& ss, ofstream &output) {
	//collect information on the student whose possessions are to be printed out
	int floor_number, student_number;
	ss >> floor_number;
	ss >> student_number;
	string garbageVal;
	//print an error if the input is provided in an incorrect format
	if (ss.fail() || ss >> garbageVal) {
		output << "Error - incorrect command" << endl;
	} else {
		//check to see if the input numbers are valid
		if (is_student_valid_on_floor(student_number, floor_number, floors, floorsizes, 
			trojans, output, true)) {
	  		//print out the students possessions
	  		for (int i = 0; i < num_possessions[floor_number-1][student_number-1]; i++) {
	  			output << trojans[floor_number-1][student_number-1][i] << endl;
	  		}
		}
	}
}

/** clear_building A function that evacuates the entire building, deleting all blocks of memory 
  * used on the heap
  * @param int floors The number of floors in the buildingg
  * @param string ***&trojans A reference to the 3D array that keeps track of the possessions 
  * of the students on each floor 
  * @param int *&floorsizes A reference to the array keeping track of the number of students 
  * on each floor
  * @param int **&num_possessions A reference to the 2D array that keeps track of the number 
  * of possessions each student has on each floor
  */
void clear_building(int floors, int* &floorsizes, string ***&trojans, int **&num_possessions) {
	for (int i=0; i<floors; i++) {
	  	//clear all possessions on each floor
	  	for (int j=0; j<floorsizes[i]; j++) {
	  		if (trojans[i] != NULL && trojans[i][j] != NULL) {
	  			delete [] trojans[i][j];
	  			trojans[i][j] = NULL;
	  		}
	  	}
	  	//delete the floor itself
	  	if (trojans[i] != NULL) {
	  		delete [] trojans[i];
	  		trojans[i] = NULL;

	  		delete [] num_possessions[i];
	  		num_possessions[i] = NULL;
	  	}
	}

	//delete the building and the bookkeeping arrays
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

  //declare all variables
  int floors;
  int *floorsizes;
  string ***trojans;
  int **num_possessions;
  string curr;

  //initialize variables
  initialize_variables(trojans, floors, floorsizes, num_possessions, input);

  while(getline(input, curr)) {
	  //read each line of the input file and act accordingly
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
	  	output << "Error - line does not begin with one of four commands: MOVEIN, MOVEOUT, 
	  			OBTAIN, OUTPUT" << endl;
	  }
  }

  clear_building(floors, floorsizes, trojans, num_possessions);
  return 0;
}
