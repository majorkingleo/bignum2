/*
 * BigInt.cc
 *
 *  Created on: 31.08.2022
 *      Author: martin
 */
#include "BigInt.h"
#include "bignum2.h"
#include <format.h>
#include <debug.h>

using namespace Tools;
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

BigInt::BigInt( int number )
: data( new vchar( format("%d", number ).c_str() ) )
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

BigInt & BigInt::operator+=( int amount )
{
	DEBUG( format( "%d += %d", *this, amount ));
	vchar buffer;
	addsub( *data, vchar(format("%d", amount).c_str()), buffer, '+' );
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

BigInt & BigInt::operator-=( int amount )
{
	vchar buffer;
	addsub( *data, vchar(format("%d", amount).c_str()), buffer, '-' );
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

BigInt & BigInt::operator/=( const BigInt & other )
{
	vchar result;
	vchar mod;
	vchar a( *(this->data) );
	vchar b( *(other.data) );
	div( a, b, result, mod );
	strcpy( *data, result );
	return *this;
}

bool BigInt::operator<=( const BigInt & other )
{
	if( *this == other ) {
		return true;
	}

	size_t len_a = strlen( *data );
	size_t len_b = strlen( *(other.data) );

	if( len_a < len_b ) {
		return true;
	}

	if( len_a > len_b ) {
		return false;
	}

	// DEBUG( format( "len_a: %d '%s' len_b: %d '%s'", len_a, *data, len_b, *other.data ) );

	for( ssize_t pos = len_a-1; pos >= 0; pos-- ) {
		char sign_a = data->get_const_char(pos);
		char sign_b = other.data->get_const_char(pos);

		// DEBUG( format( "pos: %d sign_a: %c sign_b: %c", pos, sign_a, sign_b ) );

		if( sign_a > sign_b ) {
			return false;
		}

		if( sign_a < sign_b ) {
			return true;
		}
	}

	assert(0); // should never been reached
	return false;
}

BigInt operator-( const BigInt & other )
{
	BigInt buf( other );
	buf *= BigInt("-1");
	return buf;
}

bool operator==( const BigInt & a, const BigInt & b )
{
	if( strcmp( *a.getData(), *b.getData() ) == 0 ) {
		return true;
	}

	return false;
}

BigInt faculty( const BigInt & other )
{
	BigInt res = "1";

	for( BigInt i = "2"; i <= other; ++i ) {
		// DEBUG( format( "i: %d", i ));
		res *= i;
	}

	return res;
}

} // namespace BigNum2
