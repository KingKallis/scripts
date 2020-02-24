#/usr/bin/perl -w

# For He3

$E =  $ARGV[0];               # runnr for the detBinRange file
# FROM NIST website: for relative atomic mass
#$u = 931.49432;             # from NIST website
#$m =  3.016029309 * $u;  # NIST relative atomic mass times u
#
# From http://fusedweb.pppl.gov/CPEP/Chart_Pages/3.HowFusionWorks.html
# nuclear masses are:
#$u =931.466;         
#$m =  3.014932 * $u ;
#
# FROM NIST Helion Mass NIST; the helion is the nucleas of He-3 atom
$m=2808.39142; #mhelion=2808.391 42(24) MeV 

# Atomic Mass Tables of G. Audi and A. Wapstra3 (Source 3). 
# See http://64.233.161.104/search?q=cache:JOmA4yH8_d0J:www.nndc.bnl.gov/csewg_members/ENDF-102/src/Fmts-H.doc+triton+mass&hl=en&gl=za&ct=clnk&cd=10
# Triton mass	3.016049268	amu
# E equiv of u	9.31494013	10^8 eV/amu
# Triton mass	2809.43184	MeV
$mt=2809.43184;


$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\n He3:    ",int(10000*$P)/10000," MeV/c \n";
#print "Nonrelativistic: ",$nrP," MeV/c \n";

$Pt=sqrt(($E+$mt)*($E+$mt)-$mt*$mt);

print " triton: ",int(10000*$Pt)/10000," MeV/c \n\n";


close IN;



