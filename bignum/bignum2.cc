//==========================================================================
//                           b i g n u m                   
//==========================================================================
// history : 
// 14-Jul-2002
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
// 29-Sep-2002 : optimized and moved strchar() to vchar.cpp
//==========================================================================
// available functions : 
//
// format of input data:
//    strcpy(z2, "894770000077777777777777777774440");
//    strcpy(z1, "-54894");
//
//    addsub( in1, in2, result,'+')
//    addsub( in1, in2, result,'-')
//    mult( z1, z2, result)
//    divf( dividend, divisor, quotient, rest) .. dividend and divisor destroyed
//    modexp(a, b, n, res) ..... a destroyed
//    euclidext(e, p, q, d);
//    bcd_binhex(in, outbin, outhex);
//
//==========================================================================


#include "vchar.h"
#include "bignum2.h"

namespace BigNum2 {

//
// functions
//
pchar addsub1( pchar ax, pchar bx, pchar cx, char as);
pchar addsub( pchar aa, pchar bb, pchar cc, char flag);


pchar mult( pchar ay, pchar by, pchar cy);


// mult/div 
void test2();

//
// flags for debug : 1= debug, 0 = no debug
//
int debug = 0;
int multdebug = 0;

#if 0
//==========================================================================
int main( int argc, char **argv)
{
	int maxii;

	if( argc > 1 )
	{
		sscanf( argv[1], "%d", &maxii );

	} else {
		printf( "usage: %s 1234\n", argv[0] );
		return 1;
	}

	vchar z1;
	vchar z2;
	vchar z3;
	vchar z4;
	vchar z5;
	int ii;
	printf("---------- test Fakultaet %d -----------\n", maxii );
	strcpy(z1, "1");
	strcpy(z2, "1");
	strcpy(z4, "1");
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
#endif

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
pchar addsub( pchar aa, pchar bb, pchar cc, char flag)
{
	char signx[3] , signy[3];
	char addsub_signa, addsub_signb, addsub_xx, addsub_yy;
	pchar pa, pb ;
	int i,la,lb;
	int addsub_carry, addsub_swapflag;
	vchar oo;
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
//
// function addsub1
//
//===============================================================
// parameter : ax,bx : char array with 2 integer numbers without sign
//             cx : output string
//             as : char + or - 
// function returns pointer to cx
//===============================================================
pchar addsub1( pchar ax, pchar bx, pchar cx, char as)
{
	int i, j, c,  ii, jj;
	int add_la, add_lb, add_lmax, add_x;
	pchar pa, pb, pc;
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
		if(debug) printf("addsub1: i=%d c=%c %c %d %d\n", i, axx[0], bxx[0], (int)axx[0], (int)bxx[0]);
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

//===============================================================
//
//    function mult
//
//===============================================================
// parameter : ay * by ... result cy
//             returns pointer to cy
//===============================================================
pchar mult( pchar ay, pchar by, pchar cy)
{
	char signx[3], signy[3];
	pchar pa, pb ;
	char mult_signa, mult_signb, mult_sigmult;
	int la, lb;
	//
	vchar *pmz[10];
	vchar mz1;
	vchar mz2;
	vchar mz3;
	vchar mz4;
	vchar mz5;
	vchar mz6;
	vchar mz7;
	vchar mz8;
	vchar mz9;
	//
	vchar mult_mult2;
	vchar mult_mult3;
	pchar z2, z3;
	vchar mult_result;
	vchar mult_digten;
	vchar mult_zsum;

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
	pmz[1] = &mz1;
	pmz[2] = &mz2;
	pmz[3] = &mz3;
	pmz[4] = &mz4;
	pmz[5] = &mz5;
	pmz[6] = &mz6;
	pmz[7] = &mz7;
	pmz[8] = &mz8;
	pmz[9] = &mz9;
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

			//       printf( "%s\n%s\n%s\n\n", pa, z2, z3 );

			strcpy( z2, z3);

			//       printf( "%s\n%s\n%s\n\n\n", pa, z2, z3 );
		}
		strcpy( *pmz[mult_mim], z2);
	}
	strcpy( *pmz[1], pa);
	for(i=1; i<=9; i++) {
		if (multdebug) printf("i= %d %s\n", i, *pmz[i]);
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
		strcpy(mult_zsum, *pmz[mult_z]);
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

} // namespace BigNum2

