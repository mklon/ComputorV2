// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_4.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/09 12:34:49 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/09 12:35:01 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"

std::string	Solver::mult_mat( std::string lhs, std::string rhs, char op ) {
	auto	ls = _mat->at( lhs );
	auto	rs = _mat->at( rhs );

	if ( ls[0].size() != rs.size() )
		throw ( SolvExp( "invalid size to multiply matrices" ));
	double 								res = 0;
	std::vector<double>					temp;
	std::vector<std::vector<double>>	mid;

	for ( int i = 0; i < ls.size(); i++ ) {
		for ( int j = 0; j < rs[0].size(); j++ ) {
			for ( int a = 0; a < rs.size(); a++ )
				res += ls[i][a] * rs[a][j];
			temp.push_back( res );
			res = 0;
		}
		mid.push_back( temp );
		temp.clear();
	}
	if ( _mat->find( "1_@" ) != _mat->end() )
		_mat->at( "1_@" ) = mid;
	else
		_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( "1_@", mid ));
	return ( "1_@" );

}

std::string	Solver::add_sub_mat( std::string lhs, std::string rhs, char op ) {
	auto	ls = _mat->at( lhs );
	auto	rs = _mat->at( rhs );

	if ( ls.size() != rs.size() || ls[0].size() != rs[0].size() ) {
		if ( op == '+' )
			throw ( SolvExp( "add two matrix with different size" ));
		else
			throw ( SolvExp( "subtract two matrix with different size" ));
	}
	std::vector<double>					temp;
	std::vector<std::vector<double>>	mid;

	for ( int i = 0; i < ls.size(); i++ ) {
		for ( int j = 0; j < ls[0].size(); j++ ) {
			if ( op == '+' )
				temp.push_back( ls[i][j] + rs[i][j] );
			else
				temp.push_back( ls[i][j] - rs[i][j] );
		}
		mid.push_back( temp );
		temp.clear();
	}
	if ( _mat->find( "1_@" ) != _mat->end() )
		_mat->at( "1_@" ) = mid;
	else
		_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( "1_@", mid ));
	return ( "1_@" );
}

std::string	Solver::mat_n_mat( std::string lhs, std::string rhs, char op ) {
	if ( op == '%' || op == '^') {
		std::string	res;
		res += "impossible to use \'";
		res += op;
		res += "\' to matrix";
		throw ( SolvExp( res ));
	}
	if ( op == '+' || op == '-' )
		return ( add_sub_mat( lhs, rhs, op ));
	else if ( op == '*' )
		return ( mult_mat( lhs, rhs, op ));
	else if ( op == '/' );
		;
}

std::string	Solver::matrix_op( std::string lhs, std::string rhs, char op ) {
	if ( _mat->find( lhs ) != _mat->end() &&
		 _mat->find( rhs ) != _mat->end() )
		return ( mat_n_mat( lhs, rhs, op ));
	if ( _var->find( lhs ) != _var->end() &&
		 _var->find( rhs ) != _var->end() )
		;//mat_n_var
	if ( _fun->find( lhs ) != _fun->end() &&
		 _fun->find( rhs ) != _fun->end() )
		;//mat_n_func
}

std::string	Solver::operation( std::string lhs, std::string rhs, char op ) {
	if ( _mat->find( lhs ) != _mat->end() ||
			_mat->find( rhs ) != _mat->end() )
		return ( matrix_op( lhs, rhs, op ));

	double	n1, n2;

	n1 = find_var( lhs );
	n2 = find_var( rhs );

	if ( op == '+' )
		n1 += n2;
	else if ( op == '-' )
		n1 -= n2;
	else if ( op == '*' )
		n1 *= n2;
	else if ( op == '/' ) {
		if ( n2 == 0 )
			throw ( SolvExp( "division by zero"));
		n1 /= n2;
	}
	else if ( op == '%' )
		n1 = fmod( n1, n2 );
	else
		n1 = pow( n1, n2 );
	return ( std::to_string( n1 ));
}
