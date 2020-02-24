#/usr/bin/perl -w

# For d

$E =  $ARGV[0];               # 

$m =      1875.61282;         # MeV; from NIST website

$P = 0;
$nrP = 0;

$P=sqrt(($E+$m)*($E+$m)-$m*$m);
$nrP=sqrt($E*2*$m);

print "\n d:    ",int(10000*$P)/10000," MeV/c \n\n";
#print "Nonrelativistic: ",$nrP," MeV/c \n";


close IN;



