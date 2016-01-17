#include <iostream>
#include <fstream>
using namespace std;

void print_last(string * terms, int length) {
	if (length == 0) {
		return;
	} else {
		cout << terms[length-1] << endl;
		print_last(terms, length-1);
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

	int num_words;

	in_file >> num_words;

	if (in_file.fail()) {
		cerr << "File did not start with number of words!" << endl;
		return -1;
	}

	/*const char ** words = new const char*[num_words];
	//char temp_bufs */

	string * words = new string[num_words];
	for (int i=0; i<num_words; i++) {
		string word;
		in_file >> word; 
		if (in_file.fail()) {
			cerr << "Discrepancy between number of words listed at the top and actual number of words" << endl;
			return -1;
		}
		/*int length = word.length();
		words[i] = new char[length];
		words[i] = word.c_str();
		//words[i] = word.c_str(); */
		words[i] = word;
	}
 /*
	for (int i=0; i<num_words; i++) {
		cout << words[i] << endl;
		//delete [] words[i];
	}  */

	print_last(words, num_words);

	delete [] words;

}

