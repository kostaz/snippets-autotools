#include <iostream>
#include <fstream>

#include "serialize.h"
#include "core.h"

using namespace std;

int main()
{
	CTransaction tx1;

	tx1.nLockTime = 0xbeaf1122;
	cout << hex << "tx1.nLockTime = " << tx1.nLockTime << endl;

	/*
	 * Check serialize size
	 */
	cout << "tx1.GetSerializeSize(0, 0) = " << tx1.GetSerializeSize(0, 0) << endl;

	/*
	 * Serialize
	 */
	ofstream ofile;
	ofile.open("serialize.test");

	cout << "Calling to tx1.Serialize(0, 0)" << endl;
	tx1.Serialize(ofile, 0, 0);
	ofile.close();

	/*
	 * Unserialize
	 */
	CTransaction tx2;
	ifstream ifile;
	ifile.open("serialize.test");

	cout << "Calling to tx2.Unserialize(0, 0)" << endl;
	tx2.Unserialize(ifile, 0, 0);
	ifile.close();

	cout << hex << "tx2.nLockTime = " << tx2.nLockTime << endl;

	return 0;
}

