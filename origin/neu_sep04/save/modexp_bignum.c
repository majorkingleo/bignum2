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
  void test6();
  void test7();
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
   
   test6();
   test7();
   return(0);
 }
//===================================================================

//===============================================================
// test7 :  pow (a,b) mod n
//          needs 42 minutes for one number
//          needs 12.45 minutes for one number with new fast divide
//          needs 11.0 minutes for one number with new fast modexpf
//                1.45 min with 650 Mhz
//===============================================================
  void test7() {
   char d[ARRAYLENGTH];
   char zahl1[ARRAYLENGTH];
   char zahl2[ARRAYLENGTH];
   char zahl3[ARRAYLENGTH];
   char n[ARRAYLENGTH];
   char e[ARRAYLENGTH];
   char r[ARRAYLENGTH];
   int x;
   printf( "---- rsa243 pow (a,b) mod n ---\n");
// n243
  strcpy(n,"6305482150701295471567183324958896322344341454119712758883769876032602");
  strcat(n,"2525278792613527673894410568910003629553586814142438653640364957870769");
  strcat(n,"9128189491432138631900590774729214990015369102760964884776344849717811");
  strcat(n,"484309528915040117952098061886881");
// d vom euklidischen algorithmus
  strcpy(d,"37596151776653337419535334112497554360708311749303756353996319663215286483855671243164897736438502271149130504165852074124585880523291499123910190345598116011326256898562180469616127693050575097619317602876777557156491759762785651714389821431");
   strcpy(e,"508075310835159009812633969174411123496728859672737076695139826186257647581337481521676692825102982808222076238747753504407");
//
//===========================================================
  printf("====  s1z1 ====\n");
  strcpy(zahl1,"224923982645255075764641682644299099941567835922453543993512357836217839079");
  strcat(zahl1,"170831131358885202320077383402328253733459392614232456270099377924856504863");
  strcat(zahl1,"531650648222840476724197684978335435824683210303529490850440904599551700481");
  strcat(zahl1,"267015709865801294");
  strcpy(zahl3, zahl1);
  printf(" a:%s\n", zahl1);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexpf(zahl1,d,n,r);
  printf(" anach:%s\n", zahl1);
  printf(" dnach:%s\n", d);
  printf(" nnach:%s\n", n);
  printf(" rnach:%s\n", r);
//
// check back
//
  printf("====  s1z1 ==== : convert back and compare\n");
  strcpy(zahl2, r);
  printf(" a:%s\n", zahl2);
  printf(" e:%s\n", e);
  printf(" n:%s\n", n);
  modexpf(zahl2,e,n,r);
  printf(" r:%s\n", r);
  x=strcmp(zahl3, r);
  if(strcmp(zahl3, r) !=0) {
   printf("error: different numbers : %d\n", x);
  } else {
   printf("Result OK\n");
  }
//
printf("====  s1z2 ====\n");
strcpy(zahl2,"118258470832316669144058875416102351904053138796970926136701764061349060941");
strcat(zahl2,"852624180336543102927177997592642823268526761712338243425118709505929634585");
strcat(zahl2,"129941908175387374033840112508268338553661529059969292674670879868530695454");
strcat(zahl2,"832472445529723758");
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  printf(" r:%s\n", r);

printf("====  s1z3 ====\n");
strcpy(zahl2,"772544757693754456729319755881351285253938343187181763725329874984367897849");
strcat(zahl2,"365947442772697122487386373867905176117864752061760902698170691553716305719");
strcat(zahl2,"558766445448893886699570160729033886915169137819678381034916080051118496388");
strcat(zahl2,"86828324342473962");
  printf(" a:%s %d\n", zahl2, strlen(zahl2));
  printf(" d:%s %d\n", d, strlen(d));
  printf(" n:%s %d\n", n, strlen(n));
  modexp(zahl2,d,n,r);
  printf(" r:%s %d\n", r, strlen(r));
printf("====  s1z4 ====\n");
strcpy(zahl2,"624180031453114854949495080075834709524791381733488934025690365079943413527");
strcat(zahl2,"585036298247777958097547345290840985910576392073427968568137617907096276709");
strcat(zahl2,"951420892774376799878876620679797398585754941387679429336610773194054090420");
strcat(zahl2,"153324737762120838");
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  printf(" r:%s\n", r);
printf("====  s1z6 ====\n");
strcpy(zahl2,"344895900995366080289908735120682533093895921421582855861862924334483375405");
strcat(zahl2,"609850237957330855230478069832102326748790806530490215356958599851748431535");
strcat(zahl2,"026574676740652110100227401001871947524238965313435861753529223722905902680");
strcat(zahl2,"673672208735993542");
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  printf(" r:%s\n", r);
printf("====  s1z8 ====\n");
strcpy(zahl2,"613584394813541911847883915334096266586073529179946909804716591147501895116");
strcat(zahl2,"881991842936728722110808873432204741358706165468717065608356184000479054515");
strcat(zahl2,"317925204741900785143680363189399884262556671110581144964862281687402843712");
strcat(zahl2,"691723495975822060");
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  printf(" r:%s\n", r);
// berechne  : s4z10^ d % n243
printf("====  s4z10 ====\n");
strcpy(zahl2,"851503301304841404390068340092981135887481765652086223136128621216438506812");
strcat(zahl2,"797616967801614782225006764178017841381467480345264666743113037420077333796");
strcat(zahl2,"881400811811100095398945848387618843589150962504519975368203684812533834441");
strcat(zahl2,"27096251456813610");
//
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  //modexpf(zahl2,d,n,r);
  printf(" r:%s\n", r);
//
printf("====  s1z5 ====\n");
strcpy(zahl2,"282449978354743647358321414434683421840997661402379905631187918775850753578");
strcat(zahl2,"821434316879020726609253988848901270205891031695476865646707867527346380946");
strcat(zahl2,"031865258828958679111555801572006223444328543509069212026619948299528990038");
strcat(zahl2,"386262847370225562");
//
  printf(" a:%s\n", zahl2);
  printf(" d:%s\n", d);
  printf(" n:%s\n", n);
  modexp(zahl2,d,n,r);
  //modexpf(zahl2,d,n,r);
  printf(" r:%s\n", r);

  }
//===============================================================
// test6 :  pow (a,b) mod n
//===============================================================
  void test6() {
   char a[ARRAYLENGTH];
   char aa[ARRAYLENGTH];
   char b[ARRAYLENGTH];
   char n[ARRAYLENGTH];
   char r[ARRAYLENGTH];
   printf( "---- test pow (a,b) mod n ---\n");
   // public exponent
//
//  r = pow(a e) modn
//
   printf( "---- test 1 ----\n");
   strcpy(b,"65537");
   strcpy(a,"11182516201512150709");
   strcpy(aa,a);
   // modulus
   strcpy(n,"415758465533848642967");
   printf(" a:%s\n", a);
   printf(" b:%s\n", b);
   printf(" n:%s\n", n);
   modexpf(a,b,n,r);
   printf(" a^b mod n : %s\n", r);
   printf(" should be : 71043117991897565951\n");
//
// check a = pow(r d) modn
//
   // privat exponent
   printf( "---- test 2 ----\n");
   strcpy(b,"16481384459631305873");
   strcpy(n,"415758465533848642967");
   strcpy(a,r);
   printf(" a:%s\n", a);
   printf(" b:%s\n", b);
   printf(" n:%s\n", n);
   modexpf(a,b,n,r);
   printf(" a^b mod n : %s\n", r);
   if((strcmp(aa,r)) !=0) {
     printf("Error\n");
   } else {
     printf("Conversion ok !!\n");
   }
}
//===============================================================
