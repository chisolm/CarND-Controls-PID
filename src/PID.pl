#!/usr/bin/perl 

$twiddle = 1;

#hack for twiddle read
if ($twiddle == 1) {
	print "p0\tp1\tp2\tdp0\tdp1\tdp2\n";
} else {  # default
	print "count\tp_err\td_err\ti_err\tp0\tp1\tp2\tdp0\tdp1\tdp2\tcte\tsteer\tspeed\n";
}

while (<>) {

	#print $_;
	next if ( /best_particle_association/ );
	if (/Count: (.*)$/) {
		$count = $1;
	}
	if (/error:\t(.*)$/) {
		$error = $1;
	}
	if (/p values:\t(.*)$/) {
		$pvalues = $1;
	}
	if (/dp values:\t(.*)$/) {
		$dpvalues = $1;
	}
	if (/CTE: ([-\d\.]*) Steering Value: ([-\d\.]*) Speed ([-\d\.]*)$/) {
		($cte, $steer, $speed) = ($1, $2, $3);
		next;
	}
	if (/CTE:/) {
		print "Error $_";
	}
	if (/^42/) {
		#print "XXX";
		if ($twiddle == 1) {
			print "$pvalues\t$dpvalues\n";
		} else {
			print "$count\t$error\t$pvalues\t$dpvalues\t$cte\t$steer\t$speed\n";
		}
	}
}
