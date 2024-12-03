#!/usr/bin/awk -f

{
	while (match($0, /mul\([0-9]{1,3},[0-9]{1,3}\)/))
	{
		matched_str = substr($0, RSTART, RLENGTH);

		num1 = substr($0, RSTART + 4, index(substr($0, RSTART), ",") - 1);
		num2 = substr($0, RSTART + index(substr($0, RSTART), ","), RLENGTH - index(substr($0, RSTART), ",") - 1);

		total += num1 * num2;

		print matched_str, num1 * num2, total;
		$0 = substr($0, RSTART + RLENGTH);
	}

	print total;
}
