#/usr/bin/perl -w

$P =  $ARGV[0];               # runnr for the detBinRange file
$E = 0;

# FROM NIST website: for relative atomic mass
#$u = 931.49432;             # from NIST website
#$m =  3.016029309 * $u;  # NIST relative atomic mass times u

$m =3727.379109 ; # in MeV from http://physics.nist.gov/cuu/Constants/Table/allascii.txt


$E=sqrt($m*$m+$P*$P)-$m;

print "\n alpha: ",int(10000*$E)/10000," MeV ";

$E=$P*$P/(2*$m);
print "\n alpha non-rel: ",int(10000*$E)/10000," MeV\n\n ";



close IN;



