#/usr/bin/perl -w

# for triton: 

$E =  $ARGV[0];           
 
# 208Pb mass	208 amu         JUST A GUESS!!
# E equiv of u	931.494013	MeV/amu
$m=208*931.494013;


$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\nfor triton  --> ",$P," MeV/c \n\n";

print "(Nonrelativistically ",$nrP," MeV/c) \n";

close IN;





