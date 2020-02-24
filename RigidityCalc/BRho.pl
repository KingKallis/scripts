#/usr/bin/perl -w

use Math::Trig;

$E =  $ARGV[0];              
$P = 0.;

# see CERN-magnet_Lecture2.pdf 
# BRho in Tesla meter = 10/2.998 beta E (in GeV)
# if we have p=gamma*mv then one can easily show (pc/e) becomes (gamma*E*beta/e)
#-------------------------------
$mp =  938.272046;         # MeV; from NIST website 2014
$md =  1875.61282;         # MeV; from NIST website
$mt =  2808.920906;        # MeV: see http://physics.nist.gov/cgi-bin/cuu/Value?mtc2mev
                           # I had it originally as 2809.43184;
                           # 2814.81675 MeV is simply multiply p mass times 3
$mhe3 = 2808.39142;        # MeV; NIST website for He3
$mhe4 = 3727.37917;        # MeV; from NIST website
#-------------------------------
# nuclear masses are:
$u=931.494028;             # NIST website                u=931.49432  from Nuclear Wallet Card, Jan 2000

$mkp = 1.00727646688;     # amu  
$mkd = 2.01355321270;     # amu http://en.wikipedia.org/wiki/Deuterium
$mkt = 3.016049268;       # amu
$mkhe3 =  3.014932;    # amu From http://fusedweb.pppl.gov/CPEP/Chart_Pages/3.HowFusionWorks.html
$mkhe4 = 4.0015061747;   # amu 

$mkhe6=6.0188891;        
$mhe6  =  $mkhe6*$u;      # 

$mkhe8=8.0;               # just a guess
$mhe8  =  $mkhe8*$u;      # 

$mkli7=7.0160034256;      # from http://adsabs.harvard.edu/abs/2006PhRvL..96p3004N
$mli7=$mkli7*$u;

$mkli8=8.;                 # just a guess
$mli8=$mkli8*$u;

$mO16=15.99491461956*$u;   # relative atomic weight from NIST
$mO18=17.9991610*$u;       # relative atomic weight from NIST

$mNe20=19.9924401754*$u;       # relative atomic weight from NIST

#-------------------------------

$qp=1.;
$qd=1.;
$qt=1.;
$qhe3=2.;
$qhe3_1plus=1.;
$qhe4=2.;
$qhe6=2.;
$qhe8=2.;
$qli7=3.;
$qli7_2plus=2.;
$qli8=3.;
$qO16=8.;
$qO16_plus7=7.;
$qO16_plus6=6.;
$qO16_plus5=5.;
$qO18=8.;
$qNe20=10.;
$qNe20_9plus=9.;
$qNe20_8plus=8.;
$qNe20_7plus=7.;


$Pp=sqrt(($E+$mp)*($E+$mp)-$mp*$mp);
$Pd=sqrt(($E+$md)*($E+$md)-$md*$md);
$Pt=sqrt(($E+$mt)*($E+$mt)-$mt*$mt);
$Phe3=sqrt(($E+$mhe3)*($E+$mhe3)-$mhe3*$mhe3);
$Phe4=sqrt(($E+$mhe4)*($E+$mhe4)-$mhe4*$mhe4);
$Phe6=sqrt(($E+$mhe6)*($E+$mhe6)-$mhe6*$mhe6);
$Phe8=sqrt(($E+$mhe8)*($E+$mhe8)-$mhe8*$mhe8);
$Pli7=sqrt(($E+$mli7)*($E+$mli7)-$mli7*$mli7);
$Pli8=sqrt(($E+$mli8)*($E+$mli8)-$mli8*$mli8);
$PO16=sqrt(($E+$mO16)*($E+$mO16)-$mO16*$mO16);
$PO18=sqrt(($E+$mO18)*($E+$mO18)-$mO18*$mO18);
$PNe20=sqrt(($E+$mNe20)*($E+$mNe20)-$mNe20*$mNe20);


$bRhop=($Pp/$qp)*10/2.998;  # gives answer in kG cm
$bRhod=($Pd/$qd)*10/2.998;
$bRhot=($Pt/$qt)*10/2.998;
$bRhohe3=($Phe3/$qhe3)*10/2.998;
$bRhohe3_1plus=($Phe3/$qhe3_1plus)*10/2.998;
$bRhohe4=($Phe4/$qhe4)*10/2.998;
$bRhohe6=($Phe6/$qhe6)*10/2.998;
$bRhohe8=($Phe8/$qhe8)*10/2.998;
$bRholi7=($Pli7/$qli7)*10/2.998;
$bRholi7_2plus=($Pli7/$qli7_2plus)*10/2.998;
$bRholi8=($Pli8/$qli8)*10/2.998;
$bRhoO16=($PO16/$qO16)*10/2.998;
$bRhoO16_plus7=($PO16/$qO16_plus7)*10/2.998;
$bRhoO16_plus6=($PO16/$qO16_plus6)*10/2.998;
$bRhoO16_plus5=($PO16/$qO16_plus5)*10/2.998;
$bRhoO18=($PO18/$qO18)*10/2.998;
$bRhoNe20=($PNe20/$qNe20)*10/2.998;
$bRhoNe20_9plus=($PNe20/$qNe20_9plus)*10/2.998;
$bRhoNe20_8plus=($PNe20/$qNe20_8plus)*10/2.998;
$bRhoNe20_7plus=($PNe20/$qNe20_7plus)*10/2.998;


print "\n B-Rho of a ",$E," MeV proton   (momentum ",int(1000*$Pp)/1000," MeV/c) = ",int(1000*$bRhop)/1000,"  kG cm  \n";
print " B-Rho of a ",$E," MeV deuteron (momentum ",int(1000*$Pd)/1000," MeV/c) = ",int(1000*$bRhod)/1000,"  kG cm  \n";
print " B-Rho of a ",$E," MeV triton   (momentum ",int(1000*$Pt)/1000," MeV/c) = ",int(1000*$bRhot)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV He3      (momentum ",int(1000*$Phe3)/1000," MeV/c) = ",int(1000*$bRhohe3)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV He3  1+  (momentum ",int(1000*$Phe3)/100," MeV/c) = ",int(1000*$bRhohe3_1plus)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV He4      (momentum ",int(1000*$Phe4)/1000," MeV/c) = ",int(1000*$bRhohe4)/1000,"  kG cm \n";

print " B-Rho of a ",$E," MeV He4      (momentum ",int(1000*$Phe4)/1000," MeV/c) = ",int(1000*$bRhohe4)/1000000,"  T m \n";

print " B-Rho of a ",$E," MeV He6      (momentum ",int(1000*$Phe6)/100," MeV/c) = ",int(1000*$bRhohe6)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV He8      (momentum ",int(1000*$Phe8)/100," MeV/c) = ",int(1000*$bRhohe8)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Li7      (momentum ",int(1000*$Pli7)/100," MeV/c) = ",int(1000*$bRholi7)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Li7  2+  (momentum ",int(1000*$Pli7)/100," MeV/c) = ",int(1000*$bRholi7_2plus)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Li8      (momentum ",int(1000*$Pli8)/100," MeV/c) = ",int(1000*$bRholi8)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV O16      (momentum ",int(1000*$PO16)/100," MeV/c) = ",int(1000*$bRhoO16)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV O16  7+  (momentum ",int(1000*$PO16)/100," MeV/c) = ",int(1000*$bRhoO16_plus7)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV O16  6+  (momentum ",int(1000*$PO16)/100," MeV/c) = ",int(1000*$bRhoO16_plus6)/1000,"  kG cm \n";
print " B-Rho of a ",$E," MeV O16  5+  (momentum ",int(1000*$PO16)/100," MeV/c) = ",int(1000*$bRhoO16_plus5)/1000,"  kG cm \n";

#print " B-Rho of a ",$E," MeV O18      (momentum ",int(1000*$PO18)/100," MeV/c) = ",int(1000*$bRhoO18)/1000,"  kG cm \n\n";
#print " B-Rho of a ",$E," MeV Ne20     (momentum ",int(1000*$PNe20)/100," MeV/c) = ",int(1000*$bRhoNe20)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Ne20  9+ (momentum ",int(1000*$PNe20)/100," MeV/c) = ",int(1000*$bRhoNe20_9plus)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Ne20  8+ (momentum ",int(1000*$PNe20)/100," MeV/c) = ",int(1000*$bRhoNe20_8plus)/1000,"  kG cm \n";
#print " B-Rho of a ",$E," MeV Ne20  7+ (momentum ",int(1000*$PNe20)/100," MeV/c) = ",int(1000*$bRhoNe20_7plus)/1000,"  kG cm \n";

print "To go from (kG cm) to (T m):  divide by 1000\n" ;


close IN;



# He-3
# FROM NIST website: for relative atomic mass 
#$u = 931.49432;             # from NIST website
#$m =  3.016029309 * $u;  # NIST relative atomic mass times u
#      3.0160497 is mass in amu in new SPEXCIT
#
# From http://fusedweb.pppl.gov/CPEP/Chart_Pages/3.HowFusionWorks.html
# nuclear masses are:
#$u =931.466;
#$m =  3.014932 * $u ;
#
# FROM NIST Helion Mass NIST; the helion is the nucleas of He-3 atom


# Atomic Mass Tables of G. Audi and A. Wapstra3 (Source 3). 
# See http://64.233.161.104/search?q=cache:JOmA4yH8_d0J:www.nndc.bnl.gov/csewg_members/ENDF-102/src/Fmts-H.doc+triton+mass&hl=en&gl=za&ct=clnk&cd=10
# Triton mass	3.016049268	amu
# E equiv of u	9.31494013	10^8 eV/amu
# Triton mass	2809.43184	MeV


#$mp = 938.272029;        # from NIST website
#$md = 1875.61282;        # from NIST website
#$mhe4 = 3727.37917;     # from NIST website
#$mhe3=2808.39142; #mhelion=2808.391 42(24) MeV
#$mt=2808.920906;   # MeV: see http://physics.nist.gov/cgi-bin/cuu/Value?mtc2mev
