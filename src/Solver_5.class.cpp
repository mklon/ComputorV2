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

void	Solver::complex( std::string lhs, std::string rhs ) {
	int 	i = 0, j;
	comp_n	num;

	num.a = 0;
	num.b = 0;
	while ( rhs[i] == ' ' && rhs[i] == '\t' ) i++;
	j = i++;
	while ( rhs[i] != 'i' && rhs[i] != '*' && i < rhs.size() ) i++;
	num.b = find_var( _help.word_split( rhs.substr( j, i - j )));

	if ( rhs[i] == '*' )
		while ( rhs[i] != 'i' ) i++;

	while ( rhs[i] != '-' && rhs[i] != '+' && i < rhs.size() ) i++;

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
