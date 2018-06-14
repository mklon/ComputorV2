// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_2.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/08 11:53:16 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/08 11:53:17 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"

std::vector<double>	Solver::rows( std::string rhs, int &i ) {
 	int		j;
	std::vector<double>	row;

	i++;
	while ( true ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		j = i;

		while ( rhs[j] != ',' && rhs[j] != ']' && rhs[j] != ' ' ) {
			if ( !isdigit( rhs[i] ) && rhs[i] != '-' && rhs[i] != '.' && !isalpha( rhs[i] ))
				throw ( SolvExp( "unknown variable" ));
			j++;
		}
		row.push_back( find_var( rhs.substr( i, j - i )));
		i = j;
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		if ( rhs[i] != ',' && rhs[i] != ']' )
			throw ( SolvExp( "invalid matrix definition" ));
		if (rhs[i++] == ']')
			break;
	}
	return ( row );
}

std::vector<std::vector<double>>	Solver::lines( std::string rhs, int &i ) {
	std::vector<std::vector<double>>	line;
	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	if ( rhs[i++] != '[' )
		throw ( SolvExp( "[" ));
	while ( true ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

		if ( rhs[i] == '[' )
			line.push_back( rows( rhs, i ));

		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

		if ( rhs[i] != ';' && rhs[i] != ']' )
			throw ( SolvExp( "invalid matrix definition" ));
		if ( rhs[i] == ']')
			break;
		i++;
	}
	get_help().size_check( line );
	return ( line );
}

void	Solver::read_matrix( std::string lhs, std::string rhs ) {
	int 	i = 0;
	std::vector<std::vector<double>>	res;

	res = lines( rhs, i );
	while ( ++i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i] != '\t' )
			throw ( SolvExp( "invalid matrix definition" ));

	if ( _mat->find( lhs ) != _mat->end() )
		_mat->at( lhs ) = res;
	else
		_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, res ));
	result( lhs, lhs );
}

void	Solver::oper_hand( std::string lhs, std::string rhs ) {
	int 	i = 0;
	rhs = get_help().word_split( rhs );
	if ( rhs != "?" )
		throw ( SolvExp( "impossible assignment" ));
	std::cout << std::stod( summary( lhs, i ) ) << endl;
}
