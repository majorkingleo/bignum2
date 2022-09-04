//===============================================================
//          big integer library based in strings 
//===============================================================
// last modified : 30-Oct-04
//===============================================================
#include "bignum.h"
//===============================================================
//  17-Sep-04 : divf special case fixed
//  18-Sep-04 : divff same fix done 
//  20-Sep-04 : randbigint added, fermat added
//===============================================================
//
// char *addsub1(ax,bx,cx,as)
// char *mult(ay,by,cy)
// char *div(ay,by,cy,dy)
// char *divf(ay,by,cy,dy)
// char *euclidext(e, p, q, d)
// char *modexp(a, b, n, res)
// char *modexpf(a, b, n, res)
// char *divff(ay,cy,dy, dz1,dz2,dz3,dz4,dz5,dz6,dz7,dz8,dz9,slen0)
// char *bcd_binhex(bcddec, bcdbin, bcdhex)
// char *hex_bcd(inhex, outbcd)
// int randbigint( random, 200);
// int fermattest( prime, iterations, a_ll); 
//
// flags for debug : 1= debug, 0 = no debug
//---------------------------------------------
//
  int debug = 0;
  int multdebug = 0;
  int divdebug = 0;
  int divfdebug = 0;
  int bcdddebug = 0;
  int hexdebug = 0;
  int modexpdebug = 0;
//
// fast a^b modn
  int modexpfdebug = 0;
  int divffdebug = 0;
//==========================================================================
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
//  char strchar();
//  int substr();
//
//===============================================================
//
// function addsub
//
//===============================================================
// addsub with signs :
// greater >   less then <
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
//
//  strings with numbers must be correct
//
//===============================================================
   char *addsub(aa,bb,cc,flag)
    char *aa,*bb,*cc;
    char flag;
    {
    char signx[3] , signy[3];
    char addsub_signa, addsub_signb, addsub_xx, addsub_yy;
    char *pa, *pb ;
    int i,la,lb;
    int addsub_carry, addsub_swapflag;
    char oo[ARRAYLENGTH];
//
// check for valid input here
//
   if( strlen(aa) < 1){
     printf( "addsub : Input Error addsub ");
     printf( "addsub : Zero length string a");
     printf( "addsub : === addsub terminated abnormally ===");
     strcpy( cc,"addsub error");
     return( cc);
   }
   if( strlen(bb) < 1) {
     printf( "addsub : Input Error addsub ");
     printf( "addsub : Zero length string b");
     printf( "addsub : === addsub terminated abnormally ===");
     strcpy( cc,"addsub error");
     return( cc);
   }
//
// flag : + = add, - = sub
//
// check and remove sign
//
   if(debug) {
     printf("addsub ax: %s\n", aa);
     printf("addsub bx: %s\n", bb);
        //printf("la,lb,sign: %d %d %c\n", add_la, add_lb, as);
   }
//
//
   strncpy( signx, aa, 1);
   strncpy( signy, bb, 1);
   signx[1] = '\0';
   signy[1] = '\0';
//
// find signs
//
   if( debug ) printf("addsub signs;  %s %s \n", signx , signy);
//
   if((strncmp(signx , "-", 1)) == 0) {addsub_signa = '-';}
   else {addsub_signa = '+';}
   if((strncmp(signy , "-", 1)) == 0) {addsub_signb = '-';}
   else {addsub_signb = '+';}
   if(debug) printf("addsub: signa,signb %c %c\n", addsub_signa, addsub_signb);
//
// is a or b 0 ?
//
   pa = aa;
   pb = bb;
   if(strcmp( aa,"0") == 0) {
     if(flag == '+') {
       strcpy( cc,bb);
     } else {
       if( addsub_signb == '-') {
         pb = strpbrk(pb,"123456789");
       } else {
         strcpy( cc,"-");
         strcat( cc,pb);
       }
     }
     return(cc); 
   }
   if(strcmp( bb,"0") == 0) {
     strcpy( cc,aa);
     return(cc); 
   }
//
// remove sign
//
   pa = strpbrk(pa,"123456789");
   pb = strpbrk(pb,"123456789");
   la = strlen( pa);
   lb = strlen( pb);
   //strcpy( aa, pa);
   //strcpy( bb, pb);
   if(debug) printf("addsub: la,lb : %d %d\n", la, lb);
//
// check abs val and swap aa,bb
// max abs val is aa
//
   addsub_carry = 0;
   if( la == lb) {
      for (i = 1 ; i <= la ; i++) {
       addsub_xx = strchar( aa,i);
       addsub_yy = strchar( bb,i);
       // printf(" xx,yy: %c %c \n", addsub_xx, addsub_yy);
       if(addsub_xx == addsub_yy) continue;
       if(addsub_xx < addsub_yy) {
          addsub_carry = 1;
          break;
       }
       else break;
       }
   }
   if(debug) printf( "addsub: addsub_carry: %d\n", addsub_carry);
//
// check abs val of a b
//
   addsub_swapflag=0;
   if( (la < lb) || addsub_carry ) {
     addsub_swapflag = 1;
     if(debug) printf( "addsub: swapflag\n");
   }
//
// addition
//
  if(flag == '+') {
   if( addsub_signa == '+' && addsub_signb == '+') {
     cc = addsub1(pa,pb,cc,'+');
     goto finish;
   }
   if( addsub_signa == '-' && addsub_signb == '-') {
     cc = addsub1(pa,pb,cc,'+');
     goto finish_minus;
   }
   if( addsub_signa == '-' && addsub_signb == '+') {
     if(addsub_swapflag) {
        cc = addsub1(pb,pa,cc,'-');
        goto finish;
     } else {
        cc = addsub1(pa,pb,cc,'-');
        goto finish_minus;
     }
   }
   if( addsub_signa == '+' && addsub_signb == '-') {
     if(addsub_swapflag) {
        cc = addsub1(pb,pa,cc,'-');
        goto finish_minus;
     } else {
        cc = addsub1(pa,pb,cc,'-');
        goto finish;
     } 
   }
//
// subtraction
//
  } else if (flag == '-') {
   if( addsub_signa == '+' && addsub_signb == '+') {
     if(addsub_swapflag) {
        cc = addsub1(pb,pa,cc,'-');
        goto finish_minus;
     } else {
       cc =  addsub1(pa,pb,cc,'-');
       goto finish;
     } 
   }
   if( addsub_signa == '-' && addsub_signb == '-') {
     if(addsub_swapflag) {
        cc = addsub1(pb,pa,cc,'-');
        goto finish;
     } else {
        cc = addsub1(pa,pb,cc,'-');
        goto finish_minus;
     } 
   }
   if( addsub_signa == '-' && addsub_signb == '+') {
     cc = addsub1(pa,pb,cc,'+');
     goto finish_minus;
   }
   if( addsub_signa == '+' && addsub_signb == '-') {
     cc = addsub1(pa,pb,cc,'+');
     goto finish;
   }
//
// error
//
  } else {
   printf("addsub error : %c\n", flag);
   strcpy( cc, "addsub error");
   return(cc);
  }
   finish_minus:
    if( (strncmp(cc,"0",1))!= 0) {
      strcpy( oo, cc);
      cc[0] = '-'; cc[1] = '\0';
      strcat( cc, oo);
    } 
   finish:
   if(debug) printf("addsub: %s\n", cc);
   return(cc);
//
  }
//===============================================================
//===============================================================
//
// function addsub1
//
//===============================================================
// parameter : ax,bx : char array with 2 integer numbers without sign
//             cx : output string
//             as : char + or - 
// function returns pointer to cx
//===============================================================
  char *addsub1(ax,bx,cx,as)
   char *ax,*bx,*cx;
   char as;
   {
    int i, j, c,  ii, jj;
    int add_la, add_lb, add_lmax, add_x;
    char *pa, *pb, *pc;
    char axx[3];
    char bxx[3];
    char cxx[3];
    int ia,ib,add_carry, pm, add_out;

    add_la = strlen(ax);
    add_lb = strlen(bx);
    add_lmax = add_lb;
    add_lmax = ( add_la > add_lb) ? add_la : add_lb;
    if(debug) {
        printf("addsub1 ax: %s\n", ax);
        printf("addsub1 bx: %s\n", bx);
        printf("addsub1: la,lb,sign: %d %d %c\n", add_la, add_lb, as);
    }
//
// set pointers to end of string
//
    pa = ax;
    pa--;
    axx[1] = '\0';
    for(i=1; i<=add_la; i++){
      pa++;
    }
    pb = bx;
    pb--;
    axx[1] = '\0';
    for(i=1; i<=add_lb; i++){
      pb++;
    }
//
//-----------------------
// + -
    if(as == '+') {
     pm = 1;
    } else if (as == '-') {  
     pm=0;
    } else {
     printf("addsub1 error: Illegal sign\n");
     strcat(cx , "addsub1 error");
     return(cx);
    }
// -----------------------
    ii=0; jj=0;
    add_carry = 0;
//----------------------------------------
    pc = cx;
    strcpy( pc,"");
    cxx[1] = '\0';
//----------------------------------------
// loop all characters
    for(i=1; i<=add_lmax; i++){
      ii++; jj++;
      if(ii <= add_la) {
        axx[0] = *pa;
        pa--;
      } else {
         axx[0] = '0';
      }
      if(jj <= add_lb) {
	bxx[0] = *pb;
        pb--;
      } else {
        bxx[0] = '0';
      }
      if(debug) printf("addsub1: i=%d c=%c %c %d %d\n", i, axx[0], bxx[0], axx[0], bxx[0]);
      ia = (int)axx[0] - 48; // - '0'
      ib = (int)bxx[0] - 48;
      
      if(pm) {
         add_out = ia + ib + add_carry;
         add_carry = 0;
         if( add_out > 9) {
         add_out = add_out - 10;
         add_carry = 1;
         }
      }
      if(!pm) {
         add_out = ia ;
         add_x = ib + add_carry ;
         add_carry = 0;
         if( add_out < add_x ) {
           add_out = add_out + 10;
           add_carry = 1;
         }
         add_out = add_out - add_x;
      }
     cxx[0] = (char)( add_out + 48);
     strcat( pc, cxx);
    }
// ende loop
//----------------------------------------
// add : add carry
     if(pm) {
       if(add_carry) strcat( pc, "1");
     }
// reverse string
     for(i=0,j=strlen(pc)-1; i < j; i++,j--) {
        c = cx[i];
        cx[i] = cx[j];
        cx[j] = c;
     }
// sub:  remove leading 0 or create 0 
    if(!pm) {
      pc = strpbrk(pc,"123456789");
      if(pc == NULL ) {
        pc = cx;
        strcpy(pc,"0");
      }
    }
    if( debug) printf("addsub1: out: %s \n", pc);
     strcpy( cx, pc);
    return(cx);
   } 
//===================================================================
//      strchar : finde Zeichen n string s auf Position p 
//===================================================================
  char strchar(s, pos) 
   char *s ;
   int pos ;
  {
    int n,i;
    char *p;
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
  }
//===============================================================
//
//    function mult
//
//===============================================================
// parameter : ay * by ... result cy
//             returns pointer to cy
//===============================================================
char *mult(ay,by,cy)
    char *ay,*by,*cy;
    {
    char signx[3], signy[3];
    char *pa, *pb ;
    char mult_signa, mult_signb, mult_sigmult;
    int la, lb;
//
    char *pmz[10];
    char mz1[ARRAYLENGTH] ;
    char mz2[ARRAYLENGTH] ;
    char mz3[ARRAYLENGTH] ;
    char mz4[ARRAYLENGTH] ;
    char mz5[ARRAYLENGTH] ;
    char mz6[ARRAYLENGTH] ;
    char mz7[ARRAYLENGTH] ;
    char mz8[ARRAYLENGTH] ;
    char mz9[ARRAYLENGTH] ;
//
    char mult_mult2[ARRAYLENGTH] ;
    char mult_mult3[ARRAYLENGTH] ;
    char *z2, *z3;
    char mult_result[ARRAYLENGTH];
    char mult_digten[ARRAYLENGTH];
    char mult_zsum[ARRAYLENGTH];

    int mult_mlb, mult_mjm, mult_mim;
    int mult_i, i;
    int mult_z;
//
// check for valid input here
//
   if( strlen(ay) < 1){
     printf( "mult: Input Error mult \n");
     printf( "mult: Zero length string a\n");
     printf( "mult: === mult terminated abnormally ===\n");
     strcpy( cy,"mult error");
     return( cy);
   }
   if( strlen(by) < 1) {
     printf( "mult: Input Error mult \n");
     printf( "mult: Zero length string b\n");
     printf( "mult: === mult terminated abnormally ===\n");
     strcpy( cy,"mult error");
     return( cy);
   }
//
// check and remove sign
//
   if(multdebug) {
     printf("mult: ay  %s\n", ay);
     printf("mult: by  %s\n", by);
   }
//
// 0 result
//
   if( (strncmp( ay, "0", 1) == 0)  || ( strncmp( by ,"0",1) == 0)) {
     strcpy( cy,"0");
     return( cy);
   }
//
// find signs
//
   strncpy( signx, ay, 1);
   strncpy( signy, by, 1);
   signx[1] = '\0';
   signy[1] = '\0';
   if( multdebug ) printf("mult signs;  %s %s \n", signx , signy);
//
// get final sign
//
   if((strncmp(signx , "-", 1)) == 0) {mult_signa = '-';}
   else {mult_signa = '+';}
   if((strncmp(signy , "-", 1)) == 0) {mult_signb = '-';}
   else {mult_signb = '+';}
   if( multdebug) printf("multmult: signa,signb %c %c\n", mult_signa, mult_signb);
//
// final sign
//
   mult_sigmult = '+';
   if((mult_signa == '+') && (mult_signb == '-')) mult_sigmult = '-';
   if((mult_signa == '-') && (mult_signb == '+')) mult_sigmult = '-';
   pa = ay;
   pb = by;
//
// remove sign
//
   pa = strpbrk(pa,"123456789");
   pb = strpbrk(pb,"123456789");
   la = strlen( pa);
   lb = strlen( pb);
   //strcpy( ay, pa);
   //strcpy( by, pb);
   if(multdebug) {
     printf("mult: ay  %s\n", ay);
     printf("mult: by  %s\n", by);
   }
   if(multdebug) printf("mult: la,lb : %d %d\n", la, lb);
//
// pointers to  buffer for multiplied values
// 
   pmz[1] = mz1;
   pmz[2] = mz2;
   pmz[3] = mz3;
   pmz[4] = mz4;
   pmz[5] = mz5;
   pmz[6] = mz6;
   pmz[7] = mz7;
   pmz[8] = mz8;
   pmz[9] = mz9;
//
// create array with multiplied numbers
// multiply from from 2 to 9
//
   z2= mult_mult2;
   z3= mult_mult3;
   for(mult_mim = 2 ; mult_mim <= 9; mult_mim++) {
   strcpy( mult_mult2 ,"0");
     for(mult_mjm = 1; mult_mjm <= mult_mim ; mult_mjm++) {
       z3= addsub1(pa, z2, mult_mult3,'+');
       strcpy( z2, z3);
     }
     strcpy(pmz[mult_mim], z2);
   } 
   strcpy(pmz[1], pa);
   for(i=1; i<=9; i++) {
     if (multdebug) printf("i= %d %s\n", i, pmz[i]);
   }
//
// get length 
   mult_mlb = lb;
// set pointer to end
    //pb=by;
    pb--;
    for(i=1; i<=mult_mlb; i++) pb++;
//
// add multiplied numbers to final result and
// shift by adding 0
   strcpy(mult_result,"");
   strcpy(mult_digten,"");
//--------------------------
   for (mult_i = 1 ; mult_i <= mult_mlb ; mult_i++) {
     mult_z = *pb - 48;
     if(multdebug) printf("mult: %d %d \n", mult_i, mult_z);
      if(mult_z == 0) {
        strcat( mult_digten ,"0");
        pb--;
        continue;
      }
      strcpy(mult_zsum, pmz[mult_z]);
      strcat(mult_zsum, mult_digten);
      z3 = addsub1(mult_zsum,mult_result,mult_mult3,'+');
      strcpy(mult_result, z3);
      if(multdebug) printf("mult: result: %s\n", mult_result);
      strcat( mult_digten ,"0");
      pb--;
   }
//--------------------------
   if(mult_sigmult == '-') {
     strcpy( cy, "-");
   } else {
     strcpy( cy, "");
   }
   strcat( cy, mult_result);
   return( cy );
}
//===============================================================
//
//                       function div 
//  slow version of div
//
//===============================================================
// parameter : ay / by ... result cy , mod dy
//             returns pointer to cy
//             ay = cy * by + dy
// attention : ay and by is modified, must be stored
//===============================================================
//  attention : ouput of sign not finished, add from divf
//===============================================================
char *div(ay,by,cy,dy)
    char *ay,*by,*cy,*dy;
    {
    char signx[3], signy[3];
    char *pa, *pb ;
    char div_signa, div_signb, div_sigdiv;
    int la, lb;
    int div_i, div_cnt; 
    char divbuf1[ARRAYLENGTH];
    char divbuf2[ARRAYLENGTH];
    char *z1, *z2;
    char cdiv_cnt[3];
    int ll, j, div_0;
//
// check for valid input here
//
   if( strlen(ay) < 1){
     printf( "div:  Input Error div \n");
     printf( "div:  Zero length string a\n");
     printf( "div:  === div terminated abnormally ===\n");
     strcpy( cy,"div error");
     return( cy);
   }
   if( strlen(by) < 1) {
     printf( "div:  Input Error div \n");
     printf( "div:  Zero length string b\n");
     printf( "div:  === div terminated abnormally ===\n");
     strcpy( cy,"div error");
     return( cy);
   }
//
// check and remove sign
//
   if(divdebug) {
     printf("div: ay  %s\n", ay);
     printf("div: by  %s\n", by);
   }
//
// find signs
//
   strncpy( signx, ay, 1);
   strncpy( signy, by, 1);
   signx[1] = '\0';
   signy[1] = '\0';
   if( divdebug ) printf("div signs:  %s %s \n", signx , signy);
//
// get final sign
//
   if((strncmp(signx , "-", 1)) == 0) { div_signa = '-';}
   else { div_signa = '+';}
   if((strncmp(signy , "-", 1)) == 0) { div_signb = '-';}
   else { div_signb = '+';}
   if( divdebug) printf("div: signa,signb %c %c\n",  div_signa,  div_signb);
//
// final sign
//
   div_sigdiv = '+';
   if(( div_signa == '+') && ( div_signb == '-'))  div_sigdiv = '-';
   if(( div_signa == '-') && ( div_signb == '+'))  div_sigdiv = '-';
   pa = ay;
   pb = by;
//
// remove sign
//
   if(strncmp(pa,"0",1) != 0) pa = strpbrk(pa,"123456789");
   if(strncmp(pb,"0",1) != 0) pb = strpbrk(pb,"123456789");
   la = strlen( pa);
   lb = strlen( pb);
   strcpy( ay, pa);
   strcpy( by, pb);
   if(divdebug) printf("div: la,lb : %d %d\n", la, lb);
//
// dividend < divisor
//
  if( la < lb ) {
   strcpy( cy, "0" );
   strcpy( dy, ay );
   return( cy );
  }
//
// divisor = 0
//
  if( strncmp( by, "0", 1) == 0) {
    printf( "div: Zero division error\n");
    printf( "div: === div terminated abnormally ===\n");
    strcpy( cy,"div error");
    return( cy);
  }
//
//  number of 0 and number of digits to add
//
  div_0 = 0;
  for( j = 1; j <= la - lb ; j++) {
   div_0++;
   strcat( by, "0");
  }
  if(divdebug) printf("by: %s\n", by);
// 
// subtract divisor from dividend down to 0
// count number of subtractions
//
  strcpy( divbuf2, "");
  z1 = divbuf1;
  if(divdebug) printf( "div: ---------- begin mainloop ----------\n");
//
// main loop 
//------------------------------------------------------
  for ( div_i = 1 ; div_i <= div_0 + 1; div_i ++) {
      if(divdebug) printf( "div: ---------- div_i: %d ----------\n", div_i);
      div_cnt = 0;
      for(;;) {
          div_cnt++;
          if(divdebug) printf( "div: before add : ay, by: %s %s\n",ay,by);
          z1 = addsub(ay,by,divbuf1,'-');
          if(divdebug) printf( "div: after add  : ay, by, sum: %s %s %s\n",ay,by,z1);
          strcpy( ay, z1);
          if( ay[0] == '-' ) {
            if(divdebug) printf( "div: add correct ay,by:%s %s\n",ay,by);
            z1 = addsub(ay,by, divbuf1,'+');
            strcpy( ay, z1);
            div_cnt--;
            break;
          }
      }
      if(divdebug) printf( "div: sum, count: %s %d\n", ay, div_cnt);
      // remove last 0 of string	
      ll = strlen(by);
      by[ll-1] = '\0';
      // append result
      cdiv_cnt[0] = (char) (div_cnt + 48);
      cdiv_cnt[1] = '\0';
      strcat( divbuf2, cdiv_cnt);
      if(divdebug) printf("div: append : %s \n", divbuf2);
  }
//------------------------------------------------------
  if(divdebug) printf( "div: ---------- end mainloop ----------\n");
// 
//
  strcpy( dy,ay);
//
// remove leading 0 or create 0
//
  strcpy( cy,divbuf2);
  z2 = strpbrk(cy,"123456789");
  if( z2 == NULL) {
     strcpy( cy, "0");
  } else {
     strcpy( cy, z2);
  }
  if( divdebug) printf("div: quot, mod : %s %s\n", cy, dy);
//
// add sign
//
  strcpy( divbuf1, cy);
  if(div_sigdiv == '-') {
    strcpy( cy, "-");
  } else {
    strcpy( cy, "");
  }
  strcat( cy, divbuf1);
  if( divdebug) printf("div: quot, mod : %s %s\n", cy, dy);
  return( cy );
  }
// end function div
//===============================================================
//
//    function divf 
//    fast division
//
//===============================================================
// parameter : ay / by ... result cy , mod dy
//             returns pointer to cy
//             ay = cy * by + dy
// attention : ay and by is modified, must be stored
//===============================================================
// algorithm :
//    -  find difference in length of dividend and divisor
//       and add 0 digits to divisor
//    -  divisor is multiplied 2 - 9 and stored 
//    -  find position of dividend in stored array by string compare 
//       strcmp returns -, 0 ,+
// 
//===============================================================
char *divf(ay,by,cy,dy)
    char *ay,*by,*cy,*dy;
    {
    char signx[3], signy[3];
    char *pa, *pb ;
    char div_signa, div_signb, div_sigdiv;
    int la, lb;
    int div_i, div_cnt1; 
    char divbuf1[ARRAYLENGTH];
    char divbufx[ARRAYLENGTH];
    char *z1, *z2, *z3;
    int j, div_0;
    char mult_mult2[ARRAYLENGTH];
    char mult_mult3[ARRAYLENGTH];
    int mim,mjm;
    int slen[15], alen, icomp, breakflag,  pos;
    char cdiv_cnt1[3];
// 
    char *pdz[10];
    char dz1[ARRAYLENGTH] ;
    char dz2[ARRAYLENGTH] ;
    char dz3[ARRAYLENGTH] ;
    char dz4[ARRAYLENGTH] ;
    char dz5[ARRAYLENGTH] ;
    char dz6[ARRAYLENGTH] ;
    char dz7[ARRAYLENGTH] ;
    char dz8[ARRAYLENGTH] ;
    char dz9[ARRAYLENGTH] ;
//
// check for valid input here
//
   if( strlen(ay) < 1){
     printf( "div:  Input Error div \n");
     printf( "div:  Zero length string a\n");
     printf( "div:  === div terminated abnormally ===\n");
     strcpy( cy,"div error");
     return( cy);
   }
   if( strlen(by) < 1) {
     printf( "div:  Input Error div \n");
     printf( "div:  Zero length string b\n");
     printf( "div:  === div terminated abnormally ===\n");
     strcpy( cy,"div error");
     return( cy);
   }
//
// check and remove sign
//
   if(divfdebug) {
     printf("div: ay  %s\n", ay);
     printf("div: by  %s\n", by);
   }
//
// find signs
//
   strncpy( signx, ay, 1);
   strncpy( signy, by, 1);
   signx[1] = '\0';
   signy[1] = '\0';
   if( divfdebug ) printf("div signs:  %s %s \n", signx , signy);
//
// get final sign
//
   if((strncmp(signx , "-", 1)) == 0) { div_signa = '-';}
   else { div_signa = '+';}
   if((strncmp(signy , "-", 1)) == 0) { div_signb = '-';}
   else { div_signb = '+';}
   if( divfdebug) printf("div: signa,signb %c %c\n",  div_signa,  div_signb);
//
// final sign
//
   div_sigdiv = '+';
   if(( div_signa == '+') && ( div_signb == '-'))  div_sigdiv = '-';
   if(( div_signa == '-') && ( div_signb == '+'))  div_sigdiv = '-';
   pa = ay;
   pb = by;
//
// remove sign
//
   if(strncmp(pa,"0",1) != 0) pa = strpbrk(pa,"123456789");
   if(strncmp(pb,"0",1) != 0) pb = strpbrk(pb,"123456789");
   la = strlen( pa);
   lb = strlen( pb);
   strcpy( ay, pa);
   strcpy( by, pb);
   if(divfdebug) printf("div: la,lb : %d %d\n", la, lb);
//
// dividend < divisor
//
  if( la < lb ) {
   strcpy( cy, "0" );
   strcpy( dy, ay );
   return( cy );
  }
//
// divisor = 0
//
  if( strncmp( by, "0", 1) == 0) {
    printf( "div: Zero division error\n");
    printf( "div: === div terminated abnormally ===\n");
    strcpy( cy,"div error");
    return( cy);
  }
//
// pointers to  buffer for multiplied divisor values
// 
   pdz[1] = dz1;
   pdz[2] = dz2;
   pdz[3] = dz3;
   pdz[4] = dz4;
   pdz[5] = dz5;
   pdz[6] = dz6;
   pdz[7] = dz7;
   pdz[8] = dz8;
   pdz[9] = dz9;
//
//  number of 0 and number of digits to add
//
   div_0 = 0;
   for( j = 1; j <= la - lb ; j++) {
    div_0++;
    strcat( by, "0");
   }
   if(divfdebug) printf("by: %s\n", by);
//
// create array with multiplied numbers of divisor
// multiply from from 2 to 9
//
   z2= mult_mult2;
   z3= mult_mult3;
   for(mim = 2 ; mim <= 9; mim++) {
   strcpy( mult_mult2 ,"0");
     for(mjm = 1;mjm <= mim ; mjm++) {
       z3= addsub1(by, z2, mult_mult3,'+');
       strcpy( z2, z3);
     }
     strcpy(pdz[mim], z2);
   } 
   strcpy(pdz[1], by);
   for(mim=1; mim<=9; mim++) {
     slen[mim]= strlen(pdz[mim]);
     if (divfdebug) printf("i= %d %s %d\n", mim, pdz[mim], slen[mim]);
   }
//----------------------------------------------------
// 
// find position of dividend in array : this is the quotient
//
   strcpy( divbufx, "");
   z1 = divbuf1;
   if(divfdebug) printf( "div: ---------- begin mainloop ----------\n");
//
// main loop 
//------------------------------------------------------
//  loop over difference of digits dividend/divisor
//  dividend is compared with array of divisor multiplied by 1-9 ( same string length )
//  strcmp returns -, 0, + : find position : this is one digit of quotient 
//  divisor array is shorted by one digit after comparison
//  attentio :
//  3 extra conditions are handelt after multiplied divisor comparison :
//    - 0 condition :  eg quotient  1234000012 : string length slen > alen 
//    - 9 contition :  eg quotien  12399  : string length slen < alen 
//    - extra condition : sting length changes in loop
//                  eg compare  970  against 300/600/900/1200
//                      900 to low, 1200 string longer
//
  div_cnt1 = 0;
//
  for ( div_i = 1 ; div_i <= div_0 + 1; div_i ++) {
      if(divfdebug) printf( "div: ---------- div_i: %d ----------\n", div_i);
          alen = strlen(ay);
          breakflag = 0;
          pos = 0;
          //----------------------
           for(mim=1; mim<=9; mim++) {
            if( divdebug) printf( " mim: %d  slen: %d alen: %d\n",mim,slen[mim], alen);
            if( slen[mim] == alen ) {
             pos = mim;
             icomp = strcmp( pdz[mim], ay);
             if(divfdebug) printf("    compare : %s %s %d pos: %d\n", ay,pdz[mim],icomp, mim); 
             if(icomp > 0) {
                div_cnt1 = mim - 1;
               if(divfdebug) printf( ">>>>>>> gt 0  %d\n", div_cnt1);
               breakflag = 1;
               break;
             } 
             if(icomp == 0) {
                div_cnt1 = mim;
               if(divfdebug) printf( ">>>>>>> eq 0%d\n", div_cnt1);
               breakflag = 1;
               break;
             } 
            } 
           }
          //----------------------
          //
          //  very important :
          //  correct 3 special cases 
          //
          // string length changes in compare loop and no result found
           if(!breakflag && pos > 0) {
               div_cnt1 = pos;
               if( divdebug) printf( "special case length change : pos : %d\n", pos);
           }
           // string length not equal :  slen < alen  , quotient digit = 9 
           if( slen[9] + 1 == alen ) {
               div_cnt1 = 9;
               if( divdebug) printf( "special case 9 : pos : %d\n", pos);
           // string length not equal :  slen > alen , quotient digit = 0 
           } else if(pos == 0 ) {
               if( divdebug) printf( "special case 0 : pos : %d\n", pos);
               div_cnt1 = 0;
           }
           if(divfdebug)
              printf( ">>>>>>> count : %d break : %d pos : %d <<<<<<\n", div_cnt1, breakflag, pos);
           if(div_cnt1 > 0) {
              z1 = addsub(ay,pdz[div_cnt1],divbuf1,'-');
              if(divfdebug) printf( "div: after add  : ay, by, sum: %s %s %s\n",ay,by,z1);
              strcpy( ay, z1);
           }
           //  divide divisor by 10 by removing last character(0)
           dz1[slen[1]-1] = '\0';
           dz2[slen[2]-1] = '\0';
           dz3[slen[3]-1] = '\0';
           dz4[slen[4]-1] = '\0';
           dz5[slen[5]-1] = '\0';
           dz6[slen[6]-1] = '\0';
           dz7[slen[7]-1] = '\0';
           dz8[slen[8]-1] = '\0';
           dz9[slen[9]-1] = '\0';
           // reduce length by 1 
           for(mim=1; mim<=9; mim++) {
             slen[mim]--;
           }
           // append result
           cdiv_cnt1[0] = (char) (div_cnt1 + 48);
           cdiv_cnt1[1] = '\0';
           strcat( divbufx, cdiv_cnt1);
           if(divfdebug) printf("div: append : %s \n", divbufx);
  }
//------------------------------------------------------
  if(divfdebug) printf( "div: ---------- end mainloop ----------\n");
// 
//
  strcpy( dy,ay);
//
// remove leading 0 or create 0
//
  strcpy( cy,divbufx);
  z2 = strpbrk(cy,"123456789");
  if( z2 == NULL) {
     strcpy( cy, "0");
  } else {
     strcpy( cy, z2);
  }
//
// add sign
//
  strcpy( divbuf1, cy);
  if(div_sigdiv == '-') {
    strcpy( cy, "-");
  } else {
    strcpy( cy, "");
  }
  strcat( cy, divbuf1);
  if( divfdebug) printf("div: quot, mod : %s %s\n", cy, dy);
  return( cy );
  }
//===============================================================
//
//  function euclidext
//  extended euclid algorithmn
//
//===============================================================
//
// algorithm fromPC Magazin "Kryptographie"
// solve equation  e*d mod (p-1) * (q-1) = 1
// find d     
// p and q are prime  n = p * q , e = public exponent, n public mod
// sources : 1.) Buchmann : Einfuehrung in die Kryptographie:
//                   Erweiterter Euklidischer Algorithmus
//           2.) Rudolf Kippenhan : Verschluesselte Botschaften 
//                   Anhang C
//
//===============================================================
  char *euclidext(e, p, q, d)
   char *e, *p, *q, *d;
  {
   char pmin1[ARRAYLENGTH];
   char qmin1[ARRAYLENGTH];
   char p1q1[ARRAYLENGTH];
   char a[ARRAYLENGTH];
   char b[ARRAYLENGTH];
   char s1[ARRAYLENGTH];
   char s2[ARRAYLENGTH];
   char s[ARRAYLENGTH];
   char t1[ARRAYLENGTH];
   char t2[ARRAYLENGTH];
   char t[ARRAYLENGTH];
   char dummy1[ARRAYLENGTH];
   char dummy2[ARRAYLENGTH];
   char qx[ARRAYLENGTH];
   char r[ARRAYLENGTH];
//
   char eins[10] = "1";
   char null[10] = "0";
   char *p_pmin1, *p_qmin1, *pa;
   int iteration;
//
   printf( "----- extended euclid algorithm -----\n");
//
// p-1, q-1
//
   p_pmin1 = pmin1;
   p_qmin1 = qmin1;
   p_pmin1 = addsub(p,eins,pmin1,'-'); 
   p_qmin1 = addsub(q,eins,qmin1,'-'); 
   printf( "input : (p-1) (q-1) :  %s %s \n", p_pmin1, p_qmin1);
   printf( "input :           e :  %s \n", e);
   pa = a;
   pa = mult( p_pmin1, p_qmin1, a);   
// save (p-1) * (q-1) 
   strcpy(p1q1, pa);
//
// setup
//
   strcpy(b,e);
   strcpy(s1,eins);
   strcpy(s2,null);
   strcpy(s,null);
   strcpy(t1,null);
   strcpy(t2,eins);
   strcpy(t,eins);

   iteration = 0;
//
// main loop
//
//---------------------------------------------------
  for(;;) {
   iteration ++;
   printf("------------------ %d ---------------------\n", iteration);
   strcpy( dummy1, a);
   strcpy( dummy2, b);
   div( dummy1, dummy2, qx, r);
   printf("      a : %s    b : %s\n" ,a,b);
   printf("   quot : %s  mod : %s\n" ,qx,r);
   if( strncmp(r ,"0", 1) == 0) break;
   // s= s1 - q * s2
   mult(qx, s2, dummy1 );
   addsub(s1, dummy1, s, '-');
   printf("s1,q*s2,s: %s %s %s\n", s1,dummy1,s);
   // t= t1 - q * t2
   mult(qx, t2, dummy1 );
   addsub(t1, dummy1, t, '-');
   printf("t1,q*t2,t: %s %s %s\n", t1,dummy1,t);
   //
   strcpy( s1, s2);
   strcpy( s2, s);
   strcpy( t1, t2);
   strcpy( t2, t);
   strcpy( a, b);
   strcpy( b, r);
  }
//---------------------------------------------------
//
// make correction if t negativ
// replace d(t) by : d = d + (p-1)(q-1)
//
   if(strncmp(t,"-",1) == 0) {
     printf(">>>> make  correction:  t : t = t + (p-1)(q-1) <<<<\n");
     addsub(t, p1q1, dummy1,'+');
     strcpy( t, dummy1);
   }
   printf("------------------ solution --------------------\n");
   printf(" Equation : 1 = e * d + s * n\n");
   printf("     e : %s\n", e);
   printf("     p : %s\n", p);
   printf("     q : %s\n", q);
   printf("     d : %s\n", t);
   printf("     s : %s\n", s);
   printf(" p1*q1 : %s\n", p1q1);
   printf("------------------------------------------------\n");
//
//  check
//
   printf(" check : e * d mod (p-1)(q-1) =? 1\n");
   mult(e, t, dummy1);
   printf("   e * d : %s\n", dummy1);
   div(dummy1, p1q1, dummy2,r);
   printf("   quot  : %s\n", dummy2);
   printf("   mod   : %s\n", r);
//
   printf("----- end of extended euclid algorithm -----\n");
   strcpy(d,t);
   return(d);
  }
//====================================================================
//
//  function modexp
//
//====================================================================
// compute pow (a,b) mod n with binary multiply
// attention : a is modified
//====================================================================
// algorithm for a^b modn
//  huge a,b,y
//  y = 1
//  for all bits in b do ( from low bit to to high)
//    if bit == 1 do
//      y = (y * a) mod n
//    end if
//    a = (a * a) mod n
//  end for
// return y
//====================================================================
 char *modexp(a, b, n, res)
   char *a, *b, *n, *res;
   { 
   char outbin[ARRAYLENGTH];
   char outhex[ARRAYLENGTH];
   char multres[ARRAYLENGTH];
   char divisor[ARRAYLENGTH];
   char quot[ARRAYLENGTH];
   char mod[ARRAYLENGTH];
   char y[ARRAYLENGTH];
   int i, ll;
   int cc;
   char bit;
   // convert b to bin
   if(modexpdebug) {
   printf( "------- pow (a,b) mod n ------\n");  
   printf( "a : %s\n", a);
   printf( "b : %s\n", b);
   printf( "n : %s\n", n);
   }
   bcd_binhex(b, outbin, outhex);
   if(modexpdebug) {
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   }
   // get binary string
   ll = strlen(outbin);
   strcpy(y,"1");
   cc=0;
//-----------------------------------------------
   if(modexpdebug) printf("---------- main loop ----------\n");
   for(i=ll; i >= 1; i--) {
    cc++;
    bit = strchar(outbin,i);
    if(cc == 10) {
      printf(" %d\n ",i);
      cc = 0;
    }
    if(bit == '1') {
      mult(y, a, multres);
      if(modexpdebug) printf( "bit: %d  y*a: %s\n", i, multres);
      strcpy(divisor,n);  
      divf(multres, divisor, quot, mod);
      strcpy(y, mod);
      if(modexpdebug) printf("   y*a mod n: %s\n", y);
    }
    mult(a, a, multres);
    if(modexpdebug) printf("bit: %d  a*a: %s\n",i, multres);
    strcpy(divisor,n);  
    divf(multres, divisor, quot, mod);
    strcpy(a, mod);
    if(modexpdebug) printf("  a*a mod n: %s\n", a);
    }
   if(modexpdebug) printf("---------- main loop end ----------\n");
// -----------------------------------------------
  strcpy(res, y);
  if(modexpdebug) printf("Result : %s\n", res);
  return(res);
 }
//================================================================
//                          modexpf
//================================================================
// what is implemented :
//  array n*1,n*2,....n*9 is created one time for whole modexpf
//  and copied to division divff  
//  this saves about 15 % time
//================================================================
// how to get faster modexp ??
// algorithm for a^b modn
//  huge a,b,y
//  y = 1
//  for all bits in b do ( from low bit to to high)
//    if bit == 1 do
//      y = (y * a) mod n
//    end if
//    a = (a * a) mod n
//  end for
// return y
//================================================================
// idea : 
// 1. create n*1, n*2,n*3 ......n*9 only once for whole job
//    this saves a lot of time for division, because is done now for every
//    iteration at least one time (or 2 times)
//    fill with 0 until end of buffer, add \0 for each division again
//    at correct position
// 2. create a*1, a*2,a*3 ,.....a*9 only one time for each loop, now
//    2 times if bit == 1
// 3. extra mult div function without any sign checks
// 4. strchar replace by outbin[x] == '1'
//================================================================
//   strcpy(y,"1");
//   for(i=ll; i >= 1; i--) {
//    // get bit
//    bit = strchar(outbin,i);
//    if(bit == '1') {
//      mult(a, y, multres);
//      strcpy(divisor,n);  
//      divf(multres, divisor, quot, mod);
//      strcpy(y, mod);
//    }
//    mult(a, a, multres);
//    strcpy(divisor,n);  
//    divf(multres, divisor, quot, mod);
//    strcpy(a, mod);
//    }
//================================================================
 char *modexpf(a, b, n, res)
   char *a, *b, *n, *res;
   { 
   char outbin[ARRAYLENGTH];
   char outhex[ARRAYLENGTH];
   char multres[ARRAYLENGTH];
   char quot[ARRAYLENGTH];
   char mod[ARRAYLENGTH];
   char y[ARRAYLENGTH];
   int  i, ll;
   int  cc;
   char bit;
//
   char *pdz[10];
   char dz1[ARRAYLENGTH];
   char dz2[ARRAYLENGTH];
   char dz3[ARRAYLENGTH];
   char dz4[ARRAYLENGTH];
   char dz5[ARRAYLENGTH];
   char dz6[ARRAYLENGTH];
   char dz7[ARRAYLENGTH];
   char dz8[ARRAYLENGTH];
   char dz9[ARRAYLENGTH];
//
   char *pdzsave[10];
   char dz1save[ARRAYLENGTH];
   char dz2save[ARRAYLENGTH];
   char dz3save[ARRAYLENGTH];
   char dz4save[ARRAYLENGTH];
   char dz5save[ARRAYLENGTH];
   char dz6save[ARRAYLENGTH];
   char dz7save[ARRAYLENGTH];
   char dz8save[ARRAYLENGTH];
   char dz9save[ARRAYLENGTH];
//
   char mult_mult2[ARRAYLENGTH];
   char mult_mult3[ARRAYLENGTH];
   char *z2, *z3;
   int mim, mjm;
   int slensave[15];
//
// convert b to bin
   printf( "------- fast version of pow (a,b) mod n ------\n");  
   if(modexpfdebug) {
   printf( "------- fast version of pow (a,b) mod n ------\n");  
   printf( "a : %s\n", a);
   printf( "b : %s\n", b);
   printf( "n : %s\n", n);
   }
   bcd_binhex(b, outbin, outhex);
   if(modexpfdebug) {
   printf("bin: %s\n",outbin);
   printf("hex: %s\n",outhex);
   }
   //printf( "------- create buffer arrays ------\n");  
   // get binary string
   ll = strlen(outbin);
   //strcpy(divisor,n);  
//
// pointers to  buffer for multiplied divisor values
// 
   pdzsave[1] = dz1save;
   pdzsave[2] = dz2save;
   pdzsave[3] = dz3save;
   pdzsave[4] = dz4save;
   pdzsave[5] = dz5save;
   pdzsave[6] = dz6save;
   pdzsave[7] = dz7save;
   pdzsave[8] = dz8save;
   pdzsave[9] = dz9save;
   pdz[1] = dz1;
   pdz[2] = dz2;
   pdz[3] = dz3;
   pdz[4] = dz4;
   pdz[5] = dz5;
   pdz[6] = dz6;
   pdz[7] = dz7;
   pdz[8] = dz8;
   pdz[9] = dz9;
//
// create array with multiplied numbers of divisor (n only)  
// multiply n from 2 to 9, copy 1
// slensave is the original length of n values 
//
   z2= mult_mult2;
   z3= mult_mult3;
   for(mim = 2 ; mim <= 9; mim++) {
   strcpy( mult_mult2 ,"0");
     for(mjm = 1;mjm <= mim ; mjm++) {
       z3= addsub1(n, z2, mult_mult3,'+');
       strcpy( z2, z3);
     }
     strcpy(pdzsave[mim], z2);
   } 
   strcpy(pdzsave[1], n);
   for(mim=1; mim<=9; mim++) {
     slensave[mim]= strlen(pdzsave[mim]);
     if (modexpfdebug) printf("i= %d %s %d\n", mim, pdzsave[mim], slensave[mim]);
   }
   for(mim=1; mim<=9; mim++) {
     strcpy( pdz[mim], pdzsave[mim]);
   }
//
   strcpy(y,"1");
   cc=0;
//-----------------------------------------------
   printf("---------- main loop modexpf ----------\n");
   if(modexpfdebug) printf("---------- main loop modexpf start ----------\n");
   for(i=ll; i >= 1; i--) {
    cc++;
    bit = strchar(outbin,i);
    if(cc == 10) {
      printf(" bit:  %d\n",i);
      cc = 0;
    }
    if(bit == '1') {
      mult(y, a, multres);
      if(modexpfdebug) printf( "bit: %d  y*a: %s\n", i, multres);
      for(mim=1; mim<=9; mim++) {
       strcpy( pdz[mim], pdzsave[mim]);
      }
      divff(multres,quot,mod,dz1,dz2,dz3,dz4,dz5,dz6,dz7,dz8,dz9,slensave);
      strcpy(y, mod);
      if(modexpfdebug) printf("   y*a mod n: %s\n", y);
    }
    mult(a, a, multres);
    if(modexpfdebug) printf("bit: %d  a*a: %s\n",i, multres);
    for(mim=1; mim<=9; mim++) {
      strcpy( pdz[mim], pdzsave[mim]);
    }
    divff(multres,quot,mod,dz1,dz2,dz3,dz4,dz5,dz6,dz7,dz8,dz9,slensave);
    strcpy(a, mod);
    if(modexpfdebug) printf("  a*a mod n: %s\n", a);
    }
   if(modexpfdebug) printf("---------- main loop modexpf end ----------\n");
   printf("---------- main loop modexpf end ----------\n");
// -----------------------------------------------
  strcpy(res, y);
  if(modexpfdebug) printf("Result : %s\n", res);
  return(res);
 }
//================================================================
//  function divff
//  attention : only for fast modexp
//================================================================
// algorithmus same as difv, but multiplied divisor values are 
// only computed once and passed by parameter
//  ay ... dividened
//  cy ... quotent ,   dy .... mod
//================================================================
char *divff(ay,cy,dy, dz1,dz2,dz3,dz4,dz5,dz6,dz7,dz8,dz9,slen0)
    char *ay,*cy,*dy,*dz1,*dz2,*dz3,*dz4,*dz5,*dz6,*dz7,*dz8,*dz9;
    int *slen0;
    {
    int la, lb;
    int div_i, div_cnt1; 
    char divbuf1[ARRAYLENGTH];
    char divbuf2[ARRAYLENGTH];
    char divbufx[ARRAYLENGTH];
    char *z1, *z2 ;
    int j, div_0;
    int mim, difflen;
    int alen, icomp, breakflag,  pos;
    char cdiv_cnt1[3];
//
    int slen[15];
    char *pdz[10];
//
  if( divffdebug) {
     printf("-------------------------------- begin divff --------------------------------\n");
     printf("div:  dividend: %s    %d  \n", ay, strlen(ay));
     printf("div:  divisor : %s    %d  \n", dz1, strlen(dz1));
  }
   la = strlen(ay);
   lb = strlen(dz1);
   div_0 = 0;
//
   difflen = la - lb;
   strcpy( divbuf2,"");
   // printf(" la-lb: %d \n", difflen);
   for( j = 1; j <= difflen ; j++) {
    div_0++;
    strcat( divbuf2,"0");
   }
    strcat( dz1, divbuf2);
    strcat( dz2, divbuf2);
    strcat( dz3, divbuf2);
    strcat( dz4, divbuf2);
    strcat( dz5, divbuf2);
    strcat( dz6, divbuf2);
    strcat( dz7, divbuf2);
    strcat( dz8, divbuf2);
    strcat( dz9, divbuf2);
//
   pdz[1] = dz1;
   pdz[2] = dz2;
   pdz[3] = dz3;
   pdz[4] = dz4;
   pdz[5] = dz5;
   pdz[6] = dz6;
   pdz[7] = dz7;
   pdz[8] = dz8;
   pdz[9] = dz9;
//
   for(mim=1; mim<=9; mim++) {
     slen[mim]= strlen(pdz[mim]);
     if (divffdebug) printf("i= %d %s %d\n", mim, pdz[mim], slen[mim]);
   }
   if(divffdebug) {
      printf("dz1: %s %d\n", dz1, slen0[1]);
      printf("dz2: %s %d\n", dz2, slen0[2]);
      printf("dz3: %s %d\n", dz3, slen0[3]);
      printf("dz4: %s %d\n", dz4, slen0[4]);
      printf("dz5: %s %d\n", dz5, slen0[5]);
      printf("dz6: %s %d\n", dz6, slen0[6]);
      printf("dz7: %s %d\n", dz7, slen0[7]);
      printf("dz8: %s %d\n", dz8, slen0[8]);
      printf("dz9: %s %d\n", dz9, slen0[9]);
   }
//
//-------------------main loop---------------------
// 
// find position of dividend in array : this is the quotient
//
   strcpy( divbufx, "");
   z1 = divbuf1;
   if(divffdebug) printf( "div: ---------- begin mainloop divff ----------\n");
//
// main loop 
//------------------------------------------------------
//  loop over difference of digits dividend/divisor
//  dividend is compared with array of divisor multiplied by 1-9 ( same string length )
//  strcmp returns -, 0, + : find position : this is one digit of quotient 
//  needs flags to handle 0 and 9 condition
//  divisor array is shorted by one digit
//
  div_cnt1 = 0;
//
// add 0 to array of multiplied n values
// number of 0 and number of digits to add
//
  for ( div_i = 1 ; div_i <= div_0 + 1; div_i ++) {
      if(divffdebug) printf( "div: ---------- div_i: %d ----------\n", div_i);
          alen = strlen(ay);
          breakflag = 0;
          pos = 0;
          //----------------------
           for(mim=1; mim<=9; mim++) {
            if( slen[mim] == alen) {
             pos = mim;
             icomp = strcmp( pdz[mim], ay);
             if(divffdebug) printf("    compare : %s %s %d pos: %d\n", ay,pdz[mim],icomp, mim); 
             if(icomp > 0) {
                div_cnt1 = mim - 1;
               //if(divfdebug) printf( ">>>>>>> %d\n", div_cnt1);
               breakflag = 1;
               break;
             } 
             if(icomp == 0) {
                div_cnt1 = mim;
               //if(divfdebug) printf( ">>>>>>> %d\n", div_cnt1);
               breakflag = 1;
               break;
             } 
            } 
           }
          //----------------------
          //
          //  very important :
          //  correct 3 special cases 
          //
          // string length changes in compare loop and no result found
           if(!breakflag && pos > 0) {
               div_cnt1 = pos;
               if( divdebug) printf( "special case length change : pos : %d\n", pos);
           }
           // string length not equal :  slen < alen  , quotient digit = 9 
           if( slen[9] + 1 == alen ) {
               div_cnt1 = 9;
               if( divdebug) printf( "special case 9 : pos : %d\n", pos);
           // string length not equal :  slen > alen , quotient digit = 0 
           } else if(pos == 0 ) {
               if( divdebug) printf( "special case 0 : pos : %d\n", pos);
               div_cnt1 = 0;
           }
           //
           if(divffdebug)
              printf( ">>>>>>> count : %d break : %d pos : %d <<<<<<\n", div_cnt1, breakflag, pos);
           if(div_cnt1 > 0) {
              z1 = addsub(ay,pdz[div_cnt1],divbuf1,'-');
              //if(divffdebug) printf( "div: after add  : ay, by, sum: %s %s %s\n",ay,by,z1);
              strcpy( ay, z1);
           }
           //  divide divisor by 10 by removing last character(0)
           dz1[slen[1]-1] = '\0';
           dz2[slen[2]-1] = '\0';
           dz3[slen[3]-1] = '\0';
           dz4[slen[4]-1] = '\0';
           dz5[slen[5]-1] = '\0';
           dz6[slen[6]-1] = '\0';
           dz7[slen[7]-1] = '\0';
           dz8[slen[8]-1] = '\0';
           dz9[slen[9]-1] = '\0';
           // reduce length by 1 
           for(mim=1; mim<=9; mim++) {
             slen[mim]--;
           }
           // append result
           cdiv_cnt1[0] = (char) (div_cnt1 + 48);
           cdiv_cnt1[1] = '\0';
           strcat( divbufx, cdiv_cnt1);
           if(divffdebug) printf("div: append : %s \n", divbufx);
  }
//------------------------------------------------------
  if(divffdebug) printf( "div: ---------- end mainloop divff ----------\n");
// 
// remove leading 0 or create 0
//
  strcpy( dy,ay);
//
  strcpy( cy,divbufx);
  z2 = strpbrk(cy,"123456789");
  if( z2 == NULL) {
     strcpy( cy, "0");
  } else {
     strcpy( cy, z2);
  }
  if( divffdebug) {
    printf("div: quot, mod : %s %s\n", cy, dy);
    printf("-------------------------------- end divff --------------------------------\n");
  }
  return( cy );
  }
//=======================================================================


//==========================================================================
//                   h e x b c d   and  b c d h e x
//==========================================================================
//  functions for big integer processing based on strings
//==========================================================================
//          3-Feb-03  hex_bcd : new function 
//         15-Feb-03  substr function added
//===================================================================
//                         s u b s t r
//===================================================================
//             get character in string at position pos 
//  same behavior as substr in awk :
//  return \0 (empty string), if start > length and if len < 1
//  copy string until end of string if (start + len) > n
//===================================================================
// 
  int substr(instring, outstring, start, len) 
   char *instring, *outstring ;
   int start,len ;
  {
    int n,i,j,endpos;
    n = strlen(instring);
    if( (start > n) || (len < 1)) {  
      outstring[0]='\0';
      return(1);
    }
    endpos = start + len - 1;
    if(endpos > n) endpos = n;
    j=0;
    for(i=start-1; i<= endpos-1; i++){
      outstring[j] = instring[i];
      j++;
    }
    outstring[j] = '\0';
    return(0);
  }
//=======================================================================
//
//                       b c d _ b i n h e x
//
//=======================================================================
// input  : bcddec ... input string
// result : bcdbin  ... binary result
//          bcdhex  ... hex result
//=======================================================================
// 24-Feb-03 : last version
//=======================================================================
// algorithm : 
// there are 2 registers :
//  left register : stores input number in bcd Format
//  right register : saves output bits( konverted to binary, result)
//  data in both registers are shift form left to right
//  the rightmost bit of bcd register is shifted into theleftmost bit of right register
//
//   for all bits of input decimal number do 
//     shift bcd register right 1 bit and store this bit in result
//      split bits of bcd register in groups of 4 bits
//         if (group > 8 ) group = group -3
//   end
//=======================================================================
  char *bcd_binhex(bcddec, bcdbin, bcdhex)
   char *bcddec, *bcdbin, *bcdhex;
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
   char hexres[ARRAYLENGTH];
   char xbinreg[ARRAYLENGTH];
   char dummy[ARRAYLENGTH];
   char list1[10] = "0123456789";
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

   if(bcdddebug) printf("Number decimal :%s\n", bcddec);
   if( strlen(bcddec) < 1){
     printf( "bcdhex:  Input Error bcd \n");
     printf( "bcdhex:  Zero length string bcddec\n");
     printf( "bcdhex:  === bcdhex terminated abnormally ===\n");
     strcpy( bcdbin,"bcd conversion error");
     return( bcdbin);
   }
   if(strncmp(bcddec,"0",1) == 0){
    strcpy(bcdbin,"0");
    strcpy(bcdhex,"0");
    return(bcdbin);
   }
   bcdd = bcddec;
   bcdd = strpbrk(bcddec,"123456789");
   if(bcdd == NULL) {
    strcpy(bcdbin,bcddec);
    printf("hexbcd: Illegal BCD number :  %s\n", bcddec);
    printf("hexbcd:  === bcdhex terminated abnormally ===\n");
    strcat(bcdbin,"--- illegal BCD data ---");
    return(bcdbin);
   }
   declen = strlen(bcdd);
//
// check valid bcd string
//
   if(bcdddebug) printf("length %d\n", declen);
   bcd_ok = 0;
   for(ii= 1 ; ii <= declen; ii++) {
     bcd_digit = strchar( bcddec, ii);
     for(ki=1 ; ki <= 10; ki++) {
         if(bcd_digit == strchar(list1,ki)){
           bcd_ok++;
           break;
         }
     }
   }
  if( bcd_ok != declen) {
    bcd_bad = declen - bcd_ok;
    printf("bcd_hex: Illegal BCD number :  %s\n", bcdbin);
    printf("bcd_hex: Number of bad characters: %d\n", bcd_bad);
    strcpy(bcdbin,"illegal BCD number");
    return(bcdbin);
  }
//
//  konvert BCD to 4 bit binary groups
//
   strcpy(binreg,"");
   for(i =  declen ; i >= 1 ; i--){
     bcd_digit = strchar(bcddec,i);
     strcpy( dummy, bintab[bcd_digit - 48].binval); 
     strcat( dummy, binreg);
     strcpy( binreg, dummy);
     // printf(" %d  %s\n",i, binreg);
   }
   if(bcdddebug) printf("Zahl BCD :%s\n", binreg);
   reglen = strlen(binreg);
//
// shift right all bits , subtract 3 if 4 bit  group >= 8 
// input is     : binreg
// result is in : binres
//
// ------------------------------------------------------------
   strcpy(binres, "");
   strcpy(xbinreg , binreg);
// loop over all bits
  for(mainl = 1 ; mainl <= reglen ; mainl++) {
   if(bcdddebug) printf("-------------- %d -------------\n", mainl);
      //
      // 1. step :
      // shift binreg right 1 bit , store bit in result
      // add 0 left
      //
      // get corrected data : if mainl > 1 groups are corrected
      strcpy(binreg , xbinreg);
      // get right bit
      bitout = strchar(binreg, reglen);
      // add to output
      bitout_arr[0] = bitout;
      bitout_arr[1] = '\0';
      strcpy(dummy,  binres);
      strcpy(binres, bitout_arr);
      strcat(binres, dummy);
      if(bcdddebug) {
         printf(" binreg:%s\n",binreg);
         printf(" binres:%s\n",binres);
      }

      strncpy( dummy, binreg, reglen - 1);
      dummy[reglen-1] ='\0';
      strcpy( binreg, dummy );
      // add 0 left side
      strcpy( dummy, "0");
      strcat( dummy, binreg);
      strcpy( binreg, dummy);
      if(bcdddebug) printf(" binreg:%s %c\n", binreg, bitout);
      //
      // 2. step
      // correct groups of 4 bit after shift
      // create new register 
      strcpy( xbinreg, "");
      // loop over all 4 bit groups
      for(i = 1;i <= declen ; i++) {
        k = (i - 1) * 4 + 1 ; 
        substr(binreg, group4, k, 4);
        //x1 = strchar(binreg,k);
        //x2 = strchar(binreg,k+1);
        //x3 = strchar(binreg,k+2);
        //x4 = strchar(binreg,k+3);
        //group4[0] = x1; group4[1] = x2; group4[2]= x3; group4[3]=x4; group4[4] = '\0';
        // check, if group > 8 ; if true, subtract -3
         for(k=1; k <=16; k++) {
           if(strcmp(group4,bintab[k-1].binval) == 0) break;
         }
         block = k - 1;
         if(block >= 8) {
           block = block - 3;
           strcpy( group4_1, bintab[block].binval);     
           strcpy(corrflag,"corrected");
         }else{
           strcpy( group4_1, group4);     
           strcpy(corrflag,"");
         }
         if(bcdddebug) printf("  group : %d %s  %s %s\n ", i,  group4, group4_1, corrflag);
         strcat( xbinreg, group4_1);
      } 
      if(bcdddebug) printf("binreg:%s\n", xbinreg);
  }
  //
  // convert bin to hex
  //
  strcpy(hexres, "");
  for(i = 1; i <= declen ; i++) {
        k = (i - 1) * 4 + 1 ; 
        substr(binres, group4, k, 4);
        //x1 = strchar(binres,k);
        //x2 = strchar(binres,k+1);
        //x3 = strchar(binres,k+2);
        //x4 = strchar(binres,k+3);
        //group4[0] = x1; group4[1] = x2; group4[2]= x3; group4[3]=x4; group4[4] = '\0';
       for(k=1; k <=16; k++) {
          if(strcmp( group4, bintab[k-1].binval) == 0) break;     
       }
     strcat( hexres, hextab[k-1].hexval); 
  }
  //
  // remove leading 0
  //
  bcdb= strpbrk(binres,"1");
  bcdh= strpbrk(hexres,"123456789ABCDEF");
  strcpy( bcdbin , bcdb);
  strcpy( bcdhex , bcdh);
  // 
  if( bcdddebug) {
    printf("binres:%s\n", bcdbin);
    printf("hexres:%s\n", bcdhex);
  }
  //
  return(bcdbin);
  }
//====================================================================
//=======================================================================
//
//                      h e x _ b c d
//
//=======================================================================
// algorithm for bin(hex) bcd conversion :
// shift all bits left in a new register
// check before shifting each decade and if > 4 add 3
// finished if all bits are shifted
//=======================================================================
// input : inhex
// result : outbcd 
//=======================================================================
  char *hex_bcd(inhex, outbcd)
   char *inhex,  *outbcd;
   {
   char *pinhex,*phexbinreg1;
   //
   char hex_binreg[ARRAYLENGTH];
   char hex_binreg1[ARRAYLENGTH];
   char hex_xbinreg1[ARRAYLENGTH];
   char hex_bitout[ARRAYLENGTH];
   char dummy[ARRAYLENGTH];
   char hex_bcdres[ARRAYLENGTH];
   //
   char corrflag[10];
   char group4[10], group4_1[10];
   char help[3];
   char list1[16] = "0123456789ABCDEF";
   char hex_digit, hex_bit;
   int hexlen,hex_reglen;
   int ii,i,zz,ki,hex_ok,hex_bad;
   int hex_mainl, hex_ll,hex_ll4, hex_mod;
   int block, k, hex_i, hex_k;
   int xhex_k , hex_end, hex_resl;
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
   if(hexdebug) printf("Number hex :%s\n", inhex);
   if( strlen(inhex) < 1) {
     printf( "hexbcd:  Input Error hexbcd \n");
     printf( "hexbcd:  Zero length string hexbcd\n");
     printf( "hexbcd:  === hexbcd terminated abnormally ===\n");
     strcpy( outbcd,"hex conversion error");
     return( outbcd);
   }
   if(strcmp(inhex,"0") == 0){
    strcpy(outbcd,"0");
    return(outbcd);
   }
   //phexbcd = hexbcd;
   pinhex = strpbrk(inhex,"123456789ABCDEF");
   if(pinhex == NULL) {
    strcpy(outbcd,inhex);
    printf("hexbcd: Illegal HEX number :  %s\n", inhex);
    printf("hexbcd:  === hexbcd terminated abnormally ===\n");
    strcat(outbcd,"   --- illegal HEX data ---");
    return(outbcd);
   }
   hexlen = strlen(pinhex);
   // remove leading 0
   strcpy( dummy, pinhex);
   strcpy( inhex, dummy);
//
// check valid hex string
//
   if(hexdebug) printf("length %d\n", hexlen);
   hex_ok = 0;
   for(ii= 1 ; ii <= hexlen; ii++) {
     hex_digit = strchar( inhex, ii);
     for(ki=1 ; ki <= 16; ki++) {
         if(hex_digit == strchar(list1,ki)){
           hex_ok++;
           break;
         }
     }
   }
  if( hex_ok != hexlen) {
    hex_bad = hexlen - hex_ok;
    printf("hexbcd: Illegal HEX number : %s\n", inhex);
    printf("hexbcd: Number of bad characters: %d\n", hex_bad);
    printf("hexbcd:  === hexbcd terminated abnormally ===\n");
    strcpy(outbcd,"illegal HEX number");
    return(outbcd);
  }
//
// convert hex to 4 bit binary groups
//
  strcpy(hex_binreg,"");
  for(i =  hexlen ; i >= 1 ; i--){
     hex_digit = strchar(inhex,i);
         for(zz=1; zz <=16; zz++) {
            help[0]= hex_digit; help[1]='\0';
           if( strcmp(hextab[zz-1].hexval, help) == 0) {
              strcpy( dummy, bintab[zz-1].binval); 
              strcat( dummy, hex_binreg);
              strcpy( hex_binreg, dummy);
              break;
           }
         }
  }
   hex_reglen = strlen(hex_binreg);
   if(hexdebug) {
          printf("Zahl bin :%s %d\n", hex_binreg, hex_reglen);
   }
// 
//  shift left all bits in new register and store in hexbinreg1
//  split in groups before shift and make correction
//
// algorithm : data are in hex_binreg
//    new register is hex_binreg, shift data left in
//    hexbinreg and remove leading 0 and  add 0 to get
//    a strings length multiple of 4. This 
//    makes correction easier
//  
  strcpy(hex_binreg1,"");
  strcpy(hex_xbinreg1,"");
  strcpy(hex_bitout,"");
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// loop over all bits
//
  for(hex_mainl = 1 ; hex_mainl <= hex_reglen ; hex_mainl++) {
      if( hexdebug) printf(" >>>>>>> main loop  bit:  %d bingreg1: %s\n", hex_mainl, hex_binreg1);
      strcpy(dummy, hex_xbinreg1);
     //
     // remove leading 0
     //
     phexbinreg1 = strpbrk(dummy,"1");
     if(phexbinreg1 != NULL) strcpy( hex_binreg1 , phexbinreg1);
     // add 0 groups
     hex_ll = strlen( hex_binreg1);
     hex_mod = hex_ll % 4;
     if( hexdebug) printf("          hexmod : %3d binreg1: %s\n", hex_mod, hex_binreg1);
      if(hex_mod == 0) {
        strcpy( dummy, "0000");
        strcat( dummy, hex_binreg1);
        strcpy( hex_binreg1, dummy);
      }
      if(hex_mod == 1) {
        strcpy( dummy, "000");
        strcat( dummy, hex_binreg1);
        strcpy( hex_binreg1, dummy);
      }
      if(hex_mod == 2) {
        strcpy( dummy, "00");
        strcat( dummy, hex_binreg1);
        strcpy( hex_binreg1, dummy);
      }
      if(hex_mod == 3) {
        strcpy( dummy, "0");
        strcat( dummy, hex_binreg1);
        strcpy( hex_binreg1, dummy);
      }
      hex_ll4 = strlen( hex_binreg1);
     if( hexdebug) printf("          hexll4 : %3d binreg1: %s\n", hex_ll4, hex_binreg1);
     //  split in groups of 4 bit
     strcpy(hex_xbinreg1,"");
//----------------------------------------------------------------------------
      for(hex_i = 1; hex_i <= hex_ll4/4 ; hex_i++) {
        //
        // hex_x = substr(hex_binreg1,hex_k,4)
        //-------------------------------------------------
        // hier der C Ersatz fuer substr , musste man eine funktion
        // schreiben
        hex_k = (hex_i - 1) * 4 + 1 ; 
        substr(hex_binreg1, group4, hex_k, 4);
        //x1 = strchar(hex_binreg1,hex_k);
        //x2 = strchar(hex_binreg1,hex_k+1);
        //x3 = strchar(hex_binreg1,hex_k+2);
        //x4 = strchar(hex_binreg1,hex_k+3);
        //group4[0] = x1; group4[1] = x2; group4[2]= x3; group4[3]=x4; group4[4] = '\0';
        if( hexdebug) printf("         4 bit group : %s\n", group4);
        // check, if group > 4 ; if true, add 3
         for(k=1; k <=16; k++) {
           if(strcmp(group4,bintab[k-1].binval) == 0) break;
         }
         block = k - 1;
         if(block > 4) {
           block = block + 3;
           strcpy( group4_1, bintab[block].binval);     
           if( hexdebug) strcpy(corrflag,"         corrected");
         }else{
           strcpy( group4_1, group4);     
           if( hexdebug) strcpy(corrflag,"");
         }
         if( hexdebug) if(hexdebug) printf("            group : %d %s  %s %s\n ", hex_i,  group4, group4_1, corrflag);
         strcat( hex_xbinreg1, group4_1);
      } 
//----------------------------------------------------------------------------
      if(hexdebug) printf("         binreg:%s\n", hex_xbinreg1);
      hex_bit = strchar( hex_binreg, hex_mainl);
      help[0]= hex_bit; help[1]='\0';
      if( hexdebug) printf( "          next bit: %c\n", hex_bit);
      // add to output
      strcat(hex_xbinreg1, help);
     }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  //
     if(hexdebug) printf(" result : %s\n", hex_xbinreg1);
  // convert bin to decimal
     strcpy(dummy, "0000");
     strcat(dummy, hex_xbinreg1);
     strcpy(hex_xbinreg1, dummy);
     hex_resl = strlen(hex_xbinreg1) + 1;
     strcpy(hex_bcdres,"");
     for(hex_i = 1; ; hex_i++) {
        xhex_k = hex_i  * 4  ; 
        hex_end = hex_resl - xhex_k ;
        if(hex_end < 1) break ;
           //x1 = strchar( hex_xbinreg1, hex_end);
           //x2 = strchar( hex_xbinreg1, hex_end+1);
           //x3 = strchar( hex_xbinreg1, hex_end+2);
           //x4 = strchar( hex_xbinreg1, hex_end+3);
           //group4[0] = x1; group4[1] = x2; group4[2]= x3; group4[3]=x4; group4[4] = '\0';
           substr(hex_xbinreg1, group4, hex_end, 4);
            for(k=1; k <=16; k++) {
              if(strcmp(group4,bintab[k-1].binval) == 0) break;
            }
        strcpy(dummy, hextab[k-1].hexval);
        strcat(dummy, hex_bcdres);
        strcpy(hex_bcdres, dummy);
      }
      if(hexdebug) printf(" result : %s\n", hex_bcdres);
      // remove leading 0
      phexbinreg1 = strpbrk(hex_bcdres,"123456789");
      strcpy( dummy, phexbinreg1);
      strcpy(hex_bcdres , dummy);
      if(hexdebug) printf(" result : %s\n", hex_bcdres);
      strcpy( outbcd, hex_bcdres);
      return(outbcd);
  }
//=======================================================================
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
  printf("========= begin of fermat test =========\n");
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
  printf( " length of prime : %d length of random a : %d\n", ll_n, a_length);
  if (  ll_n <= a_length ) {
     printf( "length for random number a too large : %d  %d\n", a_length, ll_n);
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
  printf(" total results of fermat check :  prime %d   composite %d \n", prime_count, composite_count);
  printf(" checked number : %s\n", prime_for_test);
  printf("========= end of fermat test =========\n");
 }
//===============================================================
//
//  function randbigint
//
//===============================================================
// create random integer number
// returns a big int with length  
// initialize random generator
//
// initialize in main program/
//  srand( (unsigned) time( NULL));
//
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
