#include <iostream>
#include <string>
#include <fstream>
#include "VECTOR.H"

using std::cout;
using std::ifstream;
using std::endl;

const std::string TEST_FILE = ".txt";

int main()
{
	ifstream file(TEST_FILE.c_str());
	
	if (file.bad())
		return -1;
	
	Vector<T> vec;
	
	return 0;
}