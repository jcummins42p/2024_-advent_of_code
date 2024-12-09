/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day9.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/09 20:17:30 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef std::array<int, 2> t_block;

typedef std::vector< t_block > t_disk;

std::ostream &operator<<( std::ostream &os, const t_block &block ) {
	os << " { " << block[0] << ", " << block[1] << " } ";
	return (os);
}

void	printBlock(const std::vector<long> &answer) {
	for (unsigned long j = 0; j < answer.size(); j++) {
		if (answer[j] < 0)
			std::cout << ".";
		else
			std::cout << answer[j];
	}
	std::cout << std::endl;
}

int	addBlock( t_disk &disk, std::string line, unsigned int disk_size, std::vector<long> &answer) {
	static unsigned long i = 0;
	t_block	output = {-1,-1};
	int	returnval = 1;

	try {
		output[0] = line[0 + i] - '0';
		for (int j = 0; j < output[0]; j++)
		   answer.push_back(i / 2);
		output[1] = line[1 + i] - '0';
		for (int j = 0; j < output[1]; j++)
		   answer.push_back(-1);
		i += 2;
		if (i >= disk_size) throw std::runtime_error("Reached end of disk");
	}
	catch (std::runtime_error &e ) {
		std::cout << " (" << e.what() << ": resetting read position)";
		returnval = i = 0;
	}
	std::cout << std::endl << "\tadded block" << output;
	disk.push_back(output);
	return (returnval);
}

int compress( std::vector<long> answer )
{
	unsigned long size = answer.size();
	for (unsigned long i = 0; i < size; i++)
	{
		if (answer[i] < 0) {
			answer[i] = answer[answer.size() - 1];
			answer.erase(answer.end());
		}
		printBlock( answer );
	}
	sleep(1);
	return (0);
}

void readfile( char *filename )
{
	std::ifstream	ifs;
	std::string		line;
	t_disk			disk;
	unsigned long	disk_size;
	unsigned long	progress = 0;
	std::vector<long> answer;

	ifs.open (filename, std::fstream::in);
	if (!ifs.is_open()) {
		std::cout << "invalid file : " << filename << std::endl;
		exit (1);
	}
	while (std::getline(ifs, line)) {
		progress = 0;
		disk_size = line.size();
		std::cout << "Input: " << line << std::endl;
		std::cout << "Reading input blocks: ";
		while (addBlock(disk, line, disk_size, answer)) {
			std::cout << "(" << (progress / 2) + 1 << "/" << ((disk_size + 1) / 2) << ")";
			progress += 2;
		}
		std::cout << "(" << (progress / 2) + 1 << "/" << ((disk_size + 1) / 2) << ")" << std::endl;
	}
	printBlock(answer);
	//compress(answer);
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
