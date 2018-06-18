// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_5.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/16 12:07:23 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/16 12:07:24 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"

std::string	Solver::comp_op( std::string lhs, std::string rhs, char op ) {
	if ( op == '^' || op == '%' ) {
		std::string	res;
		res += "impossible to use \'";
		res += op;
		res += "\' to complex number";
		throw ( SolvExp( res ));
	}
	comp_n	mid;
	auto	ls = _com->at( lhs ), rs = _com->at( rhs );
	if ( op == '+' ) {
		mid.a = ls.a + rs.a;
		mid.b = ls.b + rs.b;
	}
	else if ( op == '-' ) {
		mid.a = ls.a - rs.a;
		mid.b = ls.b - rs.b;
	}
	else if ( op == '*' ) {
		mid.a = ls.a * rs.a - ls.b * rs.b;
		mid.b = ls.a * rs.b + rs.a * ls.b;
	}
	else if ( op == '/' ) {
		mid.a = ( ls.a * rs.a - ls.b * rs.b ) / ( rs.a * rs.a + rs.b * rs.b );
		mid.b = ( rs.a * ls.b - ls.a * rs.b ) / ( rs.a * rs.a + rs.b * rs.b );
	} else
		throw ( SolvExp( "invalid operation with complex number" ));
	std::string	name = "#" + std::to_string( _count_c++ );
	if ( _com->find( name ) != _com->end() )
		_com->at( name ) = mid;
	else
		_com->insert( std::pair<std::string, comp_n>( name, mid ));
	return ( name );

}

void	Solver::complex( std::string lhs, std::string rhs ) {
	int 	i = 0, j;
	comp_n	num;

	num.a = 0;
	num.b = 0;
	while ( rhs[i] == ' ' && rhs[i] == '\t' ) i++;
	j = i++;
	while ( rhs[i] != 'i' && rhs[i] != '*' && i < static_cast<int>( rhs.size() )) i++;
	std::stringstream	iss( _help.word_split( rhs.substr( j, i - j )));
	std::string			temp;
	iss >> temp;

	if ( temp != "" )
		num.b = find_var( temp );

	if ( rhs[i] == '*' )
		while ( rhs[i] != 'i' ) i++;

	i++;
	while ( rhs[i] != '-' && rhs[i] != '+' && i < static_cast<int>( rhs.size() )) {
		if ( rhs[i] != ' ' && rhs[i] != '\t' ) {
			throw ( SolvExp( "invalid complex number definition" ));
		}
		i++;
	}

	i++;
	if ( rhs[i -1] == '-' )
		num.a = -1 * find_var( _help.word_split( rhs.substr( i )));
	else if ( rhs[i - 1] == '+' )
		num.a = find_var( _help.word_split( rhs.substr( i )));

	if ( _com->find( lhs ) != _com->end() )
		_com->at( lhs ) = num;
	else
		_com->insert( std::pair<std::string, comp_n>( lhs, num ));

	if ( _var->find( lhs ) != _var->end() )
		_var->erase( lhs );
	if ( _mat->find( lhs ) != _mat->end() )
		_mat->erase( lhs );
	if ( _fun->find( lhs ) != _fun->end() )
		_fun->erase( lhs );

	_help.display_comp( num );
}
