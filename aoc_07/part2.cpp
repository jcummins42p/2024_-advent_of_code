/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/08 22:30:40 by jcummins         ###   ########.fr       */
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

void printCalculation(const std::vector<long long int> &record, std::string operators, int n_operators, int total)
{
	std::cout << std::endl << "\t: " << record[0];
	for (long int i = 0; i < n_operators; i++) { // cycle through each operator
		std::cout << " '" << operators[i] << "' ";
		std::cout << record[i + 1];
	}
	std::cout << " = " << total;
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

std::vector<long long int> combineDigitsAt(int i, std::vector<long long int> &input)
{
	std::vector<long long int> output = input;

	output[i + 1] = catNumber(output[i], output[i + 1]);
	output.erase(output.begin() + i);
	return (output);
}

std::string setOperators(long int permutation, long int n_operators) {
	std::string operators = "";

	for (int i = 0; i < n_operators; i++) {
		if (permutation % 3 == 0)
			operators += "+";
		else if (permutation % 3 == 1)
			operators += "*";
		else if (permutation % 3 == 2)
			operators += "|";
		permutation /= 3;
		if (permutation < 0)
			permutation = 0;
	}
	//std::cout << "Operators: " << operators << std::endl;
	return operators;
}

long int checkRecord(long long int target, std::vector<long long int> record)
{
	record.erase(record.begin());	// remove the target from the record to reduce confusion
	int				n_operators = record.size() - 1;
	std::string		operators;
	long int		n_permutations = toPwr(3, n_operators);
	long int		permutation = 0;
	long long int	total = 0;

	while (permutation < n_permutations)	// set test mask
	{
		operators = setOperators(permutation, n_operators);
		total = record[0];
		for (long int i = 0; i < n_operators; i++) {	// cycle through each operator
			if (operators[i] == '+' )
				total = total + record[i + 1];
			else if (operators[i] == '*')
				total = total * record[i + 1];
			else if (operators[i] == '|')
				total = catNumber(total, record[i + 1]);
			else {
				std::cout << "Unknown operator " << operators[i] << " found, in " << operators << " at index " << i << ", aborting" << std::endl;
				return (0);
			}
		}
		//printCalculation(record, operators, n_operators, total);
		if (total == target) {
			//printCalculation(record, operators, n_operators, total);
			std::cout << "RETURNING FOUND TARGET: " << total << std::endl;
			return (target);
		}
		operators.clear();
		permutation++;
	}
	return (0);
}

void print(int i, int n_records, const std::vector<long long int> &record)
{
	std::cout << std::endl << "Record " << i + 1 << " of " << n_records << ": ";
	std::cout << std::setw(15) << record[0] << ": ";
	for (size_t j = 1; j < record.size() - 1; j++) {
		std::cout << record[j] << " ";
	}
	std::cout << record[record.size() - 1];
}

int	readfile( char *argv )
{
	long long int	result = 0;
	int 			no_calibrations = 0;
	int				n_records;
	std::ifstream	ifstream;
	std::string		line;
	t_input			input;
	std::vector<long long int>	alt;

	ifstream.open(argv, std::ifstream::in);
	if (!ifstream.is_open())
		std::cout << "Failure to read file " << argv[1] << std::endl;
	while (std::getline(ifstream, line))
		parse(line, input);
	n_records = input.size();
	for (int i = 0; i < n_records; i++) {	// print and test each record
		//print(i, n_records, input[i]);
		result += checkRecord(input[i][0], input[i]);
	}
	std::cout << std::endl << std::endl << "Found " << no_calibrations
			<< " of " << n_records
			<< " records, totalling " << result  << std::endl;
	return (0);
}

int	main( int argc, char *argv[] )
{
	if (argc != 2) {
		std::cout << "Supply one file only" << std::endl;
		return (1);
	}
	readfile(argv[1]);

	return (1);
}
