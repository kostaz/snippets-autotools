#ifndef BITCOIN_CORE_H
#define BITCOIN_CORE_H

#include "uint256.h"
#include "serialize.h"

class COutPoint
{
public:
	uint256 hash;
	unsigned int n;

	IMPLEMENT_SERIALIZE
	(
		READWRITE(FLATDATA(*this));
	)
};

class CTransaction
{
public:
	unsigned int nVersion;
	unsigned int nLockTime;

	IMPLEMENT_SERIALIZE
	(
		READWRITE(this->nVersion);
		nVersion = this->nVersion;
		READWRITE(nLockTime);
	)
};

#endif // BITCOIN_CORE_H

