/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/02 20:18:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

int	int_abs( int input ) {
	return (input < 0 ? 0 - input : input);
}

std::vector<std::string> Split(std::string str)
{
	std::istringstream iss (str);
	std::vector<std::string> v;
	while (iss >> str)
		v.push_back(str);
	return v;
}

void	get_numbers( std::string line, std::vector<int> *numbers) {
	std::vector<std::string> split = Split(line);

	for (int i = 0; i < split.size(); i++)
		numbers->push_back(std::atol(split[i].c_str()));
}

void	print_vec( std::vector<int> toprint )
{
	for (int i = 0; i < toprint.size(); i++)
		std::cout << toprint[i] << std::endl;
}

bool comp(int a, int b) {
	return a <= b;
}

void	printvector( std::vector<int> toprint ) {
	std::cout << "Printing from vector" << std::endl;
	for (int i = 0; i < toprint.size(); i++)
		std::cout << toprint[i] << " ";
	std::cout << std::endl;
}

int	no_appearances( int needle, std::vector<int> list )
{
	int	appearances = 0;
	for (int i = 0; i < list.size(); i++) {
		if (needle == list[i])
			appearances++;
	}
	return (appearances);
}

bool	isSafeAgain( std::vector<int> numbers )
{
	int	ascending = 0;

	printvector( numbers );
	for (int i = 0; i < numbers.size() - 1; i++) {
		if (ascending == 0) {
			if (numbers[i] > numbers[i + 1])
				ascending = -1;
			else if (numbers[i] < numbers[i + 1])
				ascending = 1;
		}
		if (ascending < 0 && (numbers[i] < numbers[i + 1])) {
			std::cout << "descending order violated on index " << i << std::endl;
			std::cout << numbers[i] << " is smaller than " << numbers [i + 1] << std::endl;
			return (false);
		}
		if (ascending > 0 && numbers[i] > numbers[i + 1]) {
			std::cout << "ascending order violated on index " << i << std::endl;
			std::cout << numbers[i] << " is bigger than " << numbers [i + 1] << std::endl;
			return (false);
		}
		if (int_abs(numbers[i] - numbers[i + 1]) < 1) {
			std::cout << "Two identical numbers on index " << i << std::endl;
			return (false);
		}
		if (int_abs(numbers[i] - numbers[i + 1]) > 3) {
			std::cout << "Gap too large on index " << i << std::endl;
			std::cout << numbers[i] << " jumps to " << numbers [i + 1] << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	tryEverything( std::vector<int> numbers )
{
	bool safecheck = false;
	int index = 0;
	int	size = numbers.size();

	while (index < size)
	{
		std::vector<int> trythis = numbers;
		trythis.erase(trythis.begin() + index);
		safecheck = isSafeAgain( trythis );
		if (safecheck == true)
			return true;
		trythis.clear();
		index++;
	}
	return (false);
}

bool	isSafe( std::vector<int> numbers )
{
	int	ascending = 0;

	//printvector( numbers );
	for (int i = 0; i < numbers.size() - 1; i++) {
		if (ascending == 0) {
			if (numbers[i] > numbers[i + 1])
				ascending = -1;
			else if (numbers[i] < numbers[i + 1])
				ascending = 1;
		}
		if (ascending < 0 && (numbers[i] < numbers[i + 1])) {
			//std::cout << "descending order vilated on index " << i << std::endl;
			//std::cout << numbers[i] << " is smaller than " << numbers [i + 1] << std::endl;
			return (tryEverything(numbers));
		}
		if (ascending > 0 && numbers[i] > numbers[i + 1]) {
			//std::cout << "ascending order violated on index " << i << std::endl;
			//std::cout << numbers[i] << " is bigger than " << numbers [i + 1] << std::endl;
			return (tryEverything(numbers));
		}
		if (int_abs(numbers[i] - numbers[i + 1]) < 1) {
			//std::cout << "Two identical numbers on index " << i << std::endl;
			return (tryEverything(numbers));
		}
		if (int_abs(numbers[i] - numbers[i + 1]) > 3) {
			//std::cout << "Gap too large on index " << i << std::endl;
			//std::cout << numbers[i] << " jumps to " << numbers [i + 1] << std::endl;
			return (tryEverything(numbers));
		}
	}
	return (true);
}

int	readfile( char *filename )
{
	std::ifstream 		iss;
	std::vector<int>	numbers;
	int	total = 0;
	int index = 0;

	iss.open (filename, std::fstream::in);
	if (!iss.is_open()) {
		std::cout << "Invalid file : " << filename << std::endl;
		return (1);
	}
	std::string line;
	while (std::getline(iss, line)) {
		std::cout << "From file : " << line << "\t";
		get_numbers( line, &numbers );
		if (isSafe(numbers)) {
			std::cout << index << " SAFE: total " << total << std::endl << std::endl;
			total++;
		}
		else
			std::cout << index << " NOT SAFE: total " << total << std::endl << std::endl;
		numbers.clear();
		index ++;
	}
	return (total);
}

int	main( int argc, char *argv[] )
{
	int total = 0;
	if (argc != 2) {
		std::cout << "No file supplied" << std::endl;
		return (1);
	}
	total = readfile(argv[1]);
	std::cout << "Total safe is: " << total << std::endl;
	return (1);
}
