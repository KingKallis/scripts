#/usr/bin/perl -w

$P =  $ARGV[0];        
$m =      1875.61282;         # MeV; from NIST website
$E = 0;

$E=sqrt($m*$m+$P*$P)-$m;

print "\nd:        ",$E," MeV \n\n";

close IN;



