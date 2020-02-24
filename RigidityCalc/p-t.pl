#/usr/bin/perl -w

# for triton: 

$E =  $ARGV[0];               #
 
# Atomic Mass Tables of G. Audi and A. Wapstra3 (Source 3). 
# See http://64.233.161.104/search?q=cache:JOmA4yH8_d0J:www.nndc.bnl.gov/csewg_members/ENDF-102/src/Fmts-H.doc+triton+mass&hl=en&gl=za&ct=clnk&cd=10
# Triton mass	3.016049268	amu
# E equiv of u	9.31494013	10^8 eV/amu
# Triton mass	2809.43184	MeV
$m=2809.43184;


$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\nfor triton  --> ",$P," MeV/c \n\n";

print "(Nonrelativistically ",$nrP," MeV/c) \n";

close IN;





