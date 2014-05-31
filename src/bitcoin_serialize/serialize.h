#ifndef BITCOIN_SERIALIZE_H
#define BITCOIN_SERIALIZE_H

#include <assert.h>

/******************************************************************************
 * Basic types
 ******************************************************************************/

#define WRITEDATA(s, obj)	s.write((char*)&(obj), sizeof(obj))
#define READDATA(s, obj)	s.read ((char*)&(obj), sizeof(obj))

/*******************************************************************************
 * unsigned int
 */
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

/*******************************************************************************
 * Templates for serializing to anything that looks like a stream,
 * i.e. anything that supports .read(char*, int) and .write(char*, int).
 */

class CSerActionGetSerializeSize { };
class CSerActionSerialize        { };
class CSerActionUnserialize      { };

template<typename Stream, typename T>
inline unsigned int SerReadWrite(Stream& s, const T& obj, int nType, int nVersion,
				 CSerActionGetSerializeSize ser_action)
{
	return ::GetSerializeSize(obj, nType, nVersion);
}

template<typename Stream, typename T>
inline unsigned int SerReadWrite(Stream& s, const T& obj, int nType, int nVersion,
				 CSerActionSerialize ser_action)
{
	::Serialize(s, obj, nType, nVersion);
	return 0;
}

template<typename Stream, typename T>
inline unsigned int SerReadWrite(Stream& s, T& obj, int nType, int nVersion,
				 CSerActionUnserialize ser_action)
{
	::Unserialize(s, obj, nType, nVersion);
	return 0;
}

struct ser_streamplaceholder
{
	int nType;
	int nVersion;
};

#define IMPLEMENT_SERIALIZE(statements)					\
	unsigned int GetSerializeSize(int nType, int nVersion) const	\
	{								\
		CSerActionGetSerializeSize ser_action;			\
		const bool fGetSize = true;				\
		const bool fWrite = false;				\
		const bool fRead = false;				\
		unsigned int nSerSize = 0;				\
		ser_streamplaceholder s;				\
		assert(fGetSize || fWrite || fRead);			\
		s.nType = nType;					\
		s.nVersion = nVersion;					\
		{statements}						\
		return nSerSize;					\
	}								\
	template<typename Stream>					\
	void Serialize(Stream &s, int nType, int nVersion) const	\
	{								\
		CSerActionSerialize ser_action;				\
		const bool fGetSize = false;				\
		const bool fWrite = true;				\
		const bool fRead = false;				\
		unsigned int nSerSize = 0;				\
		assert(fGetSize || fWrite || fRead);			\
		{statements}						\
	}								\
	template<typename Stream>					\
	void Unserialize(Stream& s, int nType, int nVersion)		\
	{								\
		CSerActionUnserialize ser_action;			\
		const bool fGetSize = false;				\
		const bool fWrite = false;				\
		const bool fRead = true;				\
		unsigned int nSerSize = 0;				\
		assert(fGetSize || fWrite || fRead);			\
		{statements}						\
	}

#define READWRITE(obj)							\
	(								\
		nSerSize += ::SerReadWrite(s, (obj), nType,		\
					   nVersion, ser_action)	\
	)

#endif // BITCOIN_SERIALIZE_H

