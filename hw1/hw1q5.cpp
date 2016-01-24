/**
  * Name: Mitali Karmarkar
  * USC ID: 6162824079
  * Instructor: Aaron Cote T/Th 3:30
  * HW1: Hw1q5.cpp 
  */

#include <iostream>
#include <fstream>
using namespace std;

/** print_backwards A function that recursively reads words from a file and prints them backwards
  * @param ifstream &in_file A reference to an input reader that reads words from the file
  * @param int length The number of words in the file
  */
void print_backwards(ifstream &in_file, int length) {
	//base case
	if (length == 0) {
		return;
	}
	//keep reading in the words until there is nothing more to read
	string word;
	in_file >> word;
	print_last(in_file, length-1);

	//unless word is a delimiter, print it
	if (word != "\n" && word != "\t" && word != " " && word != "") {
		cout << word << endl;
	}
}

int main(int argc, char * argv[]) { 
	if (argc != 2) {
		cerr << "Incorrect command line argument format!" << endl;
		cerr << "Correct format: Program_name File_name" << endl;
	}

	char *file_name = argv[1];

	ifstream in_file;
	in_file.open(file_name);

	//incorrect file
	if (in_file.fail()) {
		cerr << "File does not exist" << endl;
	} else {
		int num_words;

		in_file >> num_words;

		if (in_file.fail()) {
			cerr << "File did not start with number of words!" << endl;
			return -1;
		}

		print_backwards(in_file, num_words);
	}
}

