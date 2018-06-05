// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 12:06:50 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/05 12:06:51 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Helper.class.hpp"

Helper::Helper() {}

Helper::Helper( const Helper &rhs ) {
	*this = rhs;
}

Helper	&Helper::operator=( const Helper &rhs ) {
	//!!!
	return ( *this );
}

double	Helper::brackets( std::string rhs, int &i ) {
	double	n;
	int		j, temp= 0;

	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	j = i;
	if ( rhs[i] == '(' ) {
		i++;
		n = summary( rhs, i );
		if ( rhs[i] == ')' )
			i++;
		return ( n );
	}
	while ( isdigit( rhs[j + temp]) || rhs[j + temp] == '.' ) temp++;
	i += temp;
	return ( std::stod( rhs.substr( i - temp, i )));
}

double	Helper::factor( std::string rhs, int &i ) {
	int 	place;
	double	n1, n2;

	n1 = brackets( rhs, i );
	while ( i < rhs.size() ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '*' && rhs[i] != '/' && rhs[i] != '%' )
			return ( n1 );
		i++;
		n2 = brackets( rhs, i );
		if ( rhs[place] == '*')
			n1 *= n2;
		else if ( rhs[place] == '/' )
			n1 /= n2;
		else
			n1 = fmod( n1, n2 );
	}
	return ( n1 );
}

double	Helper::summary( std::string rhs, int &i ) {
	int 	place;
	double	n1,n2;

	n1 = factor( rhs, i);
	while ( i < rhs.size() ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '+' && rhs[i] != '-' )
			return ( n1 );
		i++;
		n2 = factor( rhs, i );
		if ( rhs[place] == '+')
			n1 += n2;
		else
			n1 -= n2;
	}
	return ( n1 );
}

bool	Helper::cont_opr( std::string rhs ) {
	// + - * / %
	if ( rhs.find( '+' ) != std::string::npos ||
			rhs.find( '-' ) != std::string::npos ||
			rhs.find( '+' ) != std::string::npos ||
			rhs.find( '/' ) != std::string::npos ||
			rhs.find( '%' ) != std::string::npos )
		return ( true );
	return ( false );
}

Helper::~Helper() {}


/*
	nbr = parse_factors(expr);
	while (**expr)
	{
		while (**expr == ' ')
			(*expr)++;
		op = **expr;
		if (op != '+' && op != '-')
			return (nbr);
		(*expr)++;
		nbr2 = parse_factors(expr);
		if (op == '+')
			nbr += nbr2;
		else
			nbr -= nbr2;
	}
	return (nbr);
 */