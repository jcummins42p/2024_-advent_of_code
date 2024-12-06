/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day6.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/06 11:09:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef enum direction {
	D_NON,
	D_UP,
	D_RIGHT,
	D_DOWN,
	D_LEFT
} t_direction;

typedef struct s_guard {
	int	dir;
	int	pos[2];
} 	t_guard;

void	readMap(char *filename, std::vector<std::string> &map)
{
	std::ifstream	ifs;
	std::string		line;
	int				i = 0;

	ifs.open (filename, std::fstream::in);
	if (!ifs.is_open()) {
		std::cout << "invalid file : " << filename << std::endl;
		exit (1);
	}
	while (std::getline(ifs, line)) {
		try {map.push_back(line); }
		catch ( const std::exception & ) {
			std::cout << "Error processing " << filename << " on line " << i << std::endl;
		}
	}
}

int	getDir( char check ) {
	if ( check == '^' )
		return (D_UP);
	if ( check == '>' )
		return (D_RIGHT);
	if ( check == 'v' )
		return (D_DOWN);
	if ( check == '<' )
		return (D_LEFT);
	return (D_NON);
}

void	setStart( std::vector<std::string> map, t_guard &guard )
{
	int	y = 0;
	int x = 0;
	int	dir = D_NON;

	for (int y = 0; y < map.size(); y++){
		for (int x = 0; x < map[y].size(); x++) {
			dir = getDir(map[y][x]);
			if (dir) {
				guard.pos[0] = y;
				guard.pos[1] = x;
				guard.dir = dir;
			}
		}
		x = 0;
	}
}

void initGuard( t_guard &guard ) {
	guard.pos[0] = -1;
	guard.pos[1] = -1;
	guard.dir = D_NON;
}

void printGuard( const t_guard &guard ) {
	std::cout << "Guard at x=" << guard.pos[1] + 1
			<< ", y=" << guard.pos[0] + 1;
	switch (guard.dir) {
		case D_UP:
			std::cout << " facing UP.";
			break;
		case D_RIGHT:
			std::cout << " facing RIGHT.";
			break;
		case D_DOWN:
			std::cout << " facing DOWN.";
			break;
		case D_LEFT:
			std::cout << " facing LEFT.";
			break;
	}
	std::cout << std::endl;
}

int	traverseMap( std::vector<std::string> map )
{
	int 	total = 0;
	t_guard	guard;

	initGuard(guard);
	setStart(map, guard);
	if (guard.dir >= 0)
		printGuard(guard);
	else {
		std::cout << "Error: couldn't find guard" << std::endl;
		return (0);
	}
	//while (true)
	//{

	//}
	return (1);
}

void printMap( std::vector<std::string> map )
{
	for (int i = 0; i < map.size(); i++)
		std::cout << map[i] << std::endl;
}

int	readfile( char *argv )
{
	std::vector<std::string>	map;

	readMap(argv, map);
	printMap(map);
	traverseMap( map );
	return (0);
}

int	main( int argc, char *argv[] )
{
	int total = 0;
	if (argc != 2) {
		std::cout << "Supply one file only" << std::endl;
		return (1);
	}
	total = readfile(argv[1]);

	return (1);
}
