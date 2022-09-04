#################################################################
# 1.) Gemeinlot von 2 beliebigen Geraden g und h :
# Die Geraden werden durch 2 Punkte beschrieben :
# g.... P1 (  7.00   6.00   0.00)
# g.... P2 (  0.00  10.00  10.00)
# h.... P1 ( 10.00   3.00   5.00)
# h.... P2 (  0.00   0.00  10.00)
#   7.00   6.00   0.00
#   0.00  10.00  10.00
#  10.00   3.00   5.00
#   0.00   0.00  10.00
#   fprintf(ausdat,"# Die Geraden werden durch 2 Punkte beschrieben :\n");
#
BEGIN {
#   fprintf(ausdat,"# g.... P1 (%6.2f %6.2f %6.2f)\n"
#
#
   eps = 0.001
   x=1
   y=2
   z=3

   # 7.00   6.00   0.00
   # 0.00  10.00  10.00
   # 10.00   3.00   5.00
   #  0.00   0.00  10.00

   point3_g11[x] = 7.0 ;
   point3_g11[y] = 6.0 ;
   point3_g11[z] = 0
#
#  fprintf(ausdat,"# g.... P2 (%6.2f %6.2f %6.2f)\n"
#
   point3_g12[x] = 0.0 ; point3_g12[y] =  10.0   ; point3_g12[z] = 10.0
#
#  fprintf(ausdat,"# h.... P1 (%6.2f %6.2f %6.2f)\n"
#
   point3_h11[x] = 10.0 ; point3_h11[y] =  3.0   ; point3_h11[z] = 5.0
#
#  fprintf(ausdat,"# h.... P2 (%6.2f %6.2f %6.2f)\n"
#
   point3_h12[x] = 0.0 ; point3_h12[y] =  0.0    ; point3_h12[z] = 10.0
#
   printf(" g11 = %6.2f %6.2f %6.2f\n",point3_g11[x], point3_g11[y], point3_g11[z])
   printf(" g12 = %6.2f %6.2f %6.2f\n",point3_g12[x], point3_g12[y], point3_g12[z])
   printf(" h11 = %6.2f %6.2f %6.2f\n",point3_h11[x], point3_h11[y], point3_h11[z])
   printf(" h12 = %6.2f %6.2f %6.2f\n",point3_h12[x], point3_h12[y], point3_h12[z])
#
#  vektor Richtung g 
#
   point3_g11[x] = point3_g11[x] + 0.0
   point3_g11[y] = point3_g11[y] + 0.0
   point3_g11[z] = point3_g11[z] + 0.0
   point3_g12[x] = point3_g12[x] + 0.0
   point3_g12[y] = point3_g12[y] + 0.0
   point3_g12[z] = point3_g12[z] + 0.0
#
   point3_v1[x] = point3_g11[x] - point3_g12[x];
   point3_v1[y] = point3_g11[y] - point3_g12[y];
   point3_v1[z] = point3_g11[z] - point3_g12[z];
#   print point3_v1[x]
#   print point3_v1[y]
#   print point3_v1[z]
#
#  vektor Richtung h 
#
   point3_v2[x] = point3_h11[x] - point3_h12[x];
   point3_v2[y] = point3_h11[y] - point3_h12[y];
   point3_v2[z] = point3_h11[z] - point3_h12[z];
#
# kreuzprod
#
   point3_vn[x] =   point3_v1[y] * point3_v2[z] - point3_v1[z] * point3_v2[y];
   point3_vn[y] = - point3_v1[x] * point3_v2[z] + point3_v1[z] * point3_v2[x];
   point3_vn[z] =   point3_v1[x] * point3_v2[y] - point3_v1[y] * point3_v2[x];
#
#   print point3_vn[x]
#   print point3_vn[y]
#   print point3_vn[z]
#
# Hilfsebene in g  parallel h
#
  n1[x] = point3_vn[x]; n1[y] = point3_vn[y]; n1[z]= point3_vn[z];
  d1 = n1[x] * point3_g11[x] + n1[y] * point3_g11[y] + n1[z] * point3_g11[z];
  eag = n1[x]; ebg = n1[y]; ecg = n1[z]; edg = d1;
  print "Hilfsebene gamma: in g parallel zu h : a =" eag " b = " ebg " c = " ecg " d = " edg 
  print "Hilfsebene gamma: in g normal zu gamma : a =" edg/eag " b = " ed/ebg " c = " ed/ecg " d = " edg/edg 

#  /* ebene parallel n in g */
  point3_v2[x] = point3_vn[x];
  point3_v2[y] = point3_vn[y];
  point3_v2[z] = point3_vn[z];
#
# kreuzprod
#
   point3_vn[x] =   point3_v1[y] * point3_v2[z] - point3_v1[z] * point3_v2[y];
   point3_vn[y] = - point3_v1[x] * point3_v2[z] + point3_v1[z] * point3_v2[x];
   point3_vn[z] =   point3_v1[x] * point3_v2[y] - point3_v1[y] * point3_v2[x];
   print point3_vn[x]
   print point3_vn[y]
   print point3_vn[z]
#
  n1[x] = point3_vn[x]; n1[y] = point3_vn[y]; n1[z]= point3_vn[z];
  d1 = n1[x] * point3_g11[x] + n1[y] * point3_g11[y] + n1[z] * point3_g11[z];
  ead = n1[x] ; ebd = n1[y]; ecd = n1[z]; edd = d1;
  print "Hilfsebene delta: in g normal zu gamma : a =" ead " b = " ebd " c = " ecd " d = " edd 
  print "Hilfsebene delta: in g normal zu gamma : a =" edd/ead " b = " edd/ebd " c = " edd/ecd " d = " edd/edd 
#
#void durchstoss()
#------------------
# stosse gerade h durch delta
#
  point3_gp1[x] = point3_h11[x];
  point3_gp1[y] = point3_h11[y];
  point3_gp1[z] = point3_h11[z];
  point3_gp2[x] = point3_h12[x];
  point3_gp2[y] = point3_h12[y];
  point3_gp2[z] = point3_h12[z];
  xx = point3_gp1[x] - point3_gp2[x];
  yy = point3_gp1[y] - point3_gp2[y];
  zz = point3_gp1[z] - point3_gp2[z];
  nn1 = edd-ead*point3_gp1[x] - ebd*point3_gp1[y] - ecd*point3_gp1[z];
  nn2 = ead * xx + ebd * yy + ecd * zz;
  print xx " " yy " " zz
  print nn1 " " nn2
  if (nn2*nn2 < eps ) nn2 = eps;
  s = nn1/nn2;
  point3_pkt[x] = point3_gp1[x] + s * xx;
  point3_pkt[y] = point3_gp1[y] + s * yy;
  point3_pkt[z] = point3_gp1[z] + s * zz;
  print "Durchstosspunkt FH :  x = " point3_pkt[x] " y = "  point3_pkt[y] " z = "  point3_pkt[z] 
#
  dp1[x] = point3_pkt[x]; dp1[y] = point3_pkt[y]; dp1[z] = point3_pkt[z];
#
#  /* stosse gerade durch gamma, s = 10 */
#-------------------------------------------
#
#  ea = n1[x] ; eb = n1[y]; ec = n1[z]; ed = d1;
  point3_gp1[x] = dp1[x];
  point3_gp1[y] = dp1[y];
  point3_gp1[z] = dp1[z];
  point3_gp2[x] = dp1[x] + 10.0 * eag;
  point3_gp2[y] = dp1[y] + 10.0 * ebg;
  point3_gp2[z] = dp1[z] + 10.0 * ecg;
  xx = point3_gp1[x] - point3_gp2[x];
  yy = point3_gp1[y] - point3_gp2[y];
  zz = point3_gp1[z] - point3_gp2[z];
  nn1 = edg-eag*point3_gp1[x] - ebg*point3_gp1[y] - ecg*point3_gp1[z];
  nn2 = eag * xx + ebg * yy + ecg * zz;
  print xx " " yy " " zz
  print nn1 " " nn2
  if (nn2*nn2 < eps ) nn2 = eps;
  s = nn1/nn2;
  point3_pkt[x] = point3_gp1[x] + s * xx;
  point3_pkt[y] = point3_gp1[y] + s * yy;
  point3_pkt[z] = point3_gp1[z] + s * zz;
  print "Durchstosspunkt FG :  x = " point3_pkt[x] " y = "  point3_pkt[y] " z = "  point3_pkt[z] 
#
  dp2[x] = point3_pkt[x]
  dp2[y] = point3_pkt[y]
  dp2[z] = point3_pkt[z]

#  /* Abstand der 2 Geraden */
#
  dist = sqrt((dp1[x]-dp2[x]) * (dp1[x]-dp2[x]) + (dp1[y]-dp2[y]) * (dp1[y]-dp2[y]) + (dp1[z]-dp2[z])* (dp1[z]-dp2[z]));
  print " dist = " dist
}
{
}

#xxxxxxxxxxxxxxxxxxxx
#struct coordinates3 {double x; double y; double z;};
#
#   fprintf(ausdat,"#########################################\n");
#   fprintf(ausdat,"# 1.) Gemeinlot von 2 beliebigen Geraden g und h :\n");
#   fprintf(ausdat,"# Die Geraden werden durch 2 Punkte beschrieben :\n");
#   fprintf(ausdat,"# g.... P1 (%6.2f %6.2f %6.2f)\n",point3_g11.x,point3_g11.y,point3_g11.z);
#   fprintf(ausdat,"# g.... P2 (%6.2f %6.2f %6.2f)\n",point3_g12.x,point3_g12.y,point3_g12.z);
#   fprintf(ausdat,"# h.... P1 (%6.2f %6.2f %6.2f)\n",point3_h11.x,point3_h11.y,point3_h11.z);
#   fprintf(ausdat,"# h.... P2 (%6.2f %6.2f %6.2f)\n",point3_h12.x,point3_h12.y,point3_h12.z);
#   fprintf(ausdat," %6.2f %6.2f %6.2f\n",point3_g11.x,point3_g11.y,point3_g11.z);
#   fprintf(ausdat," %6.2f %6.2f %6.2f\n",point3_g12.x,point3_g12.y,point3_g12.z);
#   fprintf(ausdat," %6.2f %6.2f %6.2f\n",point3_h11.x,point3_h11.y,point3_h11.z);
#   fprintf(ausdat," %6.2f %6.2f %6.2f\n",point3_h12.x,point3_h12.y,point3_h12.z);
#
#/*****************************************************
#      function gemeinlot : bilde das Gemeinlot
#******************************************************/
#void gemeinlot()
#{
#  struct coordinates3 n,n1,dp1,dp2;
#  double d,d1,dist;
#  char word[40];
#  /* vektor Richtung g */
#  point3_v1.x = point3_g11.x - point3_g12.x;
#  point3_v1.y = point3_g11.y - point3_g12.y;
#  point3_v1.z = point3_g11.z - point3_g12.z;
#  /* vektor Richtung h */
#  point3_v2.x = point3_h11.x - point3_h12.x;
#  point3_v2.y = point3_h11.y - point3_h12.y;
#  point3_v2.z = point3_h11.z - point3_h12.z;
#  kreuzprod();
#  /* ebene durch g parallel h */
#  n.x = point3_vn.x; n.y = point3_vn.y; n.z= point3_vn.z;
#  d = n.x * point3_g11.x + n.y * point3_g11.y + n.z * point3_g11.z;
#  ea = n.x ; eb = n.y; ec = n.z; ed = d;
#  color(GOLD);
#  ebene();
#  /* ebene parallel n in g */
#  point3_v2.x = point3_vn.x;
#  point3_v2.y = point3_vn.y;
#  point3_v2.z = point3_vn.z;
#  kreuzprod();
#  n1.x = point3_vn.x; n1.y = point3_vn.y; n1.z= point3_vn.z;
#  d1 = n1.x * point3_g11.x + n1.y * point3_g11.y + n1.z * point3_g11.z;
#  ea = n1.x ; eb = n1.y; ec = n1.z; ed = d1;
#  color(GOLD);
#  ebene();
#  /* stosse h durch delta */
#  point3_gp1.x = point3_h11.x;
#  point3_gp1.y = point3_h11.y;
#  point3_gp1.z = point3_h11.z;
#  point3_gp2.x = point3_h12.x;
#  point3_gp2.y = point3_h12.y;
#  point3_gp2.z = point3_h12.z;
#  durchstoss();
#  dp1.x = point3_pkt.x; dp1.y = point3_pkt.y; dp1.z = point3_pkt.z;
#  /* stosse gerade durch gamma, s = 10 */
#  ea = n.x ; eb = n.y; ec = n.z; ed = d;
#  point3_gp1.x = dp1.x;
#  point3_gp1.y = dp1.y;
#  point3_gp1.z = dp1.z;
#  point3_gp2.x = dp1.x + 10.0 * n.x;
#  point3_gp2.y = dp1.y + 10.0 * n.y;
#  point3_gp2.z = dp1.z + 10.0 * n.z;
#  durchstoss();
#  dp2.x = point3_pkt.x; dp2.y = point3_pkt.y; dp2.z = point3_pkt.z;
#  point3_gp2.x = dp2.x;
#  point3_gp2.y = dp2.y;
#  point3_gp2.z = dp2.z;
#  /* Abstand der 2 Geraden */
#  dist = sqrt(pow((dp1.x-dp2.x),2) + pow((dp1.y-dp2.y),2.) + pow((dp1.z-dp2.z),2.));
#  color(3);
#  gerade1();
#  color(4);
#  sprintf(word,"Gemeinlot:");
#  gpl_outtextxy(10,textoffs,word);
#
#  sprintf(word,"Punkt F1 x=%6.2f y=%6.2f z=%6.2f",dp1.x,dp1.y,dp1.z);
#  gpl_outtextxy(10,textoffs+15,word);
#  sprintf(word,"Punkt F2 x=%6.2f y=%6.2f z=%6.2f",dp2.x,dp2.y,dp2.z);
#  gpl_outtextxy(10,textoffs+30,word);
#  sprintf(word,"x =  %6.2f + s * %6.2f",dp2.x,n.x);
#  gpl_outtextxy(10,textoffs+45,word);
#  sprintf(word,"y =  %6.2f + s * %6.2f",dp2.y,n.y);
#  gpl_outtextxy(10,textoffs+60,word);
#  sprintf(word,"z =  %6.2f + s * %6.2f",dp2.z,n.z);
#  gpl_outtextxy(10,textoffs+75,word);
#  sprintf(word,"Distanz = %6.2f",dist);
#  gpl_outtextxy(10,textoffs+90,word);
#  color(9);
# /* beschreibe Punkte */
# point3.x = dp1.x + 0.2;
# point3.y = dp1.y + 0.2;
# point3.z = dp1.z;
# trans();
# sprintf(word,"F1");
# gpl_outtextxy(point2.x, point2.y, word);
# point3.x = dp2.x + 0.2;
# point3.y = dp2.y + 0.2;
# point3.z = dp2.z;
# trans();
# sprintf(word,"F2");
# gpl_outtextxy(point2.x, point2.y, word);
# 
#}
#
#/*****************************************************
#  function kreuzprod : bilde das Kreuzprodukt von 2 Vektoren
#******************************************************/
#void kreuzprod()
#{
#  point3_vn.x =   point3_v1.y * point3_v2.z - point3_v1.z * point3_v2.y;
#  point3_vn.y = - point3_v1.x * point3_v2.z + point3_v1.z * point3_v2.x;
#  point3_vn.z =   point3_v1.x * point3_v2.y - point3_v1.y * point3_v2.x;
#}
#/*****************************************************
#  function durchstoss : stosse Gerade durch Ebene
#******************************************************/
#void durchstoss()
#{
#  double xx,yy,zz,s,nn1,nn2;
#  xx = point3_gp1.x - point3_gp2.x;
#  yy = point3_gp1.y - point3_gp2.y;
#  zz = point3_gp1.z - point3_gp2.z;
#  nn1 = ed-ea*point3_gp1.x - eb*point3_gp1.y - ec*point3_gp1.z;
#  nn2 = ea * xx + eb * yy + ec * zz;
#  if (nn2*nn2 < eps ) nn2 = eps;
#  s = nn1/nn2;
#  point3_pkt.x = point3_gp1.x + s * xx;
#  point3_pkt.y = point3_gp1.y + s * yy;
#  point3_pkt.z = point3_gp1.z + s * zz;
#  pkt();
#}
#xxxxxxxxxxxxxxxxx

