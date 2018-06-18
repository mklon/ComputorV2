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

void	Solver::func_info( std::string lhs, std::string value ) {
	if ( _fun->find( lhs ) == _fun->end() )
		throw ( SolvExp( "unknown function" ));

	cout << std::stod( func_sum( lhs, value )) << endl;
}

void	Solver::functions( std::string lhs, std::string rhs ) {
	auto		i = lhs.find( '(' ), j = lhs.find_last_of( ')' );
	func		res;
	std::string	name, value;

	if ( i == std::string::npos || j == std::string::npos )
		throw ( SolvExp( "invalid function definition" ));
	name = _help.name( lhs.substr( 0, i++ ));
	value = _help.word_split( lhs.substr( i, j - i ));

	rhs = _help.mult_sign( value, rhs );

	for ( size_t k = 0; k < name.size(); k++ ) {
		if ( !isalpha( name[k] ) || lhs == "i" )
			throw ( SolvExp( "invalid function name" ));
	}

	if ( value == "" )
		throw ( SolvExp( "invalid function definition" ));
	if ( rhs.find('?') != std::string::npos ) {
		func_info( name, value );
		return;
	}
	res.name = value;
	res.value = rhs;

	get_help().str_check( value, rhs );
	if ( _fun->find( name ) != _fun->end() )
		_fun->at( name ) = res;
	else
		_fun->insert( std::pair<std::string, func>( name, res ));
	if ( _var->find( name ) != _var->end() )
			_var->erase( name );
	if ( _mat->find( name ) != _mat->end() )
		_mat->erase( name );
	if ( _com->find( name ) != _com->end() )
		_com->erase( name );
	get_help().display_fun( rhs );
}

std::string	Solver::func_sum( std::string lhs, std::string rhs ) {
	int 		j = 0;
	std::string	polynomial = _fun->at( lhs ).value;

	if ( rhs == "" )
		throw ( SolvExp( "invalid function definition" ));
	if ( _rec == "" )
		_rec = lhs;
	else if ( _help.recursion_check( _rec, polynomial ) )
		throw ( SolvExp( "recursion without exit condition" ));

	get_help().str_check( lhs, rhs );
	for ( auto i = polynomial.find( _fun->at( lhs ).name );
		  i != std::string::npos; i = polynomial.find( _fun->at( lhs ).name, i + 1 )) {
		int		j = i + _fun->at( lhs ).name.size();
		if ( polynomial[j] != '(' && !isalpha( polynomial[j] ) && !isalpha( polynomial[i - 1] )) {
			polynomial.replace( i, _fun->at( lhs ).name.size(), "(" + rhs + ")" );
			i += rhs.size() + 2;
		}
	}
	std::string	hold = summary( polynomial, j );
	if ( _rec == lhs )
		_rec = "";
	return ( hold );
}

std::string	Solver::solve_func( std::string lhs, std::string rhs, int &i ) {
	int		pos = 0, buf = 0;

	if ( rhs.find( ')' ) == std::string::npos )
		throw ( SolvExp( "invalid function definition" ));
	for ( auto j = i + 1; j < static_cast<int>( rhs.size() ); j++ ) {
		if ( rhs[j] == '(' )
			buf++;
		else if ( rhs[j] == ')' && buf )
			buf--;
		else if ( j + 1 == static_cast<int>( rhs.size() ) && buf )
			throw ( SolvExp( "invalid function definition" ));
		else if ( rhs[j] == ')' && !buf ) {
			pos = j;
			break;
		}
	}
	std::string	value = rhs.substr( i + 1, pos - i - 1 );
	i = pos + 1;
	if ( _fun->find( lhs ) == _fun->end() )
		throw ( SolvExp( "unknown function: " + lhs ));
	return ( func_sum( lhs, value ));
}
