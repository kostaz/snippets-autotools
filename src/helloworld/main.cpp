#include <iostream>

using namespace std;

int main()
{
	cout << __func__ << ": " << __LINE__ << ": ENTER." << endl;
	cout << "Hello world!" << endl;
	cout << __func__ << ": " << __LINE__ << ": EXIT." << endl;
	return 0;
}

