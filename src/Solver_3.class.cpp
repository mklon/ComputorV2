// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_3.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/08 11:52:47 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/08 11:52:47 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"



void	Solver::func_info( std::string lhs, std::string value, std::string rhs ) {
	int		i = 0;

	if ( _fun->find( lhs ) == _fun->end() )
		throw ( SolvExp( "unknown function" ));

	cout << std::stod( func_sum( lhs, value )) << endl;
}

void	Solver::functions( std::string lhs, std::string rhs ) {
	auto		i = lhs.find( '(' );
	func		res;
	std::string	name, value;

	if ( i == std::string::npos )
		throw ( SolvExp( "invalid lhs F" ));
	name = lhs.substr( 0, i );
	value = lhs.substr( i + 1, lhs.size() - i - 2 );
	if ( value == "" )
		throw ( SolvExp( "invalid function value" ));
	if ( rhs.find('?') != std::string::npos ) {
		func_info( name, value, rhs );
		return;
	}
	if ( _var->find( name ) != _var->end() ||
		_mat->find( name) != _mat->end() )
		throw ( SolvExp( "reassigned variable with function" ));
	res.name = value;
	res.value = rhs;

	get_help().replcae_str( value, rhs );
	if ( _fun->find( name ) != _fun->end() )
		_fun->at( name ) = res;
	else
		_fun->insert( std::pair<std::string, func>( name, res ));
	get_help().display_fun( rhs );
}

std::string	Solver::func_sum( std::string lhs, std::string rhs ) {
	int 		j = 0;
	std::string	polynomial = _fun->at( lhs ).value;

	if ( rhs == "" )
		throw ( SolvExp( "invalid function value" ));
	get_help().replcae_str( lhs, rhs );
	for ( auto i = polynomial.find( _fun->at( lhs ).name );
		  i != std::string::npos; i = polynomial.find( _fun->at( lhs ).name, i + 1 ))
		polynomial.replace( i, _fun->at( lhs ).name.size(), "(" + rhs + ")" );
	return ( summary( polynomial, j ));
}

std::string	Solver::solve_func( std::string lhs, std::string rhs, int &i ) {
	int		pos = 0, buf = 0;

	if ( rhs.find( ')' ) == std::string::npos )
		throw ( SolvExp( "invalid rhs" ));
	for ( auto j = i + 1; j < rhs.size(); j++ ) {
		if ( rhs[j] == '(' )
			buf++;
		else if ( rhs[j] == ')' && buf )
			buf--;
		else if ( j + 1 == rhs.size() && buf )
			throw ( SolvExp( "invalid rhs" ));
		else if ( rhs[j] == ')' && !buf ) {
			pos = j;
			break;
		}
	}
	std::string	value = rhs.substr( i + 1, pos - i - 1 );
	i = pos + 1;
	if ( _fun->find( lhs ) == _fun->end() )
		throw ( SolvExp( "unknown function" ));
	return ( func_sum( lhs, value ));
}

std::string	Solver::word_split( std::string rhs ) {
	int 				i = 0;
	std::istringstream	iss( rhs );

	while ( iss ) {
		iss >> rhs;
		if ( ++i > 2 )
			throw ( SolvExp( "invalid variable name" ));
	}
	if ( rhs == "" )
		throw ( SolvExp( "invalid function value" ));
	return ( rhs );
}
