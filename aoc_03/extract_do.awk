#!/usr/bin/awk -f

{
	printing = 1;

	while (match($0, /(don't\(\)|do\(\))/))
	{
		token = substr($0, RSTART, RLENGTH);

		before_match = substr($0, 1, RSTART - 1);
		if (printing && length(before_match) > 0) {
			print before_match;
		}

		if (token == "don't()") {
			#print "don't()";
			printing = 0;
		} else if (token == "do()") {
			#print "do()";
			printing = 1;
		}

		$0 = substr($0, RSTART + RLENGTH);
	}

	if (printing) {
		print $0;
	}
}
