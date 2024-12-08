/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day7.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/08 17:08:08 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef std::vector< std::vector<long long int> > t_input;

void parse(std::string line, t_input& input) {
	std::istringstream iss (line);
	std::vector< long long int >	output;

	iss >> line;
	line.erase(line.end() - 1);
	output.push_back(std::atol(line.c_str()));
	while (iss >> line) {
		output.push_back(std::atol(line.c_str()));
	}
	input.push_back(output);
}

long int toPwr( long long int base, long long int exponent ) {
	long long int output = base;

	if (exponent == 0)
		return (1);
	while (exponent > 1) {
		output = output * base;
		exponent--;
	}
	return output;
}

void printBitmask(const std::vector<long long int> &record, int bitmask, int n_operators)
{
	std::cout << std::endl << "\t\t   : " << record[0];
	for (long int i = 0; i < n_operators; i++) {	// cycle through each operator
		//std::cout << "\tChecking " << i << " with bitmask " << operator_mask + 1 << std::endl;
		//std::cout << "\tDoing calculation " << record[i];
		if (bitmask & (1 << i)) {
			std::cout << " * ";
		}
		else {
			std::cout << " + ";
		}
		std::cout << record[i + 1];
	}
	std::cout << std::endl;
}

long long int catNumber(long long int a, long long int b)
{
	int	figures = 1;
	long long int tmp = b;

	while (tmp > 10) {
		tmp = tmp / 10;
		figures += 1;;
	}
	return ((a * toPwr(10, figures)) + b);
}

long int checkRecord(long long int target, std::vector<long long int> &record)
{
	record.erase(record.begin());	// remove the target from the record to reduce confusion
	int	operator_mask = 0; // dictates where multiplications happen by bit;
	int	n_operators = record.size() - 1;
	long int		iterations = toPwr(2, n_operators);
	long long int	total = 0;

	//std::cout << "Record size: " << record.size() << " means " << iterations << " total iterations to test" << std::endl;
	while (operator_mask <= iterations)	// set test mask
	{
		total = record[0];
		//std::cout << "Checking bitmask " << operator_mask << std::endl;
		for (long int i = 0; i < n_operators; i++) {	// cycle through each operator
			//std::cout << "\tChecking " << i << " with bitmask " << operator_mask + 1 << std::endl;
			//std::cout << "\tDoing calculation " << record[i];
			if (operator_mask & (1 << i)) {
				total = total * record[i + 1];
				//std::cout << " * ";
			}
			else {
				total = total + record[i + 1];
				//std::cout << " + ";
			}
			//std::cout << record[i + 1] << std::endl;
		}
		//std::cout << std::endl << "\tFound total: " << total;
		if (total == target) {
			//std::cout << std::endl << "\tFound total: " << total;
			//std::cout << " in bitmask " << operator_mask;
			//std::cout << total;
			//printBitmask(record, operator_mask, n_operators);
			return (target);
		}
		operator_mask++;
	}
	//std::cout << "Found no viable solution" << std::endl;
	return (0);
}

bool	preCheckRecord(const std::vector<long long int> &record)
{
	long long int target = record[0];
	long long int maxtotal = 1;
	long long int mintotal = 0;

	for ( int i = 1; i < record.size(); i++ ) {
		if (record[i] == 1) {
			mintotal = mintotal * record[i];
			maxtotal = maxtotal + record[i];
		}
		else {
			mintotal = mintotal + record[i];
			maxtotal = maxtotal * record[i];
		}
	}
	if (maxtotal < target) {
		std::cout << ": IMPOSSIBLE (" << maxtotal << ") too low";
		return (1);
	}
	else if (mintotal > target) {
		std::cout << ": IMPOSSIBLE (" << mintotal << ") too high";
		return (1);
	}
	if (maxtotal == target) {
		std::cout << std::endl << "\nNext solution should be in bitmask " << toPwr(2, (record.size() - 2)) - 1;
		return (0);
	}
	if (mintotal == target) {
		std::cout << std::endl << "\nNext solution should be in bitmask 0";
		return (0);
	}
	return(0);
}

void print(int i, int n_records, const std::vector<long long int> &record)
{
	std::cout << std::endl << "Record " << i + 1 << " of " << n_records << ": ";
	std::cout << std::setw(20) << record[0] << ": ";
	for (int j = 1; j < record.size() - 1; j++) {
		std::cout << record[j] << " ";
	}
	std::cout << record[record.size() - 1];
}

int	readfile( char *argv )
{
	long long int	total_calibration= 0;
	long int		tmp = 0;
	int 			no_calibrations = 0;
	int				n_records;
	std::ifstream	ifstream;
	std::string		line;
	t_input			input;
	long long int	result;

	ifstream.open(argv, std::ifstream::in);
	if (!ifstream.is_open())
		std::cout << "Failure to read file " << argv[1] << std::endl;
	while (std::getline(ifstream, line)) {
		parse(line, input);
	}
	n_records = input.size();
	for (int i = 0; i < n_records; i++) {	// print and test each record
		print(i, n_records, input[i]);
		//std::cout << "Record #" << i + 1 << ": ";
		if (!preCheckRecord(input[i])) // only print records in possible range
		{
			result = checkRecord(input[i][0], input[i]);
			if (result) {
				no_calibrations++;
			}
			//std::cout << result;
			total_calibration += result;
			result = 0;
		}
		//else
			//std::cout << "0";
		//std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << "Found " << no_calibrations
			<< " of " << n_records
			<< " records, totalling " << total_calibration << std::endl;
	return (0);
}

int	main( int argc, char *argv[] )
{
	int total = 0;
	if (argc != 2) {
		std::cout << "Supply one file only" << std::endl;
		return (1);
	}
	//total = readfile(argv[1]);

	return (1);
}
