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

  char *bin_hex();

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
  //char zahl2[ARRAYLENGTH] = "2";

  char zahl1[ARRAYLENGTH] ;
  char nmin1[ARRAYLENGTH] ;
  char a[ARRAYLENGTH] ;
  char n[ARRAYLENGTH] ;
  char r[ARRAYLENGTH] ;
  char p[ARRAYLENGTH] ;
  char q[ARRAYLENGTH] ;
  char e[ARRAYLENGTH] ;
  char divisor[ARRAYLENGTH] ;
  char dividend[ARRAYLENGTH] ;
  char prime_for_test[ARRAYLENGTH] ;

  char quotient1[ARRAYLENGTH] ;
  char rest1[ARRAYLENGTH] ;
  char quotient2[ARRAYLENGTH] ;
  char rest2[ARRAYLENGTH] ;
  char testzahl[ARRAYLENGTH] ;

  char bin_in_test[ARRAYLENGTH] ;
  char outbcd[ARRAYLENGTH] ;
  int breakflag; 
//
   strcpy(p , "37419669101");
   strcpy(q , "11110693267");
   mult( p,q,zahl1);
//
// rsa155
//
// prime
//  strcpy(q, "12844205165381031491662259028977553198964984323915864368216177647043137765477");
// n is composit
//  strcpy(n, "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463");
//
// rsa243
//
//   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
//   strcpy(p,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529430243075948799");
//   strcpy(q,"25110719126901354976190933395867124680240805711276844886250959824156205188949406184735295788387561135167529435118429780319");
// n243  .... composite
//  strcpy(n,"6305482150701295471567183324958896322344341454119712758883769876032602");
//  strcat(n,"2525278792613527673894410568910003629553586814142438653640364957870769");
//  strcat(n,"9128189491432138631900590774729214990015369102760964884776344849717811");
//  strcat(n,"484309528915040117952098061886881");

//-------------------------------
// this number is prime !!!
//the following composite number is failing every primality test I ran it
//across.
//Any ideas?
//Thanks, Flip
   strcpy( testzahl, "4934673806156388163176845045527104259242504392822688623822144");
   strcat( testzahl, "81069979759413742943343660994174309730576376709981153337038337");
   strcat( testzahl, "833607099357863733152761402652533");
//-------------------------------
//
   printf("========================\n");
   printf(" Large Integer numbers :\n");
   printf("========================\n");
   printf("Compiled with buffer length : %d\n", arrlen);

//-----------------------------------------------------
//  srand( (unsigned) time(NULL));
//
   // ok strcpy( prime_for_test,"37419669101");
   //strcpy( prime_for_test,"3741966910000000001");
   strcpy( prime_for_test,"999999999999999");
// prime
   //strcpy( prime_for_test,"1296473");
   //strcpy( prime_for_test,"129");
// composite
   // 11*31
   strcpy( prime_for_test,"341");
   strcpy( prime_for_test, testzahl);
   //strcpy( prime_for_test, e);

   //strcpy( prime_for_test, zahl1);
   //strcpy( prime_for_test, q);
   //strcpy( prime_for_test, n);
//
// call test   
//
   millerrabintest( prime_for_test, 10); 
//
}   
//===================================================================
//                  m i l l e r _ r a b i n 
//===================================================================
// written by aob : 19.10.04
//===================================================================
// miller rabin probabilistic primality test
// see Handbook of applied cryptography  4.24 page 139
// and sci.crypt 1997/06/27  freelip Miller Rabin probabilistic Primality test
// implementation (James Pate Williams)
//===================================================================
// -------------- start miller rabin --------------------
//
   int millerrabintest( prime_for_test, iterations) 
     char *prime_for_test;
     int iterations;
   {
   verylong za, zb, zn, zn1,zr,zy;
   verylong inbcd, outbin, outbcd, outhex;

   char eins[ARRAYLENGTH] = "1";
   char zwei[ARRAYLENGTH] = "2";
   // char drei[ARRAYLENGTH] = "3";
   char strdummy[ARRAYLENGTH] ;
   char quotient[ARRAYLENGTH] ;
   char rest[ARRAYLENGTH] ;
   char hex_out_test[ARRAYLENGTH] ;

   int lll, le, iter, length_zn1, comp1, comp2, j_mr, s_mr;
   int composflag, value;
   char last_bit;

   printf( "\n");
   printf( "<<<<<<<<< miller rabin primality test <<<<<<<<<\n");
   printf( "\n");

   lll = strlen( prime_for_test);
   printf("number for test : %s length : %d\n", prime_for_test, lll);
   strcpy( zn , prime_for_test);
// odd ?
   strcpy( strdummy, zwei);
   divf( zn, strdummy, quotient, rest); 
//
   if(strcmp( rest, "0") == 0) {
     printf( "Miller Rabin test : number for check is even number\n");
     exit(0);
   }
// > 3,  but we check for 3 digits to get random number 
   strcpy( zn , prime_for_test);
   if( lll <= 2) {
     printf( "Miller Rabin test : number for check should be > 100\n");
     exit(0);
   }
//
// subtract 1
//
   addsub( zn, eins, zn1, '-');
   strcpy( zr, zn1 );
   strcpy( inbcd, zr );
   //printf("inbcd : %s\n", inbcd);
   bcd_binhex(inbcd, outbin, outhex);
   //printf( "   outbin :%s\n", outbin);
//
// get last bit
//
   le = strlen( outbin);
   last_bit = strchar( outbin, le); 
   //printf( "lastbit: %c\n", last_bit) ;
//
// convert zn1 : 2^s*r  ... r odd
//---------------------------------
//
   s_mr = 0;
   //printf("----------------------\n");
   for(;;) {
     if( last_bit == '1') break;
     s_mr++;
     le = strlen( outbin);
     last_bit = strchar( outbin, le - 1); 
     outbin[le - 1] = '\0';
     // printf( " x outbin :%s\n", outbin);
   }
   //printf("----------------------\n");
   // printf( " y outbin :%s s: %d\n", outbin, s_mr);
//
   bin_hex( outbin, hex_out_test);
   // printf("hexout : %s \n", hex_out_test);
   hex_bcd(hex_out_test, outbcd); 
   printf("=============== convert n-1 : (2^s)*r  ... r odd ===============\n");
   strcpy( zr, outbcd);
   printf("   n-1 : %s\n", zn1);
   printf("   r   : %s\n", zr);
   printf("   s   : %d\n", s_mr);
//
// loop iterations
//-------------------------------------
//
// initialize random generator
//
   srand(( unsigned) time (NULL));
//
// main loop of miller rabin check
//------------------------------------------------------------
   length_zn1 = strlen(zn1);
   composflag = 0;
   value = 1;
   for( iter = 1 ; value && iter <= iterations ; iter++) {
    printf("=============== begin of main loop : %d ===============\n", iter);
     // get random number >=2 and < zn1
     // check for small numbers
     randbigint( za, length_zn1-1); 
     //
     printf("   za : %s\n", za);
     printf("   zr : %s\n", zr);
     printf("   zn : %s\n", zn);
     modexpf(za, zr, zn, zy);      // za destroyed 
     printf(" zy =  (za^zr) mod zn : %s\n", zy);
     comp1 = strcmp( zy, eins);
     comp2 = strcmp( zy, zn1);
     if( comp1 != 0 && comp2 !=0) {
         j_mr = 1;
         printf("=============== begin sub loop  ===============\n");
         while( value && j_mr <= s_mr - 1 && strcmp( zy, zn1) != 0) {
             printf("   j    : %d\n", j_mr);
             printf("   zy   : %s\n", zy);
             //printf("   zwei : %s\n", zwei);
             printf("   zn   : %s\n", zn);
             modexpf(zy, zwei, zn, zb);      // zy destroyed 
             printf(" (zy*zy)mod zn  : %s\n", zb);
             //printf("   zwei : %s\n", zwei);
             strcpy( zy, zb) ;
             if( strcmp( zy , eins) == 0) {
                printf("zy = 1 : composite\n");
                composflag = 1;
                value = 0;
             }
             j_mr++;
         } 
         printf("=============== end sub loop  ===============\n");
         if( strcmp( zy , zn1) != 0) {
            printf(" zy != zn : composite\n");
            composflag = 1;
            value = 0;
         }
     }
    printf("=============== end of main loop ===============\n");
   }
   if(!composflag) {
      printf("number is prime : %s\n", zn);
   } else {
      printf("number is composite : %s\n", zn);
   }
   printf( "\n");
   printf( "<<<<<<<<< end of miller rabin test <<<<<<<<<\n");
   printf( "\n");
   return(0);
 }
//===================================================================
//                          b i n h e x 
//===================================================================
//
  char *bin_hex(bin, hex)
   char  *bin, *hex;
   {
   char *bcdd, *bcdb, *bcdh;
   int bcd_ok, i, ii, ki, declen, reglen;
   int k, block, mainl; 
   char group4[10], group4_1[10];
   char bitout; 
   char bitout_arr[5];
   char corrflag[10];
   char bcd_digit, bcd_bad;
   char binreg[ARRAYLENGTH];
   char binres[ARRAYLENGTH];
   char hexreg[ARRAYLENGTH];
   char dummy[ARRAYLENGTH];

   char bin_digit;
   char list1[10] = "0123456789";
   int bcdddebug;
   int binlen, binlen1, binlen4, hex_mod, bin_ok, bin_bad;
   struct bin { 
        char *binval ;
   } bintab[] ={
                 {"0000"}, 
                 {"0001"}, 
                 {"0010"}, 
                 {"0011"}, 
                 {"0100"}, 
                 {"0101"}, 
                 {"0110"}, 
                 {"0111"}, 
                 {"1000"}, 
                 {"1001"}, 
                 {"1010"}, 
                 {"1011"}, 
                 {"1100"}, 
                 {"1101"}, 
                 {"1110"}, 
                 {"1111"} 
   };
   struct hex { 
        char *hexval ;
   } hextab[] ={
                 {"0"}, 
                 {"1"}, 
                 {"2"}, 
                 {"3"}, 
                 {"4"}, 
                 {"5"}, 
                 {"6"}, 
                 {"7"}, 
                 {"8"}, 
                 {"9"}, 
                 {"A"}, 
                 {"B"}, 
                 {"C"}, 
                 {"D"}, 
                 {"E"}, 
                 {"F"} 
   };
//
// 
   int binhexdebug = 0;
   if(binhexdebug) printf("binhex : bin : %s\n", bin);
   if( strlen(bin) < 1){
     printf( "binhex:  Input Error bin \n");
     printf( "binhex:  Zero length string \n");
     printf( "binhex:  === binhex terminated abnormally ===\n");
     strcpy( hex,"bcd conversion error");
     return( hex);
   }
   binlen = strlen(bin);
//
// check valid bin string
//
   if(binhexdebug) printf("binhex : length %d\n", binlen);
   bin_ok = 0;
   for(ii= 1 ; ii <= binlen; ii++) {
     bin_digit = strchar( bin, ii);
         if(bin_digit == '0'){
           bin_ok++;
         }
         if(bin_digit == '1'){
           bin_ok++;
         }
   }
  if( bin_ok != binlen) {
    bin_bad = binlen - bin_ok;
    printf("bin_hex: Illegal bin number : %s\n", bin);
    printf("bin_hex: Number of bad characters: %d\n", bin_bad);
    strcpy(hex,"illegal bin number");
    return(hex);
  }
//
   hex_mod = binlen % 4;
   if( hex_mod != 0 ) {
      if(hex_mod == 1) {
        strcpy( dummy, "000");
        strcat( dummy, bin);
        strcpy( binreg, dummy);
      }
      if(hex_mod == 2) {
        strcpy( dummy, "00");
        strcat( dummy, bin);
        strcpy( binreg, dummy);
      }
      if(hex_mod == 3) {
        strcpy( dummy, "0");
        strcat( dummy, bin);
        strcpy( binreg, dummy);
      }
   } else {
     strcpy( binreg, bin);
   }
//   
   if( binhexdebug) printf("binhex : binreg: %s \n", binreg);
      binlen1 = strlen( binreg);
      binlen4 = binlen1/4;
      strcpy( hexreg, "");
      //loop over all 4 bit groups
      for(i = 1;  i <= binlen4;  i++) {
        k = (i - 1) * 4 + 1 ; 
        substr(binreg, group4, k, 4);
         for(k=1; k <=16; k++) {
           if(strcmp(group4,bintab[k-1].binval) == 0) break;
         }
         if(binhexdebug) printf("binhex : group : %d %d %s \n", i, k, group4);
         strcat( hexreg, hextab[k-1].hexval);
      } 
      if(binhexdebug) printf("binhex : %s\n", hexreg);
      strcpy( hex, hexreg);
      return( hex);
 }
//==========================================================================
