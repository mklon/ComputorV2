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
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] == '+' || rhs[i] == '*' ||
				 rhs[i] == '/' || rhs[i] == '-' || rhs[i] == '^' )
				throw ( SolvExp( "invalid function definition" ));
		}
		if (( isdigit( rhs[i] ) && ( rhs[i + 1] == ' ' ||
				rhs[i + 1] == '\t')) || rhs[i] == '@') {
			i++;
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] != '+' && rhs[i] != '*' && rhs[i] != '/'
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
	auto	i = lhs.find( '(' );
	func	res;
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
