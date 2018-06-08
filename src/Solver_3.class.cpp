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

comp_n	Solver::read_cm( std::string rhs ) {
	int 	i = 0, j;
	comp_n	num;

	while ( rhs[i] == ' ' || rhs[i] == '\t' ) i++;
	j = i;
	while ( isalpha( rhs[j] ) ||
			isdigit( rhs[j] ) ||
			rhs[j] == '.' ) j++;

	std::string	temp = rhs.substr( i, j - i );
	while ( rhs[i] == ' ' || rhs[i] == '\t' ) i++;
	if ( rhs[i] != '+' && rhs[i] != '-' && rhs[i] != '*' )
		throw ( SolvExp( "invalid complex number definition" ));
	if ( rhs[i] == '*' ) {
		i++;

	}

	return ( num );
}

void	Solver::complex( std::string lhs, std::string rhs ) {
	comp_n	res;

	res = read_cm( rhs );
}
