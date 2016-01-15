#include <iostream>
#include <fstream>
using namespace std;

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

	char ** words = new char*[num_words];
	for (int i=0; i<num_words; i++) {
		string word;
		in_file >> word;
		int length = word.length();
		words[i] = new char[length];
		words[i] = word.c_str();
		//words[i] = word.c_str();
	}

	for (int i=0; i<num_words; i++) {
		cout << words[i] << endl;
		delete [] words[i];
	} 


	delete [] words;

}