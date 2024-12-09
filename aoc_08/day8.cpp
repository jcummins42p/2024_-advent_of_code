/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/09 03:54:41 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

typedef std::array<int, 2> t_pos;

std::ostream &operator<<( std::ostream &os, const t_pos &pos) {
	os << "{" << pos[0] << ", " << pos[1] << "} ";
	return (os);
}

class Map;

class Network
{
	public:
		Network( const char &name, Map &map ) : _name(name), _n_antenna(0), map(map) {};
		~Network( void ) {};

		void			addAntenna( const int &y, const int &x );
		static bool 	knownNetwork( const char &name );
		char		 	getName( void ) const ;
		bool 			addAnode( t_pos input ) ;
		void			addAnodes( void );
		int	getNumAntenna( void ) const ;
	private:
		char				_name;
		std::vector<t_pos>	antenna_pos;
		std::vector<t_pos>	anode_pos;
		int					_n_antenna;

		Map &map;
} ;

class Map
{
	public:
		Map( const char *filename );
		~Map( void ) {};

		void print( void ) const;
		void printAnodes( void ) ;
		int getHeight( void ) const { return _height; };
		int getWidth( void ) const { return _width; };
		int getAnodeCount( void ) const { return n_anodes; };

		void	addAnode( t_pos input);

		Network &findNetwork( const char &identifier );
		bool	findAnodePos( const t_pos &search );
		void	addNetwork( const int &y, const int &x, const char &identifier );
		void	addNetworks( void );
		void	populateAnodes( void );
	private:
		std::vector<std::string> _map;
		int	_height;
		int	_width;

		std::vector<Network> 	networks;
		std::vector<t_pos>		anode_pos;
		int			n_networks;
		int			n_anodes;
} ;

Map::Map( const char *filename ) : n_networks(0), n_anodes(0) {
	std::ifstream	ifs;
	std::string		line;

	ifs.open (filename, std::fstream::in);
	if (!ifs.is_open()) {
		std::cout << "invalid file : " << filename << std::endl;
		exit (1);
	}
	while (std::getline(ifs, line)) {
		_width = line.size();
		_map.push_back(line);
	}
	_height = _map.size();
}

void Map::printAnodes( void )  {
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			if (_map[y][x] == '.' && findAnodePos({y,x}))
					std::cout << '#';
			else
				std::cout << _map[y][x];
		}
		std::cout << std::endl;
	}
}

void Map::print( void ) const {
	for (int i = 0; i < _height; i++)
		std::cout << _map[i] << std::endl;
	std::cout << "Map dimensions: y=" << _height << ", x=" << _width << std::endl;
}

char	Network::getName( void ) const {return _name;}

Network &Map::findNetwork( const char &identifier ) {
	for (int i = 0; i < n_networks; i++) {
		if (identifier == networks[i].getName())
			return (networks[i]);
	}
	throw std::runtime_error("Network not found ");
}

bool	Map::findAnodePos( const t_pos &search ) {
	for (int i = 0; i < n_anodes; i++) {
		if (anode_pos[i] == search)
			return (true);
	}
	return (false);
}

void Network::addAntenna( const int &y, const int &x ) {
	t_pos newAntenna = {y, x};
	antenna_pos.push_back(newAntenna);
	_n_antenna++;
}

int Network::getNumAntenna( void ) const { return (_n_antenna); }

void Map::addNetwork(const int &y, const int &x, const char &identifier) {
	std::cout << "Looking for network " << identifier << ": ";
	try {
		findNetwork( identifier ).addAntenna( y , x );
		std::cout << "Found network " << identifier << std::endl;
	}
	catch ( const std::exception &e ) {
		std::cout << e.what() << " creating new network " << identifier << std::endl;
		Network network( identifier, *this );
		network.addAntenna( y, x );
		networks.push_back(network);
		n_networks++;
	}
}

void Map::addNetworks( void ) {
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			if (_map[y][x] != '.')
			   addNetwork(y, x, _map[y][x]);
		}
	}
}

void	Map::addAnode( t_pos input ) {
	anode_pos.push_back(input);
	std::cout << "Success" << std::endl;
	n_anodes++;
}

bool Network::addAnode( t_pos input ) {
	std::cout << "\t\tAdding anode at " << input;
	if (input[0] < 0 || input[0] >= map.getWidth() || input[1] < 0 || input[1] >= map.getWidth()) {
		std::cout << "Anode beyond map boundary" << std::endl;
		return (0);
	}
	else if (map.findAnodePos( input )) {
		std::cout << "Anode already exists" << std::endl;
	} else {
		anode_pos.push_back(input);
		map.addAnode( input );
	}
	return (1);
}

void Network::addAnodes( void ) {
	t_pos tmp = {0, 0};
	int	dx = 0;
	int dy = 0;

	std::cout << "Adding anodes for antenna type " << _name << ": " << std::endl;
	for (int j = 0; j < getNumAntenna(); j++ ) {
		std::cout << "\tLocation " << j << " at " << antenna_pos[j] << std::endl;
		for (int k = 0; k < getNumAntenna(); k++ ) {
			if (&antenna_pos[j] == &antenna_pos[k])
				std::cout << "\t(Same antenna: cannot create anode)" << std::endl;
			else {
				if (_n_antenna > 1) {
					tmp = {antenna_pos[j][0], antenna_pos[j][1]};
					addAnode(tmp);
				}
				std::cout << "\tCalculating anode between " << antenna_pos[j] << " and " << antenna_pos[k] << std::endl;
				dy = antenna_pos[j][0] - antenna_pos[k][0];
				dx = antenna_pos[j][1] - antenna_pos[k][1];
				tmp = {antenna_pos[j][0] + dy, antenna_pos[j][1] + dx};
				int i = 2;
				while (addAnode(tmp)) {
					tmp = {antenna_pos[j][0] + (dy * i), antenna_pos[j][1] + (dx * i)};
					i++;
				}
				i = 2;
				tmp = {antenna_pos[k][0] - dy, antenna_pos[k][1] - dx};
				while (addAnode(tmp)) {
					tmp = {antenna_pos[k][0] - (dy * i), antenna_pos[k][1] - (dx * i)};
					i++;
				}
				std::cout << "Found " << map.getAnodeCount() << " anodes" << std::endl;
			}
		}
	}
}

void Map::populateAnodes( void ) {	// loop through antennae in network
	for (int i = 0; i < n_networks; i++) { // loop through networks
		networks[i].addAnodes();
	}
}

void	readfile( char *argv )
{
	Map	map( argv );
	map.print();
	map.addNetworks();
	map.populateAnodes();
	map.printAnodes();
	std::cout << "Found " << map.getAnodeCount() << " anodes" << std::endl;
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
