#ifndef BITCOIN_SERIALIZE_FLAT_DATA_H
#define BITCOIN_SERIALIZE_FLAT_DATA_H

#include <iostream>

using namespace std;

class CFlatData
{
protected:
	char* pbegin;
	char* pend;

public:
	CFlatData(void* pbeginIn, void* pendIn)
		: pbegin((char*)pbeginIn), pend((char*)pendIn)
	{
		// empty
	}

	char* begin()
	{
		return pbegin;
	}

	const char* begin() const
	{
		return pbegin;
	}

	char* end()
	{
		return pend;
	}

	const char* end() const
	{
		return pend;
	}

	void self_print()
	{
		unsigned char* it = (unsigned char*)pbegin;
		int len = pend - pbegin;

		cout << "Len = " << len << endl;

		for (int i = 0; i < len; i++)
			printf("%02x ", (unsigned int)(it[i]));

		cout << endl;
	}

	unsigned int GetSerializeSize(int, int = 0) const
	{
		return pend - pbegin;
	}

	template<typename Stream>
	void Serialize(Stream& s, int, int = 0) const
	{
		s.write(pbegin, pend - pbegin);
	}

	template<typename Stream>
	void Unserialize(Stream& s, int, int = 0)
	{
		s.read(pbegin, pend - pbegin);
	}
};

template<typename T>
inline T& REF(const T& val)
{
	return const_cast<T&>(val);
}

#define FLATDATA(obj) \
	REF(CFlatData((char *)&(obj), (char *)&(obj) + sizeof(obj)))

inline unsigned int GetSerializeSize(const CFlatData& flatData, int, int = 0)
{
	return flatData.GetSerializeSize(0, 0);
}

template<typename Stream>
inline void Serialize(Stream& s, const CFlatData& flatData, int, int = 0)
{
	flatData.Serialize(s, 0, 0);
}

template<typename Stream>
inline void Unserialize(Stream& s, CFlatData& flatData, int, int = 0)
{
	flatData.Unserialize(s, 0, 0);
}

#endif // BITCOIN_SERIALIZE_FLAT_DATA_H

