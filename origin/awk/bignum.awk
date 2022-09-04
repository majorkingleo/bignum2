#================================================================
#
#                   bignum awk library
#
#================================================================
# 5-Dec-00  : started
# 13-Jan-00 : finished
# 29-Jun-01 : 1024 bit test added
#  3-Nov-01 : euclid p-1,q-1 : output fixed
#================================================================
# functions :
#================================================================
#
#    multf(a,b)      ... result in multf_result
#    mult(a,b)       ... slow mult not used            
#    div(a,b)        ... result in div_quot , div_mod
#    addsub(a,b,"+") ... result in add_sum  
#    addsub(a,b,"-")                           
#    euclidext(e, p, q) ... result in eucl_t 
#    bcd_binhex(bcdnumber) ... binary result in bcd_binres
#                              hex result    in bcd_hexres
#    hex_bcd(hexnumber) ...... result in hex_bcdres
#    modexp(a,b.n) ........... pow(a,b) mod n
#                              result in modexp_res
#    test1(dummy) .....  test devide and multiply
#    test2(dummy) .....  test euclid algorithm small values 
#    test3(dummy) .....  test euclid algorithm RSA155 
#    test4(dummy) .....  test pow (a,b) modn for small values
#    test_hex(dummy) ... test bcd hex and hex_bcd
#    ossi(dummy) ....  test with ossifrage RSA129
#    singh(dummy) .... solve example of singh RSA155 cipher challenge stage 10
#
#================================================================
BEGIN{
#
# Definitions for hex conversions
# do not change
#
  hex[1]= "0" 
  hex[2]= "1" 
  hex[3]= "2" 
  hex[4]= "3" 
  hex[5]= "4" 
  hex[6]= "5" 
  hex[7]= "6" 
  hex[8]= "7" 
  hex[9]= "8" 
  hex[10]= "9" 
  hex[11]= "A" 
  hex[12]= "B" 
  hex[13]= "C" 
  hex[14]= "D" 
  hex[15]= "E" 
  hex[16]= "F" 
#
  bhex[1]= "0000" 
  bhex[2]= "0001" 
  bhex[3]= "0010" 
  bhex[4]= "0011" 
  bhex[5]= "0100" 
  bhex[6]= "0101" 
  bhex[7]= "0110" 
  bhex[8]= "0111" 
  bhex[9]= "1000" 
  bhex[10]= "1001" 
  bhex[11]= "1010" 
  bhex[12]= "1011" 
  bhex[13]= "1100" 
  bhex[14]= "1101" 
  bhex[15]= "1110" 
  bhex[16]= "1111" 
#
#
   debug = 0
# 
# end of header block 
#------------------------------------------------------------
#
# call functions
#
   test_hex1024(dummy)
   exit
   ossifrage(dummy)
   exit
   singh(dummy)
   exit
   test4(dummy)
   exit
   test_hex(dummy)
   exit
   test1(dummy)
   exit
   test3(dummy)
   exit
   test2(dummy)
   exit
#------------------------------------------------------------
   #b="65537"
   #a="11182516201512150709"
   #n="415758465533848642967"
   b="16481384459631305873"
   a="71043117991897565951"
   n="415758465533848642967"
   modexp( a,b,n)
   print modexp_res
   #a = "1236588888900000999"
   #b = "1"
   #a = "-999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
   #a = ""
   #b = "-111111111111111111111111111111111111111111111111"
   a = "-4440"
   b = "4440"
   print "a     : " a
   print "b     : " b
   addsub(a,b,"+")
   print "Sum : " add_sum
   # exit
   #   for(;;) {
   #      print "a     : " a
   #      print "b     : " b
   #      sum=add(a,b)
   #      print "Summe : " sum
   #      a = sum
   #      b = add(b,"100000")
   #   }
   #
   print "a     : " axx
   print "b     : " bxx
   print "Laenge a,b :" length(axx) " " length(bxx)
   #mult(axx,bxx)
   #print "Mult  : " mult_result
   #print "a     : " axx
   #print "b     : " bxx
   #multf(axx,bxx)
   div(axx,bxx)
   exit
   print "Multf : " mult_result
   print "Laenge : " length(multf_result)
   exit
   axx = "2"
   bxx = "2"
   for(it=1;it<=1000; it++) {
     multf(axx,bxx)
     axx = multx
   }
   print "---------------"
   print "Summe : " multx
   print "---------------"
}
#===============================================================
{
}
#===============================================================
END{
}
#===============================================================
#
# function addsub
#
#===============================================================
# addsub mit Vorzeichen :
#  GR  KL
#  + + +   + ADD
#  - + +   - SUB GR - KL
#  + + -   + SUB GR - KL
#  - + -   - ADD
#
#  GR  KL
#  + - +  + SUB GR - KL
#  - - +  - ADD
#  + - -  + ADD
#  - - -  - SUB GR - KL
#
#  strings with numbers must be correct
#
#===============================================================
function addsub(aa,bb,flag) {
#
# check for valid input here
#
   if( length(aa) < 1){
     print "Input Error addsub "
     print "Zero length string a"
     print "=== addsub terminated abnormally ==="
     exit
   }
   if( length(bb) < 1) {
     print "Input Error addsub "
     print "Zero length string b"
     print "=== addsub terminated abnormally ==="
     exit
   }
#
# flag : + = add, - = sub
#
# check and remove sign
#-------------------------
  addsub_x = substr(aa,1,1)
  addsub_y = substr(bb,1,1)
  if(addsub_x=="-") addsub_signa = "-"
  else addsub_signa = "+"
  if(addsub_y=="-") addsub_signb = "-"
  else addsub_signb = "+"
  gsub(/\+/,"",aa)
  gsub(/\-/,"",aa)
  gsub(/\+/,"",bb)
  gsub(/\-/,"",bb)
  addsub_la = length(aa)
  addsub_lb = length(bb)
  # print "Laenge:"addsub_la " " addsub_lb
#
# check abs val and swap aa,bb
# max abs val is aa
#---------------------------------
  addsub_carry = 0
  if( addsub_la == addsub_lb) {
      for (addsub_i = 1 ; addsub_i <= addsub_la ; addsub_i++) {
       # addsub_p = addsub_la - addsub_i + 1
       addsub_xx = substr(aa,addsub_i,1)
       addsub_yy = substr(bb,addsub_i,1) 
       if(addsub_xx == addsub_yy) continue
       if(addsub_xx < addsub_yy) {
          addsub_carry = 1
          break
      }
       else break
      }
  }
  #print "addsubcarr:" addsub_carry
# check abs val of a b
  addsub_swapflag=0
  if( (addsub_la < addsub_lb) || addsub_carry ) {
    addsub_swapflag = 1
     # xxxx
     # print "swapflag"
  }
#
# addition or subtraction
#----------------------------- 
# addition
  if(flag == "+") {
   if( addsub_signa == "+" && addsub_signb == "+") {
     addsub1(aa,bb,"+")
   }
   if( addsub_signa == "-" && addsub_signb == "-") {
     addsub1(aa,bb,"+")
     if(add_sum != "0") add_sum = "-" add_sum
   }
   if( addsub_signa == "-" && addsub_signb == "+") {
     if(addsub_swapflag) {
        addsub1(bb,aa,"-")
     } else {
        addsub1(aa,bb,"-")
        if(add_sum != "0") add_sum = "-" add_sum
     }
   }
   if( addsub_signa == "+" && addsub_signb == "-") {
     if(addsub_swapflag) {
        addsub1(bb,aa,"-")
        if(add_sum != "0") add_sum = "-" add_sum
     } else {
        addsub(aa,bb,"-")
     } 
   }
# subtract
  } else if (flag == "-") {
   if( addsub_signa == "+" && addsub_signb == "+") {
     if(addsub_swapflag) {
        addsub1(bb,aa,"-")
        if(add_sum != "0") add_sum = "-" add_sum
     } else {
        addsub1(aa,bb,"-")
     } 
   }
   if( addsub_signa == "-" && addsub_signb == "-") {
     if(addsub_swapflag) {
        addsub1(bb,aa,"-")
     } else {
        addsub1(aa,bb,"-")
        if(add_sum != "0") add_sum = "-" add_sum
     } 
   }
   if( addsub_signa == "-" && addsub_signb == "+") {
     addsub1(aa,bb,"+")
     if(add_sum != "0") add_sum = "-" add_sum
   }
   if( addsub_signa == "+" && addsub_signb == "-") {
     addsub1(aa,bb,"+")
   }
  } else {
   print "Error addsub : " addsub_flag
   exit
  }
  #------------------------
  }
# 
#===============================================================
#
#  function addsub1
#
#===============================================================
function addsub1(ax,bx,as) {
# integer addition of 2 strings
#
  if(debug) {
     print "add ax : " ax
     print "add bx : " bx
  }
  add_la = length(ax)
  add_lb = length(bx)
  add_lmax = add_lb
  if( add_la > add_lb) add_lmax = add_la
  # lmax
  # print "lmax:" lmax
  for (add_i = add_la ; add_i >= 1 ; add_i--) {
   add_p = add_la - add_i + 1
   add_ara[add_p]= substr(ax,add_i,1)
   #print p " " ara[p]
   if(add_p == add_la) break
  }
  for (add_i = add_lb ; add_i >= 1 ; add_i--) {
   add_p =add_lb - add_i + 1
   add_arb[add_p]= substr(bx,add_i,1)
   #print p " " arb[p]
   if(add_p==add_lb) break
  }
 #------------------
 if(as == "+") {
 #
 # add
 #
  add_carry = 0
  add_sum = ""
  for( add_i = 1 ; add_i <= add_lmax ; add_i++) {
   #  print"i = " i " ab:" ara[i] " " arb[i]
   add_out = add_ara[add_i] + add_arb[add_i] + add_carry
   delete add_ara[add_i]; delete add_arb[add_i]
   add_carry = 0
   if( add_out > 9) {
    add_out = add_out - 10
    add_carry = 1
   }
   add_sum = add_out add_sum
  }
  if(add_carry) add_sum = add_carry add_sum
  if(debug) {
     print "add s : " add_sum
  }
  return add_sum
 } else if (as == "-") {  
#
# sub
#
# xxxxxxxxxxxxxxxx
  add_carry = 0
  add_sum = ""
  for( add_i = 1; add_i <= add_lmax ; add_i++) {
   # print "i = " add_i " ab:" add_ara[add_i] " " add_arb[add_i]
   add_out = add_ara[add_i] + 0
   add_x = add_arb[add_i] + add_carry
   add_carry = 0
   if( add_out < add_x ) {
    add_out = add_out + 10
    add_carry = 1
   }
   #print "add_out, add_x:" add_out " " add_x
   add_out = add_out - add_x
   #print "ad_out addsum:" add_out " " add_sum
   add_sum = add_out add_sum
   delete add_ara[add_i]; delete add_arb[add_i]
  }
  # remove 0 from left
  gsub(/^0*/,"",add_sum)
  if( add_sum == "") add_sum = "0"
  if(debug) {
     print " sub s : " add_sum
  }
  return add_sum
 } else {
   print "error"
 }
}
#===============================================================
#
#    function mult
# slow version of mult
#
#===============================================================
#  2  *  35 digit 99999......... 10 sec
# how does it work :
#            9876 * 1234
#    ------------------------
#          39504  = 9876 * 4
#         296280  = 98760 * 3
#        1975200  = 987600 * 2
#        9876000  = 9876000 * 1
#    ------------------------
# sum = 12186984
#===============================================================
function mult(ay,by) {
#
# remove sign
#
  mult_x = substr(ay,1,1)
  mult_y = substr(by,1,1)
  if(mult_x == "-") mult_signa = "-"
  else mult_signa = "+"
  if(mult_y == "-") mult_signb = "-"
  else mult_signb = "+"
  gsub(/\+/,"",ay)
  gsub(/\-/,"",ay)
  gsub(/\+/,"",by)
  gsub(/\-/,"",by)
  mult_mlb = length(by)
#
# final sign
#
  if(mult_signa == "-" && mult_signb == "-") mult_sigmult = ""
  if(mult_signa == "+" && mult_signb == "-") mult_sigmult = "-"
  if(mult_signa == "-" && mult_signb == "+") mult_sigmult = "-"
  if(mult_signa == "-" && mult_signb == "-") mult_sigmult = ""
#
# split array
#
  for (mult_i = mult_mlb ; mult_i >= 1 ; mult_i--) {
   mult_p = mult_mlb - mult_i + 1
   mult_arbm[mult_p]= substr(by,mult_i,1)
   #print p " " arbm[p]
   if(mult_p == mult_mlb) break
  }
  if( ay == "0" || by == "0") {
     mult_result="0"
     return
  }
#---------------------------------------
  mult_result = ""
  for(mult_im =1 ; mult_im <= mult_mlb ; mult_im++) {
   if(debug) {
      print "im :" mult_im " mlb:" mult_mlb " arbm[m]:"  mult_arbm[mult_im] " mult1:" mult_result " ay:" ay
   }
   mult_mend = mult_arbm[mult_im] + 0 
    for(mult_jm = 1 ; mult_jm <= mult_mend ; mult_jm++) {
      addsub1(ay,mult_result,"+")
      mult_result = add_sum
      #print "jm:" jm " " mult1
    }
    ay = ay "0"   
    delete mult_arb[mult_m]
  } 
  mult_result = mult_sigmult mult_result
}
#===============================================================
#
#    function multf
#
#===============================================================
# fast version of mult
#  121 Stellen : 20 Sekunden
#  178 Stellen : 40 Sekunden
#  218 Stellen : 60 Sekunden
#
#===============================================================
function multf(ay,by) {
#
# check for valid input here
#
   if( length(ay) < 1){
     print "Input Error multf "
     print "Zero length string a"
     print "=== addsub terminated abnormally ==="
     exit
   }
   if( length(by) < 1) {
     print "Input Error multf "
     print "Zero length string b"
     print "=== addsub terminated abnormally ==="
     exit
   }
#
# remove sign
#
  multf_x = substr(ay,1,1)
  multf_y = substr(by,1,1)
  if(multf_x == "-") multf_signa = "-"
  else multf_signa = "+"
  if(multf_y == "-") multf_signb = "-"
  else multf_signb = "+"
  gsub(/\+/,"",ay)
  gsub(/\-/,"",ay)
  gsub(/\+/,"",by)
  gsub(/\-/,"",by)
  multf_mlb = length(by)
#
# final sign
#
  multf_sigmult = ""
  if(multf_signa == "+" && multf_signb == "-") multf_sigmult = "-"
  if(multf_signa == "-" && multf_signb == "+") multf_sigmult = "-"
#
# split array
#
  for (multf_i = multf_mlb ; multf_i >= 1 ; multf_i--) {
   multf_p = multf_mlb - multf_i + 1
   multf_arbm[multf_p] = substr(by,multf_i,1)
   #print p " " arbm[p]
   if(multf_p == multf_mlb) break
  }
  if( ay == "0" || by == "0") {
     multf_result="0"
     return
  }
#---------------------------------------
# create array with multiplied numbers
# multiply from from 2 to 9
#
  for(multf_mim = 2 ; multf_mim <= 9; multf_mim++) {
  multf_mult2 = "0"
    for(multf_mjm = 1; multf_mjm <= multf_mim ; multf_mjm++) {
      # print "im,jm:" im" "  mjm
      # print "m2:" mult2
      addsub1(ay,multf_mult2,"+")
      multf_mult2 = add_sum
      # print "im,jm,mult2: " im" " mjm " " multf_mult2
    }
   multf_multarr[multf_mim] = multf_mult2
  } 
  multf_multarr[1] = ay
  # for(im=1; im<= 9; im++) {
  #  print "im:" im " " multf_multarr[im]
  # }
#
#-----------------------
# add multiplied numbers to final result and
# shift by adding 0
  multf_result = ""
  multf_digten = ""
  for(multf_im = 1; multf_im <= multf_mlb ; multf_im++) {
   multf_z = multf_arbm[multf_im] + 0 
   if(multf_z == 0) {
     multf_digten = multf_digten "0"
     continue
   }
   multf_zsum1 = multf_multarr[multf_z] multf_digten
   #print "im,z,zsum1:" im " "  z " " zsum1
    addsub1(multf_zsum1,multf_result,"+")
    multf_result = add_sum
   multf_digten = multf_digten "0"
   delete multf_arbm[multf_im]
  }
  multf_result = multf_sigmult multf_result
}
#===============================================================
#
#   function div
#
#===============================================================
function div(ay,by) {
#
# check for valid input here
#
   if( length(ay) < 1){
     print "Input Error addsub "
     print "Zero length string a"
     print "=== addsub terminated abnormally ==="
     exit
   }
   if( length(by) < 1) {
     print "Input Error addsub "
     print "Zero length string b"
     print "=== addsub terminated abnormally ==="
     exit
   }
#
# remove sign
#
  div_x = substr(ay,1,1)
  div_y = substr(by,1,1)
  if(div_x == "-") div_signa = "-"
  else div_signa = "+"
  if(div_y == "-") div_signb = "-"
  else div_signb = "+"
  gsub(/\+/,"",ay)
  gsub(/\-/,"",ay)
  gsub(/\+/,"",by)
  gsub(/\-/,"",by)
  div_lb = length(by)
  div_la = length(ay)
#
# dividend < divisor
#
  if( div_la < div_lb ) {
   div_quot = "0"
   div_mod = ay
   return
  }
# divisor = 0
  if( by == "0") {
     print "Zero division error"
     print "=== div terminated abnormally ==="
  }
#
# final sign
#
  if(div_signa == "-" && div_signb == "-") div_sigdiv = ""
  if(div_signa == "+" && div_signb == "-") div_sigdiv = "-"
  if(div_signa == "-" && div_signb == "+") div_sigdiv = "-"
  if(div_signa == "-" && div_signb == "-") div_sigdiv = ""

  div_by = by
#
#  number of 0 and number of digits to add
#
  div_0 = 0
  for( j = 1; j <= div_la - div_lb ; j++) {
   #print "yyyy"
   div_0++
   div_by = div_by "0"
  }
#
  #print "div_by :" div_by
  #print "div_0 : " div_0
  
  div_quot = ""
# 
# subtract divisor from dividend down to 0
# count number of subtractions
#------------------------------------------------------
  for ( div_i = 1 ; div_i <= div_0 + 1; div_i ++) {
  # print "div_i:" div_i
  div_cnt = 0
  for(;;) {
   div_cnt++
   # print "ay,div_by:"ay " "div_by
   addsub(ay,div_by,"-")
    #print "div_by, ay, sum:" div_by " " ay " "add_sum
   ay = add_sum
   if( substr(ay,1,1) == "-" ) {
     #print "wieder dazu"
     # print "ay,div_by:" ay " " div_by
     addsub(ay,div_by,"+")
     # print ">>> : " ay " "add_sum
     ay = add_sum
     div_cnt--
     break
   }
  }
  #print "add_sum, cnt:" ay " " div_cnt
  gsub(/0$/,"",div_by)
  div_quot = div_quot div_cnt 
  }
#------------------------------------------------------
  div_mod = ay
  gsub(/^0*/,"",div_quot)
  if(div_quot == "") div_quot = 0
  div_quot = div_sigdiv div_quot
}
#===============================================================
# test divide and  multiplication
#===============================================================
function test1(dummy) {
   print "---- 1. test ----"
   axx = "3199044596370769"
   bxx = "-312593329000312593329"
   print "a     : " axx
   print "b     : " bxx
   multf(axx, bxx)
   print "mult  : " multf_result
   print "---- 2. test ----"
   axx= "60967068778579064460287972"
   bxx= "7419043440758059956596"
   print "a * b : 452317331723962514217511611516823866219980863312"
   print "a     : " axx
   print "b     : " bxx
   multf(axx, bxx)
   print "mult  : " multf_result
   #mult(axx, bxx)
   #print "mult  : " mult_result
   print "---- 3. test ----"
   axx= "452317331723962514217511611516823866219980863312"
   bxx= "60967068778579064460287972"
   print "a     : " axx
   print "b     : " bxx
   div(axx,bxx)
   print "quot  : " div_quot
   print "mod   : " div_mod
   bxx= "7419043440758059956596"
   print "a     : " axx
   print "b     : " bxx
   div(axx,bxx)
   print "quot  : " div_quot
   print "mod   : " div_mod
   print "---------- 4. test1 : a/b = c --> c * b + mod = a  ----------"
   axx = "188888888888888888888888888888888888888888888888888823456789000000000000000000123456789099"
   bxx = "999999991234567890000000001144"
# ok
#   axx = "-100000000000000000000000000000000000000000000000000000000000"
#   bxx = "-1000000000000000000000000000000000"
   #bxx = "188888888888888888888888888888888888888888888888888823456789000000000000000000123456789099"
   #axx = "999999991234567890000000001144"
   print "a     : " axx
   print "b     : " bxx
   div(axx,bxx)
   print "quot  : " div_quot
   print "mod   : " div_mod
   multf(bxx, div_quot)
   print "mult  : " multf_result
   addsub(multf_result, div_mod, "+")
   print "add   : " add_sum
   addsub(add_sum, axx,"-")
   print "diff  : " add_sum
#
}
#===============================================================
#
#  function euclidext
#  extended euclid algorithmn
#
#===============================================================
#
# algorithm fromPC Magazin Kryptographie
# solve equation  e*d mod (p-1) * (q-1)
# find d     
# p and q are prime  n = p * q , e = public exponenet, n public mod
#
#
#===============================================================
function euclidext(eucl_e , eucl_p, eucl_q) {
  print "----- extended euclid algorithm -----"
#
# p-1, q-1
#
  addsub(eucl_p,"1","-") ; eucl_p1 = add_sum 
  addsub(eucl_q,"1","-") ; eucl_q1 = add_sum 
  multf(eucl_p1, eucl_q1)
  eucl_a = multf_result 
  eucl_p1q1 = eucl_a
 # print "(p-1) * (q-1): " eucl_a
  eucl_b = eucl_e
  eucl_g = "1"
  eucl_s1 = "1"
  eucl_s2 = "0"
  eucl_s = "0"
  eucl_t1 = "0"
  eucl_t2 = "1"
  eucl_t = "1"
#---------------
  for(;;) {
   div( eucl_a, eucl_b)
   if(div_mod == "0") break
   eucl_r = div_mod
   eucl_u = div_quot
   print "      a : " eucl_a "   b : " eucl_b
   print "   quot : " eucl_u " mod : " eucl_r
 #
   multf(eucl_u, eucl_s2)
   addsub(eucl_s1, multf_result,"-")
   # print "q*s2:" multf_result
   eucl_s = add_sum
 #
   multf(eucl_u, eucl_t2)
   # print "q,t2:" eucl_u " " eucl_t2
   # print "q*t2:" multf_result
   addsub(eucl_t1, multf_result,"-")
   eucl_t = add_sum
   #  print "s,t : " eucl_s " " eucl_t
 #
   eucl_s1 = eucl_s2
   eucl_s2 = eucl_s
   eucl_t1 = eucl_t2
   eucl_t2 = eucl_t
   eucl_a = eucl_b
   eucl_b = eucl_r
  }
   if(substr(eucl_t,1,1) == "-") {
     addsub(eucl_t, eucl_p1q1,"+")
     eucl_t = add_sum
   }
   print " Equation : 1 = e * d + s * n"
   print "   e : " eucl_e
   print " p-1 : " eucl_p
   print " q-1 : " eucl_q
   print "   d : " eucl_t
   print "   s : " eucl_s
   print "   n : " eucl_p1q1
#
#  check
#
   print " check : e * d mod n =? 1"
   multf(eucl_e, eucl_t)
   div(multf_result, eucl_p1q1)
   print "   e * d : " multf_result
   print "   quot  : " div_quot
   print "   mod   : " div_mod
  print "---------------------------------------"
}   
#===============================================================
# check euclid algorithm
#===============================================================
function test2(dummy) {
# p=47, q=71, e = 79 d = 1019
   q = "71"
   p = "47"
   e = "79"
   euclidext(e, p, q) 
   q = "17"
   p = "11"
   e = "7"
   euclidext(e, p, q) 
   p = "37419669101"
   q = "11110693267"
   e = "65537"
   # d = 16481384459631305873
   euclidext(e , p, q) 
}
#===============================================================
#  singh
#===============================================================
#  compute d from singhs stage 10
#===============================================================
# from stage 9
# exponent is 3735928559 in decimal and the public modulus is the
# following 155-digit decimal integer
# 10742 78829 12665 65907 17841 12799 42116 61266 39217 94753 29458
# 88778 17210 35546 41509 80121 87903 38329 26235 28109 07506 72083
# 50494 19964 33143 42555 83344 01855 80898 94268 92463
#===============================================================
# 10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463
# 155
#107427882912665659071784112799421166126639217947532945888778172103554641509801 ...
#...21879033832926235281090750672083504941996433143425558334401855808989426892463 = <BR>
# = p78 x 12844205165381031491662259028977553198964984323915864368216177647043137765477
#
# from book :
# encrypted message :10052309732229513534129906692115454819045820926472181191154299190012948726620201558098093292390967106434191354276852757248495788598062733369293563609485523
#===============================================================
function singh(dummy) {
   print "-------- Simon Singh Cipher Challenge stage 10 --------"
   n_singh = "10742788291266565907178411279942116612663921794753294588877817210355464150980121879033832926235281090750672083504941996433143425558334401855808989426892463"
   q77_singh = "12844205165381031491662259028977553198964984323915864368216177647043137765477"
   print "n     : " n_singh " " length(n_singh)
   print "q77   : " q77_singh " " length(q77_singh)
   div(n_singh,q77_singh)
   print "quot  : " div_quot " " length(div_quot)
   print "mod   : " div_mod
   p78_singh = div_quot
   multf(q77_singh, p78_singh)
   if(multf_result != n_singh) {
     print "Error p*q"
     exit
   }
   e_singh = "3735928559" 
   euclidext(e_singh , p78_singh, q77_singh) 
   d_singh = eucl_t
   print "d     : " d_singh " " length(d_singh)
   enc_singh = "10052309732229513534129906692115454819045820926472181191154299190012948726620201558098093292390967106434191354276852757248495788598062733369293563609485523"
#
# decrypt message
#
   modexp(enc_singh, d_singh, n_singh)
   print "Result:" modexp_res
   bcd_binhex(modexp_res)
   print "Bin : " bcd_binres "   " length(bcd_binres)
   print "Hex : " bcd_hexres "   " length(bcd_hexres)
#    bcd_binhex(bcdnumber) ... result in bcd_binres
#                                        bcd_hexres
}
#===============================================================
# test4
#===============================================================
# test pow (a,b) mod n
#===============================================================
function test4(dummy) {
   print "---- test pow (a,b) mod n ---"
   # public exponent
   b="65537"
   a="11182516201512150709"
   # modulus
   n="415758465533848642967"
   modexp( a,b,n)
   print modexp_res
   # privat exponent
   b="16481384459631305873"
   # a="71043117991897565951"
   n="415758465533848642967"
   modexp(modexp_res,b,n)
   print modexp_res
   if(a != modexp_res) {
     print "Error"
   } else {
     print "Conversion ok !!"
   }
}
#===============================================================
# test_hex
#===============================================================
#
# test of hex conversion
function test_hex(dummy) {
  print "Test hex-bcd and bcd-hex conversion"
  print "Test1:"
  # hex_zahl = "FFFFFFFFFFFFFFFFFFFFFFFF000000000FFFFF0000000FFFFFFFFFF123456789ABCDEFF"
  hex_zahl = "FFFFFFFFFFFFFFFFFFFFFFFF000000000FFFFF0000000FFFFFFFFFF123456789ABCDEFF"
  print "Hex : " hex_zahl
  print "Length : " length(hex_zahl)
  hex_bcd(hex_zahl) 
  print "Bcd : " hex_bcdres
  print "Length : " length(hex_bcdres)
  bcd_binhex(hex_bcdres)
  #print "Bin : " bcd_binres
  print "Bin :" bcd_binres
  print "Hex : " bcd_hexres
  if(hex_zahl != bcd_hexres) print "Not equal"
  #
  print "Test2:"
  zahl = "68719476736"
  print "Zahl decimal :" zahl
  bcd_binhex(zahl)
  print "Bin          :" bcd_binres
  print "Hex          :" bcd_hexres
}
#===============================================================
# test_hex1024
#===============================================================
# test of hex conversion
#
function test_hex1024(dummy) {
  print "Test hex-bcd and bcd-hex conversion"
  print "Test1:"
# 256 hex = 1024 bit
hex_zahl="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
  print "Hex : " hex_zahl
  print "Length : " length(hex_zahl)
  hex_bcd(hex_zahl) 
  print "Bcd : " hex_bcdres
  print "Length : " length(hex_bcdres)
  bcd_binhex(hex_bcdres)
  #print "Bin : " bcd_binres
  print "Bin :" bcd_binres
  print "Length : " length(bcd_binres)
  print "Hex : " bcd_hexres
  print "Test2:"
# 256 hex = 1024 bit
hex_zahl="8000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
  print "Hex : " hex_zahl
  print "Length : " length(hex_zahl)
  hex_bcd(hex_zahl) 
  print "Bcd : " hex_bcdres
  print "Length : " length(hex_bcdres)
  bcd_binhex(hex_bcdres)
  #print "Bin : " bcd_binres
  print "Bin :" bcd_binres
  print "Length : " length(bcd_binres)
  print "Hex : " bcd_hexres
}
#=======================================================================
#
# function bcd_binhex
#
#=======================================================================
function bcd_binhex(bcd_zahl) {
#=======================================================================
# result : bcd_binres  ... binary result
#          bcd_hexres  ... hex result
#=======================================================================
# algorithm : 
#   bin = ""
#   for all bits do
#     shift right 1 bit
#      split array in groups of 4 bits
#         if (group > 8 ) group = group -3
#   end
#=======================================================================
#
  #print "Zahl decimal :" bcd_zahl
  if(bcd_zahl == "0" || bcd_zahl == "") {
   bcd_binres = "0" 
   bcd_hexres = "0" 
   return
  }
  gsub(/^0*/,"", bcd_zahl)
  if(bcd_zahl == "") {
   bcd_binres = "0" 
   bcd_hexres = "0" 
   return
  }
  bcd_zahl_len = length(bcd_zahl)
#
# check valid bcd string
#
  bcd_ok = 0
  for(bcd_ii= 1 ; bcd_ii <= bcd_zahl_len; bcd_ii++) {
    bcd_digit = substr(bcd_zahl,bcd_ii,1)
    for(bcd_ki=1 ; bcd_ki <= 10; bcd_ki++) {
        if(bcd_digit == hex[bcd_ki]){
        bcd_ok++
        break
      }
    }
  }
  if( bcd_ok != bcd_zahl_len) {
    bcd_bad = bcd_zahl_len - bcd_ok
    print "Illegal BCD number : Bad char : " bcd_bad " String : " bcd_zahl
    exit
  }
  # konvert BCD to binary
  bcd_binreg= ""
  for(bcd_i =  bcd_zahl_len ; bcd_i >= 1 ; bcd_i--){
     bcd_digit = substr(bcd_zahl,bcd_i,1)
     # print "digit : " bcd_digit
     bcd_digit = bcd_digit + 1
     bcd_binreg =  bhex[bcd_digit] bcd_binreg
  }
  # print "Zahl BCD     :" bcd_binreg
  bcd_reglen = length(bcd_binreg)
  #
  # shift right all bits , subtract 3 if 4 bit  group >= 8 
  #------------------------------------------------------------
  bcd_binres = ""
  bcd_xbinreg = bcd_binreg
  for(bcd_mainl = 1 ; bcd_mainl <= bcd_reglen ; bcd_mainl++) {
      bcd_binreg = bcd_xbinreg
      # get right bit
      bcd_bitout = substr(bcd_binreg, bcd_reglen, 1)
      # add to output
      bcd_binres =  bcd_bitout bcd_binres
      bcd_binreg = substr(bcd_binreg, 1, bcd_reglen - 1)
      # add 0 left side
      bcd_binreg = "0" bcd_binreg
      # print " shift: " bcd_mainl" bit:" bcd_bitout " reg:" bcd_binreg
      #--------
      # correct groups of 4 bit after shift
      bcd_xbinreg = ""
      for(bcd_i = 1; bcd_i <= bcd_zahl_len ; bcd_i++) {
        bcd_k = (bcd_i - 1) * 4 + 1  
        bcd_x = substr(bcd_binreg,bcd_k,4)
        # printf("x:%s ", bcd_x)
         for(bcd_k=1; bcd_k <=16; bcd_k++) {
           if(bcd_x == bhex[bcd_k]) break
         }
         bcd_block = bcd_k - 1
         if(bcd_block >= 8) {
           bcd_block = bcd_block - 3
           bcd_y = bhex[bcd_block+1]      
         }else{
           bcd_y = bcd_x
         }
        # printf("y:%s ", bcd_y)
        bcd_xbinreg = bcd_xbinreg bcd_y 
      } 
      #print ""
      #--------
  }
  #------------------------
  # print "Zahl binaer  :" bcd_bin
  # convert bin to hex
  bcd_hexres = ""
  for(bcd_i = 1; bcd_i <= bcd_zahl_len ; bcd_i++) {
     bcd_k = (bcd_i - 1) * 4 + 1  
     bcd_x = substr(bcd_binres,bcd_k,4)
       for(bcd_k=1; bcd_k <=16; bcd_k++) {
         if(bcd_x == bhex[bcd_k]) break
       }
     bcd_z = bcd_k
     bcd_hexres = bcd_hexres hex[bcd_z]
  }
  gsub(/^0*/,"", bcd_hexres)
  gsub(/^0*/,"", bcd_binres)
#
}
#=======================================================================
#
# function hex_bcd
#
#=======================================================================
# algorithm for bin(hex) bcd conversion :
# shift all bits left in a new register
# check before shifting each decade and if > 4 add 3
# finished if all bits are shifted
#=======================================================================
# result in hex_bcdres
#=======================================================================
function hex_bcd(hex_zahl) {
  # print "hexzahl : " hex_zahl
  if(hex_zahl == "0" || hex_zahl == "") {
   hex_bcdres = "0" 
   return
  }
  gsub(/^0*/,"", hex_zahl)
  if(hex_zahl == "") {
   hex_bcdres = "0" 
   return
  }
  hex_zahl_len = length(hex_zahl)
#
# check valid hex string
#
  hex_ok = 0
  for(hex_ii= 1 ; hex_ii <= hex_zahl_len; hex_ii++) {
    hex_digit = substr(hex_zahl,hex_ii,1)
    for(hex_ki=1 ; hex_ki <= 16; hex_ki++) {
        if(hex_digit == hex[hex_ki]){
        hex_ok++
        break
      }
    }
  }
  if( hex_ok != hex_zahl_len) {
    hex_bad = hex_zahl_len - hex_ok
    print "Illegal HEX number : Bad char : " hex_bad " String : " hex_zahl
    exit
  }
  # convert hex to bin
  hex_binreg= ""
  for(hex_i =  hex_zahl_len ; hex_i >= 1 ; hex_i--){
     hex_digit = substr(hex_zahl,hex_i,1)
      # print "digit : " hex_digit
         for(hex_zz=1; hex_zz <=16; hex_zz++) {
           if( hex[hex_zz] == hex_digit) {
            hex_binreg = bhex[hex_zz] hex_binreg
            break
           }
         }
  }
  # print "Zahl bin     :" hex_binreg
  hex_reglen = length(hex_binreg)
 #
 # shift left all bits in new register and store in hexbinreg1
 # split in groups before shift and make correction
 # 
  hex_binreg1 = ""
  hex_xbinreg1 = ""
  hex_bitout = ""
  # loop over all bits
  for(hex_mainl = 1 ; hex_mainl <= hex_reglen ; hex_mainl++) {
      #print"xx:" hex_xbinreg1
      hex_binreg1 = hex_xbinreg1 
      gsub(/^0*/,"", hex_binreg1)
      hex_ll = length(hex_binreg1) 
      hex_mod = hex_ll % 4
      if(hex_mod == 0) hex_binreg1 = "0000" hex_binreg1
      if(hex_mod == 1) hex_binreg1 = "000" hex_binreg1
      if(hex_mod == 2) hex_binreg1 = "00" hex_binreg1
      if(hex_mod == 3) hex_binreg1 = "0" hex_binreg1
      hex_ll4 = length(hex_binreg1)
      # print hex_ll4 " " hex_binreg1
      # split in groups of 4 bit
      hex_xbinreg1 = ""
      for(hex_i = 1; hex_i <= hex_ll4/4 ; hex_i++) {
        hex_k = (hex_i - 1) * 4 + 1  
        hex_x = substr(hex_binreg1,hex_k,4)
        # printf("x:%s ", hex_x)
        # correct group
        #----------------
         for(hex_k=1; hex_k <=16; hex_k++) {
           if(hex_x == bhex[hex_k]) break
         }
         hex_block = hex_k - 1
         if(hex_block > 4) {
           hex_block = hex_block + 3
           hex_y = bhex[hex_block+1]      
         }else{
           hex_y = hex_x
         }
         #printf("y:%s ", hex_y)
         hex_xbinreg1 = hex_xbinreg1 hex_y 
        #----------------
      }
      # print ""
      # get leftt bit
      hex_bitout = substr(hex_binreg, hex_mainl, 1)
      # add to output
      hex_xbinreg1 =  hex_xbinreg1 hex_bitout
  }
  # convert bin to decimal
  # print "Ergebnis:" hex_xbinreg1
  hex_xbinreg1 = "0000" hex_xbinreg1
  hex_resl = length(hex_xbinreg1) + 1
  hex_bcdres = ""
  for(hex_i = 1; ; hex_i++) {
     xhex_k = hex_i  * 4   
     hex_end = hex_resl - xhex_k
     if(hex_end < 1) break
     hex_x = substr(hex_xbinreg1, hex_resl - xhex_k, 4)
     # print hex_end " " hex_i " " hex_x
       for(hex_k=1; hex_k <=16; hex_k++) {
         if(hex_x == bhex[hex_k]) break
       }
     hex_z = hex_k
     hex_bcdres = hex[hex_z] hex_bcdres
  }
  gsub(/^0*/,"", hex_bcdres)
  #print "bcdzahl : " hex_bcdres
}
#=======================================================================
#
#  modexp
#
#=============================================================
# compute pow (a,b) mod n with binary multiply
#=============================================================
# algorithm
#  huge a,b,y
#  y = 1
#  for all bits in b do ( from low bit to to high)
#    if bit == 1 do
#      y = (y * a) mod n
#    end if
#    a = ( a * a) mod n
#  end for
#  return y
#===============================================================
function modexp(mex_a, mex_b, mex_n) {
  # convert b to bin
  print "------- pow (a,b) mod n ------"  
  print "a : " mex_a
  print "b : " mex_b
  print "n : " mex_n
  bcd_binhex(mex_b)
  # get binary string
  mex_ll = length(bcd_binres)
  print "b binary : " bcd_binres
  mex_y = "1"
  mex_cc = 0
  for(mex_i=mex_ll; mex_i >= 1; mex_i--) {
    mex_bit = substr(bcd_binres, mex_i, 1)
    # print mex_bit
    if(mex_bit == "1") {
      mex_cc++
      multf(mex_y, mex_a)
      printf(" %d", mex_i)
      if(mex_cc == 12) {
       print ""
       mex_cc = 0
      }
       #  print ">>> bit: " mex_i " y*a:" multf_result
      div(multf_result, mex_n)
      mex_y = div_mod
       #  print "y*a mod n:" mex_y
    }
    multf(mex_a, mex_a)
     #  print "a*a:" multf_result
    div(multf_result, mex_n)
    mex_a = div_mod
     #  print "a*a mod n:" mex_a
  }
  modexp_res = mex_y 
  print ""
  print "Result :" modexp_res
}
#===============================================================
#    bcd_binhex(bcdnumber) ... result in bcd_binres
#                                        bcd_hexres
#    hex_bcd(hexnumber) ..... result in hex_bcdres
#    multf(a,b)       ... result in multf_result
#    div(a,b)        ... result in div_quot , div_mod
#    addsub(a,b,"+") ... result in add_sum  
#    addsub(a,b,"-")                           
#    euclidext(e, p, q) ... result in eucl_t 
#    bcd_binhex(bcdnumber) ... result in bcd_binres
#                                        bcd_hexres
#    hex_bcd(hexnumber) ..... result in hex_bcdres
#===============================================================
# ossifrage
# solution of RSA 129
#===============================================================
function ossifrage(dummy) {
# following challenge was published 1977
 print "------- squeamish ossifrage -------"
# public modulus
 oss_n129 = "114381625757888867669235779976146612010218296721242362562561842935706935245733897830597123563958705058989075147599290026879543541"
# public exponent
 oss_e = "9007"
# factoring done 1994 17 years later
 oss_p64 = "3490529510847650949147849619903898133417764638493387843990820577"
 oss_q65 = "32769132993266709549961988190834461413177642967992942539798288533"
#
# check 
 multf( oss_p64, oss_q65)
 print "n129 : " oss_n129
 print "p64  : " oss_p64
 print "q65  : " oss_q65
 print "e    : " oss_e
 print multf_result
 if(multf_result != oss_n129){
    print "Error 1"
 } else {
    print ">>> p*q ok "
 }
 #
 # get private exponent
 euclidext(oss_e, oss_p64, oss_q65)
 oss_d = eucl_t
 print "d   : " oss_d
 print "length :" length(oss_d)
#
# encrypted message published 1977 in Scientific America
#
 oss_mess = "96869613754622061477140922254355882905759991124574319874695120930816298225145708356931476622883989628013391990551829945157815154"
#
# decrypt message
#
 modexp(oss_mess, oss_d, oss_n129)
 print "Result:" modexp_res
#
# convert to text
#
  oss_a[0] = " "
  oss_a[1] = "A"
  oss_a[2] = "B"
  oss_a[3] = "C"
  oss_a[4] = "D"
  oss_a[5] = "E"
  oss_a[6] = "F"
  oss_a[7] = "G"
  oss_a[8] = "H"
  oss_a[9] = "I"
  oss_a[10] = "J"
  oss_a[11] = "K"
  oss_a[12] = "L"
  oss_a[13] = "M"
  oss_a[14] = "N"
  oss_a[15] = "O"
  oss_a[16] = "P"
  oss_a[17] = "Q"
  oss_a[18] = "R"
  oss_a[19] = "S"
  oss_a[20] = "T"
  oss_a[21] = "U"
  oss_a[22] = "V"
  oss_a[23] = "W"
  oss_a[24] = "X"
  oss_a[25] = "Y"
  oss_a[26] = "Z"
#Result :200805001301070903002315180419000118050019172105011309190800151919090618010705
#oss_result="200805001301070903002315180419000118050019172105011309190800151919090618010705"
  oss_result = modexp_res
  print oss_result
  oss_l = length(oss_result)
  print oss_l
  print " Decrypted message : "
  for ( oss_i =1; oss_i <oss_l; oss_i=oss_i+2) {
   oss_aa = substr ( oss_result, oss_i, 2)
   oss_aa = oss_aa + 0
   printf("%s", oss_a[oss_aa])
  }
  print""
 print "------- end of squeamish ossifrage -------"
}
#===============================================================
