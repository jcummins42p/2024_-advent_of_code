/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day6.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/09 16:42:28 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef std::array<int, 2> t_pos;

typedef std::vector<std::pair<t_pos, int>> t_hist;

typedef enum direction {
	D_NON,
	D_UP,
	D_RIGHT,
	D_DOWN,
	D_LEFT
} t_dir;

typedef enum moveresult {
	R_ENDSIM,
	R_WALL,
	R_COUNTED,
	R_EMPTY,
} t_moveresult;

typedef struct s_guard {
	int		dir;
	t_pos	pos;
	int 	spacesmoved;
	bool	loop;
	t_hist	history;
} 	t_guard;

std::ostream &operator<<( std::ostream &os, const t_pos &pos ) {
	os << "{ " << pos[0] << " , " << pos[1] << " }";
	return (os);
}

bool	addToHistory(t_guard &guard) // returns true if path has been trod before
{
	std::pair<t_pos, int> newSquare = {{guard.pos[0], guard.pos[1]}, guard.dir};
	if (find(guard.history.begin(), guard.history.end(), newSquare) == guard.history.end()) {
		guard.history.push_back(newSquare);
		return false;
	}
	std::cout << "Found loop at x=" << guard.pos[1] << ", y=" << guard.pos[0] << std::endl;
	guard.loop = true;
	return true;
}

void	readMap(char *filename, std::vector<std::string> &map)
{
	std::ifstream	ifs;
	std::string		line;
	int				i = 0;

	map.clear();	// reset to empty
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
	int dir = D_NON;

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
	guard.spacesmoved = 0;
	guard.history.clear();
	addToHistory(guard);
	guard.loop = false;
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

int moveTo( std::vector<std::string> &map, t_guard &guard, int y, int x )
{
	if (y < 0 || x < 0 || y >= map.size() || x >= map[y].size()) {
		map[guard.pos[0]][guard.pos[1]] = 'E';
		guard.spacesmoved++;
		return ( R_ENDSIM );
		}
	char square = map[y][x];
	if (square == '#' || square == 'O') {
		guard.dir = ((guard.dir % 4) + 1);
		return ( R_WALL );	// change direct
		}
	if (square == '.') {
		map[guard.pos[0]][guard.pos[1]] = 'X';
		addToHistory(guard);
		guard.pos[0] = y;
		guard.pos[1] = x;
		guard.spacesmoved++;
		return ( R_EMPTY );
		}
	if (square == 'X') {
		map[guard.pos[0]][guard.pos[1]] = 'X';
		addToHistory(guard);
		guard.pos[0] = y;
		guard.pos[1] = x;
		return ( R_COUNTED);
		}
	map[guard.pos[0]][guard.pos[1]] = 'S';
	std::cout << "Error: unknown char '" << square << "' in map, quitting." << std::endl;
	return (0);
}

void printMap( std::vector<std::string> map )
{
	std::cout << std::endl;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '#')
				std::cout << "🎄";
			else if (map[i][j] == '.')
				std::cout << "🟫";
			else if (map[i][j] == 'X')
				std::cout << "🎅";
			else if (map[i][j] == 'E')
				std::cout << "🏆";
		}
		std::cout << std::endl;
	}
	sleep(1);
	std::cout << "\033[2J";
}

int	traverseMap( std::vector<std::string> &map, t_guard &guard, std::vector<t_pos> &history )
{
	static int run_count = -1;
	int 	total = 0;
	int		moveresult = 1;
	int x = guard.pos[1];
	int y = guard.pos[0];
	t_pos	newpos;

	run_count++;
	while (moveresult && !guard.loop)
	{
		x = guard.pos[1];
		y = guard.pos[0];
		if (!run_count) {
			newpos = {guard.pos[0], guard.pos[1]};
			history.push_back(newpos);
			//std::cout << "Adding to history: " << newpos;
		}
		switch (guard.dir)
		{
			case D_UP:
				moveresult = (moveTo(map, guard, y - 1, x)) ;
				if (!moveresult)
					return (guard.spacesmoved);
				break;
			case D_RIGHT:
				moveresult = (moveTo(map, guard, y, x + 1)) ;
				if (!moveresult)
					return (guard.spacesmoved);
				break;
			case D_DOWN:
				moveresult = (moveTo(map, guard, y + 1, x)) ;
				if (!moveresult)
					return (guard.spacesmoved);
				break;
			case D_LEFT:
				moveresult = (moveTo(map, guard, y, x - 1)) ;
				if (!moveresult)
					return (guard.spacesmoved);
				break;
		}
	}
	if (guard.loop) {
		return (-1);
	}
	else
		std::cout << "Error: reached end of map traversal without leaving map or finding loop. I don't know how this happened." << std::endl;
	return (guard.spacesmoved);
}

bool	isInHistory( const std::vector<t_pos> &history, const t_pos &search ) {
	//std::cout << "There are " << history.size() << " places to place the obstacle" << std::endl;
	int hist_size = history.size();
	for (int i = 0; i < hist_size; i++) {
		if (history[i] == search)
			return (1);
	}
	return (0);
}

bool	addObstacle( std::vector<std::string> &map , const std::vector<t_pos> &history) {
	static int y = 0;
	static int x = 0;

	map[y][x] = 'O';
	while  (map[y][x] && (map[y][x] != '.'))
		x++;
	if (isInHistory(history, {y,x})) {
		return (1);
	}
	while (!isInHistory(history, {y,x})) {
		if (x < map[y].size()) {
			x++;
		}
		else if (y < map.size()) {
			x = 0;
			y++;
		}
	}
	if (x >= map[y].size() && y >= map.size())
		return (0);
	return (1);
}

int	readfile( char *argv )
{
	std::vector<std::string> map;
	std::vector<t_pos>	history;
	t_guard	guard;
	int		result = 0;

	readMap(argv, map);

	initGuard(guard);
	setStart(map, guard);
	if (guard.dir >= 0)
		printGuard(guard);
	else {
		std::cout << "Error: couldn't find guard" << std::endl;
		return (0);
	}
	traverseMap(map, guard, history);
	while (addObstacle(map, history)) {	// adds obstacle to each square in the map
		if (traverseMap(map, guard, history) < 0)
			result++;
		printMap(map);
		//sleep(1);
		readMap(argv, map); // resets map to original state
		initGuard(guard);
		setStart(map, guard);
	}
	std::cout << "Found " << result << " spaces to put obstacle for infinite loop" << std::endl;
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
