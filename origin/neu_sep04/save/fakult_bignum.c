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
  void test3();
  void test_fakultaet();
  void test1_1();
  void test1();
  void test2();
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
   
   test_fakultaet();
   //test3();
   //test1();
   //test2();
   //test1_1();
   return(0);

 }
//===================================================================


//===============================================================
// test3 : addsub test
//  >   <
//  + + +   + ADD
//  - + +   - SUB    > - < 
//  + + -   + SUB    > - < 
//  - + -   - ADD
//
//  >   < 
//  + - +  + SUB     > - < 
//  - - +  - ADD
//  + - -  + ADD
//  - - -  - SUB     > - < 
//===============================================================
  void test3()
   {
   char zahl1[ARRAYLENGTH];
   char zahl2[ARRAYLENGTH];
   char zahl3[ARRAYLENGTH];
   char zahl4[ARRAYLENGTH];
   char zahl5[ARRAYLENGTH];
   char *z1, *z2, *z3, *z4, *z5;
   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   z5 = zahl5;
//
   printf(" plus :\n");
   strcpy(z1,"999");
   strcpy(z2,"999");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'+');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"-999");
   strcpy(z2,"998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'+');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"999");
   strcpy(z2,"-998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'+');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"-999");
   strcpy(z2,"-998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'+');
   printf("zahl3: %s\n", zahl3);
//
   printf(" minus :\n");
   strcpy(z1,"996");
   strcpy(z2,"999");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'-');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"-999");
   strcpy(z2,"998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'-');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"999");
   strcpy(z2,"-998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'-');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"-999");
   strcpy(z2,"-998");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'-');
   printf("zahl3: %s\n", zahl3);
//
   strcpy(z1,"999999999999999999999999999");
   strcpy(z2,"-999999999999999999999999999");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = addsub(z1,z2,zahl3,'-');
   printf("zahl3: %s\n", zahl3);
   
   }
//===============================================================
// test fakultaet
//===============================================================
  void test_fakultaet()
   {
   char z1[ARRAYLENGTH];
   char z2[ARRAYLENGTH];
   char z3[ARRAYLENGTH];
   char z4[ARRAYLENGTH];
   char z5[ARRAYLENGTH];
   int maxii, ii;
   printf("---------- test Fakultaet-----------\n");
   strcpy(z1, "1");
   strcpy(z2, "1");
   strcpy(z4, "1");
   maxii=1000;
   for(ii=1; ii<=maxii; ii++) {
      mult(z1,z2,z3);
      strcpy(z1,z3);
      addsub(z2,z4,z5,'+');
      strcpy(z2,z5);
      printf("i=%d  %s\n",ii, z3);
      //printf("i=%d \n",ii);
   }
   printf("i=%d %s length: %d\n", ii, z3, strlen(z3));
   }
//===============================================================
// test2 : mult/div test
//===============================================================
  void test2()
   {
   char zahl1[ARRAYLENGTH];
   char zahl2[ARRAYLENGTH];
   char zahl3[ARRAYLENGTH];
   char zahl4[ARRAYLENGTH];
   char zahl5[ARRAYLENGTH];
   char *z1, *z2, *z3, *z4, *z5;
   int ii, maxii;
   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   z5 = zahl5;
   printf(" Test Mult \n");
   printf("===========\n");
   printf("---------- test1 -----------\n");
   strcpy(z2, "7419043440758059956596");
   strcpy(z1, "60967068778579064460287972");
   z3 = mult(zahl1, zahl2, zahl3,'-');
   printf("zahl3: %s\n", z3);
   printf("a * b: 452317331723962514217511611516823866219980863312\n");
//
   printf( "---------- test2 : a/b = c --> c * b + mod = a  ----------\n");
   strcpy(z1, "188888888888888888888888888888888888888888888888888823456789000000000000000000123456789099");
   strcpy(z2, "999999991234567890000000001144");
   strcpy(z5, z2);
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl1 nach div: %s\n", zahl1);
   printf("zahl2 nach div: %s\n", zahl2);
   printf("quot, div : %s %s\n", z3, z4);
   strcpy( zahl1, z3);
   z3 = mult(z3, z5, zahl3);
   z5 = addsub( z3,z4,zahl5, '+');
   printf("z5 = %s \n", z5);
//
//  multiply 2 ^ ii  and divide 
//
   printf("---------- test3 -----------\n");
   strcpy(z1, "2");
   strcpy(z2, "2");
   maxii=400;
   for(ii=1; ii<=maxii; ii++) {
      z3 = mult(zahl1, zahl2, zahl3);
      strcpy(zahl1, z3);
      printf("i=%d  %s\n",ii, z3);
   }
   printf("i=%d %s length: %d\n", ii, z3, strlen(z3));
     strcpy( zahl1, z3);
   for(ii=1; ii<=maxii; ii++) {
     strcpy( zahl2, "2");
     //z3 = div(zahl1, zahl2, zahl3, zahl4);
     z3 = divf(zahl1, zahl2, zahl3, zahl4);
     strcpy( zahl1, z3);
     printf("i=%d  %s %s\n",ii, z3, z4);
   }
   printf("i=%d  %s %s\n",ii, z3, z4);
   }
//===============================================================
// test1_1 : div test
//===============================================================
  void test1_1()
   {
   char zahl1[ARRAYLENGTH];
   char zahl2[ARRAYLENGTH];
   char zahl3[ARRAYLENGTH];
   char zahl4[ARRAYLENGTH];
   char *z1, *z2, *z3, *z4;
   // strcpy(z1, "60967068778579064460287972");
   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   printf(" Test fast Division \n");
   printf("====================\n");
   printf("---------- test1 -----------\n");
   //strcpy(z2, "28");
   //strcpy(z1, "3876513");
   strcpy(z2, "-7419043440758059956596");
   //strcpy(z2, "452317331723962514217511611516823866219980863312");
   strcpy(z1, "+452317331723962514217511611516823866219980863312");
   //strcpy(z1, "1000000000000000000000000000000000000000000000");
   //strcpy(z2, "3");
   // strcpy(z2, "-2");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = divf(zahl1, zahl2, zahl3, zahl4);
   //printf("zahl1: %s\n", zahl1);
   //printf("zahl2: %s\n", zahl2);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("     : 60967068778579064460287972\n");
   }
//===============================================================
// test1 : div test
//===============================================================
  void test1()
   {
   char zahl1[ARRAYLENGTH];
   char zahl2[ARRAYLENGTH];
   char zahl3[ARRAYLENGTH];
   char zahl4[ARRAYLENGTH];
   char *z1, *z2, *z3, *z4;
   // strcpy(z1, "60967068778579064460287972");
   z1 = zahl1;
   z2 = zahl2;
   z3 = zahl3;
   z4 = zahl4;
   printf(" Test Division \n");
   printf("===============\n");
   printf("---------- test1 -----------\n");
   strcpy(z2, "7419043440758059956596");
   strcpy(z1, "-452317331723962514217511611516823866219980863312");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("     : 60967068778579064460287972\n");
   printf("---------- test2 -----------\n");
   strcpy(z1, "-452317331723962514217511611516823866219980863312");
   strcpy(z2, "452317331723962514217511611516823866219980863312");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("---------- test3 -----------\n");
   strcpy(z1, "452317331723962514217511611516823866219980863312");
   strcpy(z2, "452317331723962514217511611516823866219980863313");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("---------- test4 -----------\n");
   strcpy(z1, "452317331723962514217511611516823866219980863312");
   strcpy(z2, "452317331723962514217511611516823866219980863311");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("---------- test5 -----------\n");
   strcpy(z1, "0");
   strcpy(z2, "452317331723962514217511611516823866219980863311");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
   printf("---------- test6 -----------\n");
   strcpy(z1, "452317331723962514217511611516823866219980863311");
   strcpy(z2, "0");
   printf("zahl1: %s\n", zahl1);
   printf("zahl2: %s\n", zahl2);
   z3 = div(zahl1, zahl2, zahl3, zahl4);
   printf("zahl3: %s rest: %s\n", z3, z4);
//
//
   
   }
//===============================================================
