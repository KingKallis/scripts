#/usr/bin/perl -w

$E =  $ARGV[0];               
$m = 938.272046;        # from NIST website, 2014 value
$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\n  --> ",$P," MeV/c \n\n";

print "(Nonrelativistically ",$nrP," MeV/c) \n";

close IN;



