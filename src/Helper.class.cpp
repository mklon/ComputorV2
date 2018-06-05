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

double	Helper::find_var( std::string rhs ) {

	if ( _var->find( rhs ) == _var->end() ) {
		for ( int i = 0; i < rhs.size(); i++ )
			if ( !isdigit( rhs[i] ) && rhs[i] != '.' && rhs[i] != '^' )
				throw ( HelpExp( "invalid rhs" ));
		return ( std::stod( rhs ));
	}
	else {
		return ( _var->at(rhs) );
	}
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
	while ( isdigit( rhs[j + temp] ) ||
			isalpha( rhs[j + temp] ) ||
			rhs[j + temp] == '.' ) temp++;
	i += temp;
	std::string	temp1 = rhs.substr( i - temp, i - j );
	return ( find_var( temp1 ));
}

double	Helper::factor( std::string rhs, int &i ) {
	int 	place;
	double	n1, n2;

	n1 = brackets( rhs, i );
	while ( i < rhs.size() ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '*' && rhs[i] != '/' && rhs[i] != '%' && rhs[i] !='^' )
			return ( n1 );
		i++;
		n2 = brackets( rhs, i );
		if ( rhs[place] == '*')
			n1 *= n2;
		else if ( rhs[place] == '/' )
			n1 /= n2;
		else if ( rhs[place] == '%')
			n1 = fmod( n1, n2 );
		else
			n1 = pow( n1, n2 );
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

double	Helper::solve_line( std::string lhs, std::string rhs ) {
	int					i = 0;
	double				res;
	std::string			temp;
	std::istringstream	iss( rhs );

	iss >> temp;
	if ( temp == "?" ) {
		return ( _var->at( lhs ) );
	}
	res = summary( rhs, i );
	while ( i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i++] != '\t' )
			throw ( HelpExp( "invalid rhs" ));
	return ( res );
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


// CompExp

Helper::HelpExp::HelpExp() {}


Helper::HelpExp::HelpExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Helper::HelpExp::HelpExp(HelpExp const &rhs) {
	*this = rhs;
}

const char	*Helper::HelpExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Helper::HelpExp	&Helper::HelpExp::operator=(HelpExp const &rhs) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Helper::HelpExp::~HelpExp() throw() {}
