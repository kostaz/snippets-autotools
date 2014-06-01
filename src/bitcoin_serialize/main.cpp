#include <iostream>
#include <fstream>
#include <stdint.h>

#include "serialize.h"
#include "core.h"

using namespace std;

void test_serialize_transaction()
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
	ofile.open("serialize_transaction.test");

	cout << "Calling to tx1.Serialize(0, 0)" << endl;
	tx1.Serialize(ofile, 0, 0);
	ofile.close();

	/*
	 * Unserialize
	 */
	CTransaction tx2;
	ifstream ifile;
	ifile.open("serialize_transaction.test");

	cout << "Calling to tx2.Unserialize(0, 0)" << endl;
	tx2.Unserialize(ifile, 0, 0);
	ifile.close();

	cout << hex << "tx2.nLockTime = " << tx2.nLockTime << endl;
}

void test_serialize_outpoint()
{
#if 1
	COutPoint outPoint1;

	cout << "sizeof(uint256)  = " << sizeof(outPoint1.hash) << endl;
	cout << "sizeof(outPoint) = " << sizeof(outPoint1) << endl;

	outPoint1.hash = uint64_t(0x123456789abc);
	outPoint1.n = 0xbeafdead;

	cout << "Calling hash.self_print(): " << endl;
	outPoint1.hash.self_print();

	CFlatData fd1((char*)&outPoint1.hash, (char*)&outPoint1.hash + sizeof(outPoint1.hash));
	cout << "Calling fd1.self_print(): " << endl;
	fd1.self_print();

	CFlatData fd2((char*)(&outPoint1), (char*)(&outPoint1) + sizeof(outPoint1));
	cout << "Calling fd2.self_print(): " << endl;
	fd2.self_print();
#endif

#if 1
	/*
	 * Serialize
	 */
	ofstream ofile;
	ofile.open("serialize_out_point.test");

	cout << "Calling to outPoint1.Serialize(0, 0)" << endl;
	outPoint1.Serialize(ofile, 0, 0);
	ofile.close();
#endif

#if 0
	int n = 0x12345678;
	cout << "int n = 0x" << hex << n << endl;
	cout << "sizeof(int) = " << sizeof(int) << endl << endl;
	cout << "*((unsigned char *)(&n))     = " << hex << int(*((unsigned char *)(&n))) << endl;
	cout << "*((unsigned char *)(&n) + 1) = " << hex << int(*((unsigned char *)(&n) + 1)) << endl;
	cout << "*((unsigned char *)(&n) + 2) = " << hex << int(*((unsigned char *)(&n) + 2)) << endl;
	cout << "*((unsigned char *)(&n) + 3) = " << hex << int(*((unsigned char *)(&n) + 3)) << endl;

	ofstream ofile;
	ofile.open("serialize_int.test");

	cout << "print int byte-by-byte: 0x";
	unsigned char* pc = (unsigned char*)&n;
	for (int i = 0; i < sizeof(int); i++) {
		ofile << pc[i];
	}
	ofile.close();
	cout << endl;
#endif
}

int main()
{
	// test_serialize_transaction();
	test_serialize_outpoint();
	return 0;
}

