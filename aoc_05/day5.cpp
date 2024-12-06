/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day5.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:54:17 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/05 13:46:48 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <sstream>

void	readUpdates(char *filename, std::vector<std::vector<int>> &updates)
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
		if (i >= updates.size()) {
			updates.push_back(std::vector<int>());
		}
		std::istringstream 	iss( line );
		std::string			numberStr;

		int j = 0;
		while (std::getline(iss, numberStr, ',')) {
			if (j != 0)
				std::cout << ",";
			try {updates[i].push_back(std::stoi(numberStr)); }
			catch ( const std::exception & ) {
				std::cout << "Error processing " << filename << " on line " << i << std::endl;
			}
			std::cout << updates[i][j++];
		}
		std::cout << std::endl;
		i++;
	}
}

void	readRules(char *filename, std::vector<std::vector<int>> &rules)
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
		if (i >= rules.size()) {
			rules.push_back(std::vector<int>());
		}
		std::istringstream	iss( line );
		std::string			numberStr;
		int	j = 0;

		while (std::getline(iss, numberStr, '|')) {
			if (j != 0)
			   std::cout << "|";
			try { rules[i].push_back(std::stoi(numberStr)); }
			catch ( const std::exception & ) {
				std::cout << "Error processing " << filename << " on line " << i << std::endl;
			}
			std::cout << rules[i][j++];
		}
		std::cout << std::endl;
		i++;
	}
}

int	checkCorrectPositions(std::vector<int> &update, int j, std::vector<std::vector<int>> &rules)
{
	//	checking updates at position j, need the whole vector updats and set of vectors rules to check against
	int corrected = 0;

	for (int i = 0; i < rules.size(); i++) {
		if (update[j] == rules[i][0]) // check that the current rule applies to this number
		{	// check that other numbers in the update follow the rule
			for (int k = 0; k < update.size(); k++)
			{
				if (k < j && update[k] == rules[i][1] )
				{
					corrected = 1;
					int tmp = update[j];
					update[j] = update[k];
					update[k] = tmp;
				}
			}
		}
	}
	return (corrected);
}

int	checkUpdate(std::vector<int> &update, std::vector<std::vector<int>> &rules)
{
	for ( int j = 0; j < update.size(); j++)	// for each number in record
	{
		if (checkCorrectPositions(update, j, rules)) {
			std::cout << "Corrected error in pageno index " << j << std::endl;
			return (1);
		}
	}
	return (0);
}

int	processData( std::vector<std::vector<int>> &rules, std::vector<std::vector<int>> &updates )
{
	int size = updates.size();
	int	total = 0;

	for ( int i = 0; i < size; i++ )	// for each update record
	{
		std::cout << "Checking Update #" << i << ": ";
		if (checkUpdate(updates[i], rules)) {
			while (checkUpdate(updates[i], rules))
					std::cout << "\tupdate " << i << " re-ordering..." << std::endl;
			std::cout << "OK: Adding middle number " << updates[i][updates[i].size() / 2]
					<< std::endl;
			total += updates[i][updates[i].size() / 2];
		}
	}
	std::cout << "Total: " << total << std::endl;
	return (0);
}

int	readfiles( char *argv[] )
{
	std::vector<std::vector<int>>	rules;
	std::vector<std::vector<int>>	updates;
	int					total = 0;

	readRules(argv[1], rules);
	readUpdates(argv[2], updates);
	processData( rules, updates );
	return (total);
}

int	main( int argc, char *argv[] )
{
	int total = 0;
	if (argc != 3) {
		std::cout << "Supply two files only" << std::endl;
		return (1);
	}
	total = readfiles(argv);

	return (1);
}
