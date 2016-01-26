/**
  * Name: Mitali Karmarkar
  * USC ID: 6162824079
  * Instructor: Aaron Cote T/Th 3:30
  * HW1: Palindrome.cpp 
  */

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std; 

/** helper The function that checks whether a string is a palindrome 
 * @param stringstream &input A reference to a stringstream parsing the commandline
 * @param int len The length of the palindrome
 * @return True if the string is a palindrome, false otherwise 
 */
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
		//if val is a palindrome, compare the characters before (input) and after (temp) val to 
		//see if that combination of characters is a palindrome
		char temp;
		input >> temp;
		return prev==temp;
	} 
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
