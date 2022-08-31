/*
 * BigInt.cc
 *
 *  Created on: 31.08.2022
 *      Author: martin
 */
#include "BigInt.h"
#include "bignum2.h"

namespace BigNum2 {

BigInt::BigInt()
: data( new vchar() )
{

}

BigInt::~BigInt()
{
	delete data;
}

BigInt::BigInt( const BigInt & other )
: data( new vchar( *other.data ) )
{

}

BigInt::BigInt( const char *number )
: data( new vchar( number ) )
{

}

BigInt & BigInt::operator=( const BigInt & other )
{
	*data = *other.data;
	return *this;
}

BigInt & BigInt::operator=( const char *number )
{
	strcpy( *data, number );
	return *this;
}

const char* BigInt::operator*() const
{
	return data->c_str();
}

BigInt & BigInt::operator+=( const BigInt & other )
{
	vchar buffer;
	addsub( *data, *other.data, buffer, '+' );
	strcpy( *data, buffer );
	return *this;
}

BigInt & BigInt::operator-=( const BigInt & other )
{
	vchar buffer;
	addsub( *data, *other.data, buffer, '-' );
	strcpy( *data, buffer );
	return *this;
}

BigInt & BigInt::operator*=( const BigInt & other )
{
	vchar buffer;
	mult( *data, *other.data, buffer );
	strcpy( *data, buffer );
	return *this;
}


} // namespace BigNum2
