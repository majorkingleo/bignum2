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
#include "../lib/prime_100000.c"
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
  //void test5();
// hex_bcd
  //void test5_1();
  //void test5_2();
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

  //char zahl2[ARRAYLENGTH] = "7419043440758059956596";
  //char zahl1[ARRAYLENGTH] = "452317331723962514217511611516823866219980863312";
  //char zahl1[ARRAYLENGTH] = "2";
  //char zahl2[ARRAYLENGTH] = "2";
  char eins[ARRAYLENGTH] = "1";
  char nmin1[ARRAYLENGTH] ;
  char a[ARRAYLENGTH] ;
  char n[ARRAYLENGTH] ;
  char r[ARRAYLENGTH] ;
  char p[ARRAYLENGTH] ;
  char q[ARRAYLENGTH] ;
  char e[ARRAYLENGTH] ;
  char divisor[ARRAYLENGTH] ;
  char dividend[ARRAYLENGTH] ;
  char quotient[ARRAYLENGTH] ;
  char rest[ARRAYLENGTH] ;

  char quotient1[ARRAYLENGTH] ;
  char rest1[ARRAYLENGTH] ;
  char quotient2[ARRAYLENGTH] ;
  char rest2[ARRAYLENGTH] ;

  char pstr[30];

  int breakflag; 

   verylong zahl1,zahl2,zahl3,zahl4;
   char *z1, *z2, *z3, *z4;

   int ii;
// xxxxxxxxxxxxxxxx
//   strcpy(p , "37419669101");
//   strcpy(q , "11110693267");
//   mult( p,q,zahl1);
//
//
// rsa155
//  strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
//
// rsa243
//   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
//   strcpy( n, e) ;
   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
//   strcpy( n, p) ;
   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");

   printf(" Large Integer numbers :\n");
   printf("========================\n");
   printf("Compiled with buffer length : %d\n", arrlen);
      strcpy( dividend, q) ;
      dividend[22] = '\0';
      strcpy( divisor, "11");
      printf( "dividend : %s\n",  dividend); 
      printf( "divisor  : %s\n",  divisor); 
      divf( dividend, divisor, quotient, rest); 
      //div( dividend, divisor, quotient, rest); 
      printf( "quotient : %s\n", quotient);
      printf( "rest     : %s\n", rest);
      strcpy( dividend, q) ;
      dividend[22] = '\0';
      strcpy( divisor, "11");
      div( dividend, divisor, quotient, rest); 
      printf( "quotient : %s\n", quotient);
      printf( "rest     : %s\n", rest);
      //exit(0);
// divison 120 digits number  95000 prime numbers
// divf 2.16
// div  7.3
//-----------------------------------------------------
   srand( (unsigned) time(NULL));
//
for(;;) {
//
   randbigint( p, 55);
//
   breakflag = 0;
   printf( "===================================\n"); 
   printf( "randum number : %s\n", p); 
   for( ii=0 ; ii <=95000 ; ii++) {
      // printf( "> %d  %d \n", ii, primetable[ii]); 
      sprintf( pstr ,"%d", primetable[ii]); 
      strcpy( dividend, p) ;
      strcpy( divisor, pstr);
   //
   //  printf( "dividend : %s\n",  dividend); 
   //  printf( "divisor  : %s\n",  divisor); 
   //
     divf( dividend, divisor, quotient, rest); 
   //
  //  printf( "quotient : %s\n", quotient);
  //  printf( "rest     : %s\n", rest);
  //    strcpy( quotient1, quotient);
  //    strcpy( rest1 , rest);
  //
  //    strcpy( dividend, q) ;
  //    strcpy( divisor, pstr);
  //    div( dividend, divisor, quotient, rest); 
  //  printf( "quotient : %s\n", quotient);
  //  printf( "rest     : %s\n", rest);
  //
  //    strcpy( quotient2, quotient);
  //    strcpy( rest2 , rest);
  // if(strcmp( quotient1, quotient2) != 0) {
  //    printf( "quotient unterschiedlich \n") ;
  // } else {
  //    // printf( "quotient ok \n") ;
  // } 
  // if(strcmp( rest1, rest2) != 0) {
  //    printf( "rest unterschiedlich\n") ;
  // } else {
  //    // printf( "rest ok \n") ;
  // } 
   if(strcmp( rest, "0") == 0) {
      // printf( "p : %s\n",  p); 
      printf( "composit : divided by %s\n", pstr) ;
      breakflag = 1;
      break;
   } 
   }
   if( ! breakflag) {
     printf("<<<<<<<<<<<<<<<<<<<<<<<<  may be prime <<<<<<<<<<<<<<<<<<\n");
   }
}
   printf( "ende\n");
//-----------------------------------------------------

   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   
   //test5();
   //test5_1();
   //test5_2();
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
//   printf( "Solution should be: \n");
//   printf( "d = 16481384459631305873\n");
// 
//   strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
//
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
