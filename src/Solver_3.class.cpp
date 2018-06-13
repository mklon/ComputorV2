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

void	Solver::func_check( std::string rhs ) {
	int		i = -1;

	while ( ++i < rhs.size() ) {
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' || rhs[i] == '^' ) {
			i++;
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] == '+' || rhs[i] == '*' ||
				 rhs[i] == '/' || rhs[i] == '-' || rhs[i] == '^' )
				throw ( SolvExp( "invalid function definition" ));
		}
		if (( isdigit( rhs[i] ) && ( rhs[i + 1] == ' ' ||
				rhs[i + 1] == '\t')) || rhs[i] == '@') {
			i++;
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] != '+' && rhs[i] != '*' && rhs[i] != '/' && rhs[i] != ')'
				 && rhs[i] != '-' && rhs[i] != '^' && i < rhs.size() )
				throw ( SolvExp( "invalid function definition" ));
		}
	}
}

void	Solver::display_fun( std::string rhs ) {
	int 	i = -1;

	while ( ++i < rhs.size() ) {
		if ( rhs[i] == ' ' || rhs[i] =='\t')
			continue;
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' )
			cout << " ";
		cout << rhs[i];
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' )
			cout << " ";
	}
	cout << endl;
}

void	Solver::replcae_str( std::string lhs, std::string rhs ) {
	for ( auto i = 0; i < lhs.size(); i++ ) {
		if ( !isalpha( lhs[i] ))
			throw ( SolvExp( "invalid function value" ));
	}
	for ( auto i = rhs.find( lhs ); i != std::string::npos; i = rhs.find( lhs, i + 1 ))
		rhs.replace( i, lhs.size(), "@" );
	for ( auto i = 0; i < rhs.size(); i++ ) {
		if ( !isdigit( rhs[i] ) && rhs[i] != ' '
			 && rhs[i] != '\t' && rhs[i] != '+'
			 && rhs[i] != '-' && rhs[i] != '/'
			 && rhs[i] != '*' && rhs[i] != '%'
			 && rhs[i] != '^' && rhs[i] != '@'
			 && rhs[i] != '(' && rhs[i] != ')'
				&& rhs[i] != '.')
			throw ( SolvExp( "invalid function" ));
	}
	func_check( rhs );
}

void	Solver::functions( std::string lhs, std::string rhs ) {
	auto		i = lhs.find( '(' );
	func		res;
	std::string	name, value;

	if ( i == std::string::npos )
		throw ( SolvExp( "invalid lhs F" ));
	name = lhs.substr( 0, i );
	value = lhs.substr( i + 1, lhs.size() - i - 2 );
	if ( _var->find( name ) != _var->end() ||
		_mat->find( name) != _mat->end() )
		throw ( SolvExp( "reassigned variable with function" ));
	res.name = value;
	res.value = rhs;

	replcae_str( value, rhs );
	if ( _fun->find( name ) != _fun->end() )
		_fun->at( name ) = res;
	else
		_fun->insert( std::pair<std::string, func>( name, res ));
	display_fun( rhs );
}

std::string	Solver::func_sum( std::string lhs, std::string rhs ) {
	int 		j = 0;
	std::string	polynomial = _fun->at( lhs ).value;

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
	if ( _mat->find( value ) != _mat->end() )
		throw ( SolvExp( "matrix as function argument" ));
	return ( func_sum( lhs, value ));
}
