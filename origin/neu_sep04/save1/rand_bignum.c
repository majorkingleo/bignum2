//==========================================================================
//                standard main program for bignum
//==========================================================================
//  functions for big integer processing based on strings
//==========================================================================
// Date : 20-Sep-04
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
//                                                  and divisor destroyed
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
#include "../lib/bignum.h"
//
// functions
//
//  char *addsub1();
//  char *addsub();
//  char *mult();
//  char *div();
//  char *divf();
//  char *divff();
//  char *euclidext();
//  char *modexp();
//  char *modexpf();
//  char *bcd_binhex();
//  char *hex_bcd();
//  int substr();
//  char strchar();
//
// test functions
//---------------------------------------------
//
// bcd_binhex
//  void test5();
// hex_bcd
//  void test5_1();
//  void test5_2();
//
//==========================================================================
main(argc,argv)
 int argc;
 char *argv[];
 {
  //char name[100];
  //int j;
  // typedef char verylong[arrayl]; 

  int arrlen = ARRAYLENGTH;
  int iterations, a_ll;

  //char zahl2[ARRAYLENGTH] = "7419043440758059956596";
  //char zahl1[ARRAYLENGTH] = "452317331723962514217511611516823866219980863312";
  //char zahl1[ARRAYLENGTH] ;
  //char zahl2[ARRAYLENGTH] ;
  //char p[ARRAYLENGTH] ;
  //char q[ARRAYLENGTH] ;
  //char e[ARRAYLENGTH] ;
  //char n[ARRAYLENGTH] ;

  verylong prime_random,prime_for_test;
  verylong p,q,e,n,dividend,divisor,quotient,rest;

  //verylong zahl1,zahl2,zahl3,zahl4;
  //char *z1, *z2, *z3, *z4;
  //char *p1;

  printf(" Large Integer numbers :\n");
  printf("========================\n");
  printf("Compiled with buffer length : %d\n", arrlen);

//   z1 = zahl1;
//   z2 = zahl2;
//   z3 = zahl3;
//   z4 = zahl4;

//---------------------------------------------
//
// initialize random generator
//
  srand( (unsigned) time( NULL));
//
//=======================================================================
//#define TEST0
#ifdef TEST0
// randtest
//-----------
  randlength = 500 ;
   for(ii=1; ii< 7; ii++) {
     randbigint( randall, randlength);
     printf(" randint : %s\n", randall);
   }
#endif
//=======================================================================
//#define TEST7
#ifdef TEST7
// rsa155
  strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
  strcpy( prime_for_test, q) ;
  iterations = 5 ;
  a_ll = 15;
  fermattest( prime_for_test, iterations, a_ll); 
  strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
  strcpy( dividend, n);
  strcpy( divisor, q);
  divf( dividend, divisor, p, rest); 
  printf( "p : %s rest: %s\n", p, rest);
  strcpy( prime_for_test, p) ;
  fermattest( prime_for_test, iterations, a_ll); 
//
#endif
//=======================================================================
//
//#define TEST2
#ifdef TEST2
//
// rsa243
   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
   strcpy( prime_for_test, e) ;
   iterations = 5 ;
   a_ll = 15;
   fermattest( prime_for_test, iterations, a_ll); 
   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
   strcpy( prime_for_test, p) ;
   iterations = 5 ;
   a_ll = 15;
   fermattest( prime_for_test, iterations, a_ll); 
   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");
   strcpy( prime_for_test, q) ;
   iterations = 5 ;
   a_ll = 15;
   fermattest( prime_for_test, iterations, a_ll); 
//
#endif
//=======================================================================
//
//#define TEST1
#ifdef TEST1
   iterations = 5 ;
   a_ll = 15;
   randbigint( prime_random, 25);
   fermattest( prime_random, iterations, a_ll); 
#endif
//=======================================================================
//
// Carmichael Zahlen
//
#define TEST4
#ifdef TEST4
   iterations = 5 ;
   a_ll = 2;
   strcpy( prime_for_test,"251");
   fermattest( prime_for_test, iterations, a_ll); 
   strcpy( prime_for_test,"341");
   fermattest( prime_for_test, iterations, a_ll); 
   // pseudoprime zu jeder Basis : 3x11x17
   strcpy( prime_for_test,"561");
   fermattest( prime_for_test, iterations, a_ll); 
   // pseudoprime zu jeder Basis :  7x13x19
   strcpy( prime_for_test,"1729");
   fermattest( prime_for_test, iterations, a_ll); 
#endif
 }
//===================================================================
