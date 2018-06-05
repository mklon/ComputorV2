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

Computor::Computor() {
	_help._var = &_var;
}

Computor::Computor( const Computor &rhs ) {
	*this = rhs;
}

Computor	&Computor::operator=( const Computor &rhs ) {
	//!!!
	return ( *this );
}

void	Computor::var_handle( std::string lhs, std::string rhs ) {
	int		i = 0;
	_var.insert( std::pair<std::string, double>(lhs, _help.summary(rhs, i)));
	cout << _var.at(lhs) << endl;
}

void	Computor::lhs_handle( std::string lhs, std::string rhs ) {
	int 				i = 0;
	std::istringstream	iss( lhs );

	if ( _help.cont_opr( lhs ) ) {
		cout << "oper_handle" << endl;
		return;
	}

	while ( iss ) {
		iss >> lhs;
		i++;
		if ( i > 2 )
			throw ( CompExp( "invalid lhs" ));
	}
	if ( lhs[lhs.size() - 1] == ')' )
		cout << "func_handle" << endl;
	else
		var_handle( lhs, rhs );
}

void	Computor::parse_line() {
	unsigned long int	i;
	std::string			part;

	if (( i = _line.find( '=' )) == std::string::npos )
		throw ( CompExp( "error" ) );
	lhs_handle( _line.substr( 0, i ), _line.substr( i + 1 ));

}

void	Computor::run() {
	while ( std::getline( std::cin, _line ) ) {
		try {
			parse_line();
		}
		catch ( std::exception &e ) {
			cout << e.what() << endl;
		}
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