/* 
   a dynamic string classes that emulates a char[] array string, by being dynamic 

   (C) 2002 by Martin Oberzalek under the terms of the GNU GPL

 ********************************************************************
 ********************************************************************

   implemented functions:

   printf()    // the function is limited to 4 parameters exclusiv of the
               // format string
   strcat()
   strcpy()
   strncpy()
   strcmp()
   strpbrk()
   strncmp()
   strlen()
   strchar()  // adopted and optimized from bignum2.cpp 

 **************************************

   Old C Code

 ***************************************

   void testx( cx, pos )
     char *cx;
     int  pos;
     {
       char *zahl1[ARRAYLENGTH];
       char *zahl2[ARRAYLENGTH];
       char *zahl3[ARRAYLENGTH];
       char *z1, *z2, *z3;

       strcpy( zahl1, "123456789" );
       strcpy( zahl2, "987654321" );

       z1 = zahl1;
       z2 = zahl2;
       z3 = zahl3;

       z3 = addsub( z1, z2, zahl3, '+' );

       printf( "zahl1: %s\n", z1 );
       printf( "zahl2: %s\n", z2 );
       printf( "zahl3: %s\n", z3 );


 ***************************************

   New C++ Style

 ***************************************

   void testx( pchar cx, int pos )
    {
       vchar zahl1;
       vchar zahl2;
       vchar zahl3;
       pchar z1, z2, z3;

       strcpy( zahl1, "123456789" );
       strcpy( zahl2, "987654321" );

       z1 = zahl1;
       z2 = zahl2;
       z3 = zahl3;

       z3 = addsub( z1, z2, zahl3, '+' );

       printf( "zahl1: %s\n", z1 );
       printf( "zahl2: %s\n", z2 );
       printf( "zahl3: %s\n", z3 );

   ---------------------------------------

   There are 3 changes:

   1) notation of function names
   2) vchar x   versus   char x[ARRAYLENGTH]
   3) pchar y   versus   char *y

 ***************************************

 */

#ifndef VCHAR_H
#define VCHAR_H

#include <vector>
#include "format.h"
#include <assert.h>

// #define DEBUG
#ifdef DEBUG
#  define BTT std::cout << format( "\t+ %s\n",  __PRETTY_FUNCTION__ );
#  define LTT std::cout << format( "\t- %s\n", __PRETTY_FUNCTION__ );
#else
#  define BTT
#  define LTT
#endif


using namespace std;

namespace BigNum2 {

class vchar;

/*
  Class BChar, a kind of virtual char, that checks if 
  operator[] was accessed for reading or writing.

  And if a '\0' character should be set to the buffer
  the length of the string will be set

  In normal cases you won't notice this class.
 */

class BChar
{
private:

	vchar *v;
	const int pos;

	BChar() = delete;

public:

	BChar( const vchar *v, int pos ) : v( const_cast<vchar*>(v)), pos(pos) {}

	inline void operator=(char c );
	inline operator char() const;
	inline char* operator&();
	inline const char* operator&() const;
	inline void operator=( const BChar &b );
};

/*
  Class that simulates a pointer to a buffer
  use it instead of char*
 */
class pchar
{
	vchar *data;
	int pos;
	bool c_data;

public:

	pchar() : data(0), pos(0), c_data( false) {};
	pchar( vchar &data ) : data( &data ), pos(0), c_data(false) {}
	pchar( const vchar &data ) : data( &(const_cast<vchar&>(data)) ), pos(0), c_data( false ) {}
	inline pchar( const char* s );
	pchar( const pchar &pc );
	inline ~pchar();

	void operator=( vchar &vc ) { data = &vc; pos = 0; }
	void operator=( const pchar &pc );
	void operator=( int n ) { data = (vchar*)n; }

	void operator++( int i ) { pos++; }
	void operator--( int i ) { pos--; }

	void operator++() { pos++; }
	void operator--() { pos--; }

	void operator+=( int i ) { pos += i; }
	void operator-=( int i ) { pos -= i; }

	inline BChar operator[]( int i );

	const BChar operator[] ( int i ) const;

	BChar operator*();
	const BChar operator*() const;

	vchar operator()() const;

	inline const vchar* get() const;
	unsigned int position() const { return pos; }

	bool has_c_data() const { return c_data; }

	friend bool operator==( const pchar &p, const void* n );
};


inline bool operator==( const pchar &p, const void* n )
		{
	return ( (void*)(p.data) == n );
		}

/*
  a dynamic character array ( char [] )
  handle it as a normal char array, use pchar for
  pointing to and inside the buffer
 */

class vchar
{
private:
	vector<char> buffer;

	mutable unsigned int len;
	mutable bool len_changed;

public:
	vchar() : len(0), len_changed( false ) {}
	explicit vchar( const char* s );
	~vchar() {}

	unsigned int size() const { return buffer.size(); }
	void resize( unsigned int nsize ) { buffer.resize( nsize ); }
	char* c_str() { return &buffer[0]; }
	const char* c_str() const { return &buffer[0]; }

	pchar operator*(){ return *this; }
	const pchar operator*() const { return *this; }

	BChar operator[]( int pos ) { return BChar( this, pos ); }
	const BChar operator[]( int pos ) const { return BChar( this, pos ); }

	unsigned int strlen( unsigned int startpos = 0 ) const
	{
		if( !len_changed )
			return len - startpos;

		unsigned int i = startpos;
		const unsigned int s = size();

		assert( startpos < s );

		const char *b = &buffer[startpos];

		for( ; i < s; ++i, ++b )
			if( *b == '\0' )
				break;

		len = i;
		len_changed = false;

		return i - startpos;
	}

	char& get_char( int pos )
	{
		len_changed = true;

		if( pos >= (int)size() )
			resize( pos + 5 );

		assert( pos >= 0 );

		return buffer[pos];
	}

	const char& get_const_char( int pos ) const
	{
		assert( pos < (int) size() );
		assert( pos >= 0 );

		return buffer[pos];
	}

	void set_strlen( unsigned int length ) const
	{
		len = length;
		len_changed = false;
	}
};


/*
  BChar inline functions
 */

inline void BChar::operator=( char c )
{
	v->get_char( pos ) = c;

	if( c == '\0' )
		v->set_strlen( pos );
}

inline BChar::operator char() const { return v->get_const_char( pos ); }
inline char* BChar::operator&() { return &(v->get_char( pos )); }
inline const char* BChar::operator&() const { return &(v->get_const_char( pos )); }

inline void BChar::operator=( const BChar &b ) 
{
	char c = b.v->get_const_char( b.pos );

	v->get_char( pos ) = c;

	if( c == '\0' )
		v->set_strlen( pos );
}

/*
  pchar inline functions
 */

inline BChar pchar::operator[]( int i )
{
	assert( data != 0 );
	assert( pos + i >= 0 );

	return (*data)[pos + i];
}

inline BChar pchar::operator*()
{
	assert( data != 0 );
	assert( pos >= 0 );

	return (*data)[pos];
}

inline pchar::pchar( const char *s )
: pos(0),
  c_data( true )
{
	data = new vchar( s );
}

inline pchar::~pchar()
{
	if( c_data )
		delete data;
}

inline const vchar* pchar::get() const 
{ 
	assert( data != 0 );

	return data;
}



/*
  strlen()
 */

inline unsigned int strlen( const vchar &vc ) { return vc.strlen(); }
inline unsigned int strlen( const pchar &pc ) { return pc.get()->strlen( pc.position() ); }
unsigned int strlen( const char *s );

/*
  strcpy()
 */

void strcpy( pchar &to, const pchar &from );

inline void strcpy( vchar &to, const vchar &from ) { to = from; }

inline void strcpy( vchar &to, const pchar &from ) 
{
	strcpy( to, from() );
}

inline void strcpy( vchar &to, const char *from )
{
	strcpy( to, vchar( from ) );
}

inline void strcpy( pchar &to, const char *from )
{
	const char *f = from;

	unsigned i;

	for( i = 0; *f != '\0'; ++i, f++ )
		to[i] = *f;

	to[i] = '\0';
}


/*
  strcat()
 */

const pchar& strcat( pchar &to, const pchar &from );

inline pchar strcat( vchar &to, const char *from )
{
	pchar pto = to;

	return strcat( pto, from );
}

inline pchar strcat( vchar &to, const vchar &from )
{
	pchar pto( to );
	pchar pfrom( from );

	return strcat( pto, pfrom );
}

inline const pchar& strcat( pchar &to, const char *from )
{
	pchar t1( to );

	t1 += strlen( to );

	strcpy( t1, from );

	return to;
}


/*
  strncpy()
 */

void strncpy( pchar &to, const pchar &from, unsigned int n );
void strncpy( char *, const pchar &from, unsigned int n );

/*
  strcmp()
 */

int strcmp( const pchar &a, const pchar &b );
int strcmp( const pchar &a, const char *b );

/*
  strncmp()
 */

int strncmp( const pchar &a, const pchar &b, unsigned int size );

/*
  strpbrk()
 */

pchar strpbrk( const pchar &s, const pchar &st );

/*
  strchar() // find a sign up to position pos
 */

char strchar( const pchar &s, int pos);

/*
  operator << for pchar
 */

inline std::ostream& operator<<( std::ostream &out, const pchar &p )
{
	return out << p().c_str();
}

/*
  operator << for vchar
 */

inline std::ostream& operator<<( std::ostream &out, const vchar &v )
{
	return out << v.c_str();
}

/*
  printf()
 */

template <typename... Args> void printf(  const std::string & format, Args... args )
{
	std::vector<Tools::Format2::BaseArg*> v_args;

	Tools::Format2::add_args( v_args, args... );

	Tools::Format2::Format2 f2( format, v_args );

	for( auto x: v_args )
	{
		delete x;
	}

	std::cout << f2.get_string();
}

} // namespace BigNum2

#endif
