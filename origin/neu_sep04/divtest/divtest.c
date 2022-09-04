//==========================================================================
//                   h e x b c d   and  b c d h e x
//==========================================================================
//  functions for big integer processing based on strings
//==========================================================================
// history : bcd_binhex : already done  
//          3-Feb-03  hex_bcd : new function 
//         15-Feb-03  substr function added
//           
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
  void test5();
// hex_bcd
  void test5_1();
  void test5_2();
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
   
   //test5();
   test5_1();
   //test5_2();
   return(0);

 }
//===============================================================
// test5 : bcd_binhex
//===============================================================
  void test5_2() {
   char in[ARRAYLENGTH];
   char out[ARRAYLENGTH];
   int st,le;
   printf("============= test substr ============\n");
   strcpy(in, "123456789abcedfg");
   st=10; le=1;
   substr(in, out, st, le); 
   printf("in:%s out:%s %d %d\n",in,out,st,le);
   st=10; le=21;
   substr(in, out, st, le); 
   printf("in:%s out:%s %d %d\n",in,out,st,le);
   st=1; le=1;
   substr(in, out, st, le); 
   printf("in:%s out:%s %d %d\n",in,out,st,le);
   st=16; le=1;
   substr(in, out, st, le); 
   printf("in:%s out:%s %d %d\n",in,out,st,le);
   st=26; le=1;
   substr(in, out, st, le); 
   printf("in:%s out:%s %d %d\n",in,out,st,le);
  }
//===============================================================
// test5 : bcd_binhex
//===============================================================
  void test5_1() {
   char inhex[ARRAYLENGTH];
   char outbcd[ARRAYLENGTH];
   char outbin[ARRAYLENGTH];
   char outhex[ARRAYLENGTH];
//
//   char in1[ARRAYLENGTH];
//   char in2[ARRAYLENGTH];
//   char outbin[ARRAYLENGTH];
//
   char dividend1[ARRAYLENGTH];
   char divisor1[ARRAYLENGTH];
   char quotient1[ARRAYLENGTH];
   char rest1[ARRAYLENGTH];
//
   char dividend2[ARRAYLENGTH];
   char divisor2[ARRAYLENGTH];
   char quotient2[ARRAYLENGTH];
   char rest2[ARRAYLENGTH];


   printf("============= test div ============\n");
   //strcpy(in, "63");
   //strcpy(in, "1023");
   printf("\n");
   printf(">>>>>>>>>>>>>> test1 <<<<<<<<<<<<<<\n");
   printf("\n");
//
   for(;;) {
     printf("-------------------------------------------------\n");
     printf("Type dividend : ");
     scanf("%s", dividend1);
     printf("Dividend : %s\n", dividend1);
     //gets(inhex);
     //printf("filename :%s\n",filename);
     //strcpy(inhex, "FFFFFF");
     printf("Type divisor : ");
     scanf("%s", divisor1);
     printf("Divisor : %s\n", divisor1);
     printf("------- divf -------\n");
     strcpy( dividend2, dividend1);
     strcpy( divisor2, divisor1);
     divf( dividend1, divisor1, quotient1, rest1);
     printf("Quotient : %s\n", quotient1);
     printf("Rest : %s\n", rest1);


     printf("------- div -------\n");
     div( dividend2, divisor2, quotient2, rest2);
     printf("Quotient : %s\n", quotient2);
     printf("Rest : %s\n", rest2);

     if(strcmp( quotient1, quotient2) != 0) {
        printf(" quotient unterschiedlich \n");
     }
     if(strcmp( rest1, rest2) != 0) {
        printf(" rest unterschiedlich \n");
     }


    // printf("------- hex_bcd -------\n");
    // hex_bcd(inhex, outbcd);
    // printf("------- nach hex_bcd -------\n");
    // printf("bcd: %s\n",outbcd);
     //printf("hex: %s\n",inhex);
    // printf("\n");
    // printf("------- bcd_hex -------\n");
    // bcd_binhex(outbcd, outbin, outhex);
    // printf("------- nach bcd_hex -------\n");
    // printf("bin: %s\n",outbin);
    // printf("hex: %s\n",outhex);
    // if(strcmp( inhex, outhex) != 0){
    //    printf(" unterschiedlich \n");
    // }
   }
   }
//===============================================================
// test5 : bcd_binhex
//===============================================================
  void test5() {
   char in[ARRAYLENGTH];
   //char in1[ARRAYLENGTH];
   //char in2[ARRAYLENGTH];
   char outbin[ARRAYLENGTH];
   char outhex[ARRAYLENGTH];
   //int i;
   printf("============= test bcd_binhex ============\n");
   //strcpy(in, "63");
   // strcpy(in, "1023");

   //strcpy(in, "68719476736");
   //strcpy(in, "12345");
   printf("\n");
   printf(">>>>>>>>>>>>>> test1 <<<<<<<<<<<<<<\n");
   printf("\n");
   strcpy(in, "68719476735");
   printf("Dezimal Zahl : %s\n", in);
   bcd_binhex(in, outbin, outhex);
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   printf("\n");
   printf(">>>>>>>>>>>>>> test2 <<<<<<<<<<<<<<\n");
   printf("\n");
   strcpy(in, "68719476736");
   printf("Dezimal Zahl : %s\n", in);
   bcd_binhex(in, outbin, outhex);
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   printf("\n");
   printf(">>>>>>>>>>>>>> test3 <<<<<<<<<<<<<<\n");
   printf("\n");
   strcpy(in, "1");
   printf("Dezimal Zahl : %s\n", in);
   bcd_binhex(in, outbin, outhex);
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   printf("\n");
   printf(">>>>>>>>>>>>>> test4 <<<<<<<<<<<<<<\n");
   printf("\n");
   strcpy(in, "0");
   printf("Dezimal Zahl : %s\n", in);
   bcd_binhex(in, outbin, outhex);
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   printf("\n");
   //printf(">>>>>>>>>>>>>> test3 <<<<<<<<<<<<<<\n");
   //printf("\n");
   //strcpy( in, "1");
   //strcpy( in1, "1");
   //for( i=1; i<=1024; i++) {
   //   bcd_binhex(in1, outbin, outhex);
   //   printf("i: %d bin: %s hex:%s\n",i, outbin, outhex);
   //   addsub( in1, in, in2,'+');
   //   strcpy( in1, in2);
   //}
   }
//===================================================================
