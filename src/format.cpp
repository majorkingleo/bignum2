#include "format.h"

void Format::CFormat::reset()
{
  valid = false;
  adjust = RIGHT;
  special = false;
  precision = 6;
  precision_explicit = false;
  zero = false;
  sign = false;
  width = 0;
  internal = false;
  setupper = false;
  grouping = false;
  conversion = false;
  base = DEC;
  floating = FIXED;
  showbase = false;
}

int Format::skip_atoi( std::string s, ST start, ST& pos )
{
  pos = start;
  ST len = s.size();
  
  while( (pos < len) && isdigit( s[pos] ) )
    pos++;
  
  return atoi( s.substr( start, start-pos ).c_str() );
}

void Format::CFormat::set( std::ostream& out )
{
  if( !valid )
    {
      return;
    }

  switch( adjust )
    {
    case LEFT: out.setf( std::ios::left, std::ios::adjustfield ); break;
    case RIGHT: out.setf( std::ios::right, std::ios::adjustfield ); break;
    }

  if( zero ) out << std::setfill('0');
  else out << std::setfill( ' ' );
    
  if( sign ) out.setf( std::ios::showpos );
    else out.unsetf( std::ios::showpos );

  if( internal ) 
    out.setf( std::ios::internal, std::ios::adjustfield );
  
  switch( base )
    {
    case OCT: out.setf( std::ios::oct, std::ios::basefield ); break;
    case DEC: out.setf( std::ios::dec, std::ios::basefield ); break;
    case HEX: out.setf( std::ios::hex, std::ios::basefield ); break;
    }

  if( setupper ) out.setf( std::ios::uppercase );
  else out.unsetf( std::ios::uppercase );

  switch( floating )
    {
    case FIXED: out.setf( std::ios::fixed, std::ios::floatfield ); break;
    case SCIENTIFIC: out.setf( std::ios::scientific, std::ios::floatfield ); break;
    }

  if( showbase )
    out.setf( std::ios::showbase );
  else
    out.unsetf( std::ios::showbase );

  out << std::setw( width );
  out << std::setprecision( precision );
}
