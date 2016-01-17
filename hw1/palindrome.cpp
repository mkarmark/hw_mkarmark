/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std;

bool helper(stringstream &input, int len)
{
	char prev;

	//if we are at the midpoint of the string, return true.
	if (len == 0) return true;

	/**
	 * If the length of the string is odd, and the next
	 * character is the midpoint of the string, consume it
	 * and return true.
	 */
	input >> prev;
	//cerr << prev << endl;
	if (len == 1) return true;

	bool val = helper(input, len-2);

	//make your changes below this line.
	if (val) {
		char temp;
		input >> temp;
		//cerr << "Starting letter: " << temp << endl;
		//cerr << "Length: " << len << endl;
		/*for (int i=1; i<3; i++) {
			input >> temp;
			cerr << "temp " << temp << ", ";
		} */
		//cerr << "Prev: " << prev << " Temp: " << temp << endl;
		return prev==temp;
	} //return true;
	return false;
}

//do not change the main function.
int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters." << endl;
    return 1;
  }
  stringstream ss;
  ss << argv[1];
  if(helper(ss, strlen(argv[1])))
	  cout << "Palindrome" << endl;
  else cout << "Not a Palindrome" << endl;
  return 0;
}
