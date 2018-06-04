// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Computor.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/04 12:06:47 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/04 12:06:47 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Computor.class.hpp"

Computor::Computor() {}

Computor::Computor( const Computor &rhs ) {
	*this = rhs;
}

Computor	&Computor::operator=( const Computor &rhs ) {
	//!!!
	return ( *this );
}

void	Computor::parse_line() {
	std::istringstream	iss( _line.substr( 0, _line.find('=')) );
	std::string l;

	iss.str( _line.substr( _line.find('=') + 1 ));
}

void	Computor::run() {
	while ( std::getline( std::cin, _line ) ) {
		parse_line();
	}
}

Computor::~Computor() {}

// CompExp

Computor::CompExp::CompExp() {}


Computor::CompExp::CompExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Computor::CompExp::CompExp(CompExp const &rhs) {
	*this = rhs;
}

const char	*Computor::CompExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Computor::CompExp	&Computor::CompExp::operator=(CompExp const &rhs) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Computor::CompExp::~CompExp() throw() {}