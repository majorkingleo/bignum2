//==========================================================================
//                standard main program for bignum
//==========================================================================
//  functions for big integer processing based on strings
//==========================================================================
// Date :    
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
  char p[ARRAYLENGTH] ;
  char q[ARRAYLENGTH] ;
  char e[ARRAYLENGTH] ;
  char n[ARRAYLENGTH] ;

   verylong prime_random;

   verylong zahl1,zahl2,zahl3,zahl4;
   char *z1, *z2, *z3, *z4;
 
   char *p1;


   printf(" Large Integer numbers :\n");
   printf("========================\n");
   printf("Compiled with buffer length : %d\n", arrlen);

//   z1 = zahl1;
//   z2 = zahl2;
//   z3 = zahl3;
//   z4 = zahl4;

//
// initialize random generator
//
  srand( (unsigned) time( NULL));
//
//---------------------------------------------
//
// randtest
//-----------
//  randlength = 500 ;
//   for(ii=1; ii< 7; ii++) {
//     randbigint( randall, randlength);
//     printf(" randint : %s\n", randall);
//   }
   strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
//   strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
//
// xxxxxxxxxxxxxxxx
   strcpy(p , "37419669101");
   strcpy(q , "11110693267");
   mult( p,q,zahl1);
// rsa155
//   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
//   strcpy( n, e) ;
//   strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
// rsa243
   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");
//
   iterations = 5 ;
   a_ll = 15 ;
   // strcpy( n, q) ;
   // strcpy( n, p) ;
   //strcpy( n, zahl1) ;
   randbigint( prime_random, 200);
   fermattest( prime_random, iterations, a_ll); 
 }
// xxxxxxxxxxxx
//===============================================================
//
//  function fermattest
//
//===============================================================
//
// check for : a^(n-1) mod_n == 1 
// if != 1  no prime
// if == 1  may be prime, but also composite
// a .... 1 - (n-1)
// 
// input : prime_for_test .... input number for check
// iterations ..... number of loops
// a_length ..... length of a 
//
//==========================================================================
//
  int fermattest( prime_for_test, iterations, a_length) 
   char *prime_for_test;
   int iterations, a_length ;
  {
  char randall[ARRAYLENGTH];
  char prime_min_1[ARRAYLENGTH] ;
  char a[ARRAYLENGTH] ;
  char r[ARRAYLENGTH] ;
  char eins[ARRAYLENGTH] = "1";
  int  randlength;
  int ii, down, up;
  int prime_count, composite_count;
  int ll_n, ll_a; 
//
  printf("========= fermat test =========\n");
  printf(" check for :  a^(n-1) mod_n == 1\n"); 
  printf(" iterations : %d\n", iterations);
//
// n-1
//
   addsub( prime_for_test, eins, prime_min_1, '-'); 
//
  prime_count = 0;
  composite_count = 0;
  ll_n = strlen( prime_for_test) ; 
  printf( " length of prime : %d length of a : %d\n", ll_n, a_length);
  if (  ll_n <= a_length ) {
     printf( "length for a too large : %d  %d\n", a_length, ll_n);
     printf( " === fermat test terminated abnormally ===\n");
     exit(0);
  } 
//
  for(ii=1; ii<= iterations; ii++) {
  printf("----------------------------------------------------\n");
     randbigint( randall, a_length);
     // printf(" randint : %s\n", randall);
     strcpy( a, randall);
     printf(" a  : %s\n", a);
     printf(" n  : %s\n", prime_for_test);
     // printf(" n-1: %s\n", prime_min_1);
//
//    char *modexpf(a, b, n, res) ..... a destroyed
//
     modexpf( a, prime_min_1, prime_for_test, r);
     printf(" r : %s\n", r);
//
     if(strcmp( r, eins) == 0) {
       printf(" >>>>> is prime \n");
       prime_count ++;
     } else {
       printf(" >>>>> is composite\n");
       composite_count ++;
     }
  printf("----------------------------------------------------\n");
  }
  printf(" total of fermat check results :  prime %d   composite %d \n", prime_count, composite_count);
 }
//===============================================================
//
//  function randbigint
//
//===============================================================
// create random integer number
// returns a big int with length  
//==========================================================================
//
  int randbigint( randint, randlen) 
   char *randint;
   int randlen ;
  {
  int i, l, ltot, looplength,  breakflag;
  int randzahl;
  char randzahlstr[100];

  looplength = ARRAYLENGTH ; 

// initialize

  ltot = 0;
  breakflag = 0;
//
// each call of rand creates 10 numbers 
// convert to string and add to array with ARRAYLENGTH
// this is always done
// actual length is created by \0
//
//------------------------------------  
  for(i=1; i<=1000; i++) {
    randzahl = rand();
    // printf(" rand : %d\n", randzahl);
    sprintf( randzahlstr, "%d", randzahl);
    //printf(" rand1 : %s\n", randzahlstr);
    l = strlen( randzahlstr);
    if( i == 1) {
       strcpy(randint, randzahlstr);
    } else {
       strcat(randint, randzahlstr);
    }
    ltot = ltot + l;
    if( ltot + 30 > ARRAYLENGTH) {
     breakflag = 1;
        break;  
    }
  }
//------------------------------------  
   if( ! breakflag) {
     printf( " error generating random number \n");
   }
    //printf("----%d %d\n",i, ltot);
    //printf(" randint : %s\n", randint);

    randint[randlen] = '\0';
    //printf(" randint : %s\n", randint);
    return(0);
  } 
//===================================================================
//
// nur zur reserve
//
//   strcpy(p , "37419669101");
//   strcpy(q , "11110693267");
//   strcpy(e , "65537");
//   euclidext(e, p, q, d);
//   printf( "d= %s\n", d);
//  printf( "Solution should be: \n");
//   printf( "d = 16481384459631305873\n");
// 
//   strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
//   strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
//   printf("n     : %s  %d\n", n, strlen(n));
//   printf("q     : %s  %d\n", q, strlen(q));
//   strcpy(dummy1,n);
//   strcpy(dummy2,q);
// n/q = p
//   div(dummy1, dummy2,p,mod);
//   printf("quot  : %s  %d\n" ,p, strlen(p));
//   printf("mod   : %s\n" ,mod);
// check, if correct
//   mult(q, p, dummy);
//   if(strcmp( dummy, n) != 0) {
//     printf( "Error p*q :%s\n",dummy);
//   }
//   strcpy(e,"3735928559"); 
//
// rsa243
//
//   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
//   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
//   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");
//
//===============================================================
