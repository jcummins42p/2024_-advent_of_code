/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mullitover.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:43:14 by jcummins          #+#    #+#             */
/*   Updated: 2024/12/03 10:48:07 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

typedef struct s_mulpair {
	int		index;
	int		end;
	char 	a;
	char 	b;
} mulpair ;

int	handle_line(std::string line, std::vector<mulpair> answers)
{
	std::string	needle ("mul(");
	mulpair		solution;

	solution.index = line.find(needle);
	solution.end = line.find(needle, solution.index);
	std::cout << std::string(&line[solution.index], &line[solution.end]);
	return (0);
}

int handle_file(char const *argv1)
{
	std::ifstream 			infile;
	std::string 			line;
	std::vector<mulpair>	answers;

	infile.open (argv1, std::fstream::in);
	if (!infile.is_open()) {
		std::cout << "invalid file\n";
		return (1);
	}
	while (getline(infile, line)) {
		handle_line(line, answers);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "one file argument only\n";
		return (1);
	}
	handle_file(argv[1]);
	return (0);
}
