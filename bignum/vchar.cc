#include "vchar.h"

#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace BigNum2 {

/*
  vchar stuff
*/

vchar::vchar( const char* s )
{
  BTT;  

  len = std::strlen( s );
  len_changed = false;

  if( len >= size() )
    resize( len + 100 );

  for( unsigned int i = 0; i <= len; ++i )
    {
      buffer[i] = s[i];
    }

  LTT;
}

/*
  pchar stuff
*/

pchar::pchar( const pchar &pc )
  : pos(pc.pos),
    c_data(pc.c_data)
{
  if( pc.c_data )
    data = new vchar( *pc.data );
  else
    data = pc.data;
}

void pchar::operator=( const pchar &pc )
{
  if( c_data )
    delete data;

  c_data = pc.c_data;
  pos = pc.pos;
  
  if( pc.c_data )
    data = new vchar ( *pc.data );
  else
    data = pc.data;
}

const BChar pchar::operator[]( int i ) const
{
  assert( data != 0 );
  assert( pos + i >= 0 );

  const vchar *d = data;

  return (*d)[pos + i];
}

const BChar pchar::operator*() const
{
  BTT;

  assert( data != 0 );
  assert( pos >= 0 );

  const vchar *d = data;

  LTT;

  return (*d)[pos];
}

vchar pchar::operator()() const 
{
  BTT;

  assert( data != 0 );

  vchar ret;

  const vchar *d = data;

  //  const unsigned int len = strlen( *data );

  const char *f = &(*d)[pos];

  //  printf( "len: %s\n", len );

  //  assert( len < 100 );

  unsigned int i;

  for(  i = 0; *f != '\0'; ++i, f++ )
    ret[i] = *f;

  ret[i] = '\0';

  LTT;

  return ret;
}

/*
  strlen()
*/

unsigned int strlen( const char *s )
{
  unsigned i = 0;

  while( s[i] != '\0' )
    ++i;

  return i;
}

/*
  strcpy()
*/

void strcpy( pchar &to, const pchar &from )
{
  BTT;

  const char *f = &from[0];

  unsigned i;

  for( i = 0; *f != '\0'; ++i, f++ )
    to[i] = *f;

  to[i] = '\0';

  LTT;
}

/*
  strncpy()
*/

void strncpy( pchar &to, const pchar &from, unsigned int n )
{
  const unsigned int len = strlen( from );

  for( unsigned int i = 0; i <= len && i < n; ++i )
    to[i] = from[i];

  for( unsigned int i = len; i < n; ++i )
    to[i] = '\0';  
}

void strncpy( char *to, const pchar &from, unsigned int n )
{
  const char *f = &from[0];

  unsigned int i;

  for( i = 0; f[i] != '0' && i < n; ++i )
    to[i] = f[i];

  for( ; i < n; ++i )
    to[i] = '\0';  
}

/*
  strncmp()
*/

int strcmp( const pchar &a, const pchar &b )
{
  const char* sa = &a[0];
  const char* sb = &b[0];

  while( ( *sa != '\0' ) && 
	 ( *sb != '\0' ) && 
	 ( *sa == *sb ) )
    {
      sa++; 
      sb++;
    }

  if( ( *sa == '\0' ) && ( *sb != '\0' ) )
    return -1;

  if( (  *sb == '\0' ) && ( *sa != '\0' ) )
      return 1;

  return *sa - *sb;

}

int strncmp( const pchar &a, const pchar &b, unsigned int size )
{
  BTT;

  unsigned int i = 0;

  const unsigned int sa = strlen(a);
  const unsigned int sb = strlen(b);

  while( ( i < sa ) && 
	 ( i < sb ) && 
	 ( a[i] == b[i] ) )
    {
      if( i >= size )
	{
	  LTT;
	  return 0;
	}

      ++i;
    }

  if( (i == sa - 1) && ( i < sb ) )
    {
      LTT;
      return -1;
    }

  if( ( i == sb -1) && ( i < sa ) )
    {
      LTT;
      return 1;
    }

  LTT;
  return a[i] - b[i];
}


/*
  strcmp()
*/

int strcmp( const pchar &a, const char *b )
{
  BTT;
  LTT;

  return strcmp( a, vchar( b ) );
}

/*
  strcat()
*/

const pchar& strcat( pchar &to, const pchar &from )
{
  BTT;

  pchar t1 = to;

  t1 += strlen( to );

  strcpy( t1, from );

  LTT;

  return to;
}

/*
  strpbrk()
*/

pchar strpbrk( const pchar &s, const pchar &st )
{
  const char *as = &s[0];
  const char *bs = &st[0];
  const char *pbs = bs;

  for( int i  = 0; *as != '\0'; ++as, ++i )
    for( bs = pbs; *bs != '\0'; bs++ )
      if( *as == *bs )
	{
	  pchar ret( s );
	  ret += i;

	  return ret;
	}

  return pchar();
}

/*
  strchar()
*/

char strchar( const pchar &s, int pos) 
{
/*
  // old code (use of strlen())
  
  int n,i;
  pchar p;
  char out;
  n = strlen(s);
  // printf("n,p %d %d\n", n, pos);
  p = s;
  p--;
  for(i=1; i<=n; i++){
    p++;
    if( i == pos) break;
    // printf("i=%d %s\n",i,p);
  }
  out = *p; 
  // printf("out %c\n",out);
  return out;
*/

  const char *p = &s[0];
  char out;
  
  for(int i=1; i <= pos && *p != '\0'; i++, p++);
  
  out = *p; 
  
  return out;
}

} // namespace BigNum2
