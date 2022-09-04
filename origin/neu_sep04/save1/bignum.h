//==========================================================================
//                           b i g n u m . h                
//==========================================================================
//     functions for big integer processing based on strings
//==========================================================================
// history : 
// 15-Jul-2002 : addsub 
// 17-Jul-2002 : addsub finished
// 19-Jul-2002 : character arrays used
// 21-Jul-2002 : mult started
// 23-Jul-2002 : mult finished
//               div started
// 25-Jul-2002 : div tested
// 28-Jul-2002 : div finished
// 29-Jul-2002 : tests added
// 30-Jul-2002 : euclid started
//  2-Aug-2002 : test euclid finished
//  4-Aug-2002 : begin bcd_binhex
//  6-Aug-2002 : bcd weiter
//  9-Aug-2002 : bcd weiter
// 10-Aug-2002 : bcd-binhex fertig, tests
// 11-Aug-2002 : bcd-binhex fertig, begin modexp
//               modexp fertig
//               test rsa243
// 15-Aug-2002 : new div version
// 16-Aug-2002 : new div version cont
// 17-Aug-2002 : new div test
// 19-Aug-2002 : rsa243 tested
// 20-Aug-2002 : more testing
// 22-Aug-2002 : more testing
//             : hex_bcd started 
// 25-Aug-2002 : how to speed up modexp ??? first ideas
// 27-Aug-2002 : modexpf tested, no large improvement 
// 31-Aug-2002 : more tested
//  1-Sep-2002 : what can be added : - hex_bcd must be added with test routine
//                                   - not forget to finish sign div slow .... ok
//                                   - a general routine for a^b modn
//                                   - ggT general
//                                   - prime generation with fermat and miller rabin test 
//                                   - add ifdef to remove test routines
//                                   - debug fuer add in adddebug aendern
//  7-Sep-2004 : hex_bcd und bcd_hex added
// 20-Sep-2004 : randbigint added, fermattest added
//==========================================================================
// available functions : 
//
// format of input data:
//    strcpy(z2, "894770000077777777777777777774440");
//    strcpy(z1, "-54894");
//
//    char *addsub( in1, in2, result,'+')
//    char *addsub( in1, in2, result,'-')
//    char *mult( z1, z2, result)
//    char *div( dividend, divisor, quotient, rest) .. dividend and divisor destroyed
//    char *divf( dividend, divisor, quotient, rest) .. fast version, dividend
//                                                      and divisor destroyed
//    char *modexp(a, b, n, res) ..... a destroyed
//    char *modexpf(a, b, n, res) .... faster version , a destroyed
//    char *euclidext(e, p, q, d) ... destroys ????;
//    char *bcd_binhex(in, outbin, outhex);
//    char *hex_bcd(inhex, outbcd) ...
//
//==========================================================================
#include <sys/types.h>
#include <sys/timeb.h>
#include <math.h>
#include <string.h>
#include <assert.h>
//
// this is the buffer length
//
#define ARRAYLENGTH 3000
//
// const int arrayl = ARRAYLENGTH;
//
// functions
//
  char *addsub1();
  char *addsub();
  char *mult();
  char *div();
  char *divf();
  char *divff();
  char *euclidext();
  char *modexp();
  char *modexpf();
  char *bcd_binhex();
  char *hex_bcd();
  char strchar();
  int substr();
  int randbigint();
  int fermattest();
//
typedef char verylong[ARRAYLENGTH]; 
//
//==========================================================================
