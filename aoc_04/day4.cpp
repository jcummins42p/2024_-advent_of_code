/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day4.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/04 11:14:50 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

#define GRID_HEIGHT 140

//	starts at top right
bool isDiagonalOne( const std::string line[GRID_HEIGHT], const std::string &find, int y, int x )
{
	if (line[y][x] == find[0]) {
		if (line[y + 1][x - 1] == find[1])
			if (line[y + 2][x - 2] == find[2]) {
				//if (line[y + 3][x - 3] == find[3]) {
					//std::cout << "Found " << find << " at " << y << ", " << x << std::endl;
					return true;
				}
	}
	return false;
}

bool isDiagonalTwo( const std::string line[GRID_HEIGHT], const std::string &find, int y, int x )
{
	if (line[y][x] == find[0]) {
		if (line[y + 1][x + 1] == find[1])
			if (line[y + 2][x + 2] == find[2]) {
				//if (line[y + 3][x + 3] == find[3]) {
					//std::cout << "Found " << find << " at " << y << ", " << x << std::endl;
					return (true);
				}
	}
	return (false);
}

int	findCross( const std::string line[GRID_HEIGHT], const std::string &find )
{
	int y = 0;
	int x = 0;
	int found_t = 0;
	int found_l = 0;
	std::string revf = find;
	std::reverse(revf.begin(), revf.end());
	std::cout << "Reverse string is " << revf << std::endl;

	while (y + 2 < GRID_HEIGHT)
	{
		while (line[y + 2][x + 2])
		{
			if ((isDiagonalTwo(line, find, y, x) || isDiagonalTwo(line, revf, y, x))
					&& (isDiagonalOne(line, find, y, x + 2) || isDiagonalOne(line, revf, y, x + 2))) {
				std::cout << "Full cross found at " << y << ", " << x << std::endl;
				found_l++;
			}
			x++;
		}
		//std::cout << "CROSS: On " << y + 1 << " of " << find << " there are " << found_l << std::endl;
		found_t += found_l;
		found_l = 0;
		x = 0;
		y++;
	}
	std::cout << std::endl;
	return found_t;
}

int	findDiagonalOne( const std::string line[GRID_HEIGHT], const std::string &find )
{
	int y = 0;
	int x = 3;
	int found_t = 0;
	int found_l = 0;

	while (y < GRID_HEIGHT)
	{
		while (line[y][x])
		{
			if (isDiagonalOne(line, find, y, x))
				found_l++;
			x++;
		}
		std::cout << "DIAG1: On " << y + 1 << " of " << find << " there are " << found_l << std::endl;
		found_t += found_l;
		found_l = 0;
		x = 3;
		y++;
	}
	std::cout << std::endl;
	return found_t;
}

int	findDiagonalTwo( const std::string line[GRID_HEIGHT], const std::string &find )
{
	int y = 0;
	int x = 0;
	int found_t = 0;
	int found_l = 0;

	while (y < GRID_HEIGHT)
	{
		while (line[y + 3][x + 3])
		{
			if (isDiagonalTwo(line, find, y, x))
				found_l++;
			x++;
		}
		std::cout << "DIAG2: On " << y + 1 << " of " << find << " there are " << found_l << std::endl;
		found_t += found_l;
		found_l = 0;
		x = 0;
		y++;
	}
	std::cout << std::endl;
	return found_t;
}

int	findHorizontal( const std::string line[GRID_HEIGHT], const std::string &find )
{
	int y = 0;
	int x = 0;
	int found_t = 0;
	int found_l = 0;

	while (y < GRID_HEIGHT)
	{
		while (line[y][x])
		{
			if (line[y][x + 0] == find[0]) {
				if (line[y][x + 1] == find[1])
					if (line[y][x + 2] == find[2])
						if (line[y][x + 3] == find[3])
							found_l++;
			}
			x++;
		}
		std::cout << "HORIZ: On " << y + 1 << " of " << find << " there are " << found_l << std::endl;
		found_t += found_l;
		found_l = 0;
		x = 0;
		y++;
	}
	std::cout << std::endl;
	return found_t;
}

int	findVertical( const std::string line[GRID_HEIGHT], const std::string &find )
{
	int y = 0;
	int x = 0;
	int found_t = 0;
	int found_l = 0;

	while (y < GRID_HEIGHT)
	{
		while (line[y + 3][x])
		{
			if (line[y][x] == find[0]) {
				if (line[y + 1][x] == find[1])
					if (line[y + 2][x] == find[2])
						if (line[y + 3][x] == find[3])
							found_l++;
			}
			x++;
		}
		std::cout << "VERT: On row " << y + 1 << " of " << find << " there are " << found_l << std::endl;
		found_t += found_l;
		found_l = 0;
		x = 0;
		y++;
	}
	std::cout << std::endl;
	return found_t;
}

int	readfile( char *filename )
{
	std::ifstream 		iss;
	std::vector<int>	numbers;
	int index = 0;
	std::string 		words[GRID_HEIGHT + 1];
	int					total = 0;

	iss.open (filename, std::fstream::in);
	if (!iss.is_open()) {
		std::cout << "Invalid file : " << filename << std::endl;
		return (1);
	}
	while (std::getline(iss, words[index])) {
		index ++;
	}
	//total += findHorizontal(words, "XMAS");
	//total += findHorizontal(words, "SAMX");
	//total += findDiagonalOne(words, "XMAS");
	//total += findDiagonalOne(words, "SAMX");
	//total += findDiagonalTwo(words, "XMAS");
	//total += findDiagonalTwo(words, "SAMX");
	//total += findVertical(words, "XMAS");
	//total += findVertical(words, "SAMX");
	total += findCross(words, "MAS");
	std::cout << "Total found: " << total;
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

	std::cout << "Total found: " << total << std::endl;
	return (1);
}
