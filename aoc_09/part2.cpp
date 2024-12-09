/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/09 23:50:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef std::array<int, 3> t_block;

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
		output[2] = -1;
		i += 2;
		if (i >= disk_size) throw std::runtime_error("Reached end of disk");
	}
	catch (std::runtime_error &e ) {
		//std::cout << " (" << e.what() << ": resetting read position)";
		returnval = i = 0;
	}
	//std::cout << std::endl << "\tadded block" << output;
	disk.push_back(output);
	return (returnval);
}

int compress( std::vector<long> &answer )
{
	unsigned long size = answer.size();
	for (unsigned long i = 0; i < size; i++)
	{
		while (answer[answer.size() - 1] < 0) {
			answer.erase(answer.end() - 1);
			size = answer.size();
		}
		if (answer[i] < 0) {
			answer[i] = answer[answer.size() - 1];
			answer.erase(answer.end() - 1);
		}
	}
	printBlock( answer );
	//sleep(1);
	return (0);
}

std::vector<long> writeDisk( t_disk disk ) {
	std::vector<long> output;
	unsigned long size = disk.size();

	for (unsigned long i = 0; i < size; i++)
	{
		for (int j = 0; j < disk[i][0]; j++)
			output.push_back(i / 2);
		for (int j = 0; j < disk[i][1]; j++) {
			if (!(disk[i][2] < 0))
			   output.push_back(disk[i][2]);
			else
			   output.push_back(-1);
		}
		i += 2;
		if (i >= size)
			break;
	}
	printBlock( output );
	return (output);
}

t_disk compressDisk( t_disk disk ) {
	unsigned long size = disk.size();

	for (unsigned long i = 0; i < size; i++ )
	{
		for (unsigned long j = (size - 1 - i); j > 0; j--)
		{
			if (disk[j][0] <= disk[i][1] && disk[i][2] < 0) {
				disk[i][2] = j;
				break;
			}
		}
	}
	return (disk);
}

unsigned long long checksum( std::vector<long> answer) {
	unsigned long long output = 0;
	unsigned long size = answer.size();

	for (unsigned long i = 0; i < size; i++) {
		std::cout << answer[i] << " * " << i << " + ";
		output += answer[i] * i;
	}
	return (output);
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
		//std::cout << "Input: " << line << std::endl;
		//std::cout << "Reading input blocks: ";
		while (addBlock(disk, line, disk_size, answer)) {
			//std::cout << "(" << (progress / 2) + 1 << "/" << ((disk_size + 1) / 2) << ")";
			progress += 2;
		}
		//std::cout << "(" << (progress / 2) + 1 << "/" << ((disk_size + 1) / 2) << ")" << std::endl;
	}
	printBlock(answer);
	compress(answer);
	writeDisk(compressDisk(disk));
	//std::cout << checksum(answer) << std::endl;
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
