#/usr/bin/perl -w

$P =  $ARGV[0];        
$m = 938.272046;        # from NIST website 2014
$E = 0;

$E=sqrt($m*$m+$P*$P)-$m;

print "\n",$E," MeV \n\n";

close IN;



