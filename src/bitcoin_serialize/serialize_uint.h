#ifndef BITCOIN_SERIALIZE_UINT_H
#define BITCOIN_SERIALIZE_UINT_H

inline unsigned int GetSerializeSize(unsigned int a, int, int = 0)
{
	return sizeof(a);
}

template<typename Stream>
inline void Serialize(Stream& s, unsigned int a, int, int = 0)
{
	WRITEDATA(s, a);
}

template<typename Stream>
inline void Unserialize(Stream& s, unsigned int& a, int, int = 0)
{
	READDATA(s, a);
}

#endif // BITCOIN_SERIALIZE_UINT_H

