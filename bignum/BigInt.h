/*
 * BigInt.h
 *
 *  Created on: 31.08.2022
 *      Author: martin
 */

#ifndef SRC_BIGINT_H_
#define SRC_BIGINT_H_

#include <ostream>

namespace BigNum2 {

class vchar;

class BigInt
{
	vchar *data;

public:
	BigInt();
	BigInt( const BigInt & other );
	BigInt( const char *number );
	~BigInt();

	BigInt & operator=( const BigInt & other );
	BigInt & operator=( const char *number );

	const char* operator*() const;

	BigInt & operator+=( const BigInt & other );
	BigInt & operator-=( const BigInt & other );

	BigInt & operator*=( const BigInt & other );

};

inline BigInt operator+( const BigInt & a, const BigInt & b )
{
	BigInt res = a;
	res += b;
	return res;
}

inline BigInt operator-( const BigInt & a, const BigInt & b )
{
	BigInt res = a;
	res -= b;
	return res;
}

inline BigInt operator*( const BigInt & a, const BigInt & b )
{
	BigInt res = a;
	res *= b;
	return res;
}

inline std::ostream & operator<<( std::ostream & out, const BigInt & number )
{
	return out << *number;
}

} // namespace BigNum2


#endif /* SRC_BIGINT_H_ */
