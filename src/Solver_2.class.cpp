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
				throw ( SolvExp( "unknown variable: " + rhs ));
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
		throw ( SolvExp( "invalid matrix definition" ));
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
	while ( ++i < static_cast<int>( rhs.size() ))
		if ( rhs[i] != ' ' && rhs[i] != '\t' )
			throw ( SolvExp( "invalid matrix definition" ));

	if ( _mat->find( lhs ) != _mat->end() )
		_mat->at( lhs ) = res;
	else
		_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, res ));

	if( _fun->find( lhs ) != _fun->end() )
		_fun->erase( lhs );

	result( lhs, lhs );
}

void	Solver::question_mark( std::string lhs, std::string rhs ) {
	int 	i = 0;
	std::string			val, mark;
	std::istringstream	iss( rhs );

	while ( iss ) {
		if ( !i )
			iss >> val;
		else
			iss >> mark;
		if ( ++i > 3 )
			throw ( SolvExp( "impossible assignment" ));
	}
	if ( val == "?" && i == 2 ) {
		i = 0;
		mark = summary( lhs, i );
		if ( _mat->find( mark ) != _mat->end() )
			_help.display_mat( _mat->at( mark ));
		else
			std::cout << find_var( mark ) << endl;
		return;
	}
	else if ( mark == "?" && i == 3 ) {
		equation( lhs, val );
	}
}

void	Solver::oper_hand( std::string lhs, std::string rhs ) {
	if ( rhs.find( '?' ) != std::string::npos )
		question_mark( lhs, rhs );
	else
		functions( lhs, rhs );
}

void	Solver::equation( std::string lhs, std::string rhs ) {
	auto		i = lhs.find( '(' ), j = lhs.find_last_of( ')' );
	std::string	name, value;

	if ( i == std::string::npos || j == std::string::npos )
		throw ( SolvExp( "invalid function definition" ));
	name = _help.name( lhs.substr( 0, i++ ));
	value = _help.word_split( lhs.substr( i, j - i ));
	if ( _fun->find( name ) == _fun->end() )
		throw ( SolvExp( "unknown function: " + name ));
	auto	ls = _fun->at( name );
	if ( ls.name != value )
		throw ( SolvExp( "invalid function definition" ));
	if ( ls.value.find( '/' ) != std::string::npos || _help.replace_str( value , _fun->at( name ).value ))
		throw ( SolvExp( "invalid polynomial" ));
	std::string	eq = ls.value + " = " + rhs;
	std::string	line = "";

	for ( int i = 0; i < static_cast<int>( eq.size() ); i++ ) {
		if ( eq[i] == ' ' && eq[i + 1] != '+' && eq[i + 1] != '-' && eq[i + 1] != '*' && eq[i + 1] != '=' )
			continue;
		line += eq[i];
		if ( eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '=' ||
			eq[i + 1] == '+' || eq[i + 1] == '-' || eq[i + 1] == '*' || eq[i + 1] == '=')
			line += " ";
	}
	cout << line << endl;
	Equation	obj( line, value );
	obj.solve();
}

