#ifndef BITCOIN_CORE_H
#define BITCOIN_CORE_H

class CTransaction
{
public:
	unsigned int nLockTime;

	IMPLEMENT_SERIALIZE
	(
		READWRITE(nLockTime);
	)
};

#endif // BITCOIN_CORE_H

