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
  void test4();
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

   verylong zahl1,zahl2,zahl3,zahl4;
   char *z1, *z2, *z3, *z4;

   //int ii;

   printf(" Large Integer numbers :\n");
   printf("========================\n");
   printf("Compiled with buffer length : %d\n", arrlen);


   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   
   test4();
   return(0);

 }
//===================================================================
// test4 : extended euclid algorithm
//===============================================================
// this test routine has 5 examples for finding the private
// exponent if e, p,q,n is given (solve ed mod(p-1)(q-1) = 1) 
// There are simple examples and complicated examples with d = 243
// digits 
//===============================================================
  void test4() {
   char e[ARRAYLENGTH]; 
   char p[ARRAYLENGTH];
   char q[ARRAYLENGTH];
   char d[ARRAYLENGTH];
   char n[ARRAYLENGTH];
   char mod[ARRAYLENGTH];
   char dummy[ARRAYLENGTH];
   char dummy1[ARRAYLENGTH];
   char dummy2[ARRAYLENGTH];
   char *ep, *pp, *qp, *dp;
   // p=47, q=71, e = 79 d = 1019
   ep = e; pp = p; qp= q; dp = d;
//
//------------------------------------------------------------------------------
//                            small example
//------------------------------------------------------------------------------
// test1
   printf("\n");
   printf(">>>>>>>>>>>>>> start of test1 <<<<<<<<<<<<<<\n");
   printf("\n");
//
   strcpy( q,"71");
   strcpy( p,"47");
   strcpy( e,"79");
   dp = euclidext(e, p, q, d);
   printf( "d= %s\n", dp);
   printf(">>>>>>>>>>>>>> end of test1 <<<<<<<<<<<<<<\n");
//
// test2
   printf("\n");
   printf(">>>>>>>>>>>>>> start of test2 <<<<<<<<<<<<<<\n");
   printf("\n");
//
   strcpy( q,"17");
   strcpy( p,"11");
   strcpy( e,"7");
   dp = euclidext(e, p, q, d);
   printf( "d= %s\n", dp);
   printf(">>>>>>>>>>>>>> end of test2 <<<<<<<<<<<<<<\n");
//
// test 3
   printf("\n");
   printf(">>>>>>>>>>>>>> start of test3 <<<<<<<<<<<<<<\n");
   printf("\n");
//
   strcpy(p , "37419669101");
   strcpy(q , "11110693267");
   strcpy(e , "65537");
   euclidext(e, p, q, d);
   printf( "d= %s\n", d);
   printf( "Solution should be: \n");
   printf( "d = 16481384459631305873\n");
   printf(">>>>>>>>>>>>>> end of test3 <<<<<<<<<<<<<<\n");
// 
//------------------------------------------------------------------------------
//                             RSA 155 Simon Singh
//------------------------------------------------------------------------------
// test 4
//
   printf("\n");
   printf(">>>>>>>>>>>>>> start of test4 <<<<<<<<<<<<<<\n");
   printf("\n");

//
//------------------------------------------------------------------
// this example is from  Simon Singh Cipher Challenge stage 10 
// Factorisation of RSA 155  is from Internet
//
// compute d from singhs stage 10
//  exponent is 3735928559 in decimal and the public modulus is the
//  following 155-digit decimal integer
//  10742 78829 12665 65907 17841 12799 42116 61266 39217 94753 29458
//  88778 17210 35546 41509 80121 87903 38329 26235 28109 07506 72083
//  50494 19964 33143 42555 83344 01855 80898 94268 92463
//  10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463
//  155
// 
// 107427882912665659071784112799421166126639217947532945888778172103554641509801 ...
// ...21879033832926235281090750672083504941996433143425558334401855808989426892463 = 
//  = p78 x 12844205165381031491662259028977553198964984323915864368216177647043137765477
//------------------------------------------------------------------
//
// n,q,e is known, get p
//
   strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
   strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
   printf("n     : %s  %d\n", n, strlen(n));
   printf("q     : %s  %d\n", q, strlen(q));
   strcpy(dummy1,n);
   strcpy(dummy2,q);
// n/q = p
   div(dummy1, dummy2,p,mod);
   printf("quot  : %s  %d\n" ,p, strlen(p));
   printf("mod   : %s\n" ,mod);
// check, if correct
   mult(q, p, dummy);
   if(strcmp( dummy, n) != 0) {
     printf( "Error p*q :%s\n",dummy);
   }
   strcpy(e,"3735928559"); 
//
   dp = euclidext(e, p, q, d);
//
   printf( "d= %s %d\n", dp , strlen(dp));
//
// result  checked with awk :
//
   strcpy( dummy1,"6525347552646154161312591035650528129240345702733636194142790755228566994424546857484526024230071603641121131628417208058120288545764429922235978903797767");
   if(strcmp( dummy1, dp) != 0) {
     printf("not expected result for d\n");
   }
   printf("Result should be: \n  %s\n", dummy1);
   printf(">>>>>>>>>>>>>> end of test4 <<<<<<<<<<<<<<\n");

//------------------------------------------------------------------------------
//                                RSA 243 
//------------------------------------------------------------------------------
   printf("\n");
   printf(">>>>>>>>>>>>>> start of test4 <<<<<<<<<<<<<<\n");
   printf("\n");

//-----------------------------------------
// ------- n 243 Faktorisieren -------
//   n243 : 630548215070129547156718332495889632234434145411971275888376987603260225252787926135276738944105689100036295535868141424386536403649578707699128189491432138631900590774729214990015369102760964884776344849717811484309528915040117952098061886881
// 243
//   Faktor p :25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799
//   Laenge :122
//   Rest  :0
//   Faktor q :25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319
//   Laenge :122
//   Rest  :0
//   diff q - p :4875353831520
//   p * q :630548215070129547156718332495889632234434145411971275888376987603260225252787926135276738944105689100036295535868141424386536403649578707699128189491432138631900590774729214990015369102760964884776344849717811484309528915040117952098061886881
//   differenz n243 - p*q :0
//   -------------------------------------------------
//   e : 508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407
//Laenge e :123
//d     : 37596151776653337419535334112497554360708311749303756353996319663215286483855671243164897736438502271149130504165852074124585880523291499123910190345598116011326256898562180469616127693050575097619317602876777557156491759762785651714389821431 242
//-----------------------------------------
//
   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");
//
   dp = euclidext(e, p, q, d);
//
   printf("d= %s %d\n", dp , strlen(dp));
   strcpy(dummy1,"37596151776653337419535334112497554360708311749303756353996319663215286483855671243164897736438502271149130504165852074124585880523291499123910190345598116011326256898562180469616127693050575097619317602876777557156491759762785651714389821431");
   if(strcmp( dummy1, dp) != 0) {
     printf("Not expected result for d\n");
   } else {
     printf("Result checked against awk result, ok\n");
   }
   printf("Result must be: \n %s\n", dummy1);
   printf(">>>>>>>>>>>>>> end of test5 <<<<<<<<<<<<<<\n");
}
//===============================================================
