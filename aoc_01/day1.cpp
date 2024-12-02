/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day1.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/02 18:09:26 by jcummins         ###   ########.fr       */
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

void	get_numbers( std::string line, std::vector<int> *avec, std::vector<int> *bvec ) {
	std::vector<std::string> split = Split(line);

	int a = std::atol(split[0].c_str());
	int b = std::atol(split[1].c_str());
	std::cout << "Got numbers: " << a << " and " << b << std::endl;

	avec->push_back(a);
	bvec->push_back(b);
}

void	print_vec( std::vector<int> toprint )
{
	for (int i = 0; i < toprint.size(); i++)
		std::cout << toprint[i] << std::endl;
}

bool comp(int a, int b) {
	return a <= b;
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

int	readfile( char *filename )
{
	std::ifstream iss;
	std::vector<int> a, b;
	int	total = 0;

	iss.open (filename, std::fstream::in);
	if (!iss.is_open()) {
		std::cout << "Invalid file : " << filename << std::endl;
		return (1);
	}
	std::string line;
	while (std::getline(iss, line)) {
		std::cout << "From file : " << line << std::endl;
		get_numbers( line, &a, &b );
	}
	sort(a.begin(), a.end(), comp);
	sort(b.begin(), b.end(), comp);
	print_vec(a);
	print_vec(b);
	for (int i = 0; i < a.size(); i++)
		total += a[i] * no_appearances(a[i], b);
	return (total);
}

int	main( int argc, char *argv[] )
{
	if (argc != 2) {
		std::cout << "No file supplied" << std::endl;
		return (1);
	}
	std::cout << "Total answer is: " << readfile(argv[1]);
	return (1);
}
