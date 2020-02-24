#/usr/bin/perl -w

# For d

$E =  $ARGV[0];               # runnr for the detBinRange file

#$m = 4.001506179127; #amu: http://physics.nist.gov/cuu/Constants/Table/allascii.txt
$m =3727.379109 ; # in MeV from http://physics.nist.gov/cuu/Constants/Table/allascii.txt

$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\n alpha:    ",int(10000*$P)/10000," MeV/c \n\n";
print "Nonrelativistic: ",$nrP," MeV/c \n";


close IN;



