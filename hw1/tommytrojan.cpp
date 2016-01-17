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
  string curr;

  input >> floors;
  trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  floorsizes = new int[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
  }
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
		  	 if (trojans[i] != NULL) {
		  	 	output << "Error - floor " << i << " is not empty" << endl;
		  	 } else if (i < 0 || i >= floors) {
		  	 	output << "Error - floor " << i << " does not exist" << endl;
		  	 } else {
		  	 	trojans[i] = new string*[k];
		  	 	for (int a = 0; a < k; a++) {
		  	 		trojans[i][a] = NULL;
		  	 	}
		  	 	floorsizes[i] = k;
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
			if (trojans[i] == NULL) {
				output << "Error -floor " << i << " is already empty" << endl;
			} else if (i < 0 || i >= floors) {
				output << "Error - floor " << i << " does not exist" << endl;
			} else {
				//DELETE
				for (int a = 0; a < floorsizes[i]; a++) {
					if (trojans[i][a] != NULL) {
						delete [] trojans[i][a];
					}
				}
				delete [] trojans[i];
			}
		}
	  }
	  else if (curr == "OBTAIN") {

	  }
	  else if (curr == "OUTPUT") {

	  }
	  else {

	  }
  }
  return 0;
}
