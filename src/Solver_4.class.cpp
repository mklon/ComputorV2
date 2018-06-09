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

std::string	Solver::add_mat( std::string lhs, std::string rhs, char op ) {
	auto	ls = _mat->at( lhs );
	auto	rs = _mat->at( rhs );

	if ( ls.size() != rs.size() || ls[0].size() != rs[0].size() )
		if ( op == '+' )
			throw ( SolvExp( "add two matrix with different size" ));
		else
			throw ( SolvExp( "subtract two matrix with different size" ));
}

std::string	Solver::mat_n_mat( std::string lhs, std::string rhs, char op ) {
	if ( op == '%' || op == '^') {
		std::string	res;
		res += "impossible to use \'";
		res += op;
		res += "\' to matrix";
		throw ( SolvExp( res ));
	}
	if ( op == '+' || op == '-' ) {
		add_mat( lhs, rhs, op );
	}
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